#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);
volatile int button = 2;
int sensorLevel = 0;
int sensor = 0;
String value = "";
int ack = 0;

const String trigger = "3";

void setup() {
  // initialize digital pin 8 as an output.

  Serial.begin(9600);
  BTserial.begin(38400);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), buttonPressed, CHANGE);
}

void loop() {
  value = BTserial.readString();
  //Serial.println(value);
  if (value == trigger) {
    ack = 1;
    
  }
  else if (value == "3OK") {
    ack = 0;
    BTserial.println(ack);
    //sensorLevel = 0;
  }
  //Serial.println(ack);
  if (ack == 1) {
    BTserial.println(sensorLevel);
    //Serial.println("here");
    delay(10);
  }

}

void buttonPressed(){
  sensor = digitalRead(button);
  if (sensor == HIGH) {
    sensorLevel ++;
    delay(10);
  }
}
