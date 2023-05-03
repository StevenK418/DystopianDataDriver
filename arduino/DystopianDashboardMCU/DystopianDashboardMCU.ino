#include <ESP8266WiFi.h>
#include "environment.h"

const char* ssid     = SSID;
const char* password = PASSWORD;

//This is the IPV4 address of the network currently
const char* host = HOST;

# define sensorPin A0
const int R0 = 100000; 
const int B = 4275;   

void setup() {
pinMode(sensorPin, INPUT);
  
  Serial.begin(115200);
  delay(10);
  pinMode(A0, INPUT);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}


void loop() {
 delay(5000);
int val = analogRead(sensorPin);
float R = 1023.0/val-1.0;
R = R0*R;
float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15;
 Serial.print("connecting to ");
 Serial.println(host);

 // Use WiFiClient class to create TCP connections
 WiFiClient client;
 const int httpPort = 8081;
 if (!client.connect(host, httpPort)) {
  Serial.println("connection failed");
  return;
 }

 // We now create a URI for the request
 String url = "/";

 Serial.print("Requesting URL: ");
 Serial.println(url);

  //Data to send to the server
  String data = "temperature=" + String(temperature);

  Serial.print("Requesting POST: ");

  // Send request to the server:
  client.println("POST / HTTP/1.1");
  client.println("Host: server_name");
  client.println("Accept: */*");
  client.println("Content-Type: application/x-www-form-urlencoded");
  client.print("Content-Length: ");
  client.println(data.length());
  client.println();
  client.print(data);
  // This will send the request to the server
  //this is a get method working
  client.print(String("GET ") + url + " HTTP/1.1\r\n" + "Connection: close\r\n\r\n");

  unsigned long timeout = millis();
  while (client.available() == 0) 
  {
    if (millis() - timeout > 5000) 
    {
      Serial.println(">>> Client Timeout !");
      client.stop();
      return;
    }
  }

 //Read all the lines of the reply from server and print them to Serial
 while(client.available())
 {
  String line = client.readStringUntil('\r');
  Serial.print(line);
 }

 Serial.println();
 Serial.println("closing connection");
}