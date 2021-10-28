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


String HTML_page(float TemperatureWeb,float HumidityWeb,float PressWeb, String TimeWeb, String DateWeb);
float Temp_out;
float Hum_out;
float Press_out;

const char* ssid = "CGA2121_7QPJvFa";
const char* password = "pUCafjBwtY9rcyDeb6";  
const long utcOffsetInSeconds = 7200;
char daysOfTheWeek[7][13] = {"Niedziela", "Poniedzialek", "Wtorek", "Sroda", "Czwartek", "Piatek", "Sobota"};


WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "europe.pool.ntp.org", utcOffsetInSeconds);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

ESP8266WebServer server(80);
Adafruit_BME280 bme;

/////////////////////////////////////////PAGE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String HTML_page(float TemperatureWeb,float HumidityWeb, float PressWeb){
  String ptr = "<!DOCTYPE html> <html>";
  ptr +="<head>";
  ptr +="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<script>function refresh(refreshPeriod) {setTimeout('location.reload(true)', refreshPeriod);} window.onload = refresh(5000);</script>";
  ptr +="<title>Stacja meteorologiczna ESP8266</title>";
  ptr +="</head>";
  ptr +="<style>";
  ptr +="body{background-color:lemonchiffon;}";
  ptr +="h1{font-family:monospace,'Times New Roman';}";
  ptr +="h2{font-family: monospace,'Times New Roman';}";
  ptr +="h3{font-family: monospace,'Times New Roman';}";
  ptr +="p{margin: 15px;font-family: monospace,'Times New Roman';}";
  ptr +="</style>";
  
  ptr +="<body>";
  ptr +="<div id=\"webpage\">";
  ptr +="<center>";
  ptr +="<h1>Stacja meteorologiczna</h1>";
  ptr +="</center>";
  ptr +="<p>Aktualna godzina:</p>";

  ptr +="<h2>Warunki atmosferyczne na zewnatrz</h2>";
  ptr +="<p>Temperatura powietrza: <br>";
  ptr +=(float)TemperatureWeb;
  ptr +="*C</p>";
  ptr +="<p>Wilgotnosc powietrza: <br>";
  ptr +=(float)HumidityWeb;
  ptr +="%</p>";
  ptr +="<p>Cisnienie atmosferyczne: <br>";
  ptr +=(float)PressWeb;
  ptr +="hPa</p>";
  
  ptr +="<h2>Odczyt w domu</h3>";
  ptr +="<p>Temperatura powietrza: <br>";
  ptr +="</div>";
  ptr +="</body>";
  ptr +="</html>";
  return ptr;
}

/////////////////////////////////////////SETUP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
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

  Serial.println(WiFi.localIP());
  server.on("/", handleRoot);
  server.begin();


  
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

void handleRoot(){
  Temp_out = bme.readTemperature(); 
  Hum_out = bme.readHumidity(); 
  Press_out = bme.readPressure() /100.0F;
  server.send(200, "text/html", HTML_page(Temp_out,Hum_out,Press_out)); 


}
/////////////////////////////////////////LOOP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
  timeClient.update();
  OLED_display();
  server.handleClient();
  /*
  client.print("Temperatura: ");
  client.println(bme.readTemperature());

  client.print("Cisnienie: ");
  client.println(bme.readPressure() /100.0F);

  client.print("Wilgotnosc: ");
  client.println(bme.readHumidity());
  
  OLED_display();
  
  client.print(daysOfTheWeek[timeClient.getDay()]);
  client.print(", ");
  client.print(timeClient.getHours());
  client.print(":");
  client.print(timeClient.getMinutes());
  client.print(":");
  client.print(timeClient.getSeconds());
  */
  
  
  
  
  
  
  
  }
