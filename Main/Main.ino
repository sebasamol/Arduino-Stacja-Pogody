
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>

#define SCREEN_WIDTH 128 //szerokosc ekranu
#define SCREEN_HEIGHT 48 //wysokosc ekranu
#define OLED_RESET     -1 

const char* ssid = "CGA2121_7QPJvFa";
const char* password = "pUCafjBwtY9rcyDeb6";  


Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiServer server(80);
Adafruit_BME280 bme;

void setup() 
{
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000);
  
  Wire.begin();
  Serial.begin(115200);
  Serial.println();

  WiFi.begin(ssid, password);
  Serial.print("Connecting");
  
  if(!bme.begin(0x76)){
    Serial.println("Sprawdź połączenie nie znajduje modułu");
    while(1);
  }
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected");

  server.begin();
 
  Serial.println(WiFi.localIP());


  
} 

void OLED_display(){
  
  display.clearDisplay(); 
  display.setTextSize(1); 

  display.setTextColor(WHITE);
  display.setCursor(32,0);  
  display.println(bme.readTemperature());
  
  

  display.setTextSize(1); 
  display.setCursor(32,24);  
  display.println(bme.readPressure() /100.0F );

  display.setTextSize(1); 
  display.setCursor(32,40);  
  display.println(bme.readHumidity());
  delay(5000);
  display.display();
}
  
  
  


void loop() {
  OLED_display();
  Serial.print("Temperatura = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");
  delay(1000);
  
  
  }
