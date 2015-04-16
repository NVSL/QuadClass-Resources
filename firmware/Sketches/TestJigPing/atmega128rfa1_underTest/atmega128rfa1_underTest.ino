/*
  ATmega128RFA1 Dev Board Under Test Jig
  by: Jim Lindblom
      SparkFun Electronics
  date: June 3, 2012
  License: Beerware. Feel free to use, reuse, and modify this code
  as you please. If you find it useful, you can buy me a beer.

  This is the code that lives on the ATmega128RFA1 under test.
  It'll wait to receive a test character sent over RF. Once
  received, it'll test its I/O pins. If the pin-test passes, it'll
  increment the value of the character by one (e.g. 'j' becomes 'k')
  and send that back over RF. Once received by the on-jig 128RFA1
  board, the pass LED should light up!
  
  Hardware:
    The ATmega128RFA1 Dev Board should do a self test.
    All I/O pins are tied to one of two nets (alternating based
    on their chip position).

 NET 1: B4, D1, D3, D5, D7, E3, E5, E7, G1, G5, F1, F3, F5, F7
 NET 2: B0, B5, D0, D2, D4, D6, E2, E4, E6, G0, G2, F0, F2, F4, F6
*/

/* Dev board specific defines: RF RX and TX LEDs: */
#define RXLED_DDR  DDRB
#define RXLED_PORT PORTB
#define RXLED_POS  PB6

#define TXLED_DDR  DDRB
#define TXLED_PORT PORTB
#define TXLED_POS  PB7  

/* Variables for test jig state machine */
enum testPoint
{
  WAITING_RX,
  TESTING_IO
};
byte testStatus = WAITING_RX;
char receivedChar = 0;

byte rssiRaw;  // Global variable to store RSSI raw reading

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
    case WAITING_RX:
      delay(1);
      break;
    case TESTING_IO:
      if (testIO() == 2)
      {
        txByte(++receivedChar);
      }
      else
      {
        txByte(0);
      }
      testStatus = WAITING_RX;
      break;
  }
}

// Initialize on-board LEDs for RF RX/TX
// Initialize nets as both inputs
void ioInit(void)
{  
  // Setup RX/TX LEDs:
  TXLED_DDR |= (1<<TXLED_POS);
  TXLED_PORT &= ~(1<<TXLED_POS);
  RXLED_DDR |= (1<<RXLED_POS);
  RXLED_PORT &= ~(1<<RXLED_POS);
  
  testIoInit();
}

void testIoInit(void)
{
  // Setup all but first net pins as inputs, no pull-up
  
  DDRB &= 0b11001110;
  DDRD &= 0b00000000;
  DDRE &= 0b00000011;
  DDRF &= 0b00000000;
  DDRG &= 0b11011000;
  
  PORTB &= 0b11001110;
  PORTD &= 0b00000000;
  PORTE &= 0b00000011;
  PORTF &= 0b00000000;
  PORTG &= 0b11011000;
}

uint8_t testIO(void)
{
  uint8_t testPass = 0;
  
  testIoInit();
  
  // Part 1: Set Net 1 high, read all pins
  DDRB |= (1<<PB4);  // Set first pin high
  PORTB |= (1<<PB4);
  DDRB |= (1<<PB0);  // Set first pin high
  PORTB &= ~(1<<PB0);
  delay(1);
  Serial.println(PIND&0xFF, HEX);
  Serial.println(PINE&0xFC, HEX);
  Serial.println(PINF&0xFF, HEX);
  Serial.println(PING&0x27, HEX);
  Serial.println("---");
  if ( ((PIND & 0xFF)==0xAA) && ((PINE & 0xFC)==0xA8) &&
       ((PINF & 0xFF)==0xAA) && ((PING & 0x27)==0x22) )
  {
    testPass++;
  }
  Serial.println(testPass);
  
  testIoInit();
  // Part 2: Set Net 2 high, read all pins
  DDRB |= (1<<PB0);  // Set first pin high
  PORTB |= (1<<PB0);
  DDRB |= (1<<PB4);  // Set first pin high
  PORTB &= ~(1<<PB4);
  delay(1);
  Serial.println(PINB&0x31, HEX);
  Serial.println(PIND&0xFF, HEX);
  Serial.println(PINE&0xFC, HEX);
  Serial.println(PINF&0xFF, HEX);
  Serial.println(PING&0x27, HEX);
  Serial.println("---");
  if ( ((PINB & 0x31)==0x21) && 
       ((PIND & 0xFF)==0x55) && ((PINE & 0xFC)==0x54) && 
       ((PINF & 0xFF)==0x55) && ((PING & 0x27)==0x05) )
  {
    testPass++;
  }
  Serial.println(testPass);
  
  return testPass;
}

void initRadio(void)
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
  
  testStatus = TESTING_IO;
  RXLED_PORT &= ~(1<<RXLED_POS);  // Turn off RX LED
}

// Receive Start ISR
ISR(TRX24_RX_START_vect)
{
  RXLED_PORT |= (1<<RXLED_POS);  // Turn on RX LED
  rssiRaw = PHY_RSSI;
}
