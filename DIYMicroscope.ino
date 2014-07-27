/* DIY Microscope Focus Adjustment And RGB LEDs Control
 
 created 2014
 by Sherif Mohamed Rashwan
 
 This example code is in the public domain.

 */

// constants won't change. Used here to 
// set pin numbers:
const int ledPin =  13;      // the number of the LED pin
#include <Servo.h> 
 
Servo myservo;  // create servo object to control a servo 
                // a maximum of eight servo objects can be created 
 
int pos = 90;    // variable to store the servo position 
const int positive = 3;
const int red = 4;
const int blue = 5;
const int green = 6;

const int flashing1 = 10;
const int flashing2 = 11;

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

// Variables will change:
int ledState = LOW;             // ledState used to set the LED
long previousMillis = 0;        // will store last time LED was updated
long previousMillis2 = 0;
long previousMillis3 = 0;
// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 10;           // interval at which to blink (milliseconds)

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);      
    Serial.begin(9600);
  inputString.reserve(500);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object 
  myservo.write(pos);
  
  pinMode(positive,OUTPUT);
  pinMode(red,OUTPUT);
  pinMode(blue,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(flashing1,OUTPUT);
  pinMode(flashing2,OUTPUT);
}
int i =0;
void loop()
{
  
  // here is where you'd put code that needs to be running all the time.

  // check to see if it's time to blink the LED; that is, if the 
  // difference between the current time and last time you blinked 
  // the LED is bigger than the interval at which you want to 
  // blink the LED.
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   

  analogWrite(positive,i);
  digitalWrite(red,HIGH);
  digitalWrite(blue,LOW);
  digitalWrite(green,LOW);
  if(i < 255)
  {
  i++;
  }else
  {
    i=0;
  }
  }
  
    unsigned long currentMillis2 = millis();
 
  if(currentMillis2 - previousMillis2 > interval) {
    // save the last time you blinked the LED 
    previousMillis2 = currentMillis2;   
  analogWrite(positive,i);
  digitalWrite(red,LOW);
  digitalWrite(blue,HIGH);
  digitalWrite(green,HIGH);
  if(i < 255)
  {
  i++;
  }else
  {
    i=0;
  }
  }
  serialdata();
}
void serialdata()
{
  if (stringComplete) {
    //int command = Serial.read();
    if(inputString == "1\n")
    {
      pos++;
      myservo.write(pos);
      stringComplete=false;
      inputString="";
    }
    if(inputString == "2\n")
    {
      pos--;
      myservo.write(pos);
      stringComplete=false;
      inputString="";
    }
    if(inputString == "3\n")
    {
      pos = 90;
      myservo.write(pos); 
      stringComplete=false;
      inputString="";
    }
    //Serial.write(inByte); 
  }
}
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read(); 
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
      

    } 
  }
}
