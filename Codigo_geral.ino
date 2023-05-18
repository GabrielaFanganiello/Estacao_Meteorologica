int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3; double tensao, res, lum;
float volts;
float celcius;
#include "DHT.h"
#include <Wire.h> 
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

#define DHTPIN 2     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27,16,2);


Adafruit_BMP280 bmp;


byte graus[8]={
  B00100,
  B01010,
  B00100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000,  
};

void setup() {
  lcd.init();
  lcd.createChar(0,graus);
  lcd.begin(16,2);
  pinMode(A0, INPUT);
  analogReference(INTERNAL); //1.1V

  unsigned status;
  status = bmp.begin(0x76);

  dht.begin();
  
}

void loop() {
  //Temperatura(TMP)
  sensorValue1 = analogRead(A0);
  volts = (sensorValue1 *1.1)/1023.0;
  celcius = 105.1369631 * volts-50.19079209;
  lcd.setCursor(2,0);
  lcd.print("Temperatura:");
  lcd.setCursor(5,1);
  lcd.print(celcius);
  lcd.write(byte(0));
  lcd.print("C");
  delay(2000);
  lcd.backlight();
  lcd.clear();

  //Pressao(BMP)
  lcd.setCursor(4,0);
  lcd.print(F("Pressao:"));
  lcd.setCursor(3,1);
  lcd.print(bmp.readPressure()/1000);
  lcd.print(" kPa");
  delay(2000);
  lcd.backlight();
  lcd.clear();

  //Umidade(%)
  float h = dht.readHumidity();
  sensorValue2 = h *1.290497634-0.165070647;
  lcd.setCursor(4,0);
  lcd.print(F("Umidade: "));
  lcd.setCursor(5,1);
  lcd.print(sensorValue2);
  lcd.print("% UR");
  delay(2000);
  lcd.backlight();
  lcd.clear();
  

  sensorValue3 = analogRead(A1);
  tensao = (sensorValue3/1023.0)*1.1;
  res = (tensao* 100000.0)/(3.3-tensao);
  lum = pow(10,4.38-0.58*log10(res));
  lcd.setCursor(2,0);
  lcd.print("Luminosidade: ");
  lcd.setCursor(3,1);
  lcd.print(lum);
  lcd.print(" Lux");
  delay(2000);
  lcd.backlight();
  lcd.clear();
}
