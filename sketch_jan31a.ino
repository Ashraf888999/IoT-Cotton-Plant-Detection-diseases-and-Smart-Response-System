int water; // Variable to store the signal from the soil moisture sensor
float waterPercentage; // Variable to store the calculated water percentage

void setup() {
  pinMode(3, OUTPUT); // Set pin 3 as an output for the relay board
  pinMode(6, INPUT);  // Set pin 6 as an input for the soil moisture sensor
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  water = digitalRead(6); // Read the signal from the soil moisture sensor connected to pin 6
  
  if (water == HIGH) {
    // If the water level is full (soil is wet), cut the relay by setting pin 3 LOW
    digitalWrite(3, LOW);
    Serial.println("Pump off"); // Print "Pump off" to serial monitor
  } else {
    // If the water level is not full (soil is dry), continue providing signal and water supply by setting pin 3 HIGH
    digitalWrite(3, HIGH);
    Serial.println("Pump on"); // Print "Pump on" to serial monitor
  }
  
  // Calculate water percentage
  int sensorValue = analogRead(A0); // Read sensor value from analog pin A0
  waterPercentage = map(sensorValue, 0, 1023, 0, 100); // Map sensor value to percentage scale
  
  // Adjusting for sensor calibration
  // You may need to adjust these values based on your sensor's calibration
  waterPercentage = constrain(waterPercentage, 0, 100); // Ensure the percentage is within 0-100 range
  
  Serial.print("Water percentage: ");
  Serial.print(waterPercentage);
  Serial.println("%"); // Print water percentage to serial monitor
  
  delay(400); // Delay for stability
}
