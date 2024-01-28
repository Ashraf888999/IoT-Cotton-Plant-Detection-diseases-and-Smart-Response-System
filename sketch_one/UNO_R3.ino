#include <DHT.h>

// Define constants for DHT sensor
#define DHTPIN 2       // Pin connected to the DHT sensor
#define DHTTYPE DHT11  // Type of the DHT sensor

// Define constants for pump control
const int pumpPin = 8;  // Digital pin for water pump

// Define constants for Soil Moisture Sensors
const int soilMoisturePin1 = A0;  // Analog pin for Soil Moisture Sensor 1
const int soilMoisturePin2 = A1;  // Analog pin for Soil Moisture Sensor 2

class DHTSensor {
public:
  DHTSensor(int pin, int type) : dht(pin, type) {}

  void begin() {
    dht.begin();
  }

  float getTemperature() {
    return dht.readTemperature();
  }

  float getHumidity() {
    return dht.readHumidity();
  }

private:
  DHT dht;
};

class WaterPump {
public:
  WaterPump(int pin) : pumpPin(pin) {}

  void initialize() {
    pinMode(pumpPin, OUTPUT);
    digitalWrite(pumpPin, LOW);
  }

  void turnOn() {
    digitalWrite(pumpPin, HIGH);
    delay(5000); // Run the pump for 5 seconds
    digitalWrite(pumpPin, LOW);
  }

private:
  int pumpPin;
};

class SoilMoistureSensor {
public:
  SoilMoistureSensor(int pin) : soilMoisturePin(pin) {}

  void readMoisture() {
    int soilMoistureValue = analogRead(soilMoisturePin);

    // Convert the analog value to a percentage (assuming a 10-bit ADC)
    int moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

    Serial.print("Soil Moisture ");
    Serial.print(soilMoisturePin == soilMoisturePin1 ? "1: " : "2: ");
    Serial.print(moisturePercentage);
    Serial.println("%");
  }

  int getMoisturePercentage() {
    int soilMoistureValue = analogRead(soilMoisturePin);
    return map(soilMoistureValue, 0, 1023, 0, 100);
  }

private:
  int soilMoisturePin;
};

void setup() {
  Serial.begin(9600);

  // Instantiate objects
  DHTSensor dhtSensor(DHTPIN, DHTTYPE);
  WaterPump waterPump(pumpPin);
  SoilMoistureSensor soil_moisture1(soilMoisturePin1);
  SoilMoistureSensor soil_moisture2(soilMoisturePin2);

  // Initialize components
  dhtSensor.begin();
  waterPump.initialize();
}

void loop() {
  // Read temperature and humidity
  DHTSensor dhtSensor(DHTPIN, DHTTYPE);
  float temperature = dhtSensor.getTemperature();
  float humidity = dhtSensor.getHumidity();

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" °C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");

  // Control water pump based on soil moisture
  SoilMoistureSensor soil_moisture1(soilMoisturePin1);
  SoilMoistureSensor soil_moisture2(soilMoisturePin2);

  int moisture1 = soil_moisture1.getMoisturePercentage();
  int moisture2 = soil_moisture2.getMoisturePercentage();

  Serial.print("Comparison: ");
  if (moisture1 == moisture2) {
    Serial.println("Moisture levels are equal");
  } else if (moisture1 > moisture2) {
    Serial.println("Moisture level of sensor 1 is higher");
  } else {
    Serial.println("Moisture level of sensor 2 is higher");
  }

  soil_moisture1.readMoisture();
  soil_moisture2.readMoisture();

  delay(5000);  // Delay for 5 seconds before reading again
}
