//incluse the software serial library
#include <SoftwareSerial.h>

// Definitions
//xbee software serial pins software
#define xbee_rxPin 9
#define xbee_txPin 10

//declare software serial for the xbee
SoftwareSerial xbee_Serial(xbee_rxPin, xbee_txPin);

//declare a constant variable for the communication speed
const int theBaud = 9600;

//declare the strings for incomming data and set them to empty
String xbee_inString = "";
String hub_inString = "";

//*****************
//Pin assignments
//DO NOT CHANGE
//these are your INPUT/OUTPUT pins
//there are 6 I/O pins all together

//DIGITAL INPUT/OUTPUT
//3,6,7 have pwm
int io_1 = 3;
int io_2 = 6;
int io_3 = 7;

//ANALOG INPUT (and can be digital I/O)
int io_5 = A0;
int io_6 = A1;
int io_7 = A2;

//*****************

//DO NOT CHANGE
//LED Variables
int led0 = 2;
int led1 = 4;

int blinks;
int blinkDelay = 100;

// the setup routine runs once
void setup() {

  //set the pinmode of the LED
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);

  //start usb/hub serial
  Serial.begin(theBaud);

  //start the xbee software serial
  xbee_Serial.begin(theBaud);

  //hub_Serial.println("SoftWareSerial Connected");
  Serial.println("Running_HUB_RXTX_5");

  //blink LED on startup
  blink_start(3);

}


// the loop routine runs over and over forever:
void loop() {

  //listen to the xbee radio
  xbee_listening();

  //listen to the hub
  hub_listening();

}

void xbee_listening()
{

  //Serial.println("xbee");

  //listen to the xbee for information
  while (xbee_Serial.available() > 0)
  {
    //Serial.println("xbee");
    //put incomming data into the inData variable
    char xbee_inData = xbee_Serial.read();

    xbee_inString += xbee_inData;

    if (xbee_inData == '\n') {

      //send the value to the hub
      Serial.println(xbee_inString);

      //clear the string for new input:
      xbee_inString = "";

      //blink the led once
      xbeeBlink(1);
      break;
    }

  }

}

void hub_listening()
{

  //xbee_Serial.print("1");
  //xbee_Serial.println("in");
 
  //listen to the hub for information
  while (Serial.available() > 0)
  {

    //put incomming data into the inData variable
    char hub_inData = Serial.read();

    //add the data to the incomming string
    hub_inString += hub_inData;

    if (hub_inData == '\n') {
      //send the data to the serial monitor
      //Serial.println(hub_inString);

      //send the value to the appropriate xbee
      xbee_Serial.println(hub_inString);
      //      xbee_Serial.print("1");
      //      xbee_Serial.println("in");

      // clear the string for new input:
      hub_inString = "";

      //bink the led once
      rpiBlink(1);
      break;
    }

  }

}


//these functions blink the LEDs
//blinks for sent data
void xbeeBlink(int blinks)
{

  for (int i = 0; i < blinks; i++)
  {

    digitalWrite(led1, HIGH);
    delay(blinkDelay);
    digitalWrite(led1, LOW);
    delay(blinkDelay);

  }

}

//blinks for data received
void rpiBlink(int blinks)
{

  for (int i = 0; i < blinks; i++)
  {

    digitalWrite(led0, HIGH);
    delay(blinkDelay);
    digitalWrite(led0, LOW);
    delay(blinkDelay);

  }

}

//blinks for startup
void blink_start(int blinks)
{

  for (int i = 0; i < blinks; i++)
  {

    digitalWrite(led0, HIGH);
    delay(blinkDelay);
    digitalWrite(led0, LOW);
    digitalWrite(led1, HIGH);
    delay(blinkDelay);
    digitalWrite(led1, LOW);

  }

}
