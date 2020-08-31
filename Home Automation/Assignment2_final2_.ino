#include<SoftwareSerial.h> 
#include "sim_interface.h"
#include "Home_Automation.h"
SoftwareSerial serialSIM800(9, 10); 

int sensorPin = A0;
int sensorValue = 0;
int buzzer = 12;
int ledPin = 3;
char c;
int pirState = LOW;
int inputPin = 4;
int val=0;
int LDR = A0;

void setup()
{
  pinMode(buzzer,OUTPUT); 
  Serial.begin(9600);
  simSetup();
  serialSIM800.begin(9600); 
  updateSerial();
  pinMode(ledPin,OUTPUT);
  serialSIM800.write("AT+CMGF=1\r\n");
  delay(1000);
  serialSIM800.println("AT+CNMI=2,2,0,0,0"); // AT Command to recieve a live SMS
  delay(1000);
  pinMode(inputPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(LDR, INPUT);
}

static char relayOnMsg[100] = "Flame Detected !";
static int inputChar;

void loop() 
{

  motionDetect();
  
  flameDetect();

  updateSerial();
}
