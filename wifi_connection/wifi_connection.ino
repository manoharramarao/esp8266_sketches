/* Connects to given wifi and get the data from a website over http by connecting to the website over port 80 */

#include <ESP8266WiFi.h>

#define WLAN_SSID "ssid"
#define WLAN_PWD "password"

const char* host = "makerdemy.com";

void setup()
{
	Serial.begin(115200);
	delay(5000);

	// connecting to wifi
	Serial.print("connecting to ");
	Serial.println(WLAN_SSID);

	WiFi.begin(WLAN_SSID, WLAN_PWD);

	// Wait until connected
	while(WiFi.status() != WL_CONNECTED){
	    delay(500);
	    Serial.print(".");
	}

	Serial.println("");
	Serial.print("Connected to wifi with IP ");
	Serial.println(WiFi.localIP());

	// connect to the site defined in "host" on port 80
	WiFiClient client;
	if(!client.connect(host, 80)){
		Serial.println("Connection failed");
	}

	Serial.println("Connected to host - sending request...");

	client.print(String("GET /code/esp8266.html HTTP/1.1\r\n") + 
		"Host: " + host + "\r\n" + 
		"Connection: close\r\n\r\n");

	Serial.println("request sent - waiting for reply...");
	delay(10);

	// read the response and flush it to serial output
	while(client.available()){
		String line = client.readStringUntil('\r');
		Serial.print(line);
	}

	Serial.println();
	Serial.println("Connection closed.");
}

void loop()
{
	
}


