//definindo variáveis do tipo inteira, float e real
int sensorValue1 = 0;
int sensorValue2 = 0;
int sensorValue3; double tensao, res, lum;
float volts;
float celcius;

//incluindo bibliotecas necessárias
#include "DHT.h"
#include <Wire.h> 
#include <SPI.h>
#include <Adafruit_BMP280.h>
#include <LiquidCrystal_I2C.h>

// definindo o pino 2 para a entrada do senssor DHT
#define DHTPIN 2     
#define DHTTYPE DHT22   
DHT dht(DHTPIN, DHTTYPE);

//passando o endereço do LCD e numero de linhas e colunas que existem nele por meio do uso da bibliotecs <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

//chamando o bmp da biblioteca Adafruit_BMP280(sensor de pressão)
Adafruit_BMP280 bmp;

//criando byte do desenho do grau
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

//criando byte do desenho do 'ã'
byte acento[8] = {
  B01101,
  B10010,
  B01110,
  B00010,
  B11110,
  B10010,
  B11110,
  B00000
};

//inicializando o programa
void setup() {
  lcd.init(); // inicia a exibição do LCD
  lcd.createChar(0,graus); 
  lcd.createChar(1,acento);
  lcd.begin(16,2);
  pinMode(A0, INPUT); //pino A0, de entrada de informações 
  analogReference(INTERNAL); //1.1V

  unsigned status;
  status = bmp.begin(0x76); //endereço do sensor de pressão

  dht.begin(); //inicializando o dht(sensor de umidade)
  
}
// criando o loop do programa
void loop() {
  //Temperatura(TMP)
  sensorValue1 = analogRead(A0); //entrada analógica A0
  volts = (sensorValue1 *1.1)/1023.0;
  celcius = 105.1369631 * volts-50.19079209; //calibrando o sensor
  lcd.setCursor(2,0); //escolhendo as linhas para exibiçao do texto
  lcd.print("Temperatura:");
  lcd.setCursor(5,1);
  lcd.print(celcius);
  lcd.write(byte(0)); //escrevendo os bytes no LCD 
  lcd.print("C");
  delay(2000); //tempo do loop
  lcd.backlight(); //liga a luz do LCD
  lcd.clear(); //apaga as informações anteriores

  //Pressao(BMP)
  lcd.setCursor(4,0);
  lcd.print(F("Press:"));
  lcd.setCursor(9,0);
  lcd.write(byte(1));
  lcd.setCursor(10,0);
  lcd.print(F("o: "));
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
  
  //Luminosidade
  sensorValue3 = analogRead(A1); //entrada analógica A1
  tensao = (sensorValue3/1023.0)*1.1;
  res = (tensao* 100000.0)/(3.3-tensao);
  lum = pow(10,4.38-0.58*log10(res));
  lcd.setCursor(2,0);
  lcd.print("Luminosidade: ");
  lcd.setCursor(3,1);
  lcd.print(lum);
  lcd.print(" Lx");
  delay(2000);
  lcd.backlight();
  lcd.clear();
}