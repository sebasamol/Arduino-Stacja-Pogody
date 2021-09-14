#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

Adafruit_BME280 bme;

void setup() {
  Serial.begin(9600);
  if (!bme.begin(0x76)) {
    Serial.println("Error");
    while (1);
  }

}

/* Measuring temperature */
void measure_temp()
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");
}

/*Measuring humidity */
void measure_hum()
{
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");
}

/*Measuring pressure */
void measure_press()
{
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");
}


void loop() {
  measure_temp();
  measure_hum();
  measure_press(); 
  delay(1000);

}
