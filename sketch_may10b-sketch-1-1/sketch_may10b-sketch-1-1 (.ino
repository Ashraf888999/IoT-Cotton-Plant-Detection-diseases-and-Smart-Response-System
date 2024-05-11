#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

char auth[] = "milI53oqPeLXPrbyPWBR6pHgPFSVRQLO";
char ssid[] = "Elshami";
char pass[] = "l4070245";

BlynkTimer timer;

#define DHTPIN 27
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);

#define WATER_SENSOR_PIN 32
#define WATER_PUMP_PIN 26
#define PESTICIDE_PUMP_PIN 25

void sendSensor()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  int waterSensorValue = analogRead(WATER_SENSOR_PIN);
  float waterPercentage = map(waterSensorValue, 0, 1023, 0, 100);
  
  int waterPumpState = digitalRead(WATER_PUMP_PIN);
  int pesticidePumpState = digitalRead(PESTICIDE_PUMP_PIN);
  
  Blynk.virtualWrite(V0, temperature);
  Blynk.virtualWrite(V1, humidity);
  Blynk.virtualWrite(V2, waterPumpState);
  Blynk.virtualWrite(V3, waterPercentage);
  Blynk.virtualWrite(V4, pesticidePumpState); // Sending pesticide pump status to Blynk
  
  Serial.print("Temperature : ");
  Serial.print(temperature);
  Serial.print("    Humidity : ");
  Serial.print(humidity);
  Serial.print("    Water Pump State : ");
  Serial.print(waterPumpState == HIGH ? "ON" : "OFF");
  Serial.print("    Pesticide Pump State : ");
  Serial.print(pesticidePumpState == HIGH ? "ON" : "OFF");
  Serial.print("    Water Percentage : ");
  Serial.println(waterPercentage);
}

BLYNK_WRITE(V4) {
  int pumpState = param.asInt();
  digitalWrite(PESTICIDE_PUMP_PIN, pumpState);
  Blynk.virtualWrite(V4, pumpState); //
