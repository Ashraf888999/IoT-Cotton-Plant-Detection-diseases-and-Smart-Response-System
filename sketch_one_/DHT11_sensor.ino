
#include <DHT.h>



DHT dht(DHTPIN, DHTTYPE);  // Initialize the DHT sensor

void setup() {
  Serial.begin(9600);  // Initialize serial communication
  dht.begin();         // Initialize the DHT sensor
}

void loop() {
  delay(2000);                     // Delay for 2 seconds
  
  float temperature = dht.readTemperature();     // Read temperature in Celsius
  float humidity = dht.readHumidity();           // Read humidity in percentage
  
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // You can also send the readings to an external server or perform other actions with the values
  
}

