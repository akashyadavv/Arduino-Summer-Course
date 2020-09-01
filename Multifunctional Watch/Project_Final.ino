#include <SimpleDHT.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
volatile int sec, minute = 0, hour = 0;
int b_h = 5;
int b_m = 6;
int pinDHT11 = 2;
int b_set = 3;
bool set = false;

SimpleDHT11 dht11;

void setup() {

  //Serial.begin(9600); 
  // setting up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.setCursor(0, 0);
  lcd.print(" MULTIFUNCTIONAL ");
  lcd.setCursor(0, 1);
  lcd.print(" WATCH ");
  delay(3000);
  lcd.clear();

  pinMode(b_h, INPUT_PULLUP);
  pinMode(b_m, INPUT_PULLUP);
  pinMode(b_set, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(3), buttons, FALLING); //To make sure the user gets to see the time initially


}

void loop() {

  //Pressing the set button to change the time will stop the clock with the seconds put on hold
  while (set == false)
  {
    lcd.setCursor(0, 1);
    lcd.print("SET");
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    if (hour < 10)
    {
      lcd.print("0");
      lcd.print(hour);
    }
    else
      lcd.print(hour);

    lcd.print(":");
    if (minute < 10)
    {
      lcd.print("0");
      lcd.print(minute);
    }
    else
      lcd.print(minute);
    lcd.print(":");
    if (sec < 10)
    {
      lcd.print("0");
      lcd.print(sec);
    }
    else
      lcd.print(sec);
    lcd.print(" ");

    if (digitalRead(b_h) == LOW)
    {
      hour++;
      if (hour > 23)
        hour = 0;
    }

    if (digitalRead(b_m) == LOW)
    {
      minute++;
      if (minute > 59)
        minute = 0;
    }

  }

  //Start's the clock
  while (set == true)
  {
    byte temperature = 0;
    byte humidity = 0;
    byte data[40] = {0};
    if (dht11.read(pinDHT11, &temperature, &humidity, data)) {
      lcd.setCursor(0, 1);
      lcd.print("Read DHT11 failed");
      return;
    }
    lcd.setCursor(0, 1);
    lcd.print("Temp:");
    lcd.print((int)temperature);
    //lcd.print("*C");
    lcd.print(" ");
    lcd.print("Hum.:");
    lcd.print((int)humidity);
    lcd.print("%");
    //Serial.print("Temperature : ");
    //Serial.print((int)temperature); Serial.println(" *C ");
    //Serial.print("Humidity : ");
    //Serial.print((int)humidity); Serial.println(" %");

    lcd.setCursor(0, 0);
    //sec=millis()/1000;
    delay(1000);
    lcd.print("Time: ");
    if (hour < 10)
    {
      lcd.print("0");
      lcd.print(hour);
    }
    else
    {
      lcd.print(hour);
    }
    lcd.print(":");
    if (minute < 10)
    {
      lcd.print("0");
      lcd.print(minute);
    }
    else
    {
      lcd.print(minute);

    } 
    lcd.print(":");
    if (sec < 10)
    {
      lcd.print("0");
      lcd.print(sec);
    }
    else
    {
      lcd.print(sec);
    }
    lcd.print(" ");
    
    sec++;          //Keeps incrementing
    
    if (sec > 59)
    {
      minute++;
      sec = 0;
    }

    if (minute > 59)
    {
      hour++;
      minute = 0;
    }
    if (hour > 23)
    {
      hour = 0;
    }
  }
}

void buttons()
{
  lcd.clear();
  set = !set;
}
