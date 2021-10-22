#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
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
const long utcOffsetInSeconds = 7200;
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiServer server(80);

Adafruit_BME280 bme;

void setup() 
{
  timeClient.begin();
  
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
//WYŚWIETLANIE DANYCH Z CZUJNIKA NA OLED
void OLED_display(){
  
  display.clearDisplay(); 
  display.setTextSize(1); 

  display.setTextColor(WHITE);
  display.setCursor(32,0);  
  display.print(bme.readTemperature());
  display.println("*C");
  
  display.setTextSize(1); 
  display.setCursor(32,24);  
  display.print(bme.readPressure() /100.0F );
  display.println("hPa");
  
  display.setTextSize(1); 
  display.setCursor(32,40);  
  display.print(bme.readHumidity());
  display.println("%");
  delay(10000);
  display.display();
}






void loop() {
  timeClient.update();
  WiFiClient client = server.available();
  
  client.print("Temperatura: ");
  client.println(bme.readTemperature());

  client.print("Cisnienie: ");
  client.println(bme.readPressure() /100.0F);

  client.print("Wilgotnosc: ");
  client.println(bme.readHumidity());
  
  OLED_display();
  delay(1000);

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  
  
  }
