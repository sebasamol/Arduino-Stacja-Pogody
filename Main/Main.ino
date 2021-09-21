
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>


//Adafruit_BME280 bme;

void setup() {
  Serial.begin(115200);
  Serial.println();

  WiFi.begin("CGA2121_7QPJvFa", "pUCafjBwtY9rcyDeb6");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

} 

/*

void measure_temp() 
{
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");
}


void measure_hum()
{
  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");
}


void measure_press()
{
  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");
}


void loop() {
 // measure_temp();
 // measure_hum();
 // measure_press(); 
 // delay(1000);

} */
void loop() {}
