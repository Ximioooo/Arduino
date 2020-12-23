/*
 * Unity Control Arduino
 * .BikeSpeed
 * .FloralArea
 * 
 * Bluetooth
 * HC-05
 */
#include <SoftwareSerial.h>

/* Bluetooth */
SoftwareSerial BTSerial(10,11);

/* L298N */
//FanSpeed
const int EnA=9;
const int in1=8;
const int in2=7;
//FloralArea
const int EnB=3;
const int in3=5;
const int in4=4;

/* RGB LED */
const int Red=A1;
const int Green=A0;
const int Blue=A2;

/* received Data from Unity*/
String msg;
const char ecomChar='\n';
int Speed=0;

// SHOW color
int EndV=0;
int StarV=150;


void setup() {
  BTSerial.begin(38400);

  pinMode(Red,OUTPUT);
  pinMode(Green,OUTPUT);
  pinMode(Blue,OUTPUT);

  pinMode(EnA,OUTPUT);
  pinMode(EnB,OUTPUT);
  pinMode(in1,OUTPUT);
  pinMode(in2,OUTPUT);
  pinMode(in3,OUTPUT);
  pinMode(in4,OUTPUT);

  BTSerial.setTimeout(100);
}

void loop() {
  while(BTSerial.available()>0){
    msg=BTSerial.readStringUntil(ecomChar);

    if(msg == "on"){
      for(int i=105;i<256;i+=30){
        digitalWrite(in3,HIGH);
        digitalWrite(in4,LOW);

        analogWrite(EnB,i);
      }
    }
    else if(msg == "off"){
        digitalWrite(in3,LOW);
        digitalWrite(in4,LOW);

        analogWrite(EnB,0);
    }
    else if(msg == "disable"){
      digitalWrite(in1,LOW);
      digitalWrite(in2,LOW);
      digitalWrite(in3,LOW);
      digitalWrite(in4,LOW);

      analogWrite(Red,EndV);
      analogWrite(Green,EndV);
      analogWrite(Blue,EndV);
    }
    else{
      Speed=msg.toInt();
      FanSpeed(Speed);
    }
    delay(10);
    msg="";
  }
}

void FanSpeed(int n){
 
  if(n>30 && n<=60){
    //RGB light blue color
    analogWrite(Red,EndV);
    analogWrite(Green,StarV);
    analogWrite(Blue,StarV);

    //FanSpeed:75
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(EnA,75);
  }
  else if(n>60 && n<=120){
    //RGB Yellow color
    analogWrite(Red,StarV);
    analogWrite(Green,StarV);
    analogWrite(Blue,EndV);

    //FanSpeed:127
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(EnA,127);
  }
  else if(n>120 && n<=180){
    //RGB Red color
    analogWrite(Red,StarV);
    analogWrite(Green,EndV);
    analogWrite(Blue,EndV);

    //FanSpeed:191
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(EnA,191);
    
  }
  else if(n>180){
    //RGB Blue color
    analogWrite(Red,StarV);
    analogWrite(Green,StarV);
    analogWrite(Blue,StarV);

    //FanSpeed:255
    digitalWrite(in1,HIGH);
    digitalWrite(in2,LOW);
    analogWrite(EnA,255);
  }
  else{
    //RGB
    analogWrite(Red,EndV);
    analogWrite(Green,EndV);
    analogWrite(Blue,EndV);

    //FanSpeed:0
    digitalWrite(in1,LOW);
    digitalWrite(in2,LOW);
    analogWrite(EnA,0);
  }
}
