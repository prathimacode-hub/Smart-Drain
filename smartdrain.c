#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

#define analogPin A0// water sensor connected to the analog port 1
int waterval = 0; // definition variable val initial value as 0
int pirSensor = 2;
int flag1=0,flag2=0;

void setup ()
{

mySerial.begin(9600);
pinMode(pirSensor, INPUT);
pinMode (5, OUTPUT);// definition led as output pin
digitalWrite(5,LOW);
Serial. begin (9600); // set the baud rate as 9600
}

void loop ()
{
int sensorValue = digitalRead(pirSensor);
Serial.println(sensorValue);
delay(3000);
if (sensorValue == 1) 
{
  flag1=1; // Motion detected
}
waterval = analogRead (analogPin); // read the simulation value and send to variable val
Serial.println(waterval);
delay(1000);
if (waterval >200) 
{
flag2=1;
}
if(flag1==1&&flag2==1)
{
  SendMessage();
  SendMessage2();
  exit(1);
}
if(flag1==1)
{ digitalWrite(5,HIGH);
  SendMessage2();
  exit(1);
}
else if(flag2==1)
{
  SendMessage();
  exit(1);
}
}
 
 void SendMessage()
      {
         mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
         delay(1000);  // Delay of 1000 milli seconds or 1 second
         mySerial.println("AT+CMGS=\"+919876543210\"\r"); // Replace x with mobile number
         delay(1000);
         mySerial.println("Overflow warning!!");// The SMS text you want to send
         delay(100);
         mySerial.println((char)26);// ASCII code of CTRL+Z
         delay(1000);
      }

 void SendMessage2()
      {
         mySerial.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
         delay(1000);  // Delay of 1000 milli seconds or 1 second
         mySerial.println("AT+CMGS=\"+919876543210\"\r"); // Replace x with mobile number
         delay(1000);
         mySerial.println("Manhole lid missing!!");// The SMS text you want to send
         delay(100);
         mySerial.println((char)26);// ASCII code of CTRL+Z
         delay(1000);
      }
