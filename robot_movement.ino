#include<SoftwareSerial.h>
SoftwareSerial mySerial(2,3);//GSM Rx TX
#include<Keypad.h>
#include<LiquidCrystal.h>
const int rs = 48, en = 49, d4 = 50, d5 = 51, d6 = 52, d7 = 53;
LiquidCrystal lcd(rs,en,d4,d5,d6,d7);
 //Motor Pins
 const int M1=22;
const int M11=24;
const int M12=26;

const int M2=32;
const int M21=28;
const int M22=30;

const int M3=34;
const int M31=36;
const int M32=38;

const int M4=44;
const int M41=40;
const int M42=42;
//RF Pins
const int RF1=A8;
const int RF2=A9;

const int RF3=A10;
const int RF4=A11;

const int LDR=A12;//LDR
const int Alc=A13;//Alcohol Sensor
const int LS=A14;//Limit Switch

const int headLight1=23;
const int headLight2=25;
const int Buzz=27;

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {1,2,3},
  {4,5,6},
  {7,8,9},
  {11,10,12}
  };
byte rowPins[ROWS] = {33,35,37,39};
byte colPins[COLS] = {41,43,45,47};
Keypad customKeypad = Keypad(makeKeymap(hexaKeys),rowPins,colPins,ROWS,COLS);
int pass = 0;
int mani = 1326;
void setup() {
  // put your setup code here, to run once:
  mySerial.begin(9600);
  lcd.begin(16,2);
  delay(10);
pinMode(M11,OUTPUT);
pinMode(M12,OUTPUT);
pinMode(M21,OUTPUT);
pinMode(M22,OUTPUT);
pinMode(M31,OUTPUT);
pinMode(M32,OUTPUT);
pinMode(M41,OUTPUT);
pinMode(M42,OUTPUT);

pinMode(headLight1,OUTPUT);
pinMode(headLight2,OUTPUT);
pinMode(Buzz,OUTPUT);

pinMode(RF1,INPUT);
pinMode(RF2,INPUT);
pinMode(RF3,INPUT);
pinMode(RF4,INPUT);

pinMode(LDR,INPUT);
pinMode(Alc,INPUT);
pinMode(LS,INPUT);
digitalWrite(Buzz,LOW);
Serial.begin(9600);
Stop();
lcd.setCursor(0,0);
lcd.print("Enter Password");
}
int a=0;
void loop() {
  // put your main code here, to run repeatedly:
  while(a!=12)
  {
    a=customKeypad.getKey();
    if(a){
      if(a<=10)
      {
        if(a<10)
        {
          pass=pass*10+a;
          lcd.clear();
          delay(10);
          lcd.setCursor(5,1);
          lcd.print(pass);
        }
        else
        {
          a=0;
          pass=pass*10+a;
          lcd.clear();
          delay(10);
          lcd.setCursor(5,1);
          lcd.print(pass);
          }
        }
        else if(a==12)
        {
          break;
          }
      }
    }
  if (pass==mani)
  {
    
          lcd.clear();
          delay(10);
          lcd.setCursor(0,1);
          lcd.print("Welcome");
int Light = digitalRead(LDR);
if (Light==HIGH)
{
  digitalWrite(headLight1,HIGH);
  digitalWrite(headLight2,HIGH);
  }
  else
  {
    digitalWrite(headLight1,LOW);
    digitalWrite(headLight2,LOW);
    }
int D1=digitalRead(RF1);
int D2=digitalRead(RF2);
int D3=digitalRead(RF3);
int D4=digitalRead(RF4);
int DaruWala_Driver=digitalRead(Alc);
int Accident = digitalRead(LS);
Serial.println(Accident);
if ((Accident==HIGH)&&(DaruWala_Driver==HIGH))
{
  
  digitalWrite(Buzz,LOW);
if((D1==HIGH)&&(D2==LOW)&&(D3==HIGH)&&(D4==LOW))
{
  forward();
  }
else if((D1==LOW)&&(D2==HIGH)&&(D3==LOW)&&(D4==HIGH))
{
  backward();
  }
  else if((D1==LOW)&&(D2==LOW)&&(D3==HIGH)&&(D4==LOW))
{
  left();
  }
  else if((D1==HIGH)&&(D2==LOW)&&(D3==LOW)&&(D4==LOW))
{
  right();
  }
  else{
    Stop();
    }
}

else if (Accident==LOW)
{
  digitalWrite(Buzz,HIGH);
  Stop();
  SendMessageAccident();
  while(Accident==LOW)
  {
    Accident=digitalRead(LS);
    }
  }
  else if (DaruWala_Driver==LOW)
{
  digitalWrite(Buzz,HIGH);
  Stop();
  SendMessageDrunk();
  while(DaruWala_Driver==LOW)
  {
    DaruWala_Driver=digitalRead(Alc);
    }
  }
  }
  else
  {
    //wrong passs
    
          lcd.clear();
          delay(10);
          lcd.setCursor(0,1);
          lcd.print("Wrong Password");
          delay(2000);
          a=0;
    }
}
void forward()
{
  analogWrite(M1,150);
  analogWrite(M2,150);
  analogWrite(M3,150);
  analogWrite(M4,150);
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  digitalWrite(M31,HIGH);
  digitalWrite(M32,LOW);
  digitalWrite(M41,HIGH);
  digitalWrite(M42,LOW);
  }
  void backward()
{
  
  analogWrite(M1,150);
analogWrite(M2,150);
analogWrite(M3,150);
analogWrite(M4,150);
  digitalWrite(M11,LOW);
  digitalWrite(M12,HIGH);
  digitalWrite(M21,LOW);
  digitalWrite(M22,HIGH);
  digitalWrite(M31,LOW);
  digitalWrite(M32,HIGH);
  digitalWrite(M41,LOW);
  digitalWrite(M42,HIGH);
  }
  void left()
{
  analogWrite(M1,150);
analogWrite(M2,150);
analogWrite(M3,0);
analogWrite(M4,0);
  digitalWrite(M11,HIGH);
  digitalWrite(M12,LOW);
  digitalWrite(M21,HIGH);
  digitalWrite(M22,LOW);
  digitalWrite(M31,LOW);
  digitalWrite(M32,LOW);
  digitalWrite(M41,LOW);
  digitalWrite(M42,LOW);
  }
  void right()
{
  analogWrite(M1,0);
analogWrite(M2,0);
analogWrite(M3,150);
analogWrite(M4,150);
  digitalWrite(M11,LOW);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,LOW);
  digitalWrite(M31,HIGH);
  digitalWrite(M32,LOW);
  digitalWrite(M41,HIGH);
  digitalWrite(M42,LOW);
  }
  void Stop()
{
  analogWrite(M1,0);
analogWrite(M2,0);
analogWrite(M3,0);
analogWrite(M4,0);
  digitalWrite(M11,LOW);
  digitalWrite(M12,LOW);
  digitalWrite(M21,LOW);
  digitalWrite(M22,LOW);
  digitalWrite(M31,LOW);
  digitalWrite(M32,LOW);
  digitalWrite(M41,LOW);
  digitalWrite(M42,LOW);
  }
  void SendMessageAccident()
  {
    mySerial.println("AT+CMGF=1");
    delay(1000);
    mySerial.print("AT+CMGS=");
    mySerial.print('"');
    mySerial.print("7062268805");
    mySerial.println('"');
    delay(1000);
    mySerial.print("Accident Took Place");
    delay(100);
    mySerial.println((char)26);
    delay(1000);
    }
    void SendMessageDrunk()
  {
    mySerial.println("AT+CMGF=1");
    delay(1000);
    mySerial.print("AT+CMGS=");
    mySerial.print('"');
    mySerial.print("7062268805");
    mySerial.println('"');
    delay(1000);
    mySerial.print("Driver ne pi li h");
    delay(100);
    mySerial.println((char)26);
    delay(1000);
    }
    void SendMessageTheft()
  {
    mySerial.println("AT+CMGF=1");
    delay(1000);
    mySerial.print("AT+CMGS=");
    mySerial.print('"');
    mySerial.print("7062268805");
    mySerial.println('"');
    delay(1000);
    mySerial.print("Somebody Trying to unlock");
    delay(100);
    mySerial.println((char)26);
    delay(1000);
    }
