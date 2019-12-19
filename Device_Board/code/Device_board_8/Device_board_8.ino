//Include the software serial library
#include <SoftwareSerial.h>

//if your project uses libraries, add them here




// Definitions
//xbee software serial pins software
//DO NOT CHANGE
#define rxPin 9
#define txPin 10

//declare software serial object for the xbee
SoftwareSerial xbee_Serial(rxPin, txPin);

//declare a constant variable for the communication speed
const int theBaud = 9600;

//declare the string variable for incomming data and set it to empty
String xbee_inString = "";


//*****************


//this is your project ID number
char myID_Num = '1';


//*****************
//Pin assignments
//DO NOT CHANGE
//these are your INPUT/OUTPUT pins
//there are 8 I/O pins all together

//DIGITAL INPUT/OUTPUT
//3,6,7 have pwm
int io_1 = 3;
int io_2 = 5;
int io_3 = 6;
//no pwm
int io_4 = 11;

//ANALOG INPUT (and can be digital I/O)
int io_5 = A0;
int io_6 = A1;
int io_7 = A2;
int io_8 = A3;

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



// the setup routine runs once when you press reset:
void setup()
{

  //If you are using the Digital Input/Output pins,
  //set the PINMODE here.
  //preset pinmode commands
  //uncomment the pins you are using and change the MODE to INPUT or OUTPUT
  //pinMode(io_1, MODE);
  //pinMode(io_2, MODE);
  //pinMode(io_3, MODE);
  //pinMode(io_4, MODE);

  //DO NOT CHANGE
  //set the pinmode of the LED
  pinMode(led0, OUTPUT);
  pinMode(led1, OUTPUT);

  //start the xbee software serial
  xbee_Serial.begin(theBaud);

  //this is for testing on the arduino board
  Serial.begin(theBaud);

  //print a simple test message
  Serial.println("Running_PROJECT_RXTX_7");

  //blink LED on startup
  blink_start(3);

}


// the loop routine runs over and over forever:
void loop()
{

  //read the sensors
  readSensors();

  //send data to the hub
  talking();

  //listen for data from the hub
  //if your project does not require data from the hub, comment this out
  listening();

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


//This function sends data to the hub
void talking()
{

  //If your project sends data to the hub, send it here
  //don't change
  xbee_Serial.print(myID_Num);
  xbee_Serial.print("_");

  //change "MY_GLOBAL_VARIABLE" to your data
  xbee_Serial.println(MY_GLOBAL_VARIABLE_0);

  //this is for testing on the arduino board
  Serial.print("The Data I am sending is: ");
  Serial.print(myID_Num);
  Serial.print("_");
  Serial.println(MY_GLOBAL_VARIABLE_0);

  //blink LED on send
  blinkTX(1);

  //wait a bit to make sure all the data is sent
  delay(500);

}

//This function listens for data from the hub
void listening()
{

  char endMarker = '\n';
  bool isThisforMe = false;

  //listen to the xbee for information
  while (xbee_Serial.available() > 0)
  {

    //put incomming data into the xbee_inData variable
    char xbee_inData = xbee_Serial.read();

    if (xbee_inData == myID_Num && isThisforMe == false)
    {

      Serial.println("For Me!");

      isThisforMe = true;

    }

    if (isThisforMe)
    {

      xbee_inString += xbee_inData;

      if (xbee_inData == endMarker) {

        //this is for testing on the arduino board
        Serial.print("I am hearing: ");
        Serial.println(xbee_inString);

        //strip away your ID number leaving your data
        String theData = xbee_inString.substring(2);

        //this is for testing on the arduino board
        //Serial.println(theData);

        //Call a function to do domething here with your theData variable
        //uncomment if you are using xbee data
        //doSomething(theData);

        //clear the string for new input:
        xbee_inString = "";

        //blink the led once
        blinkRX(1);

        //set the boolean to false
        isThisforMe = !isThisforMe;

      }

    }

  }

}

//*****************


//this is where you do something with the data


//comment/uncomment the line that fits your data source
//if your data is coming from xbee_listening()
//void doSomething(string theData)

//if your data is coming from readSensors()
void doSomething(int theData)
{
  //this is for testing on the arduino board
  Serial.print("My Data is: ");
  Serial.println(theData);

  //example:
  //  if (theData <= 100)
  //  {
  //
  //    //turn the motor
  //
  //  }



}


//*****************



//these functions blink the LEDs
//blinks for sent data
void blinkTX(int blinks)
{

  for (int i = 0; i < blinks; i++)
  {

    digitalWrite(led0, HIGH);
    delay(blinkDelay);
    digitalWrite(led0, LOW);
    delay(blinkDelay);

  }

}

//blinks for data received
void blinkRX(int blinks)
{

  for (int i = 0; i < blinks; i++)
  {

    digitalWrite(led1, HIGH);
    delay(blinkDelay);
    digitalWrite(led1, LOW);
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
