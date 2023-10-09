#include <ESP8266WebServer.h>
#include <ESP8266WiFi.h>
#include "html.h"

#include <DHT.h>
#define chandht 5
#define loaidht DHT11
DHT dht(chandht, loaidht);

float nhietdo;
float doam;


const String tenwifi = "Nam";
const String nkwifi = "namkute123";
ESP8266WebServer server(80);

void ketnoi(){
  String s = MAIN_page;
  server.send(200,"text/html",s);
}
void docdulieunhietdo(){
  nhietdo = dht.readTemperature();
  String snhietdo = String(nhietdo);
  if(isnan(nhietdo)){
    server.send(200,"text/plain","cam bien khong hoat dong");
  }else{
    server.send(200,"text/plain",snhietdo);
  }
}

void docdulieudoam(){
  doam = dht.readHumidity();
  String sdoam = String(doam);
  if(isnan(doam)){
    server.send(200,"text/plain","cam bien khong hoat dong");
  }else{
    server.send(200,"text/plain",sdoam);
  }
}




void setup(){
  Serial.begin(115200);
  pinMode(chandht,INPUT);
  dht.begin();

  Serial.println("");
  Serial.print("ket noi den WiFi");
  Serial.println(tenwifi);
  WiFi.begin(tenwifi,nkwifi);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
}
Serial.println("");
Serial.println("WiFi da duoc ket noi");
Serial.println("dia chi IP: ");
Serial.println(WiFi.localIP());

server.on("/",ketnoi);
server.on("/docnhietdo",docdulieunhietdo);
server.on("/docdoam",docdulieudoam);
server.begin();
}


void loop() {
  server.handleClient();

}
