//#include <AltSoftSerial.h>

#include <SoftwareSerial.h>
SoftwareSerial BTserial1(10, 11);
SoftwareSerial BTserial2(5, 6);
SoftwareSerial BTserial3(3, 9);
int state = 0;
const int READYTOSEND = 0;
const int WAITING = 1;

String input = "";

int sensorCount = 0;
int sentCount = 0;
int receivedCount = 0;

char element = '0';
String serialInput = "";
int errorCount = 0;
int sensorFile[10];
void setup() {

  Serial.begin(9600);
  BTserial1.begin(38400);
  BTserial2.begin(38400);
  BTserial3.begin(38400);
  //pinMode(buttonPin, INPUT);
  Serial.println("Which sensor would you like information from? (For multiple elements please seperate with a ';')");
}

void loop() {
  if (Serial.available()) {
    serialInput = Serial.readString();
    Serial.print("You typed: " );
    Serial.println(serialInput);
    int l = serialInput.length();
    for (int i = 0; i < l - 1; i = i + 2) {
      element = serialInput.charAt(i);
      //make sure bad elements don't get sent
      //Serial.println(element);
      if (element == '1') {
        sensorFile[sensorCount] = 1;
        sensorCount = sensorCount + 1;
      }
      else if (element == '2') {
        sensorFile[sensorCount] = 2;
        sensorCount = sensorCount + 1;
      }
      else if (element == '3') {
        sensorFile[sensorCount] = 3;
        sensorCount = sensorCount + 1;
      }
      else {
        Serial.print ( element);
        Serial.println (" <-- This element is not the name of a recognised sensor");
      }
    }
    serialInput = "";
    if (sensorCount == 0) {
      Serial.println("No valid sensor names were entered");
      Serial.println("Which sensor would you like information from? (For multiple elements please seperate with a ';')");
    }
  }

  //Serial.print ("SEnsor count is : ");
  //Serial.println(sensorCount);

  if (sentCount <= sensorCount) {
    if (sensorFile[sentCount] != NULL) {
      if (sensorFile[sentCount] == 1) {
         send_message(BTserial1, "1");
      }
      if (sensorFile[sentCount] == 2) {
        send_message(BTserial2, "2");

      }
      if (sensorFile[sentCount] == 3) {
        send_message(BTserial3, "3");
      }
    }
  }

  if (receivedCount < sentCount) {
    if (state == WAITING) {
      // if there is a problem connecting to the sensor
      if (errorCount == 10) {
        Serial.print("ERROR RECEIVING DATA FROM SENSOR ");
        Serial.println(sensorFile[receivedCount]);
        sensorFile[receivedCount] = NULL;
        receivedCount ++;
        errorCount = 0;
      }
      errorCount ++;
      if (sensorFile[receivedCount] == 1) {
        receive_message( BTserial1, "1OK", 1);
      }
      else if (sensorFile[receivedCount] == 2) {
        receive_message( BTserial2, "2OK", 2);
      }
      else if (sensorFile[receivedCount] == 3) {
        receive_message( BTserial3, "3OK", 3);
      }
    }
    if (receivedCount == sentCount) {
      sensorCount = 0;
      sentCount = 0;
      receivedCount = 0;
      errorCount=0;
      state = READYTOSEND;
      Serial.println("--------------------------------------------------------------------------------------------------");
      Serial.println("Which sensor would you like information from? (For multiple elements please seperate with a ';')");
    }
  }
  //Serial.print ("receivedcount is : ");
  //Serial.println(receivedCount);
  //if ( receivedCount = )
}
void receive_message(SoftwareSerial BTConn, String ack, int sensor) {
  BTConn.listen();
  //test
  //input = BTConn.readStringUntil('\n');
  input = BTConn.readString();
  if (input.length() >= 3) {
    BTConn.print(ack);
    delay(10);
    BTConn.flush();
    Serial.print ("The value recieved from sensor ");
    Serial.print(sensor);
    //Serial.print(xval);
    Serial.print(" was : ");
    String fVal = getValue(input, '\n', 0);
    Serial.println(fVal);
    //state = READYTOSEND;
    sensorFile[receivedCount] = NULL;
    receivedCount++;
    input = "";
    errorCount=0;
  }
}
void send_message(SoftwareSerial BTConn, String message) {
  Serial.print("Sending message to Sensor ");
  Serial.println(sensorFile[sentCount]);
  BTConn.flush();
  BTConn.print(message);
  sentCount++;
  state = WAITING;
}
String getValue(String data, char separator, int index)
{
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data.length() - 1;

    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data.substring(strIndex[0], strIndex[1]) : "";
}
