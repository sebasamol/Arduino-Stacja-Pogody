
//#include <Adafruit_Sensor.h>
//#include <Adafruit_BME280.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 //szerokosc ekranu
#define SCREEN_HEIGHT 48 //wysokosc ekranu

#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);



const char* ssid = "CGA2121_7QPJvFa";
const char* password = "pUCafjBwtY9rcyDeb6";  

WiFiServer server(80);

//Adafruit_BME280 bme;

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
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" Connected");

  server.begin();
 
  Serial.println(WiFi.localIP());


  display.clearDisplay();
 
  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(32,3);
  display.println("27.8");
  display.display();
  delay(2000);
  display.clearDisplay();
} 


void loop() {
  
  
  
  
  }
