#include <SoftwareSerial.h>
SoftwareSerial BT(12, 11); 

int pwmMotorA=6;
int InMotorA1=9;
int InMotorA2=8;

int pwmMotorB=5;
int InMotorB1=3;
int InMotorB2=4;

int motoPower=7;

char polecenie;
 
void setup() {
  
  BT.begin(9600);

  //Mostek-h
  pinMode(7, OUTPUT);
  digitalWrite(7, HIGH);
  //buzzer
  pinMode(10, OUTPUT); 
  digitalWrite(10, LOW);
  
  //Wyjście PWM kanału A
  pinMode(pwmMotorA, OUTPUT);   
  //Wyjście cyfrowe AIN1
  pinMode(InMotorA1, OUTPUT); 
  //Wyjście cyfrowe AIN2
  pinMode(InMotorA2, OUTPUT);   
 
   //Wyjście PWM kanału B
  pinMode(pwmMotorB, OUTPUT);   
  //Wyjście cyfrowe BIN1
  pinMode(InMotorB1, OUTPUT); 
  //Wyjście cyfrowe BIN2
  pinMode(InMotorB2, OUTPUT); 

   
}

void loop() {
  
  if (BT.available())
  {
    polecenie=(BT.read());
    
    if (polecenie=='0') 
    {
    analogWrite(pwmMotorA,0);
    analogWrite(pwmMotorB,0); 
    BT.println("Stop!");
    } 
    if (polecenie=='1') 
    {
    analogWrite(pwmMotorA,255);
    analogWrite(pwmMotorB,255);   
    digitalWrite(InMotorA1, HIGH); 
    digitalWrite(InMotorA2, LOW);
   
    digitalWrite(InMotorB1, HIGH); 
    digitalWrite(InMotorB2, LOW); 
    BT.println("Do przodu!");
    }  
    
    if (polecenie=='2') 
    {
    analogWrite(pwmMotorA,255);
    analogWrite(pwmMotorB,255);   
    digitalWrite(InMotorA1, LOW); 
    digitalWrite(InMotorA2, HIGH);
  
    digitalWrite(InMotorB1, LOW); 
    digitalWrite(InMotorB2, HIGH);
    BT.println("Do tylu!");
    } 
    if (polecenie=='3') 
    {  
    BT.println("BEEP!");    
    digitalWrite(10, HIGH);
    }
    if (polecenie=='4') digitalWrite(10, LOW);
    if (polecenie=='5') 
    {
    analogWrite(pwmMotorA,255);
    analogWrite(pwmMotorB,255);   
    digitalWrite(InMotorA1, LOW); 
    digitalWrite(InMotorA2, HIGH);
  
    digitalWrite(InMotorB1, HIGH); 
    digitalWrite(InMotorB2, LOW);
    BT.println("W prawo!");
    }
   if (polecenie=='6') 
    {
    analogWrite(pwmMotorA,255);
    analogWrite(pwmMotorB,255);   
    digitalWrite(InMotorA1, HIGH); 
    digitalWrite(InMotorA2, LOW);
  
    digitalWrite(InMotorB1, LOW); 
    digitalWrite(InMotorB2, HIGH);
    BT.println("W lewo!");
    }   
    
  }

} 
