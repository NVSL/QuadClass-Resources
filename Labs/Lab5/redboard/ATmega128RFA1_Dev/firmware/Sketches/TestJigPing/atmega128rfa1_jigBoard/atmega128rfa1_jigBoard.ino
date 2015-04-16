/*
  ATmega128RFA1 Dev Board On Test Jig
  by: Jim Lindblom
      SparkFun Electronics
  date: June 3, 2012
  License: Beerware. Feel free to use, reuse, and modify this code
  as you please. If you find it useful, you can buy me a beer.

  This is the code that lives on our on-test-jig ATmega128RFA1
  board. It'll wait for a button press on PE2, then send an RF
  ping out to the board to be tested. It'll then wait for a
  response. If it receives the correct response it'll light up the
  "Pass" LED on PE3.
  
  Hardware:
    PORTE2 = Button, tied to ground
    PORTE3 = LED connected through 330&ohm; to ground
*/

/* Dev board specific defines: RF RX and TX LEDs: */
#define RXLED_DDR  DDRB
#define RXLED_PORT PORTB
#define RXLED_POS  PB6

#define TXLED_DDR  DDRB
#define TXLED_PORT PORTB
#define TXLED_POS  PB7

/* Test-jig specific defines: button and LED */
#define LED_DDR  DDRE
#define LED_PORT PORTE
#define LED_POS  PE3

#define BUTTON_DDR  DDRE
#define BUTTON_PORT PORTE
#define BUTTON_PIN  PINE
#define BUTTON_POS  PE2

/* Variables for test jig state machine */
enum testPoint
{
  WAITING_BUTTON,  // Loop waiting for the test button to press
  BUTTON_PRESSED,  // Prepare to send test char
  SENDING,  // Send the test character
  WAITING_SENT,  // Busy-loop and eventually timeout after sending
  RECEIVED,  // Upon received, check if the correct char is rec'd
  RECEIVED_GOOD,  // If received good, continue testing...
};
byte testStatus = WAITING_BUTTON;
const char testSendChar = 'j';
char receivedChar = 0;

byte rssiRaw;  // Global variable to store RSSI raw reading

unsigned int timeout = 0;
const unsigned int TIMEOUT_MAX = 1000;  // timeout in miliseconds
  
void setup()
{
  ioInit();
  Serial.begin(9600);
  initRadio();
}

void loop()
{
  switch (testStatus)
  {
    case WAITING_BUTTON:
      while (!readButton())
        ;
      while (readButton())
        ;  // Wait for button to depress
      // Button pressed, prepare to test
      testStatus = BUTTON_PRESSED;
      break;
    case BUTTON_PRESSED:
      setPassLED(0);  // Turn pass LED off
      timeout=0;  // reset timeout variable
      testStatus = SENDING;
      break;
    case SENDING:
      txByte(testSendChar);
      testStatus = WAITING_SENT;
      break;
    case WAITING_SENT:
      delay(1);
      timeout++;
      if (timeout >= TIMEOUT_MAX)
      {
        Serial.println("Timeout Error. Restarting test.");
        testStatus = WAITING_BUTTON;
      }
      break;
    case RECEIVED:
      if (receivedChar == testSendChar + 1)
      {
        setPassLED(1);
        testStatus = RECEIVED_GOOD;
      }
      else
      {
        setPassLED(0);
        Serial.print("Receive error. Received: ");
        Serial.write(receivedChar);
        Serial.println();
        testStatus = WAITING_BUTTON;
      }
      break;
    case RECEIVED_GOOD:
      delay(250);
      testStatus = BUTTON_PRESSED;
      break;
  }
}

// Initialize button, pull-up resistor on it, on E2
// Initialize the LED on E3
// Initialize on-board LEDs for RF RX/TX
void ioInit()
{
  // Setup button:
  BUTTON_DDR &= ~(1<<BUTTON_POS);  // PB2 set as input
  BUTTON_PORT |= 1<<BUTTON_POS;  // Pull-up set
  
  // Setup LED:
  LED_DDR |= (1<<LED_POS);  // PB3 set as output
  setPassLED(0);
  
  // Setup RX/TX LEDs:
  TXLED_DDR |= (1<<TXLED_POS);
  TXLED_PORT &= ~(1<<TXLED_POS);
  RXLED_DDR |= (1<<RXLED_POS);
  RXLED_PORT &= ~(1<<RXLED_POS);
}

byte readButton()
{
  if (!(BUTTON_PIN & (1<<BUTTON_POS)))
    return 1;
  else
    return 0;
}

void setPassLED(byte on)
{
  if (on)
    LED_PORT |= (1<<LED_POS);
  else
    LED_PORT &= ~(1<<LED_POS);
}

void initRadio()
{
  uint8_t status;
  
  TRXPR &= ~(1<<TRXRST);  // TRX Reset Low
  TRXPR &= ~(1<<SLPTR);   // TRX SLPTR Low
  delay(1);
  TRXPR |= (1<<TRXRST);   // TRX Reset High
  
  /* disable IRQ and clear any pending IRQ's */
  IRQ_MASK = 0;  // Disable all IRQs
  TRX_STATE = (TRX_STATE & 0xE0) | TRX_OFF;  // Set to TRX_OFF state
  delay(1);  
  status = TRX_STATUS & 0x1F;  // Check to make sure state is correct
  if (status != TRX_OFF)
    Serial.println("Error, TRX isn't off");
    
  TRX_CTRL_1 |= (1<<TX_AUTO_CRC_ON);  // Enable automatic CRC calc. 
  /* Enable RX start/end and TX end interrupts */
  IRQ_MASK = (1<<RX_START_EN) | (1<<RX_END_EN) | (1<<TX_END_EN);
  PHY_CC_CCA = (PHY_CC_CCA & 0xE0) | 11; // Set the channel to 11
  TRX_STATE = (TRX_STATE & 0xE0) | RX_ON; // Default to receiver
}

void txByte(uint8_t b)
{
  uint8_t length = 3;
  
  TRX_STATE = (TRX_STATE & 0xE0) | PLL_ON;  // Set to TX start state
  while(!(TRX_STATUS & PLL_ON))
    ;  // Wait for PLL to lock
    
  TXLED_PORT |= (1<<TXLED_POS);  // Turn on TX LED
  
  TRXFBST = length;
  memcpy((void *)(&TRXFBST+1), &b, 1);
  
  TRXPR |= (1<<SLPTR);   // SLPTR high
  TRXPR &= ~(1<<SLPTR);  // SLPTR low
  
  TRX_STATE = (TRX_STATE & 0xE0) | RX_ON;
}

// Transmit End ISR
ISR(TRX24_TX_END_vect)
{
  TXLED_PORT &= ~(1<<TXLED_POS);  // Turn off TX LED
}
// Receive END ISR
ISR(TRX24_RX_END_vect)
{
  uint8_t length;
  uint8_t tempFrame[127];
  
  if (rssiRaw & RX_CRC_VALID)
  {
    length = TST_RX_LENGTH;
    memcpy(&tempFrame[0], (void*)&TRXFBST, length);
  }
  receivedChar = tempFrame[0];
  testStatus = RECEIVED;
  
  RXLED_PORT &= ~(1<<RXLED_POS);  // Turn off RX LED
}

// Receive Start ISR
ISR(TRX24_RX_START_vect)
{
  RXLED_PORT |= (1<<RXLED_POS);  // Turn on RX LED
  rssiRaw = PHY_RSSI;
}
