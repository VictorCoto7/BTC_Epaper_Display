#include <WiFi.h>
#include <HTTPClient.h>

/////Datos del wifi
const char* ssid ="MiWiFi";
const char* password = "123456789";

//url's para hacer peticiones
const char* example ="http://example.net/";
const char* duckduckgo ="http://duckduckgo.com/";


String answer;
const int requestInterval =7000; //son 7 segundos


//////////////////////////////////////////////////////

//////////////////////////////////////////////////////

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid,password);
  Serial.println("conecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a la red con la IP ");
  Serial.println(WiFi.localIP());
  Serial.println();
 
}

void loop() {
  if(WiFi.status()==WL_CONNECTED){
    answer = getRequest(example);
    Serial.println("\n Respuesta de example.net");
    Serial.println(answer);

    delay(requestInterval);

    answer = getRequest(duckduckgo);
    Serial.println("\n\n Respuesta de duckduckgo.com: ");
    Serial.println(answer);
  }
}
//////////////////////////////////////////////////////
 
String getRequest(const char* serverName){
  HTTPClient http;
  http.begin(serverName);

  //Enviar peticion HTTP
  int httpResponseCode = http.GET();

  String payload = "...";

  if(httpResponseCode >0){
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else{
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }

  http.end();

  return payload;
}