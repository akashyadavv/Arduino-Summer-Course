#include<SoftwareSerial.h>
#include "Home_Automation.h"
#include "Arduino.h"
#include "sim_interface.h"

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
 
void motionDetect()
{
	val = digitalRead(inputPin);
	int LDRValue = analogRead(LDR);
	//Serial.println(LDRValue);
	if (LDRValue <=700)
	{
    	if (val==HIGH)
    	{
      		digitalWrite(ledPin, LOW);
      		if (pirState==LOW)
      		{
        		Serial.println("Motion Detected and It's Dark Outside; Lights status: ON");
        		pirState = HIGH;
      		}
    	}
    	else
    	{
      		if (pirState == HIGH)
      		{
        		Serial.println("Motion ended!");
        		digitalWrite(ledPin, HIGH);
        		pirState = LOW;
      		}
    	}
	}		
	else
	{
	  /*if(val ==LOW)
	  {
	  if(pirState==LOW || pirState==HIGH)
	  {Serial.println("Motion ended!It's Bright Outside; Lights status: OFF");
	    pirState=LOW;
	  }*/
		digitalWrite(ledPin, HIGH);
	}
}

void flameDetect()
{
  sensorValue = analogRead(sensorPin); 
  Serial.println(sensorValue); 
  while(sensorValue < 100) 
  {
    digitalWrite(buzzer,HIGH);
    Serial.println("App: Found key");
    delay(1000);
    inputChar = Serial.read();
    simSendSMS(relayOnMsg, "+918123333693");
    Serial.println("App: SMS sent\n");
    
    delay(10000);
  }
  delay(1000);
  checkATCmds();
  readSMSMessage();
}

void updateSerial() 
{
  while(serialSIM800.available()) 
  {
    c = serialSIM800.read();
    Serial.write(serialSIM800.read());
    if(c=='Y')
    {
      digitalWrite(ledPin,HIGH);
      Serial.write(serialSIM800.read());
    
    }
    if(c=='N')
    {
      digitalWrite(ledPin,LOW);
      Serial.write(serialSIM800.read()); 
    }
   }
}
