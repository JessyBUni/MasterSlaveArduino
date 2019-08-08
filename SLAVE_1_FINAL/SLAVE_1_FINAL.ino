#include <SoftwareSerial.h>
SoftwareSerial BTserial(10, 11);
int LRDSensor = A2 ;
int sensorLevel=0;
int ack =0;
String value = "";

void setup() {
  // initialize digital pin 8 as an output.
  Serial.begin(9600);
  BTserial.begin(38400);
  pinMode(LRDSensor,INPUT);
}

void loop() {
  sensorLevel= analogRead(LRDSensor);
  //Serial.println(sensorLevel);
  //if (BTserial.available()>0){
    value=BTserial.readString();
    //Serial.println(ack);
    if (value =="1"){
      ack =1;
    }
    if(ack==1){
      BTserial.println(sensorLevel);
      Serial.println(sensorLevel);
      delay(10);
    }
    if (value == "1OK"){
      ack =0;
      BTserial.println(ack);
    }
  //}
}
  /*state = BTserial.readString(); // Reads the data from the serial port
  Serial.println(state);
  if (state.equals("1")){
    comstatus = SENDING;
    Serial.println("hep");
      while(comstatus == SENDING){
         Serial.println("hep");
        BTserial.println(sensorLevel);
        delay(10);
        state = BTserial.readString();
          if (state.equals("1OK")){
            comstatus=RECEIVING;
          }
      }
   BTserial.println(sensorLevel);
    state="";
  }
}*/
