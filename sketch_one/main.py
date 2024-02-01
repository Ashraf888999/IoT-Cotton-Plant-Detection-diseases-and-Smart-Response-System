import time
from Adafruit_DHT import DHT11, read_retry

# Define constants for pump control
pump_pin = 8  # Digital pin for water pump

# Define constants for Soil Moisture Sensors
soil_moisture_pin1 = 0  # Analog pin for Soil Moisture Sensor 1
soil_moisture_pin2 = 1  # Analog pin for Soil Moisture Sensor 2

class DHTSensor:
    def get_data(self):
        humidity, temperature = read_retry(DHT11, DHTPIN)
        return temperature, humidity

class WaterPump:
    def __init__(self, pin):
        self.pin = pin

    def initialize(self):
        # You may need to add additional initialization logic here
        pass

    def turn_on(self):
        # Turn on the water pump
        # You may need to add logic specific to your hardware
        pass

def read_moisture(pin):
    soil_moisture_value = analogRead(pin)
    moisture_percentage = map(soil_moisture_value, 0, 1023, 0, 100)
    print(f"Soil Moisture {pin + 1}: {moisture_percentage}%")
    return moisture_percentage

# Instantiate objects
dht_sensor = DHTSensor()
water_pump = WaterPump(pump_pin)

# Initialize components
water_pump.initialize()

while True:
    # Read temperature and humidity
    temperature, humidity = dht_sensor.get_data()
    print(f"Temperature: {temperature} °C, Humidity: {humidity} %")

    # Control water pump based on soil moisture
    moisture1 = read_moisture(soil_moisture_pin1)
    moisture2 = read_moisture(soil_moisture_pin2)

    # Compare moisture levels
    print("Comparison: ", end="")
    if moisture1 == moisture2:
        print("Moisture levels are equal")
    elif moisture1 > moisture2:
        print("Moisture level of sensor 1 is higher")
    else:
        print("Moisture level of sensor 2 is higher")

    # You can add a delay here if needed
    time.sleep(5)
