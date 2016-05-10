#include <stdarg.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "types.h"

#define PROMINI
#define FAILSAFE

/************************************** MUltiwii Serial Definitions *******************************************************/
#define UART_NUMBER 1
#define RX_BUFFER_SIZE 64
#define TX_BUFFER_SIZE 128

/************************************** MultiWii Protocol Definitions *******************************************************/
// Multiwii Serial Protocol 0
#define MSP_VERSION              0

//to multiwii developpers/committers : do not add new MSP messages without a proper argumentation/agreement on the forum
#define MSP_IDENT                100   //out message         multitype + multiwii version + protocol version + capability variable
#define MSP_STATUS               101   //out message         cycletime & errors_count & sensor present & box activation & current setting number
#define MSP_RAW_IMU              102   //out message         9 DOF
#define MSP_SERVO                103   //out message         8 servos
#define MSP_MOTOR                104   //out message         8 motors
#define MSP_RC                   105   //out message         8 rc chan and more
#define MSP_RAW_GPS              106   //out message         fix, numsat, lat, lon, alt, speed, ground course
#define MSP_COMP_GPS             107   //out message         distance home, direction home
#define MSP_ATTITUDE             108   //out message         2 angles 1 heading
#define MSP_ALTITUDE             109   //out message         altitude, variometer
#define MSP_ANALOG               110   //out message         vbat, powermetersum, rssi if available on RX
#define MSP_RC_TUNING            111   //out message         rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_PID                  112   //out message         P I D coeff (9 are used currently)
#define MSP_BOX                  113   //out message         BOX setup (number is dependant of your setup)
#define MSP_MISC                 114   //out message         powermeter trig
#define MSP_MOTOR_PINS           115   //out message         which pins are in use for motors & servos, for GUI
#define MSP_BOXNAMES             116   //out message         the aux switch names
#define MSP_PIDNAMES             117   //out message         the PID names
#define MSP_WP                   118   //out message         get a WP, WP# is in the payload, returns (WP#, lat, lon, alt, flags) WP#0-home, WP#16-poshold
#define MSP_BOXIDS               119   //out message         get the permanent IDs associated to BOXes
#define MSP_SERVO_CONF           120   //out message         Servo settings

#define MSP_SET_RAW_RC           200   //in message          8 rc chan
#define MSP_SET_RAW_GPS          201   //in message          fix, numsat, lat, lon, alt, speed
#define MSP_SET_PID              202   //in message          P I D coeff (9 are used currently)
#define MSP_SET_BOX              203   //in message          BOX setup (number is dependant of your setup)
#define MSP_SET_RC_TUNING        204   //in message          rc rate, rc expo, rollpitch rate, yaw rate, dyn throttle PID
#define MSP_ACC_CALIBRATION      205   //in message          no param
#define MSP_MAG_CALIBRATION      206   //in message          no param
#define MSP_SET_MISC             207   //in message          powermeter trig + 8 free for future use
#define MSP_RESET_CONF           208   //in message          no param
#define MSP_SET_WP               209   //in message          sets a given WP (WP#,lat, lon, alt, flags)
#define MSP_SELECT_SETTING       210   //in message          Select Setting Number (0-2)
#define MSP_SET_HEAD             211   //in message          define a new heading hold direction
#define MSP_SET_SERVO_CONF       212   //in message          Servo settings
#define MSP_SET_MOTOR            214   //in message          PropBalance function

#define MSP_BIND                 240   //in message          no param

#define MSP_EEPROM_WRITE         250   //in message          no param

#define MSP_DEBUGMSG             253   //out message         debug string buffer
#define MSP_DEBUG                254   //out message         debug1,debug2,debug3,debug4

#define INBUF_SIZE 64
#define BIND_CAPABLE 0;


/************************************** Config Definitions *******************************************************/
#define MAXTHROTTLE 2000
#define MINCOMMAND  1000
#define MINTHROTTLE 1050
#define FAILSAFE_THROTTLE  (MINTHROTTLE + 100)
#define MAG_DECLINATION  0.0f

#define SERIAL0_COM_SPEED 115200
#define SERIAL1_COM_SPEED 115200

/************************************** MultiWii Definitions *******************************************************/
#define RC_CHANS 8
#define VERSION  230
#define MULTITYPE 3
#define DYNBAL 0
#define FLAP 0
#define ACC 1
#define MAG 1
#define GYRO 1
#define BARO 0
#define GPS 0
#define SONAR 0



// Serial Prototypes
void    SerialOpen(uint8_t port, uint32_t baud);
uint8_t SerialRead(uint8_t port);
void    SerialWrite(uint8_t port,uint8_t c);
uint8_t SerialAvailable(uint8_t port);
void    SerialEnd(uint8_t port);
uint8_t SerialUsedTXBuff(uint8_t port);
void    SerialSerialize(uint8_t port,uint8_t a);
void    UartSendData(uint8_t port);
// Protocol Prototypes
void serialCom();
void evaluateOtherData(uint8_t sr);
void evaluateCommand();
// EEPROM Prototypes
void LoadDefaults();
void update_constants();



// Serial Global variables
static volatile uint8_t serialHeadRX[UART_NUMBER+1],serialTailRX[UART_NUMBER+1];
static uint8_t serialBufferRX[RX_BUFFER_SIZE][UART_NUMBER+1];
static volatile uint8_t serialHeadTX[UART_NUMBER+1],serialTailTX[UART_NUMBER+1];
static uint8_t serialBufferTX[TX_BUFFER_SIZE][UART_NUMBER+1];
// Protocol Global variables
static uint8_t CURRENTPORT=0;
static uint8_t inBuf[INBUF_SIZE][UART_NUMBER];
static uint8_t checksum[UART_NUMBER];
static uint8_t indRX[UART_NUMBER];
static uint8_t cmdMSP[UART_NUMBER];
const uint32_t capability = 0+BIND_CAPABLE;
// MultiWii Global Variables
uint8_t rcSerialCount = 0;   // if > 0 overrides RX data
int16_t rcData[RC_CHANS];    // interval [1000;2000]
int16_t rcSerial[8];         // interval [1000;2000] - is rcData coming from MSP
int16_t rcCommand[4];        // interval [1000;2000] for THROTTLE and [-500;+500] for ROLL/PITCH/YAW
int16_t lookupPitchRollRC[5];// lookup table for expo & RC rate PITCH+ROLL
int16_t lookupThrottleRC[11];// lookup table for expo & mid THROTTLE
uint16_t cycleTime = 0;     // this is the number in micro second to achieve a full loop, it can differ a little and is taken into account in the PID loop
uint16_t calibratingA = 0;  // the calibration is done in the main loop. Calibrating decreases at each cycle down to 0, then we enter in a normal mode.
uint8_t  rcOptions[CHECKBOXITEMS];
int16_t  i2c_errors_count = 0;
uint16_t intPowerTrigger1;
int16_t  magHold,headFreeModeHold; // [-180;+180]
int16_t axisPID[3];
int16_t motor[8];
int16_t servo[8] = {1500,1500,1500,1500,1500,1500,1500,1000};
uint8_t PWM_PIN[8] = {8,3,5,4,6,5,A2,12};   //for a quad+: rear,right,left,front
int16_t  debug[4];
conf_t conf;
flags_struct_t f;
global_conf_t global_conf;
imu_t imu;
analog_t analog;
alt_t alt;
att_t att;
const char pidnames[] PROGMEM =
		"ROLL;"
		"PITCH;"
		"YAW;"
		"ALT;"
		"Pos;"
		"PosR;"
		"NavR;"
		"LEVEL;"
		"MAG;"
		"VEL;"
		;
const char boxnames[] PROGMEM = // names for dynamic generation of config GUI
		"ARM;"
		"ANGLE;"
		"HORIZON;"
		"MAG;"
		"HEADFREE;"
		"HEADADJ;"
		;
const uint8_t boxids[] PROGMEM = {// permanent IDs associated to boxes. This way, you can rely on an ID number to identify a BOX function.
		0, //"ARM;"
		1, //"ANGLE;"
		2, //"HORIZON;"
		5, //"MAG;"
		6, //"HEADFREE;"
		7, //"HEADADJ;"
};




//The setup function is called once at startup of the sketch
void setup() {
	// Add your initialization code here
	SerialOpen(0,SERIAL0_COM_SPEED);
	SerialOpen(1,SERIAL1_COM_SPEED);
}

// The loop function is called in an endless loop
void loop()	{

	// Set Data Received by RF Transceiver
	for (int i=0; i< RC_CHANS; i++) {
		rcData[i]=random(MINTHROTTLE, MAXTHROTTLE);
	}
	// Set imu ADC data
	for (int axis=0; axis< 3; axis++) {
		imu.accSmooth[axis] = random(0, 100);
		imu.gyroData[axis] = random(0, 1000);
		imu.magADC[axis] = random(0, 100);
		imu.gyroADC[axis] = 0;
		imu.accADC[axis] = 0;
	}
	// Set Status
	cycleTime++;
	i2c_errors_count = 0;
	// Set motors
	for (int i=0; i< 8; i++) {
		motor[i] = random(MINTHROTTLE, MAXTHROTTLE);
	}
	// Set estimated quadcopter angle
	att.angle[ROLL]=random(0, 1800);     // absolute angle inclination in multiple of 0.1 degree    180 deg = 1800
	att.angle[PITCH]=random(0, 1800);
	att.heading = random(0, 180);
	// Set altitude (Not used)
	alt.EstAlt = 0;             // in cm
	alt.vario = 0;              // variometer in cm/s
	// Set analog (Not used)
	analog.vbat = 0;               // battery voltage in 0.1V steps
	analog.intPowerMeterSum = 0;
	analog.rssi = 0;              // range: [0;1023]
	analog.amperage = 0;
	// Set configuration variables
	LoadDefaults();


	// Send/Recieve Serial data from MultiWiiConf UI
	serialCom();
	delay(5);  // Delay 5 ms.

}


// *******************************************************
// Serial Functions
// Interrupt driven UART transmitter - using a ring buffer
// *******************************************************


ISR(USART0_UDRE_vect) {  // Serial 0 on a PROMINI
	uint8_t t = serialTailTX[0];
	if (serialHeadTX[0] != t) {
		if (++t >= TX_BUFFER_SIZE) t = 0;
		UDR0 = serialBufferTX[t][0];  // Transmit next byte in the ring
		serialTailTX[0] = t;
	}
	if (t == serialHeadTX[0]) UCSR0B &= ~(1<<UDRIE0); // Check if all data is transmitted . if yes disable transmitter UDRE interrupt
}
ISR(USART1_UDRE_vect) { // Serial 1 on a MEGA or on a PROMICRO
	uint8_t t = serialTailTX[1];
	if (serialHeadTX[1] != t) {
		if (++t >= TX_BUFFER_SIZE) t = 0;
		UDR1 = serialBufferTX[t][1];  // Transmit next byte in the ring
		serialTailTX[1] = t;
	}
	if (t == serialHeadTX[1]) UCSR1B &= ~(1<<UDRIE1);
}

void UartSendData(uint8_t port) {
	switch (port) {
	case 0: UCSR0B |= (1<<UDRIE0); break;
	case 1: UCSR1B |= (1<<UDRIE1); break;
	}
}

void SerialOpen(uint8_t port, uint32_t baud) {
	uint8_t h = ((F_CPU  / 4 / baud -1) / 2) >> 8;
	uint8_t l = ((F_CPU  / 4 / baud -1) / 2);
	switch (port) {
#if defined(PROMINI)
	case 0: UCSR0A  = (1<<U2X0); UBRR0H = h; UBRR0L = l; UCSR0B |= (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0); break;
	case 1: UCSR1A  = (1<<U2X1); UBRR1H = h; UBRR1L = l; UCSR1B |= (1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1); break;
#endif
	}
}

void SerialEnd(uint8_t port) {
	switch (port) {
	case 0: UCSR0B &= ~((1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<UDRIE0)); break;
	case 1: UCSR1B &= ~((1<<RXEN1)|(1<<TXEN1)|(1<<RXCIE1)|(1<<UDRIE1)); break;
	}
}

void store_uart_in_buf(uint8_t data, uint8_t portnum) {

	uint8_t h = serialHeadRX[portnum];
	if (++h >= RX_BUFFER_SIZE) h = 0;
	if (h == serialTailRX[portnum]) return; // we did not bite our own tail?
	serialBufferRX[serialHeadRX[portnum]][portnum] = data;
	serialHeadRX[portnum] = h;
}


ISR(USART0_RX_vect)  { store_uart_in_buf(UDR0, 0); }
ISR(USART1_RX_vect)  { store_uart_in_buf(UDR1, 1); }


uint8_t SerialRead(uint8_t port) {
	uint8_t t = serialTailRX[port];
	uint8_t c = serialBufferRX[t][port];
	if (serialHeadRX[port] != t) {
		if (++t >= RX_BUFFER_SIZE) t = 0;
		serialTailRX[port] = t;
	}
	return c;
}

uint8_t SerialAvailable(uint8_t port) {
	return ((uint8_t)(serialHeadRX[port] - serialTailRX[port]))%RX_BUFFER_SIZE;
}

uint8_t SerialUsedTXBuff(uint8_t port) {
	return ((uint8_t)(serialHeadTX[port] - serialTailTX[port]))%TX_BUFFER_SIZE;
}

void SerialSerialize(uint8_t port,uint8_t a) {
	uint8_t t = serialHeadTX[port];
	if (++t >= TX_BUFFER_SIZE) t = 0;
	serialBufferTX[t][port] = a;
	serialHeadTX[port] = t;
}

void SerialWrite(uint8_t port,uint8_t c){
	SerialSerialize(port,c);UartSendData(port);
}



// *******************************************************
// Protocol Functions
// *******************************************************


uint8_t read8()  {
	return inBuf[indRX[CURRENTPORT]++][CURRENTPORT]&0xff;
}
uint16_t read16() {
	uint16_t t = read8();
	t+= (uint16_t)read8()<<8;
	return t;
}
uint32_t read32() {
	uint32_t t = read16();
	t+= (uint32_t)read16()<<16;
	return t;
}

void serialize8(uint8_t a) {
	SerialSerialize(CURRENTPORT,a);
	checksum[CURRENTPORT] ^= a;
}
void serialize16(int16_t a) {
	serialize8((a   ) & 0xFF);
	serialize8((a>>8) & 0xFF);
}
void serialize32(uint32_t a) {
	serialize8((a    ) & 0xFF);
	serialize8((a>> 8) & 0xFF);
	serialize8((a>>16) & 0xFF);
	serialize8((a>>24) & 0xFF);
}

void headSerialResponse(uint8_t err, uint8_t s) {
	serialize8('$');
	serialize8('M');
	serialize8(err ? '!' : '>');
	checksum[CURRENTPORT] = 0; // start calculating a new checksum
	serialize8(s);
	serialize8(cmdMSP[CURRENTPORT]);
}

void headSerialReply(uint8_t s) {
	headSerialResponse(0, s);
}

void inline headSerialError(uint8_t s) {
	headSerialResponse(1, s);
}

void tailSerialReply() {
	serialize8(checksum[CURRENTPORT]);UartSendData(CURRENTPORT);
}

void serializeNames(PGM_P s) {
	headSerialReply(strlen_P(s));
	for (PGM_P c = s; pgm_read_byte(c); c++) {
		serialize8(pgm_read_byte(c));
	}
}

void serialCom() {
	uint8_t c,n;
	static uint8_t offset[UART_NUMBER];
	static uint8_t dataSize[UART_NUMBER];
	static enum _serial_state {
		IDLE,
		HEADER_START,
		HEADER_M,
		HEADER_ARROW,
		HEADER_SIZE,
		HEADER_CMD,
	} c_state[UART_NUMBER];// = IDLE;

	for(n=0;n<UART_NUMBER;n++) {
#define GPS_COND
#define SPEK_COND
#define SBUS_COND
		uint8_t cc = SerialAvailable(CURRENTPORT);
		while (cc-- GPS_COND SPEK_COND SBUS_COND) {
			uint8_t bytesTXBuff = SerialUsedTXBuff(CURRENTPORT); // indicates the number of occupied bytes in TX buffer
			if (bytesTXBuff > TX_BUFFER_SIZE - 50 ) return; // ensure there is enough free TX buffer to go further (50 bytes margin)
			c = SerialRead(CURRENTPORT);
			// regular data handling to detect and handle MSP and other data
			if (c_state[CURRENTPORT] == IDLE) {
				c_state[CURRENTPORT] = (c=='$') ? HEADER_START : IDLE;
				if (c_state[CURRENTPORT] == IDLE) evaluateOtherData(c); // evaluate all other incoming serial data
			} else if (c_state[CURRENTPORT] == HEADER_START) {
				c_state[CURRENTPORT] = (c=='M') ? HEADER_M : IDLE;
			} else if (c_state[CURRENTPORT] == HEADER_M) {
				c_state[CURRENTPORT] = (c=='<') ? HEADER_ARROW : IDLE;
			} else if (c_state[CURRENTPORT] == HEADER_ARROW) {
				if (c > INBUF_SIZE) {  // now we are expecting the payload size
					c_state[CURRENTPORT] = IDLE;
					continue;
				}
				dataSize[CURRENTPORT] = c;
				offset[CURRENTPORT] = 0;
				checksum[CURRENTPORT] = 0;
				indRX[CURRENTPORT] = 0;
				checksum[CURRENTPORT] ^= c;
				c_state[CURRENTPORT] = HEADER_SIZE;  // the command is to follow
			} else if (c_state[CURRENTPORT] == HEADER_SIZE) {
				cmdMSP[CURRENTPORT] = c;
				checksum[CURRENTPORT] ^= c;
				c_state[CURRENTPORT] = HEADER_CMD;
			} else if (c_state[CURRENTPORT] == HEADER_CMD && offset[CURRENTPORT] < dataSize[CURRENTPORT]) {
				checksum[CURRENTPORT] ^= c;
				inBuf[offset[CURRENTPORT]++][CURRENTPORT] = c;
			} else if (c_state[CURRENTPORT] == HEADER_CMD && offset[CURRENTPORT] >= dataSize[CURRENTPORT]) {
				if (checksum[CURRENTPORT] == c) {  // compare calculated and transferred checksum
					evaluateCommand();  // we got a valid packet, evaluate it
				}
				c_state[CURRENTPORT] = IDLE;
				cc = 0; // no more than one MSP per port and per cycle
			}
		}
	}
}

// Send Data to the UI
void  s_struct(uint8_t *cb,uint8_t siz) {
	headSerialReply(siz);
	while(siz--) serialize8(*cb++);
}

// Received Data from the UI
void s_struct_w(uint8_t *cb,uint8_t siz) {
	headSerialReply(0);
	while(siz--) *cb++ = read8();
}

// Evaluates incoming packets
void evaluateCommand() {
	uint32_t tmp=0;

	switch(cmdMSP[CURRENTPORT]) {
	case MSP_SET_RAW_RC:
		s_struct_w((uint8_t*)&rcSerial,16);
		rcSerialCount = 50; // 1s transition
		break;
	case MSP_SET_PID:
		s_struct_w((uint8_t*)&conf.pid[0].P8,3*PIDITEMS);
		break;
	case MSP_SET_BOX:
		s_struct_w((uint8_t*)&conf.activate[0],CHECKBOXITEMS*2);
		break;
	case MSP_SET_RC_TUNING:
		s_struct_w((uint8_t*)&conf.rcRate8,7);
		break;
	case MSP_SET_MISC:
		struct {
			uint16_t a,b,c,d,e,f;
			uint32_t g;
			uint16_t h;
			uint8_t  i,j,k,l;
		} set_misc;
		s_struct_w((uint8_t*)&set_misc,22);
		conf.minthrottle = set_misc.b;
		conf.failsafe_throttle = set_misc.e;
		break;
	case MSP_MISC:
		struct {
			uint16_t a,b,c,d,e,f;
			uint32_t g;
			uint16_t h;
			uint8_t  i,j,k,l;
		} misc;
		misc.a = intPowerTrigger1;
		misc.b = conf.minthrottle;
		misc.c = MAXTHROTTLE;
		misc.d = MINCOMMAND;
		misc.e = conf.failsafe_throttle;
		misc.f = 0; misc.g =0;
		misc.h = 0;
		misc.i = 0;misc.j = 0;misc.k = 0;misc.l = 0;
		s_struct((uint8_t*)&misc,22);
		break;
	case MSP_SET_HEAD:
		s_struct_w((uint8_t*)&magHold,2);
		break;
	case MSP_IDENT:
		struct {
			uint8_t v,t,msp_v;
			uint32_t cap;
		} id;
		id.v     = VERSION;
		id.t     = MULTITYPE;
		id.msp_v = MSP_VERSION;
		id.cap   = capability|DYNBAL<<2|FLAP<<3;
		s_struct((uint8_t*)&id,7);
		break;
	case MSP_STATUS:
		struct {
			uint16_t cycleTime,i2c_errors_count,sensor;
			uint32_t flag;
			uint8_t set;
		} st;
		st.cycleTime        = cycleTime;
		st.i2c_errors_count = i2c_errors_count;
		st.sensor           = ACC|BARO<<1|MAG<<2|GPS<<3|SONAR<<4;
		// ACC
		if(f.ANGLE_MODE)   tmp |= 1<<BOXANGLE;
		if(f.HORIZON_MODE) tmp |= 1<<BOXHORIZON;
		if(f.ARMED) tmp |= 1<<BOXARM;
		// MAG
		if(f.MAG_MODE) tmp |= 1<<BOXMAG;
		// NO FIXEDWING
		if(f.HEADFREE_MODE)       tmp |= 1<<BOXHEADFREE;
		if(rcOptions[BOXHEADADJ]) tmp |= 1<<BOXHEADADJ;
		st.flag             = tmp;
		st.set              = global_conf.currentSet;
		s_struct((uint8_t*)&st,11);
		break;
	case MSP_RAW_IMU:
		s_struct((uint8_t*)&imu,18);
		break;
	case MSP_SERVO:
		s_struct((uint8_t*)&servo,16);
		break;
	case MSP_SERVO_CONF:
		s_struct((uint8_t*)&conf.servoConf[0].min,56); // struct servo_conf_ is 7 bytes length: min:2 / max:2 / middle:2 / rate:1    ----     8 servo =>  8x7 = 56
		break;
	case MSP_SET_SERVO_CONF:
		s_struct_w((uint8_t*)&conf.servoConf[0].min,56);
		break;
	case MSP_MOTOR:
		s_struct((uint8_t*)&motor,16);
		break;
	case MSP_RC:
		s_struct((uint8_t*)&rcData,RC_CHANS*2);
		break;
	case MSP_ATTITUDE:
		s_struct((uint8_t*)&att,6);
		break;
	case MSP_ALTITUDE:
		s_struct((uint8_t*)&alt,6);
		break;
	case MSP_ANALOG:
		s_struct((uint8_t*)&analog,7);
		break;
	case MSP_RC_TUNING:
		s_struct((uint8_t*)&conf.rcRate8,7);
		break;
	case MSP_PID:
		s_struct((uint8_t*)&conf.pid[0].P8,3*PIDITEMS);
		break;
	case MSP_PIDNAMES:
		serializeNames(pidnames);
		break;
	case MSP_BOX:
		s_struct((uint8_t*)&conf.activate[0],2*CHECKBOXITEMS);
		break;
	case MSP_BOXNAMES:
		serializeNames(boxnames);
		break;
	case MSP_BOXIDS:
		headSerialReply(CHECKBOXITEMS);
		for(uint8_t i=0;i<CHECKBOXITEMS;i++) {
			serialize8(pgm_read_byte(&(boxids[i])));
		}
		break;
	case MSP_MOTOR_PINS:
		s_struct((uint8_t*)&PWM_PIN,8);
		break;
	case MSP_RESET_CONF:
		if(!f.ARMED) LoadDefaults();
		headSerialReply(0);
		break;
	case MSP_ACC_CALIBRATION:
		if(!f.ARMED) calibratingA=512;
		headSerialReply(0);
		break;
	case MSP_MAG_CALIBRATION:
		if(!f.ARMED) f.CALIBRATE_MAG = 1;
		headSerialReply(0);
		break;
	case MSP_EEPROM_WRITE:
		//writeParams(1); //TODO Writes to EEPROM
		headSerialReply(0);
		break;
	case MSP_DEBUG:
		s_struct((uint8_t*)&debug,8);
		break;
	default:  // we do not know how to handle the (valid) message, indicate error MSP $M!
		headSerialError(0);
		break;
	}
	tailSerialReply();
}

// evaluate all other incoming serial data
void evaluateOtherData(uint8_t sr) {
	switch (sr) {
	// Note: we may receive weird characters here which could trigger unwanted features during flight.
	//       this could lead to a crash easily.
	//       Please use if (!f.ARMED) where neccessary
	}
}

// *******************************************************
// EEPROM Functions
// *******************************************************

void LoadDefaults() {
	uint8_t i;
	conf.pid[ROLL].P8     = 06;  conf.pid[ROLL].I8    = 05; conf.pid[ROLL].D8     = 04;
	conf.pid[PITCH].P8    = 06; conf.pid[PITCH].I8    = 05; conf.pid[PITCH].D8    = 04;
	conf.pid[PIDLEVEL].P8 = 02; conf.pid[PIDLEVEL].I8 = 02; conf.pid[PIDLEVEL].D8 = 02;
	conf.pid[YAW].P8      = 10;  conf.pid[YAW].I8     = 05;  conf.pid[YAW].D8     = 0;
	conf.pid[PIDALT].P8   = 64; conf.pid[PIDALT].I8   = 25; conf.pid[PIDALT].D8   = 24;

	conf.pid[PIDPOS].P8  = 0;     conf.pid[PIDPOS].I8    = 0;       conf.pid[PIDPOS].D8    = 0;
	conf.pid[PIDPOSR].P8 = 0; 	  conf.pid[PIDPOSR].I8   = 0;        conf.pid[PIDPOSR].D8   = 0;
	conf.pid[PIDNAVR].P8 = 0;     conf.pid[PIDNAVR].I8   = 0;        conf.pid[PIDNAVR].D8   = 0;

	conf.pid[PIDMAG].P8   = 40;

	conf.pid[PIDVEL].P8 = 0;      conf.pid[PIDVEL].I8 = 0;    conf.pid[PIDVEL].D8 = 0;

	conf.rcRate8 = 80; conf.rcExpo8 = 50;
	conf.rollPitchRate = 40;
	conf.yawRate = 40;
	conf.dynThrPID = 0;
	conf.thrMid8 = 50; conf.thrExpo8 = 0;
	for(i=0;i<CHECKBOXITEMS;i++) {conf.activate[i] = 0;}
	conf.angleTrim[0] = 0; conf.angleTrim[1] = 0;
	conf.powerTrigger1 = 0;
	update_constants();
}

void update_constants() {
	conf.failsafe_throttle = FAILSAFE_THROTTLE;
	conf.minthrottle = MINTHROTTLE;
	conf.mag_declination = (int16_t)(MAG_DECLINATION * 10);
	// writeParams(0);  //TODO Writes to EEPROM
}
