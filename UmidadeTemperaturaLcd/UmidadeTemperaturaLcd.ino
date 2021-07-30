#include <Wire.h>               // Biblioteca de comunicação I2C.
#include <LiquidCrystal_I2C.h>  // Biblioteca do cristal liquido
#include <DHT.h>                // Biblioteca do sensor DHT11 temperature and humidity sensor Predefined library

LiquidCrystal_I2C lcd(0x27, 16, 2); //FUNÇÃO DO TIPO "LiquidCrystal_I2C"

#define DHTTYPE DHT11   // DHT 11
#define dht_dpin 0      //GPIO-0 D3 pin of nodemcu

DHT dht(dht_dpin, DHTTYPE); 

float humidity, temp_f;                  // Values read from sensor
unsigned long previousMillis = 0;        // will store last temp was read
const long interval = 2000;              // interval at which to read sensor


void setup()
{
  dht.begin();     // INICIALIZA O SENSOR DE TEMPERATURA E PRESÃO

  lcd.init();      // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO)
  lcd.clear();
 
}
// Print all the custom characters:
void loop() {

  gettemperature();
  lcd.setCursor(0, 0);
  String hs="Umid: "+String((int)humidity)+" % ";
  String ts="Temp: "+String((int)temp_f)+" C ";
  lcd.setCursor(0, 0);
  lcd.print(ts);
  lcd.setCursor(0, 1);
  lcd.print(hs);

}

void gettemperature() {
  unsigned long currentMillis = millis();
 if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;   
    humidity = dht.readHumidity();          // Read humidity (percent)
    temp_f = dht.readTemperature(false);     // Read temperature as Celsius
    if (isnan(humidity) || isnan(temp_f)) {
      humidity=0;
      temp_f=0;
      Serial.println("Failed to read from DHT sensor!");
      return;
    }
  }
}
