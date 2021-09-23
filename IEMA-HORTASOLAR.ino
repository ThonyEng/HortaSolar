//Programa: Monitoracao de planta usando Arduino
//Autor: FILIPEFLOP
#include "RTClib.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
//Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x3F,16,2);
RTC_DS1307 rtc;
int valor_analogico;
String DataHora;

void setup()
{
  Serial.begin(9600);
  lcd.init();
  lcd.setBacklight(HIGH);
  pinMode(A0,INPUT);
  pinMode(6,OUTPUT);
  //INICIALIZAR RTC SALVANDO DATA DA COMPILAÇÃO
  if (!rtc.begin()){
//    Serial.println("RTC not found!");
//    while (1); //fica aqui pra sempre
  }
  if (!rtc.isrunning()){
    Serial.println("RTC is not working!");
    rtc.adjust(DateTime(2021, 9, 22, 23, 04 , 30));    //ajuste manual: DateTime(year, month, day, hour, minute, second)
  }

    DateTime now = rtc.now();
    
    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");

    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

}
 
void loop()
{
  valor_analogico = analogRead(A0);
  DateTime now = rtc.now();
  DataHora = String(now.day()) + "/" + String(now.month()) + "/" + String(now.year()) + " " + String(now.hour()) + ":" + String(now.minute());
  
  Serial.print("Umidade: ");
  Serial.print(valor_analogico);
 
  
  if (valor_analogico > 0 && valor_analogico < 400)
  {
   Serial.println(" Status: Umidade Alta");
   lcd.setCursor(0,0);
   lcd.print("Umid:Alta  T:32");
   lcd.setCursor(15,0);
   lcd.print((char)223);
   lcd.setCursor(0,1);
   lcd.print(DataHora);
   digitalWrite(6, HIGH);
  }
 
  if (valor_analogico > 400 && valor_analogico < 800)
  {
    Serial.println(" Status: Umidade moderada");
    lcd.setCursor(0,0);
    lcd.print("Umid:Media T:32");
    lcd.setCursor(15,0);
    lcd.print((char)223);
    lcd.setCursor(0,1);
    lcd.print(DataHora);
    digitalWrite(6, HIGH);
  }
 
  if (valor_analogico > 800 && valor_analogico < 1024)
  {
    Serial.println(" Status: Umidade Baixa");
    lcd.setCursor(0,0);
    lcd.print("Umid:Baixa T:32");
    lcd.setCursor(15,0);
    lcd.print((char)223);
    lcd.setCursor(0,1);
    lcd.print(DataHora);
    digitalWrite(6, LOW);
  }
  
  delay(1000);
}
