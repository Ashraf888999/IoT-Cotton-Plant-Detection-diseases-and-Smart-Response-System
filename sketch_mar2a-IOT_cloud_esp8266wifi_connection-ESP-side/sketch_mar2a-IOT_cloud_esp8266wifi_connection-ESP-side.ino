#include <ESP8266WiFi.h>
#include <WiFiClient.h>

const char* ssid = "Elshami";
const char* password = "l4070245";
const char* secretKey = "xCgHPebWs8kyIS4Uwm2vTTwqP"; // Replace "YOUR_SECRET_KEY" with your actual Secret Key
const char* deviceID = "609d46de-dd74-4920-85d5-64a92d614f3b"; // Replace "YOUR_DEVICE_ID" with your actual Device ID

WiFiServer server(80); // Create a server on port 80

void setup() {
  Serial.begin(9600); // Initialize serial communication
  delay(100);

  // Connect to Wi-Fi network
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

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available(); // Check for incoming clients

  if (client) {
    Serial.println("New client connected");
    while (client.connected()) {
      if (client.available()) {
        String request = client.readStringUntil('\r'); // Read the incoming data
        Serial.print("Received from Arduino: ");
        Serial.println(request);
        // Process the received data as needed
        
        // Send response back to the client (optional)
        client.println("Data received by ESP8266");
        break;
      }
    }
    client.stop(); // Close the connection
    Serial.println("Client disconnected");
  }
}