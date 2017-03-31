/* RadioFunctions.h
  A handful of sending and receiving functions for the 
  ATmega128RFA1.
  by: Jim Lindblom
      SparkFun Electronics
  date: July 8, 2013
  license: Beerware. Use, distribut, and modify this code freely
  however you please. If you find it useful, you can buy me a beer
  some day.
  
  Functions in here:
    rfBegin(uint8_t channel) - Initializes the radio on a channel
                                between 11 and 26.
    rfWrite(uint8_t b) - Sends a byte over the radio.
    rfPrint(String toPrint) - Sends a string over the radio.
    int rfAvailable() - Returns number of characters currently
                        in receive buffer, ready to be read.
    char rfRead() - Reads a character out of the buffer.
    
  Interrupt Sub-Routines (ISRs) in here:
    TRX24_TX_END_vect - End of radio transfer.
    TRX24_RX_START_vect - Beginning of radio receive.
    TRX24_RX_END_vect - End of radio receive. Characters are 
                        collected into a buffer here.
*/
  
#include <Arduino.h> // Required for digitalWrites, etc.

// Board pin definitions.
const int RX_LED = 34;  // B6 - RF RX LED
const int TX_LED = 35;  // B7 - RF TX LED
uint8_t rssiRaw; // Global variable shared between RX ISRs

// A buffer to maintain data being received by radio.
const int RF_BUFFER_SIZE = 127;
struct ringBuffer
{
  unsigned char buffer[RF_BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
} radioRXBuffer;


// Initialize the RFA1's low-power 2.4GHz transciever.
// Sets up the state machine, and gets the radio into
// the RX_ON state. Interrupts are enabled for RX
// begin and end, as well as TX end.
uint8_t rfBegin(uint8_t channel)
{
  for (int i=0; i<128; i++)
  {
    radioRXBuffer.buffer[i] = 0;
  }
  radioRXBuffer.tail = 0;
  radioRXBuffer.head = 0;

  // Setup RX/TX LEDs: These are pins B6/34 (RX) and B7/35 (TX).
  pinMode(RX_LED, OUTPUT);
  digitalWrite(RX_LED, LOW);
  pinMode(TX_LED, OUTPUT);
  digitalWrite(TX_LED, LOW);

  // Transceiver Pin Register -- TRXPR.
  // This register can be used to reset the transceiver, without
  // resetting the MCU.
  TRXPR |= (1<<TRXRST);   // TRXRST = 1 (Reset state, resets all registers)

  // Transceiver Interrupt Enable Mask - IRQ_MASK
  // This register disables/enables individual radio interrupts.
  // First, we'll disable IRQ and clear any pending IRQ's
  IRQ_MASK = 0;  // Disable all IRQs
  
  // Transceiver State Control Register -- TRX_STATE
  // This regiseter controls the states of the radio.
  // First, we'll set it to the TRX_OFF state.
  TRX_STATE = (TRX_STATE & 0xE0) | TRX_OFF;  // Set to TRX_OFF state
  delay(1);
  
  // Transceiver Status Register -- TRX_STATUS
  // This read-only register contains the present state of the radio transceiver.
  // After telling it to go to the TRX_OFF state, we'll make sure it's actually
  // there.
  if ((TRX_STATUS & 0x1F) != TRX_OFF) // Check to make sure state is correct
    return 0;	// Error, TRX isn't off

  // Transceiver Control Register 1 - TRX_CTRL_1
  // We'll use this register to turn on automatic CRC calculations.
  TRX_CTRL_1 |= (1<<TX_AUTO_CRC_ON);  // Enable automatic CRC calc. 
  
  // Enable RX start/end and TX end interrupts
  IRQ_MASK = (1<<RX_START_EN) | (1<<RX_END_EN) | (1<<TX_END_EN);
  
  // Transceiver Clear Channel Assessment (CCA) -- PHY_CC_CCA
  // This register is used to set the channel. CCA_MODE should default
  // to Energy Above Threshold Mode.
  // Channel should be between 11 and 26 (2405 MHz to 2480 MHz)
  if ((channel < 11) || (channel > 26)) channel = 11;  
  PHY_CC_CCA = (PHY_CC_CCA & 0xE0) | 11; // Set the channel to 11
  
  // Finally, we'll enter into the RX_ON state. Now waiting for radio RX's, unless
  // we go into a transmitting state.
  TRX_STATE = (TRX_STATE & 0xE0) | RX_ON; // Default to receiver

  return 1;
}

// This function sends a string of characters out of the radio.
// Given a string, it'll format a frame, and send it out.
void rfPrint(String toPrint)
{
  uint8_t frame[127];  // We'll need to turn the string into an arry
  int length = toPrint.length();  // Get the length of the string
  for (int i=0; i<length; i++)  // Fill our array with bytes in the string
  {
    frame[i] = toPrint.charAt(i);
  }
  
  // Transceiver State Control Register -- TRX_STATE
  // This regiseter controls the states of the radio.
  // Set to the PLL_ON state - this state begins the TX.
  TRX_STATE = (TRX_STATE & 0xE0) | PLL_ON;  // Set to TX start state
  while(!(TRX_STATUS & PLL_ON))
    ;  // Wait for PLL to lock
    
  digitalWrite(TX_LED, HIGH);
  
  // Start of frame buffer - TRXFBST
  // This is the first byte of the 128 byte frame. It should contain
  // the length of the transmission.
  TRXFBST = length + 2;
  memcpy((void *)(&TRXFBST+1), frame, length);
  // Transceiver Pin Register -- TRXPR.
  // From the PLL_ON state, setting SLPTR high will initiate the TX.
  TRXPR |= (1<<SLPTR);   // SLPTR high
  TRXPR &= ~(1<<SLPTR);  // SLPTR low
  
  // After sending the byte, set the radio back into the RX waiting state.
  TRX_STATE = (TRX_STATE & 0xE0) | RX_ON;
}

// This function will transmit a single byte out of the radio.
void rfWrite(uint8_t b)
{
  uint8_t length = 3;

  // Transceiver State Control Register -- TRX_STATE
  // This regiseter controls the states of the radio.
  // Set to the PLL_ON state - this state begins the TX.
  TRX_STATE = (TRX_STATE & 0xE0) | PLL_ON;  // Set to TX start state
  while(!(TRX_STATUS & PLL_ON))
    ;  // Wait for PLL to lock

  digitalWrite(TX_LED, HIGH);  // Turn on TX LED

  // Start of frame buffer - TRXFBST
  // This is the first byte of the 128 byte frame. It should contain
  // the length of the transmission.
  TRXFBST = length;
  // Now copy the byte-to-send into the address directly after TRXFBST.
  memcpy((void *)(&TRXFBST+1), &b, 1);

  // Transceiver Pin Register -- TRXPR.
  // From the PLL_ON state, setting SLPTR high will initiate the TX.
  TRXPR |= (1<<SLPTR);   // SLPTR = 1
  TRXPR &= ~(1<<SLPTR);  // SLPTR = 0  // Then bring it back low

  // After sending the byte, set the radio back into the RX waiting state.
  TRX_STATE = (TRX_STATE & 0xE0) | RX_ON;
}

// Returns how many unread bytes remain in the radio RX buffer.
// 0 means the buffer is empty. Maxes out at RF_BUFFER_SIZE.
unsigned int rfAvailable()
{
  return (unsigned int)(RF_BUFFER_SIZE + radioRXBuffer.head - radioRXBuffer.tail) % RF_BUFFER_SIZE;
}

// This function reads the oldest data in the radio RX buffer.
// If the buffer is emtpy, it'll return a 255.
char rfRead()
{
  if (radioRXBuffer.head == radioRXBuffer.tail)
  {
    return -1;
  }
  else
  {
    // Read from the buffer tail, and update the tail pointer.
    char c = radioRXBuffer.buffer[radioRXBuffer.tail];
    radioRXBuffer.tail = (unsigned int)(radioRXBuffer.tail + 1) % RF_BUFFER_SIZE;
    return c;
  }
}

// This interrupt is called when radio TX is complete. We'll just
// use it to turn off our TX LED.
ISR(TRX24_TX_END_vect)
{
  digitalWrite(TX_LED, LOW);
}

// This interrupt is called the moment data is received by the radio.
// We'll use it to gather information about RSSI -- signal strength --
// and we'll turn on the RX LED.
ISR(TRX24_RX_START_vect)
{
  digitalWrite(RX_LED, HIGH);  // Turn receive LED on
  rssiRaw = PHY_RSSI;  // Read in the received signal strength
}

// This interrupt is called at the end of data receipt. Here we'll gather
// up the data received. And store it into a global variable. We'll
// also turn off the RX LED.
ISR(TRX24_RX_END_vect)
{
  uint8_t length;
  // Maximum transmission is 128 bytes
  uint8_t tempFrame[RF_BUFFER_SIZE];

  // The received signal must be above a certain threshold.
  if (rssiRaw & RX_CRC_VALID)
  {
    // The length of the message will be the first byte received.
    length = TST_RX_LENGTH;
    // The remaining bytes will be our received data.
    memcpy(&tempFrame[0], (void*)&TRXFBST, length);
    
    // Now we need to collect the frame into our receive buffer.
    //  k will be used to make sure we don't go above the length
    //  i will make sure we don't overflow our buffer.
    unsigned int k = 0;
    unsigned int i = (radioRXBuffer.head + 1) % RF_BUFFER_SIZE; // Read buffer head pos and increment;
    while ((i != radioRXBuffer.tail) && (k < length-2))
    {
      // First, we update the buffer with the first byte in the frame
      radioRXBuffer.buffer[radioRXBuffer.head] = tempFrame[k++];
      radioRXBuffer.head = i; // Update the head
      i = (i + 1) % RF_BUFFER_SIZE; // Increment i % BUFFER_SIZE
    }
  }

  digitalWrite(RX_LED, LOW);  // Turn receive LED off, and we're out
}
