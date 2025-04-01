#include <MeMCore.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(0, 1);
MeRGBLed rgbled_7(7, 2);

MeUltrasonicSensor ultrasonic_1(1);

MeBuzzer buzzer;

MeDCMotor motor_9(9);
MeDCMotor motor_10(10);

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
  Serial.begin(115200);
  bluetoothSerial.begin(115200);
  
  rgbled_7.fillPixelsBak(0, 2, 1);
  rgbled_7.setColor(0, 0, 0, 0);
  rgbled_7.show();
}

void loop() {
  int distanza = ultrasonic_1.distanceCm(); 

  if(distanza < 20){
    buzzer.tone(988, 0.25 * 1000);
  }

  if (bluetoothSerial.available()) {
    char receivedChar = bluetoothSerial.read();
    
    if (receivedChar == '\r' || receivedChar == '\n') {
      return;
    }
    
    if (receivedChar == 'f') {
      rgbled_7.setColor(0, 0, 255, 0);
      rgbled_7.show();
      move(1, 90 / 100.0 * 255);
      delay(1000);
      move(1, 0);
    } else if (receivedChar == 'b') {
      rgbled_7.setColor(0, 255, 0, 0);
      rgbled_7.show();
      move(2, 90 / 100.0 * 255);
      delay(1000);
      move(2, 0);
    } else if (receivedChar == 'l') {
      rgbled_7.setColor(0, 0, 0, 255);
      rgbled_7.show();
      move(3, 80 / 100.0 * 255);
      delay(500);
      move(3, 0);
    } else if (receivedChar == 'r') {
      rgbled_7.setColor(0, 255, 255, 0);
      rgbled_7.show();
      move(4, 80 / 100.0 * 255);
      delay(500);
      move(4, 0);
    }
    delay(200);
  }
}
