#include <Arduino.h>
#include <Espini.h>
#include "config.h"
#include "ver.h"
#include <iostream>
#include <string>
#include <ESP8266WebServer.h>
#include "EmonLib.h"

EnergyMonitor    emon;
ESP8266WebServer server(80);
Espini *esp;

void responde() {
  char amp[90];
  snprintf(amp, sizeof amp,"%.2f",emon.calcIrms(1480));
  esp->log(amp);
  server.send(200,"text/plain",amp);  
}

void reset() {
   ESP.reset();
}

void setup() { 
  esp=new Espini(wifis(),"acmonitor",ver,otasrv,logsrv);
  emon.current(A0, 28.0); // Calibrado empirico
  server.on  ("/",responde);
  server.on  ("/reset",reset);
  server.begin();
}

void loop() {
  server.handleClient();
}



