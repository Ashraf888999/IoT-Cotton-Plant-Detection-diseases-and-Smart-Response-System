#include <DHT.h>
#include <DHT_U.h>
#include <Adafruit_Sensor.h>

#define DHTPIN A0 // Replace with the actual pin connected to the DHT sensor
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

int water;
float waterPercentage;
bool pumpOn = false;
const int SENSOR_DRY = 0;
const int SENSOR_WET = 1023;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(6, INPUT);
  Serial.begin(9600);
  dht.begin();
  delay(2000);
}

void loop() {
  water = digitalRead(6);
  
  if (water == HIGH) {
    digitalWrite(3, LOW);
    pumpOn = false;
    Serial.println("Pump on");
  } else {
    digitalWrite(3, HIGH);
    pumpOn = true;
    Serial.println("Pump off");
  }
  
  int sensorValue = analogRead(A0);
  waterPercentage = map(sensorValue, SENSOR_DRY, SENSOR_WET, 0, 100);
  waterPercentage = constrain(waterPercentage, 0, 100);
  Serial.print("Water percentage: ");
  Serial.print(waterPercentage);
  Serial.println("%");

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.print("°C, Humidity: ");
    Serial.print(humidity);
    Serial.println("%");
  }
  
  if (isnan(humidity) && isnan(temperature)) {
    Serial.println("Check DHT11 sensor wiring and power supply!");
  }
  
  if (waterPercentage <= 40) {
    digitalWrite(3, LOW);
    pumpOn = false;
    Serial.println("Pump off due to water level reached 40%");
  }
  
  if (pumpOn && waterPercentage > 60) {
    Serial.println("WARNING ‼ Water is high, please check the system");
  }
  
  delay(400);
}
