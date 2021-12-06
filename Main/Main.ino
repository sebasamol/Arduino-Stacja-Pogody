#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <SPI.h>
#include <Wire.h>
#include "DHT.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>


#define SCREEN_WIDTH 128 //szerokosc ekranu
#define SCREEN_HEIGHT 48 //wysokosc ekranu
#define OLED_RESET     -1 
#define DHTTYPE DHT21
#define DHTPIN 14 

String HTML_page(float TemperatureWeb,float HumidityWeb,float PressWeb,float HumHouse, float TempHouse );
float Temp_out;
float Hum_out;
float Press_out;
float Temp_house;
float Hum_house;


const char* ssid = "CGA2121_7QPJvFa";
const char* password = "pUCafjBwtY9rcyDeb6";  


WiFiUDP ntpUDP;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
DHT dht(DHTPIN, DHTTYPE);
ESP8266WebServer server(80);
Adafruit_BME280 bme;

/////////////////////////////////////////PAGE///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
String HTML_page(float TemperatureWeb,float HumidityWeb, float PressWeb,float HumHouse, float TempHouse ){
  String ptr = "<!DOCTYPE html> <html>";
    ptr+="<html lang=\"pl-PL\">";
    
    ptr +="<head>";
        ptr +="<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
        ptr +="<meta http-equiv='content-language' content='pl' />";
        ptr+="<meta charset=\"UTF-8\">";
        ptr +="<title>Stacja meteorologiczna ESP8266 </title>";
        ptr +="<link rel=\"icon\" href=\"https://www.flaticon.com/free-icon/station_1809820?term=weather%20station&page=1&position=11&page=1&position=11&related_id=1809820&origin=search\">";
        
    ptr +="<script>";
       ptr +=" function display_c(){";
            ptr +="var refresh=1000;";
            ptr +="mytime=setTimeout(\'display_ct()\',refresh)";
            ptr +="}";

            ptr +="function display_ct() {";
               ptr +=" var x = new Date()";
                ptr +="var x1=x.toUTCString();";
                ptr +="document.getElementById(\'ct\').innerHTML = x1;";
               ptr +=" tt=display_c();";
            ptr +="}";
            ptr +="setTimeout(function(){";
           ptr +=" window.location.reload(1);";
           ptr +=" }, 5000);";
    ptr +="</script>";
    ptr +="<style>";
    ptr +="body";
ptr +="{";
    ptr +="background-image: radial-gradient(73% 147%, #EADFDF 59%, #ECE2DF 100%), radial-gradient(91% 146%, rgba(255,255,255,0.50) 47%, rgba(0,0,0,0.50) 100%);";
    ptr +="background-blend-mode: screen;";
    ptr +="background-repeat: no-repeat;";
    ptr +="background-attachment: fixed;";
    ptr +="background-position: center;";
ptr +="}";
ptr +="h1";
ptr +="{  "; 
  ptr +="font-weight: normal;";
    ptr +="font-size: 40px;";
    ptr +="padding: 10px;";
    ptr +="text-align: center;";
    ptr +="font-family: 'Courier New', Courier, monospace;";
    
    
ptr +="}";

ptr +=".container";
ptr +="{";
    
    ptr +="border: 4px solid black;";
    ptr +="border-radius: 25px;";
    ptr +="background-color: cornsilk;";
    ptr +="opacity: 0.65;";
    
ptr +="}";

ptr +="h2";
ptr +="{";
    ptr +="text-align: center;";
ptr +="}";

ptr +=".heading p";
ptr +="{";
    ptr +="text-align: center;";
    ptr +="font-size: 25px;";
    ptr+="font-family: 'Courier New', Courier, monospace;";
    ptr+="margin-left: 15px;";

ptr +="}";
ptr +=".heading";
ptr +="{";
    
    ptr +="padding: 10px;";
    ptr +="margin-left: 10px;";
    
ptr +="}";
ptr +=".heading img";
ptr +="{";
    ptr +="top: 5px;";
    ptr +="left: 5px;";
    ptr +="position: relative;";
    ptr +="height: 50px;";
    ptr +="width: 50px;";
ptr +="}";

ptr +=".parametres";
ptr +="{";
    
    ptr +="font-size: 18px;";
    ptr +="padding: 10px;";
    ptr +="font-family: 'Courier New', Courier, monospace;";
    ptr +="display: inline-flex;";
    ptr +="margin-left: 20px;";
ptr +="}";

ptr +="parametres img";
ptr +="{";
    ptr +="top: 5px;";
    ptr +="left: 5px;";
    ptr +="position: relative;";
    ptr +="height: 40px;";
    ptr +="width: 40px;";
ptr +="}";
 ptr +=".parametres p";
 ptr +="{";
     ptr +="margin-left: 10px;";
 ptr +="}";
 

ptr +="span";
ptr +="{";
    ptr +="padding: 15px;";
    ptr +="margin-left: 15px;";
    ptr +="font-size: 20px;";
ptr +="}";
    ptr +="</style>";
   ptr +=" </head>";
    ptr +="<body>";
       ptr +=" <h1>Stacja meteorologiczna</h1>";
           ptr +=" <body style=\"text-align: center; font-family: 'Courier New', Courier, mononospace;\"  onload=\"display_ct()\">";
               ptr +="<span id=\'ct\'></span>";
           ptr +="</body>";

          ptr +="<div class=\"container\">";
             ptr +="<div class=\"heading\">";
                ptr +="<img src=\"(https://www.flaticon.com/premium-icon/landscape_3000665?term=outdoor&page=1&position=6&page=1&position=6&related_id=3000665&origin=search)\">";
                 ptr +="<p>Odczyt na zewnątrz:</p>";
             ptr +="</div>";
                   ptr +=" <div class=\"parametres\">";
                       ptr +="<img src=\"(https://www.flaticon.com/premium-icon/high-temperature_1585441?term=temperature&page=1&position=6&page=1&position=6&related_id=1585441&origin=search)\">";
                      
                       ptr +=(float)TemperatureWeb;
                       ptr +="*C</p>";
                       ptr +="<img src=\"(https://www.flaticon.com/premium-icon/humidity_2828582?term=humidity&page=1&position=15&page=1&position=15&related_id=2828582&origin=search)\">";
                       
                       ptr +=(float)HumidityWeb;
                       ptr +="%</p>";
                       ptr +="<img src=\"(https://www.flaticon.com/free-icon/gauge_556958?term=atmospheric%20pressure&page=1&position=1&page=1&position=1&related_id=556958&origin=search)\">";
                       
                       ptr +=(float)PressWeb;
                       ptr +="hPa</p>";
                        
                   ptr +="</div>";
              
             ptr +=" <div class=\"heading\">";
                ptr +="<img src=\"(https://www.flaticon.com/premium-icon/house_2163350?term=house&page=1&position=3&page=1&position=3&related_id=2163350&origin=search)\">";
                ptr +="<p>Odczyt w domu:</p>";
               ptr +=" </div>";
                   ptr +=" <div class=\"parametres\">";
                      ptr +="<img srcl=\"(https://www.flaticon.com/premium-icon/high-temperature_1585441?term=temperature&page=1&position=6&page=1&position=6&related_id=1585441&origin=search)\">";
    
                       ptr +=(float)TempHouse;
                       ptr +="*C</p>";
                       ptr +="<img src=\"(https://www.flaticon.com/premium-icon/humidity_2828582?term=humidity&page=1&position=15&page=1&position=15&related_id=2828582&origin=search)\">";
                      
                       ptr +=(float)HumHouse;
                       ptr +="%</p>";
                       ptr +="<img src=\"(https://www.flaticon.com/free-icon/gauge_556958?term=atmospheric%20pressure&page=1&position=1&page=1&position=1&related_id=556958&origin=search)\">";
                       
                       
                        
                    ptr +=" </div>";
                
           ptr +=" </div>";
           ptr +=" <div id=\"info\">";
              ptr +="<p>Pomiary dla miasta Poznań</p>";
              ptr +="<a href=\"https://www.accuweather.com/pl/pl/pozna%C5%84/276594/weather-forecast/276594\">Tu znajdziesz szczegółową prognozę pogody</a>";
           ptr+=" </div>";

    ptr +="</body>";
ptr +="</html>";
  
  return ptr;
}

/////////////////////////////////////////SETUP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setup() {
  //timeClient.begin();
  dht.begin();
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
  server.send(200, "text/html", HTML_page(Temp_out,Hum_out,Press_out,Temp_house,Hum_house)); 
  Temp_house = dht.readTemperature();
  Hum_house = dht.readHumidity();


}
/////////////////////////////////////////LOOP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void loop() {
//  timeClient.update();
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
