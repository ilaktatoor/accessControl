void conect(String Dsend ){
  String link = host+Dsend;
   HTTPClient http;
   WiFiClient client;
    
    http.begin(client,link);
    http.addHeader("Content-Type","text/plain");
    int respond = http.GET();

    if(respond>0){
      Serial.println("Codigo de respuesta" + String(respond));

      if(respond==200){
        
        String Body_respond = http.getString();
        Serial.println(Body_respond);
        if(Body_respond == "yes"){
          Serial.println("Existe");
          GreenBlink();
        }else{
          Serial.println("No");
          RedBlink();
        }
        
      }else{
        RedBlink();
      }
    }
}
