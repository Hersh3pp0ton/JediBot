#include <MeMCore.h>
#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include "src/bluetoothhc.h"
#include "src/HC06.h"

BluetoothClassHC bluetoothhc;

MeRGBLed rgbled_7(7, 2);

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

String carattere = "";
int speed = 150;

void move(int direction, int speed) {
  int leftSpeed = 0;
  int rightSpeed = 0;

  if(direction == 1) {
    leftSpeed = speed;
    rightSpeed = speed;
  } else if(direction == 2) {
    leftSpeed = -speed;
    rightSpeed = -speed;
  } else if(direction == 3) {
    leftSpeed = -speed;
    rightSpeed = speed;
  } else if(direction == 4) {
    leftSpeed = speed;
    rightSpeed = -speed;
  }
  motor_9.run((9) == M1 ? -(leftSpeed) : (leftSpeed));
  motor_10.run((10) == M1 ? -(rightSpeed) : (rightSpeed));
}

void setup() {
  Serial.begin(9600); 
  
  bluetoothhc.inithc(0,1,"BTSlave",1234);

  rgbled_7.fillPixelsBak(0, 2, 1);
  rgbled_7.setColor(0, 51, 0, 255);
  rgbled_7.show();
}

void loop() {
  if (bluetoothhc.dataLineAvailableHc()) {
    carattere = bluetoothhc.readDataLineHc();

    rgbled_7.setColor(0, 255, 0, 0);
    rgbled_7.show();

    delay(200);

    rgbled_7.setColor(0, 0, 0, 0);
    rgbled_7.show();

    Serial.print("Carattere: ");
    Serial.println(carattere);
    
    if(carattere == "f") {
      move(1, speed);
      delay(3);
      move(1, 0);
    } else if(carattere == "b") {
      move(2, speed);
      delay(3);
      move(2, 0);
    } else if(carattere == "l") {
      move(3, speed);
      delay(3);
      move(3, 0);
    } else if(carattere == "r") {
      move(4, speed);
      delay(3);
      move(4, 0);
    }
  }

  _loop();
}

void _loop() {
  bluetoothhc.bluetoothLoopHc();
}
