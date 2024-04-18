/*
 * CARTROTECH by Qode66  (www.qode66.xyz)
 * 
 * Projecte nº: P001
 * Descripcio: Llegir les dades d'un sensor DHT11 i presentarles en una pantalla LCD 16x02
 * mitjançant el modul de comunicacio I2C
 * Codi per a la placa que rep les dades del sensor DHT11 i goberna el LCD 1602
 * 
 * 22.08.2021
 */

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2  //Pin digital connectat al sensor DHT
#define DHTTYPE DHT11 //Tipus de sensor

DHT dht(DHTPIN, DHTTYPE);  //Declarar l'objecte DHT amb el parametres PIN i TYPE
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Crea l'objecte lcd amb la direcció 0x27, 16 caracters y 2 línees


void setup() 
{
  Serial.begin(9600);  // Obre i configura monitor serie a 9600 bps
  Wire.begin();        // unir-se al bus i2c com master
  lcd.begin();         //Inicialitza l'objecte lcd
  lcd.backlight();
  dht.begin();         //Inicialitza l'objecte DHT
}

void loop() 
{
  delay(2000);  //Espera 2 seg entre mesures

  float h = dht.readHumidity();         //Llig l'humitat
  float t = dht.readTemperature();      //Llig la temperatura en Celsius
  if (isnan(h) || isnan(t))             //Comprova que no hi ha error
    {
      lcd.clear();
      lcd.println("Fallo llegint sensor DHT!");
      return;
    }
  float hic = dht.computeHeatIndex(t, h, false);  //Calcula index de calor en Celsius
  tempinlcd(h, t, hic);                           //Crida a la funcio que presenta en pantalla
}

void tempinlcd(float HR, float TC, float IC)    //Funcio que controla la presentacio en pantalla
{
  char lcdTC[5];
  char lcdHR[5];
  char lcdIC[5];
  
  lcd.setCursor(0,0);
  lcd.print("T: ");
  dtostrf(TC,4,1,lcdTC);
  lcd.print(lcdTC);

  lcd.setCursor(8,0);
  lcd.print("H: ");
  dtostrf(HR,4,1,lcdHR);
  lcd.print(lcdHR);

  lcd.setCursor(0,1);
  lcd.print("IC: ");
  dtostrf(IC,4,1,lcdIC);
  lcd.print(lcdIC);
  
  
}
