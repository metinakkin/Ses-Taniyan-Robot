#include <SPI.h>                       // SPI Arayüzünü dahil ettik.
#include "RF24.h"                      // RF24 kütüpanelerini dahil ettik.
byte data[1];                          // Göndereceğimiz data değişkenini oluşturduk.
boolean var;                           // Bit şeklinde var değişkeninini oluşturduk.
const uint64_t pipe = 0xF0F0F0F0A1LL;  // Paralel veri yolu adresleri tanımlamasını yaptık.
RF24 radio(9,10);                      // Modülün CE pinini 9.pin CS pinini de 10.pine bağlayacağımızı belirttik.
const int sol_i = 4;
const int sol_g = 5;
const int sag_i = 6;
const int sag_g = 7;
void setup(){
 Serial.begin(115200);
 radio.begin();                         // Kablosuz iletişimi başlattık.
 radio.openReadingPipe(1,pipe);         // Veri alacağımız kanalın ID'sini tanımladık.
 radio.startListening();  
  pinMode(sag_i, OUTPUT);
  pinMode(sag_g, OUTPUT);
  pinMode(sol_i, OUTPUT);
  pinMode(sol_g, OUTPUT);              
}

void loop()
{
 if(radio.available()){
   var = false;
   while(!var){
     var = radio.read(data, 1);   
      if(data[0] == 1)
      {
      Serial.println(data[0]);
      digitalWrite(sag_i, HIGH);
      digitalWrite(sag_g, LOW);
      digitalWrite(sol_i, HIGH);
      digitalWrite(sol_g, LOW);
      delay(600);
      digitalWrite(sag_i, LOW);
      digitalWrite(sag_g, LOW);
      digitalWrite(sol_i, LOW);
      digitalWrite(sol_g, LOW);
      }
      if(data[0] == 2)
      {
      Serial.println(data[0]);
       digitalWrite(sag_i, LOW);
      digitalWrite(sag_g, HIGH);
      digitalWrite(sol_i, LOW);
      digitalWrite(sol_g, HIGH);
      delay(600);
      digitalWrite(sag_i, LOW);
      digitalWrite(sag_g, LOW);
      digitalWrite(sol_i, LOW);
      digitalWrite(sol_g, LOW);
      }
      if(data[0] == 3)
      {
      Serial.println(data[0]);
       digitalWrite(sag_i, HIGH);
      digitalWrite(sag_g, LOW);
      digitalWrite(sol_i, LOW);
      digitalWrite(sol_g, HIGH);
      delay(300);
      digitalWrite(sag_i, LOW);
      digitalWrite(sag_g, LOW);
      digitalWrite(sol_i, LOW);
      digitalWrite(sol_g, LOW);
      }
      if(data[0] == 4){
      Serial.println(data[0]);
      digitalWrite(sag_i, LOW);
      digitalWrite(sag_g, HIGH);
      digitalWrite(sol_i, HIGH);
      digitalWrite(sol_g, LOW);
      delay(300);
      digitalWrite(sag_i, LOW);
      digitalWrite(sag_g, LOW);
      digitalWrite(sol_i, LOW);
      digitalWrite(sol_g, LOW);
   }
  }
 }
}
