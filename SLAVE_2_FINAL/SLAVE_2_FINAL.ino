#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);
int button = 2;
String sensorLevel = "OFF";
int sensor = 0;
String value = "";
int ack =0;

const String trigger ="2";

void setup() {
  // initialize digital pin 8 as an output.

  Serial.begin(9600);
  BTserial.begin(38400);
  pinMode(button, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(button), buttonPressed, CHANGE);
}

void loop() {
  value = BTserial.readString();
  Serial.println(value);
  if (value==trigger){
    ack =1;
  }
  else if (value == "2OK") {
    ack = 0;
    BTserial.println(ack);
    sensorLevel = "OFF";
  }
  //Serial.println(ack);
  if (ack == 1) {
      BTserial.println(sensorLevel);
    delay(10);
  }

}
void buttonPressed(){
  sensor = digitalRead(button);
  if (sensor == HIGH) {
    sensorLevel ="ON";
  }
}
