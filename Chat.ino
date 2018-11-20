#include "ESP8266WiFi.h"
#include "ESP8266WebServer.h"
#include "index.h"
#include "ArduinoJson.h"


const char *ssid = "Chat";
const char *password = "123456789";

ESP8266WebServer server(80);
const size_t capacityArray = JSON_ARRAY_SIZE(10) + 10*(JSON_OBJECT_SIZE(2)+100);
const size_t capacityObject = JSON_OBJECT_SIZE(2)+100;
StaticJsonDocument<capacityArray> doc;
JsonArray messages = doc.to<JsonArray>();

void handleRoot(){
  String html = HTML;
  server.send(200, "text/html", html);
}

void sendMessage(){
  
  if (server.arg("json").length() > 0){
      
      StaticJsonDocument<capacityObject> docRequest;
      String requestString = server.arg("json");
      char jsonEntry[requestString.length() + 1];
      requestString.toCharArray(jsonEntry, requestString.length());
      
      deserializeJson(docRequest, jsonEntry);
      Serial.println("sendMessage called with: " + server.arg("json"));
      JsonObject json = docRequest.as<JsonObject>();

      if (json.size()>0) {
        Serial.println("JSON success!");
        const char* jsonName = json["name"];
        const char* jsonMessage = json["message"];
        String clientName =  String(jsonName);
        String message =  String(jsonMessage);
        if(clientName.length()==0){
          clientName = server.client().remoteIP().toString();
        }
        Serial.println("Name: " + clientName+ " Message: " + message);
        StaticJsonDocument<capacityObject> docResult;
        JsonObject result = docResult.to<JsonObject>();
        result["name"] = clientName;
        result["message"] = message;

        if(messages.size() >= 10){
          messages.remove(0);
        }
        if(messages.add(result)){
          Serial.println("JsonObject added to messages!");
        }else{
          Serial.println("Not enough memory!");
        }
 
        String outputJson = "";
        serializeJson(doc, outputJson);
        serializeJson(doc, Serial);
        Serial.println("");
        server.send(200, "text/json", outputJson);
        
      }else{
        Serial.println("JSON parsing failed!");
      }
  }
}

void getMessages() {
  String outputJson = "";
  serializeJson(doc, outputJson);
  server.send(200, "text/json", outputJson);
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  // Sin contraseña
  // WiFi.softAP(ssid);
  
  // Iniciamos el servidor
  server.begin(); 
  
  Serial.print("Direccion IP del servidor: ");
  Serial.println(WiFi.softAPIP()); 

  server.on("/", handleRoot);
  server.on("/getMessages", getMessages);
  server.on("/sendMessage", HTTP_POST, sendMessage);
}

void loop() {
  server.handleClient();
}
