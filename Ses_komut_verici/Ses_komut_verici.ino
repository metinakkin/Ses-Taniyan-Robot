#include  <SPI.h>                     // SPI Arayüzünü dahil ettik.
#include  "RF24.h"                    // RF24 kütüpanelerini dahil ettik.
#include <SoftwareSerial.h>
#include "VoiceRecognitionV3.h"

byte data[1];                         // Göndereceğimiz data değişkenini oluşturduk.
const uint64_t pipe = 0xF0F0F0F0A1LL; // Paralel veri yolu adresleri tanımlamasını yaptık.
uint8_t buf[64];

RF24 radio(9,10);                     // Modülün CE pinini 9.pin CS pinini de 10.pine bağlayacağımızı belirttik.
VR myVR(2,3);    // 2:RX 3:TX, you can choose your favourite pins.

void setup()
{
 myVR.begin(9600);
 radio.begin();                       // Kablosuz iletişimi başlattık.
 radio.openWritingPipe(pipe);         // Gönderim yapacağımız kanalın ID'sini tanımladık.
}

void loop()
{
  int ret;
  ret = myVR.recognize(buf, 50);
  if(ret>0){
    Serial.println(buf[1]);
    switch(buf[1])
    {
      
      case 1: // Yeşil
      { data[0]=1;
      break;}
      case 2: // Mavi
      { data[0]=2;
      break;}
      case 3: //Sarı
      { data[0]=3;
      break;}
       case 4: // Mor
      { data[0]=4;
      break;}
                
               
              
       
      default:
        break;
    }
    /** voice recognized */
   
    
  }
  radio.write(data, 1);                 //Sonra da bu mesaj gönderilsin.
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf     --> command length
           len     --> number of parameters
*/
void printSignature(uint8_t *buf, int len)
{
  int i;
  for(i=0; i<len; i++){
    if(buf[i]>0x19 && buf[i]<0x7F){
      Serial.write(buf[i]);
    }
    else{
      Serial.print("[");
      Serial.print(buf[i], HEX);
      Serial.print("]");
    }
  }
}

/**
  @brief   Print signature, if the character is invisible, 
           print hexible value instead.
  @param   buf  -->  VR module return value when voice is recognized.
             buf[0]  -->  Group mode(FF: None Group, 0x8n: User, 0x0n:System
             buf[1]  -->  number of record which is recognized. 
             buf[2]  -->  Recognizer index(position) value of the recognized record.
             buf[3]  -->  Signature length
             buf[4]~buf[n] --> Signature
*/
void printVR(uint8_t *buf)
{
  Serial.println("VR Index\tGroup\tRecordNum\tSignature");

  Serial.print(buf[2], DEC);
  Serial.print("\t\t");

  if(buf[0] == 0xFF){
    Serial.print("NONE");
  }
  else if(buf[0]&0x80){
    Serial.print("UG ");
    Serial.print(buf[0]&(~0x80), DEC);
  }
  else{
    Serial.print("SG ");
    Serial.print(buf[0], DEC);
  }
  Serial.print("\t");

  Serial.print(buf[1], DEC);
  Serial.print("\t\t");
  if(buf[3]>0){
    printSignature(buf+4, buf[3]);
  }
  else{
    Serial.print("NONE");
  }
//  Serial.println("\r\n");
  Serial.println();
}

void printRecord(uint8_t *buf, uint8_t len)
{
  Serial.print(F("Record: "));
  for(int i=0; i<len; i++){
    Serial.print(buf[i], DEC);
    Serial.print(", ");
  }
}
