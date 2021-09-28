
//#include <Wire.h>
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>

const char* ssid = "CGA2121_7QPJvFa";
const char* password = "pUCafjBwtY9rcyDeb6";  

WiFiServer server(80);

//Adafruit_BME280 bme;

void setup() 
{
  Serial.begin(115200);
  Serial.println();

  
  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected");

  server.begin();
 
  Serial.println(WiFi.localIP());

} 


void loop() {}
