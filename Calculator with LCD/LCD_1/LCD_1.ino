#include <LiquidCrystal.h>
#include<Keypad.h>
void displayresult();
const byte Rows = 4;
const byte Cols = 4;
const int rs = 8, en = 9, d4 = 7, d5 = 6, d6 = 5, d7 = 4;
char keymap[Rows][Cols]=
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
byte rPins[Rows]={3,2,A1,0};
byte cPins[Cols]={A5,A4,A3,A2};
Keypad kpd = Keypad(makeKeymap(keymap),rPins,cPins,Rows,Cols);

String n,n1,n2;
char operation;
boolean terminate = false;
int result;

void setup(){
  Serial.begin(9600);
  lcd.begin(16, 2); 
}

void loop() {
  displayresult();
  char keypressed;
  keypressed = kpd.getKey();
  if(keypressed!=NO_KEY && (keypressed=='1'||keypressed=='2'||keypressed=='3'||keypressed=='4'||keypressed=='5'||keypressed=='6'||keypressed=='7'||keypressed=='8'||keypressed=='9'||keypressed=='0'))
  {
    n=n+keypressed;
    lcd.setCursor(0,1);
    lcd.print(n);
  }
  if(keypressed!=NO_KEY && (keypressed=='B'||keypressed=='C'||keypressed=='*'||keypressed=='#'))
  {
    lcd.clear();
    n1=n;
    n="";
    if(keypressed=='B')
      operation = '+';
    if(keypressed=='C')
      operation = '-';
    if(keypressed=='*')
      operation = '*';
    if(keypressed=='#')
      operation = '/';
  }
  if(keypressed!=NO_KEY && keypressed=='D')
  {
    lcd.clear();
    n2=n;
    terminate = true;
    if(operation=='+')
      result=n1.toInt()+n2.toInt();
    if(operation=='-')
      result=n1.toInt()-n2.toInt();
    if(operation=='*')
      result=n1.toInt()*n2.toInt();
    if(operation=='/')
      result=n1.toInt()/n2.toInt();
  }
  if(keypressed!=NO_KEY && keypressed=='A')
  {
    lcd.clear();
    n1="0";
    n2="0";
    result=0;
    n="";
    terminate =false;
  }
}
  void displayresult()
  {
    lcd.setCursor(0,0);
    lcd.print(n1);
    lcd.print(operation);
    lcd.print(n2);
    if(terminate==true)
    {
      lcd.print("=");
      lcd.print(result);
    }
  }


  
