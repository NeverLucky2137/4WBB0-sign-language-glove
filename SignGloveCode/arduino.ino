/*
NAME OF THE PROJECT : SIGN LANGUAGE TRANSLATOR
MADE BY - MANMOHAN GUPTA

THIS PROJECT READS SENSOR VALUE AND TRY TO UNDERSTAND SYMBOLS GENERATED FROM AMERICAN SIGN LANGUAGE (ASL) CHART
AND DISPLAY ON A SMARTPHONE.
-------PIN CONFIGURATION----------------
A0-A4 : FLEX SENSOR
D4&D5 : FOR BLUETOOTH RX AND TX
A5&A6 : XPIN AND YPIN FOR ACCELROMETER
*/

#include <SoftwareSerial.h>

SoftwareSerial mp3(5, 6);

static uint8_t cmdbuf[8] = {0};
 
void command(int8_t cmd, int16_t dat)
{
  delay(20);
 
  cmdbuf[0] = 0x7e; // bajt startu
  cmdbuf[1] = 0xFF; // wersja
  cmdbuf[2] = 0x06; // liczba bajtow polecenia
  cmdbuf[3] = cmd;  // polecenie
  cmdbuf[4] = 0x00; // 0x00 = no feedback, 0x01 = feedback
  cmdbuf[5] = (int8_t)(dat >> 8); // parametr DAT1
  cmdbuf[6] = (int8_t)(dat); //  parametr DAT2
  cmdbuf[7] = 0xef; // bajt konczacy
 
  for (uint8_t i = 0; i < 8; i++)
  {
    mp3.write(cmdbuf[i]);
  }
}
 
char temp = '0';
int16_t tempSound = 0x0127;

//variable initializtion
int xpin = A4;
int xadc = 0;
int xmax = 0;
int xmin = 1023;

int ypin = A5;
int yadc = 0;
int ymax = 0;
int ymin = 1023;

int FLEX_PIN1 = A0; 
int flexADC1 = 0; 
int sensorMin1 = 0; 
int sensorMax1 = 900;

int FLEX_PIN2 = A1; 
int flexADC2 = 0; 
int sensorMin2 = 0; 
int sensorMax2 = 900;

int FLEX_PIN3 = A2; 
int flexADC3 = 0; 
int sensorMin3 = 0; 
int sensorMax3 = 900;

int FLEX_PIN4 = A3; 
int flexADC4 = 0; 
int sensorMin4 = 0; 
int sensorMax4 = 900;

int FLEX_PIN5 = A6; 
int flexADC5 = 0; 
int sensorMin5 = 0; 
int sensorMax5 = 900;



void setup() 
{
Serial.begin(9600);
mp3.begin(9600);

delay(500); // Czekamy 500ms na inicjalizacje  

command(0x09, 0x0002); // Wybieramy karte SD jako zrodlo
delay(200); // Czekamu 200ms na inicjalizacje

command(0x06, 0x001E); // Ustaw glosnosc na 30
  
while (!Serial) 
{
; // wait for serial port to connect. Needed for native USB port only
}


float flexADC1 = analogRead(FLEX_PIN1);
float flexADC2 = analogRead(FLEX_PIN2);
float flexADC3 = analogRead(FLEX_PIN3);
float flexADC4 = analogRead(FLEX_PIN4);
float flexADC5 = analogRead(FLEX_PIN5);


}




void printfun(char cp) //to avoid printing repeating symbols
{
if(cp!=temp)
{
Serial.println(cp);
temp=cp;
}
}

void playSound(int16_t index)
{
if(index!=tempSound){
command(0x0F, index);
tempSound=index;
}
}


void loop() 
{
// reading sensor value
float flexADC1 = analogRead(FLEX_PIN1);
float flexADC2 = analogRead(FLEX_PIN2);
float flexADC3 = analogRead(FLEX_PIN3);
float flexADC4 = analogRead(FLEX_PIN4);
float flexADC5 = analogRead(FLEX_PIN5);

flexADC1 = constrain(flexADC1,sensorMin1, sensorMax1);
flexADC2 = constrain(flexADC2,sensorMin2, sensorMax2);
flexADC3 = constrain(flexADC3,sensorMin3, sensorMax3);
flexADC4 = constrain(flexADC4,sensorMin4, sensorMax4);
flexADC5 = constrain(flexADC5,sensorMin5, sensorMax5);


float angle1= map(flexADC1, sensorMin1, sensorMax1, 0, 90);
float angle2= map(flexADC2, sensorMin2, sensorMax2, 0, 90);
float angle3= map(flexADC3, sensorMin3, sensorMax3, 0, 90);
float angle4= map(flexADC4, sensorMin4, sensorMax4, 0, 90);
float angle5= map(flexADC5, sensorMin5, sensorMax5, 0, 90); 

xadc = analogRead(xpin);
yadc = analogRead(ypin);

//Serial.println("Angle 1: " + String(angle1));
//Serial.println("Angle 2: " + String(angle2));
//Serial.println("Angle 3: " + String(angle3));
//Serial.println("Angle 4: " + String(angle4));
//Serial.println("Angle 5: " + String(angle5));
//Serial.println("X: " + String(xadc));
//Serial.println("Y: " + String(yadc));
//Serial.println("");

if(((angle1>=0)&&(angle1<=39))&&((angle2>=0)&&(angle2<=90))&&((angle3>=0)&&(angle3<=90))&&((angle4>=0)&&(angle4<=90))&&((angle5>=0)&&(angle5<=90))){
printfun('A');
playSound(0x0101); // Otwarzamy pierwszy utwor (kolejnosc nieposortowana)
}
if(((angle1>=40)&&(angle1<=90))&&((angle2>=0)&&(angle2<=90))&&((angle3>=0)&&(angle3<=90))&&((angle4>=0)&&(angle4<=90))&&((angle5>=0)&&(angle5<=90))){
printfun('B');
playSound(0x0102); // Otwarzamy pierwszy utwor (kolejnosc nieposortowana)
}

delay(500);

}

//----------------------END-----------------------------