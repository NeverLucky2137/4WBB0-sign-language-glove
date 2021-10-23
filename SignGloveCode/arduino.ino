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


float flexADC1 = analogRead(FLEX_PIN5);
float flexADC2 = analogRead(FLEX_PIN4);
float flexADC3 = analogRead(FLEX_PIN3);
float flexADC4 = analogRead(FLEX_PIN2);
float flexADC5 = analogRead(FLEX_PIN1);


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
float flexADC1 = analogRead(FLEX_PIN5);
float flexADC2 = analogRead(FLEX_PIN4);
float flexADC3 = analogRead(FLEX_PIN3);
float flexADC4 = analogRead(FLEX_PIN2);
float flexADC5 = analogRead(FLEX_PIN1);

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

Serial.println("Angle 1: " + String(angle1));
Serial.println("Angle 2: " + String(angle2));
Serial.println("Angle 3: " + String(angle3));
Serial.println("Angle 4: " + String(angle4));
Serial.println("Angle 5: " + String(angle5));
Serial.println("X: " + String(xadc));
Serial.println("Y: " + String(yadc));
Serial.println("");

//a
if(((angle1>=76)&&(angle1<=90))&&((angle2>=71)&&(angle2<=90))&&((angle3>=63)&&(angle3<=90))&&((angle4>=49)&&(angle4<=90))&&((angle5>=0)&&(angle5<=20))){
playSound(0x0101);
printfun('a');
}

//b
if(((angle1>=0)&&(angle1<=10))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=12))&&((angle4>=0)&&(angle4<=10))&&((angle5>=50)&&(angle5<=90)))
playSound(0x0102);

//c
if(((angle1>=0)&&(angle1<=20))&&((angle2>=0)&&(angle2<=60))&&((angle3>=40)&&(angle3<=75))&&((angle4>=30)&&(angle4<=75))&&((angle5>=0)&&(angle5<=20)))
playSound(0x0103);

//d
if(((angle1>=20)&&(angle1<=75))&&((angle2>=30)&&(angle2<=80))&&((angle3>=30)&&(angle3<=80))&&((angle4>=0)&&(angle4<=10))&&((angle5>=0)&&(angle5<=35)))
playSound(0x0104);

//e
if(((angle1>=70)&&(angle1<=90))&&((angle2>=89)&&(angle2<=90))&&((angle3>=80)&&(angle3<=90))&&((angle4>=89)&&(angle4<=90))&&((angle5>=80)&&(angle5<=90)))
playSound(0x0105);

//f
if(((angle1>=0)&&(angle1<=5))&&((angle2>=0)&&(angle2<=20))&&((angle3>=0)&&(angle3<=26))&&((angle4>=25)&&(angle4<=90))&&((angle5>=0)&&(angle5<=20)))
playSound(0x0106);

//g
if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=15)))
playSound(0x0107);

//h
if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=20)&&(angle5<=60)))
playSound(0x0108);

//i
if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=80))&&((angle3>=65)&&(angle3<=85))&&((angle4>=75)&&(angle4<=90))&&((angle5>=20)&&(angle5<=70)))
playSound(0x0109);

//j
//if(((angle1>=0)&&(angle1<=10))&&((angle2>=50)&&(angle2<=80))&&((angle3>=65)&&(angle3<=85))&&((angle4>=75)&&(angle4<=90))&&((angle5>=20)&&(angle5<=70)))
//playSound(0x0201);

//k
if(((angle1>=80)&&(angle1<=90))&&((angle2>=65)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=0)&&(angle5<=10)))
printfun('k');
//playSound(0x0202);

//l
//if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=15)))
//printfun('l');
//playSound(0x0203);

//m
if(((angle1>=84)&&(angle1<=90))&&((angle2>=76)&&(angle2<=82))&&((angle3>=60)&&(angle3<=70))&&((angle4>=79)&&(angle4<=85))&&((angle5>=84)&&(angle5<=90)))
printfun('m');
//playSound(0x0204);

//n
if(((angle1>=85)&&(angle1<=90))&&((angle2>=75)&&(angle2<=87))&&((angle3>=56)&&(angle3<=66))&&((angle4>=72)&&(angle4<=80))&&((angle5>=77)&&(angle5<=85)))
printfun('n');
//playSound(0x0205);

//o
if(((angle1>=50)&&(angle1<=80))&&((angle2>=65)&&(angle2<=80))&&((angle3>=55)&&(angle3<=80))&&((angle4>=70)&&(angle4<=90))&&((angle5>=0)&&(angle5<=10)))
printfun('o');
//playSound(0x0206);

//p
if(((angle1>=85)&&(angle1<=90))&&((angle2>=68)&&(angle2<=83))&&((angle3>=0)&&(angle3<=15))&&((angle4>=0)&&(angle4<=5))&&((angle5>=0)&&(angle5<=5)))
printfun('p');
//playSound(0x0207);

//q
if(((angle1>=75)&&(angle1<=90))&&((angle2>=75)&&(angle2<=90))&&((angle3>=65)&&(angle3<=90))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=15)))
printfun('q');
//playSound(0x0208);

//r
if(((angle1>=80)&&(angle1<=90))&&((angle2>=65)&&(angle2<=85))&&((angle3>=0)&&(angle3<=5))&&((angle4>=0)&&(angle4<=15))&&((angle5>=0)&&(angle5<=40)))
printfun('r');
//playSound(0x0209);

//s
if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=80)&&(angle3<=90))&&((angle4>=80)&&(angle4<=90))&&((angle5>=60)&&(angle5<=80)))
playSound(0x0301);

//t
if(((angle1>=40)&&(angle1<=61))&&((angle2>=72)&&(angle2<=84))&&((angle3>=45)&&(angle3<=65))&&((angle4>=44)&&(angle4<=63))&&((angle5>=65)&&(angle5<=86))&&(digitalRead(6)==HIGH))
playSound(0x0302);

//u
if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80)))
playSound(0x0303);

//v
if(((angle1>=70)&&(angle1<=90))&&((angle2>=80)&&(angle2<=90))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80))&&(digitalRead(6)==HIGH)) 
playSound(0x0304);

//w
if(((angle1>=70)&&(angle1<=90))&&((angle2>=0)&&(angle2<=10))&&((angle3>=0)&&(angle3<=10))&&((angle4>=0)&&(angle4<=10))&&((angle5>=60)&&(angle5<=80)))
playSound(0x0305);

//x
if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=80)&&(angle4<=89))&&((angle5>=45)&&(angle5<=80)))//&&!(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
playSound(0x0306);

//y
if(((angle1>=0)&&(angle1<=10))&&((angle2>=70)&&(angle2<=90))&&((angle3>=60)&&(angle3<=80))&&((angle4>=80)&&(angle4<=90))&&((angle5>=15)&&(angle5<=35)))
playSound(0x0307);

//z
if(((angle1>=50)&&(angle1<=72))&&((angle2>=45)&&(angle2<=90))&&((angle3>=35)&&(angle3<=75))&&((angle4>=0)&&(angle4<=10))&&((angle5>=45)&&(angle5<=80))&&(((xadc>=412)&&(xadc<=418))&&((yadc>=340)&&(yadc<=360))))
playSound(0x0308);

  

delay(5000);

}

//----------------------END-----------------------------