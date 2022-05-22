#include "SoftwareSerial.h" // TX RX software library for bluetooth
#include "HCPCA9685.h"
#define  I2CAdd 0x40
HCPCA9685 HCPCA9685(I2CAdd);


int bluetoothTx = 1; // bluetooth tx to 10 pin
int bluetoothRx = 0; // bluetoollkth rx to 11 pin

int armBase[10] = {50, 90, 130, 170, 210, 250, 290, 330, 370, 410, 450};
int armVert[10] = {50, 85, 120, 155, 190, 225, 260, 295, 330, 365, 400};
int handVert[10] = {30, 73, 116, 159, 202, 245, 288, 331, 374, 417, 460};
int handSqueeze[10] = {-4,-2, 0, 2, 4, 6, 8, 10, 12, 14};

int motor1Pin1 = 6; 
int motor1Pin2 = 7; 
int motor1EnablePin = 9; 
int motor2Pin1 = 4; 
int motor2Pin2 = 5; 
int motor2EnablePin = 10; 

int state;
int speedHigh = 100; 
int speedLow = 25;
int flag=0;        
int stateStop=0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

void setup()
{
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor1EnablePin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  HCPCA9685.Init(SERVO_MODE);
  HCPCA9685.Sleep(false);
  //Setup usb serial connection to computer
  Serial.begin(9600);
  
  //Setup Bluetooth serial connection to android
  bluetooth.begin(9600);
}

void loop()
{
  //Read from bluetooth and write to usb serial
  if(bluetooth.available()>= 2 )
  {
    state = bluetooth.read();
    Serial.println(state);
    if (state == 1) {
        forword();
        if(flag == 0){
          Serial.println("Go Forward!");
          flag=1;
        }
    }
    
    // if the state is '2' the motor will turn left
    else if (state == 2) {
        turnLeft();
        if(flag == 0){
          Serial.println("Turn LEFT");
          flag=1;
        }
        delay(1500);
        state=3;
        stateStop=1;
    }
    // if the state is '3' the motor will Stop
    else if (state == 3 || stateStop == 1) {
        Stop();
        if(flag == 0){
          Serial.println("STOP!");
          flag=1;
        }
        stateStop=0;
    }
    // if the state is '4' the motor will turn right
    else if (state == 4) {
        turnRight();
        if(flag == 0){
          Serial.println("Turn RIGHT");
          flag=1;
        }
        delay(1500);
        state=3;
        stateStop=1;
    }
    // if the state is '5' the motor will Reverse
    else if (state == 5) {
        backword();
        if(flag == 0){
          Serial.println("Reverse!");
          flag=1;
        }
    }
    if (state >= 6 && state <16) {
      int servo1 = state;
      HCPCA9685.Servo(3, servo1);
      Serial.println("Servo 1 ON");
      delay(10);
    }
    if (state >= 16 && state <26) {
      int servo2 = state;
      HCPCA9685.Servo(7, servo2);
      Serial.println("Servo 2 ON");
      delay(10);
    }
    if (state >= 26 && state <35) {
      int servo3 = state;
      HCPCA9685.Servo(11, servo3);
      Serial.println("Servo 3 ON");
      delay(10);
    }
    if (state >= 35 && state <46) {
      int servo4 = state;
      HCPCA9685.Servo(15, servo4);
      Serial.println("Servo 4 ON");
      delay(10);
    }
  }
}
void forword(){
    digitalWrite(motor1Pin1, HIGH); //HIGH
    digitalWrite(motor1Pin2, LOW);  //LOW
    digitalWrite(motor2Pin1, LOW);  //LOW
    digitalWrite(motor2Pin2, HIGH); //HIGH
    analogWrite(motor1EnablePin, Speed);
    analogWrite(motor2EnablePin, Speed);
    //Serial.println("Go Forward!");
}

void backword(){
    digitalWrite(motor1Pin1, LOW); //
    digitalWrite(motor1Pin2, HIGH); 
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(motor1EnablePin, Speed);
    analogWrite(motor2EnablePin, Speed);
    //Serial.println("Go Reverse!");

}
//
void turnRight(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    analogWrite(motor1EnablePin, Speed);
    analogWrite(motor2EnablePin, Speed);
    //Serial.println("Turn Right");

}

void turnLeft(){
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(motor1EnablePin, Speed);
    analogWrite(motor2EnablePin, Speed);
    //Serial.println("Turn Left");

}

void Stop(){
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW); 
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(motor1EnablePin, Speed);
    analogWrite(motor2EnablePin, Speed);
    //Serial.println("Stop");

}
