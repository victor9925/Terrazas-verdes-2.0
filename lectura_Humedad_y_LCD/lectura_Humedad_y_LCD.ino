
#include <DHT.h>
#include <Adafruit_Sensor.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 14, 27, 26, 25);
DHT my_sensor(33,DHT11);
float Humedad,Temeratura;
unsigned int envio=2000,tactual,tanterior;


void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  my_sensor.begin();
  
}

void loop() {

   tactual=millis();

  if(tactual-tanterior>envio){
      tanterior=tactual;
       Humedad= my_sensor.readHumidity();
      Temeratura=my_sensor.readTemperature();

    lcd.setCursor(0, 0);
        lcd.print("Humedad ");
        lcd.print(Humedad);
        lcd.print("%   ");
        lcd.setCursor(0, 2);
        lcd.print("Temperatura ");
        lcd.println(Temeratura);

  }
  
}
