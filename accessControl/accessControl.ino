#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         0           
#define SS_PIN          2          

MFRC522 mfrc522(SS_PIN, RST_PIN);   

const int azul  = 4;
const int rojo  = 5;
const int verde = 16;

const char* ssid = "PENTAGONO";
const char* password = "NOHAYUNALIENAQUI";
const String host = "http://192.168.1.66/get.php";



void setup() {
  pinMode(azul , OUTPUT);
  pinMode(rojo , OUTPUT);
  pinMode(verde , OUTPUT);

  SPI.begin();
  mfrc522.PCD_Init();
  delay(4);
  mfrc522.PCD_DumpVersionToSerial();
  
  delay(10);
  Serial.begin(9600);

  WiFi.begin(ssid,password);

  Serial.print("Connecting...");

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  BlueBlink();
  Serial.print("Conectado con exito, mi ip es:");
  Serial.println(WiFi.localIP());

}

void loop() {
  

  
  if(WiFi.status()==WL_CONNECTED){
   
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
      return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
      return;
    }

    
    String content= "";
    byte letter;
    for (byte i = 0; i < mfrc522.uid.size; i++) 
    {
       Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
       Serial.print(mfrc522.uid.uidByte[i], HEX);
       content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
       content.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.println();
    
    content.toLowerCase();
    content.replace(" ","");
    Serial.println("content "+content);
  
    String Dsend = "?card_id="+content;
    conect(Dsend);
    
    
  }

}
