#define BLYNK_TEMPLATE_ID "TMPL2m0zj3ffy"
#define BLYNK_TEMPLATE_NAME "cropkeeper"
#define BLYNK_AUTH_TOKEN "milI53oqPeLXPrbyPWBR6pHgPFSVRQLO"

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "milI53oqPeLXPrbyPWBR6pHgPFSVRQLO"; // Replace with your Blynk authentication token
char ssid[] = "Elshami";  // Replace with your WiFi name
char pass[] = "l4070245";  // Replace with your WiFi password

BlynkTimer timer;

#define DHTPIN 27 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

#define WATER_SENSOR_PIN 32 // Water percentage sensor pin
#define WATER_PUMP_PIN 26 // Water pump control pin

void sendSensor()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  int waterSensorValue = analogRead(WATER_SENSOR_PIN);
  float waterPercentage = map(waterSensorValue, 0, 1023, 0, 100); // Map analog value to percentage
  
  int pumpState = digitalRead(WATER_PUMP_PIN);
  
  // Sending descriptive values to Blynk
  Blynk.virtualWrite(V0, temperature); // Sending temperature
  Blynk.virtualWrite(V1, humidity);    // Sending humidity
  Blynk.virtualWrite(V2, pumpState); // Sending pump state
  Blynk.virtualWrite(V3, waterPercentage); // Sending water percentage
  
  // Control LED color based on pump state
  if (pumpState == HIGH) {
    Blynk.virtualWrite(V2, 255); // Set LED color to red (max brightness)
  } else {
    Blynk.virtualWrite(V2, 0); // Set LED color to off (min brightness)
  }
  
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print("    Humidity : ");
  Serial.print(humidity);
  Serial.print("    Pump State : ");
  Serial.print(pumpState == HIGH ? "ON" : "OFF");
  Serial.print("    Water Percentage : ");
  Serial.println(waterPercentage);
}

void setup()
{   
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  pinMode(WATER_SENSOR_PIN, INPUT);
  pinMode(WATER_PUMP_PIN, OUTPUT);
  timer.setInterval(1000L, sendSensor); // Send sensor data every 1 second
}

void loop()
{
  Blynk.run();
  timer.run();
}
