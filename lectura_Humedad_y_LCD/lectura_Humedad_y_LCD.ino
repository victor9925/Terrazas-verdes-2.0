#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiAP.h>
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>
#include <WebServer.h>

const char *ssid = "T1_Arus";
const char *password = "comuna13";

DHT my_sensor(33,DHT11);
LiquidCrystal lcd(13, 12, 14, 27, 26, 25);


float Humedad,Temeratura;
unsigned int envio=2000,tactual,tanterior;


WebServer server(80);

void setup() {

  Serial.begin(115200);
  
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  lcd.begin(16, 2);
  
  my_sensor.begin();
  
  server.on("/", handleConnectionRoot);
  server.onNotFound(handle_NotFound);
  server.begin(); 
 
}

void loop() {
  tactual=millis();

  
  if(tactual-tanterior>envio){ 
  Humedad= my_sensor.readHumidity();
  Temeratura=my_sensor.readTemperature();
  printlcd();
  }
  
  server.handleClient();
}


void printlcd(){
      tanterior=tactual;
        lcd.setCursor(0, 0);
        lcd.print("Humedad ");
        lcd.print(Humedad);
        lcd.print("%   ");
        lcd.setCursor(0, 2);
        lcd.print("Temperatura ");
        lcd.println(Temeratura);
        Serial.println(Temeratura);
  
  }
String device ="";
String answer ="";
String answer2 ="";

void handleConnectionRoot() {
  setAnswer();
  server.send(200, "text/html", answer); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}



void setAnswer(){
  /*answer = "<!DOCTYPE html>\
            <html>\
            <style>\
            body { background-color: #FF5733; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
            </style>\
            <body>\
            <h1>La Temperatura actual es de  \"" + (String)Temeratura + "\"!  </h1>\
            </body>\
            </html>";
    */        

  answer = " <!DOCTYPE html>\ 
            <html>\                 
            <head> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\
            <title>LED Control</title>\
            <style>\
            html { height:100% ;font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\
            body { background-image: linear-gradient(#FFFFFF,rgb(255,122,89)); font-family: Arial, Helvetica, Sans-Serif;} \
            h1 {color: #000000;margin: 50px auto 30px;}\
            h2 {color: #FF5733;margin: 50px auto 30px; font-size:20px}\
            h3 {color: #000088;margin-bottom: 50px;}\
            p {font-size: 14px;color: #888;margin-bottom: 10px;}\
            </style>\
            </head>\
            <body>\
            <h1>SENSORES TERRAZA</h1>\
            <h2>Tempertaruta</h2>\
            <h3>\"" + (String)Temeratura + "\" C</h3>\
            <h2>Humedad</h2>\
            <h3>\"" + (String)Humedad + "\" %</h3>\
            </body>\
            </html>";
            }
