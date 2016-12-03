/*
  This program was taken from https://www.baldengineer.com/mqtt-tutorial.html
*/
#include "Arduino.h"
#include "PubSubClient.h"
#include "ESP8266WiFi.h"

#define SSID "ssid"
#define PWD "password"

void callback(char* topic, byte* payload, unsigned int length){
  Serial.print("Message arrived[");
  Serial.print(topic);
  Serial.print("]");
  for(int i=0; i<length; i++){
    char receivedChar = (char)payload[i];
    Serial.print(receivedChar);
    if(receivedChar == '0'){
      digitalWrite(LED_BUILTIN, HIGH);
    }else if(receivedChar == '1'){
      digitalWrite(LED_BUILTIN, LOW);
    }
  }
  Serial.println();
}

WiFiClient espClient;
PubSubClient mqttClient(espClient);

void reconnect(){
  // Loop until we are reconnected
  while(!mqttClient.connected()){
    Serial.print("Attempting MQTT connection ...");
    // Attempt to connect
    if (mqttClient.connect("ESP8266 Client")){
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqttClient.publish("outTopic", "Registered with mqtt broker");
      // ... and resubscribe
      mqttClient.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 5 secs");
      // Wait 5 secs before retrying
      delay(5000);
    }
  }
}

void goOnAir(){
  if(WiFi.status() != WL_CONNECTED) {
    Serial.print("connecting to ");
    Serial.println(SSID);
    WiFi.begin(SSID, PWD);
  }
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("connected to wifi with IP ");
  Serial.println(WiFi.localIP());
}

void setup(){
  Serial.begin(57600);
  // connect to wifi
  goOnAir();
  mqttClient.setServer("192.168.1.6", 1883);
  mqttClient.setCallback(callback);
  pinMode(LED_BUILTIN, OUTPUT);
  delay(1500);
}

void loop(){
  if(!mqttClient.connected()){
    reconnect();
  }
  mqttClient.loop();
}
