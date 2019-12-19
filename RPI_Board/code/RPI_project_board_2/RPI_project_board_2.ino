//incluse the software serial library
#include <SoftwareSerial.h>

//if your project uses libraries, add them here




// Definitions
//xbee software serial pins software
//DO NOT CHANGE
#define xbee_rxPin 9
#define xbee_txPin 10

//declare software serial object for the xbee
SoftwareSerial xbee_Serial(xbee_rxPin, xbee_txPin);

//declare a constant variable for the communication speed
const int theBaud = 9600;

//declare the strings for incomming data and set them to empty
String xbee_inString = "";
String rpi_inString = "";

//*****************


//this is your project ID number
char myID_Num = '1';


//*****************
//Pin assignments
//DO NOT CHANGE
//these are your INPUT/OUTPUT pins
//there are 6 I/O pins all together

//DIGITAL INPUT/OUTPUT
//3,6,7 have pwm
int io_1 = 3;
int io_2 = 5;
int io_3 = 6;



//ANALOG INPUT (and can be digital I/O)
int io_5 = A0;
int io_6 = A1;
int io_7 = A2;


//*****************

//declare your global variables here
//these variable are for your sensor data
//example:
int MY_GLOBAL_VARIABLE_0;

//more variables can be added
//int MY_GLOBAL_VARIABLE_1;


//*****************

//DO NOT CHANGE
//LED Variables
int led0 = 2;
int led1 = 4;

int blinks;
int blinkDelay = 100;

//*****************



// the setup routine runs once
void setup()
{

  //If you are using the Digital Input/Output pins,
  //set the PINMODE here.
  //preset pinmode commands
  //uncomment the pins you are using and change the MODE to INPUT or OUTPUT
  //pinMode(io_1, MODE);
  //pinMode(io_2, MODE);
  //pinMode(io_3, MODE);


  //DO NOT CHANGE
  //set the pinmode of the LED
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);

  //start the xbee software serial
  xbee_Serial.begin(theBaud);

  //start usb/rpi serial
  Serial.begin(theBaud);

  //print a simple test message
  Serial.println("Running_RPI_PROJECT_RXTX_2");

  //blink LED on startup
  blink_start(3);

}


// the loop routine runs over and over forever:
void loop()
{

  //read the sensors
  readSensors();

  //listen to the xbee radio
  xbee_listening();

  //listen to the rpi
  //if your project does not require data from the hub, comment this out
  rpi_listening();

}


//This function reads your buttons and sensors
void readSensors()
{
  //DO YOUR SENSOR READING HERE
  //MAKE SURE YOUR DATA IS DECLARED IN A GLOBAL VARIABLE ABOVE
  //example:
  //MY_GLOBAL_VARIABLE = analogRead(io_5);

  //test variable
  MY_GLOBAL_VARIABLE_0 = random(0, 20);

  //this is for testing on the arduino board
  //  Serial.print("MY_GLOBAL_VARIABLE = ");
  //  Serial.println(MY_GLOBAL_VARIABLE_0);


  //do something with the data
  //uncomment if you are using sensor data
  //doSomething(MY_GLOBAL_VARIABLE_0);

}


//listen for incomming data from the xbee
//if the project is NOT receiving data from the hub, ignore this
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

      //send the value to the rpi
      Serial.println(xbee_inString);

      //OR

      //do something with the data
      //uncomment if you are using xbee data
      //doSomething(xbee_inString);

      //clear the string for new input:
      xbee_inString = "";

      //blink the led once
      xbeeBlink(1);
      break;
    }

  }

}


//listen for incomming data from the rpi
//if the project is NOT receiving data from the rpi, ignore this
void rpi_listening()
{

  //listen to the rpi for information
  while (Serial.available() > 0)
  {

    //put incomming data into the inData variable
    char rpi_inData = Serial.read();

    //add the data to the incomming string
    rpi_inString += rpi_inData;

    if (rpi_inData == '\n') {
      //this is for testing on the arduino board
      //Serial.println(rpi_inString);

      //If your project sends data to the hub, send it here
      //don't change
      xbee_Serial.print(myID_Num);
      xbee_Serial.print("_");

      //send the value to the hub
      xbee_Serial.println(rpi_inString);

      //OR*********

      //do something with the data
      //uncomment if you are using RPI data
      //doSomething(rpi_inString);


      // clear the string for new input:
      rpi_inString = "";

      //bink the led once
      rpiBlink(1);
      break;
    }

  }

}


//*****************


//this is where you do something with the data


//comment/uncomment the line that fits your data source
//if your data is coming from rpi_listening() or xbee_listening()
//void doSomething(string theData)

//if your data is coming from readSensors()
void doSomething(int theData)
{
  //this is for testing on the arduino board
  //Serial.print("My Data is: ");
  //Serial.println(theData);

  //example:
  //  if (theData <= 100)
  //  {
  //
  //    //turn the motor
  //
  //  }

}


//these functions blink the LEDs
//blinks for sent data
//green led
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
//red led
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
