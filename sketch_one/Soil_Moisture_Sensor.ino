const int soilMoisturePin = A0;  // Analog pin for Soil Moisture Sensor

void setup() {
  Serial.begin(9600);
}

void loop() {
  int soilMoistureValue = analogRead(soilMoisturePin);

  // Convert the analog value to a percentage (assuming a 10-bit ADC)
  int moisturePercentage = map(soilMoistureValue, 0, 1023, 0, 100);

  Serial.print("Soil Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");

  // Add your additional logic or IoT communication code here

  delay(5000);  // Delay for 5 seconds before reading again
}
