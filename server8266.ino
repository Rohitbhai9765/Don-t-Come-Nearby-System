#include <ESP8266WiFi.h>

const char* ssid = "YourDaddy";
const char* password = "yourdaddy";

WiFiServer server(80);
String receivedData = "";

void setup() {
  Serial.begin(9600);  // NodeMCU's serial for communication with Uno
  WiFi.softAP(ssid, password);
  Serial.println("Access Point started");

  server.begin();
  Serial.println("Server started");
}

void loop() {
  // Read data from Arduino Uno
  while (Serial.available()) {
    receivedData = Serial.readStringUntil('\n');
    Serial.println("Data received: " + receivedData);
  }

  // Handle client requests
  WiFiClient client = server.available();
  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {
      if (client.available()) {
        client.readStringUntil('\r');
        client.flush();

        // Respond with the received data
        client.print("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        client.print("<!DOCTYPE html><html><head><title>ESP8266 Server</title></head>");
        client.print("<body><h1>Data from Arduino</h1>");
        client.print("<body><h2>This is the data</h2>");
        client.print("<p>" + receivedData + "</p></body></html>");
        break;
      }
    }
    client.stop();
    Serial.println("Client disconnected");
  }
}
