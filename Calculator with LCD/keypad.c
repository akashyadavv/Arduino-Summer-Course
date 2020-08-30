#include "keypad.h" 
static unsigned char rowPins[4]; 
static unsigned char colPins[4]; 
#define R1  9 
#define R2  8 
#define R3  7 
#define R4  6 

#define C1  5 
#define C2  4 
#define C3  3 
#define C4  2 

#define DEBUG  1
static keypad_setPins_local(char rowPins_in[], int row_output, char colPins_in[], int col_output); 

void keypad_setPins(char rowPins_in[], char colPins_in[]) 
{   
	for (int i=0; i<4; i++)   
	{     
		rowPins[i] = rowPins_in[i];     
		colPins[i] = colPins_in[i];        
	} 
} 

static keypad_setPins_local(char rowPins_in[], int row_output, char colPins_in[], int col_output) 
{            
	for (int i=0; i<4; i++)     
	{                       
		if (row_output == OUTPUT)         
		{             
			pinMode(rowPins[i], OUTPUT);             
			digitalWrite(rowPins[i], LOW);                     
		}         
		else             
			pinMode(rowPins[i], INPUT_PULLUP); 
		if (col_output == OUTPUT)         
		{            
			pinMode(colPins[i], OUTPUT);             
			digitalWrite(colPins[i], LOW);                      
		}         
		else            
			pinMode(colPins[i], INPUT_PULLUP);           
		}   
} 
unsigned keyPadMatrix[4][4] = 
{ 
 	'1', '2', '3', 'A',  
	'4', '5', '6', 'B',    
	'7', '8', '9', 'C',   
	'*', '0', '#', 'D',    
}; 

unsigned char getKey() 
{ 
 	keypad_setPins_local(rowPins, OUTPUT, colPins, INPUT);         
	int col_key_index = -1;     
	for (int key_index=0; (key_index<4) && (col_key_index == -1); key_index++)     
	{         
		boolean pinValue = digitalRead(colPins[key_index]);         
		Serial.print("colPin:");         
		Serial.print(colPins[key_index]);         
		Serial.print(" -");         
		Serial.println(pinValue);   
 		if (pinValue == LOW)         
		{             
			col_key_index = key_index;                  
			Serial.println("col key set");         
		}
	}
	int row_key_index = -1;     
	if (col_key_index != -1)     
	{        
		keypad_setPins_local(rowPins, INPUT, colPins, OUTPUT);                
		for (int key_index=0; ((key_index<4) && (row_key_index == -1)); key_index++)        
		{             
			int pinValue = digitalRead(rowPins[key_index]);                                    
			if (pinValue == LOW)             
			{                 
				row_key_index = key_index;                                 
			}         
		}     
	}
	 else         
	 	return (NO_KEY_PRESSED);       
	
	if (row_key_index!=-1)     
	{         
		return(keyPadMatrix[row_key_index][col_key_index]);     
	}     
	else         
		Serial.println("Issue"); 	
}
void setup() 
{      
	char rows[4] = {R1, R2, R3, R4};   
	char cols[4] = {C1, C2, C3, C4};   
	Serial.begin(9600);   
	keypad_setPins(rows, cols); 
}

void loop() 
{    
	char key;   
	key=getKey();   
	if (key != NO_KEY_PRESSED)   
		Serial.println(key);   
	delay(1000); 
} 

