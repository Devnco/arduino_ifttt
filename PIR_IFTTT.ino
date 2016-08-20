#include <Wire.h>
#include <Ciao.h>
 
#define CONNECTOR     "rest" 
#define SERVER_ADDR   "maker.ifttt.com"
#define APIKEY_IFTTT  "YOUR_KEY"
#define IFTTT_ACTION  "YOUR_ACTION"

int ledPin = 13; 
 
void setup() {
 
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
  Ciao.begin();
}
 
void loop() {
    Serial.print(".");
    delay(50);
    if(digitalRead(6) == 1){
        Serial.println("ALERTE !");
        delay(5000);
        if(digitalRead(6) == 1){
            digitalWrite(ledPin, HIGH);
            sendNotification();
            digitalWrite(ledPin, LOW);
        }
    }
}

void sendNotification() {
    //https://maker.ifttt.com/trigger/button_pressed/with/key/YOUR_KEY/value1=XXX&value2=XXX&value3=XXX    
    String uri = "/trigger/";
    uri += IFTTT_ACTION;
    uri += "/with/key/";
    uri += APIKEY_IFTTT;
    uri += "?value1=YOUR_VALUE";
    Ciao.println("Send data on IFTTT Channel"); 
    Serial.println("Send data on IFTTT Channel"); 
    CiaoData data = Ciao.write(CONNECTOR, SERVER_ADDR, uri);
    if (!data.isEmpty()){
      Ciao.println( "State: " + String (data.get(1)) );
      Serial.println( "State: " + String (data.get(1)) );
      Ciao.println( "Response: " + String (data.get(2)) );
      Serial.println( "Response: " + String (data.get(2)) );
    }
    else{ 
      Serial.println("Error");
      Ciao.println("Error");
    } 
}