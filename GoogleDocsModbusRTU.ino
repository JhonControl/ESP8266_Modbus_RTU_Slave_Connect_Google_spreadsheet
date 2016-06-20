/*
 *  HTTPS with follow-redirect example
 *  Created by Sujay S. Phadke, 2016
 *  
 *  Based on the WifiClientSecure example by
 *  Ivan Grokhotkov
 *  *
 *  This example is in public domain.
 *
 *
 * Modified by PDAControl Jhon Valencia   -- ESP8266 Direct connection PLC Panasonic + Modbus RTU
 * http://pdacontrolenglish.blogspot.com.co
 * http://pdacontrol.blogspot.com.co
 * https://youtu.be/5f7wCeD4gB4
 *
 */


#include <modbus.h>   ///  https://github.com/JhonControl/ESP8266-Modbus-RTU-Slave-Emoncms/tree/master/Modbus    Library Modbus
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>

#include <ESP8266WiFi.h>
#include "HTTPSRedirect.h"


modbusDevice regBank;
modbusSlave slave;


// Replace with your network credentials
const char* ssid = "#########";
const char* password = "#####";




const char* host = "script.google.com";
const char* googleRedirHost = "script.googleusercontent.com";
const char *GScriptId = "################################################";
const int httpsPort = 443;

// http://askubuntu.com/questions/156620/how-to-verify-the-ssl-fingerprint-by-command-line-wget-curl/
// echo | openssl s_client -connect script.google.com:443 |& openssl x509 -fingerprint -noout
// www.grc.com doesn't seem to get the right fingerprint
// SHA1 fingerprint of the certificate

const char* fingerprint = "4B 28 4E 4C 36 AF 7C AF 51 49 C2 51 D3 D9 FC E5 62 47 E1 7A";


// Write to Google Spreadsheet
String url = String("/macros/s/") + GScriptId + "/exec?now=ESP8266_PLC_Panasonic_Connected";
// Fetch Google Calendar events for 1 week ahead
String url2 = String("/macros/s/") + GScriptId + "/exec?cal";
// Read from Google Spreadsheet
String url3 = String("/macros/s/") + GScriptId + "/exec?read";


int reintentos;

void setup() {
//  Serial.begin(9600);
//  Serial.println();
// Serial.print("Connecting to wifi: ");
// Serial.println(ssid);
  
  
  // flush() is needed to print the above (connecting...) message reliably, 
  // in case the wireless connection doesn't go through
  Serial.flush();
  
  
  
  //Assign the modbus device ID.  
  regBank.setId(1);
  regBank.add(160);
  regBank.add(161);  
  
  regBank.add(40001);  
  regBank.add(40002);  
  regBank.add(40003);  
  regBank.add(40004);  
  regBank.add(40005);  
  regBank.add(40006);  
  regBank.add(40007);  
  regBank.add(40008);  
  regBank.add(40009);  
  regBank.add(40010);  
  regBank.add(40100);  
  regBank.add(40101);  

  slave._device = &regBank;  
  slave.setBaud(19200);   //19200 None    Modbus 
    

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  //  Serial.print(".");
  }
 // Serial.println("");
 // Serial.println("WiFi connected");
 // Serial.println("IP address: ");
 // Serial.println(WiFi.localIP());

  // Use HTTPSRedirect class to create TLS connection
  HTTPSRedirect client(httpsPort);
 // Serial.print("Connecting to ");
 // Serial.println(host);

  bool flag = false;
  for (int i=0; i<5; i++){
    int retval = client.connect(host, httpsPort);
    if (retval == 1) {
       flag = true;
       break;
    }
    else
    //  Serial.println("Connection failed. Retrying...");
    ;
  }
  
 // Serial.flush();
  if (!flag){
 ////   Serial.print("Could not connect to server: ");
 //   Serial.println(host);
 //   Serial.println("Exiting...");
 ;
    return;
  }
  
 // Serial.flush();
  if (client.verify(fingerprint, host)) {
 //   Serial.println("Certificate match.");
 ;
  } else {
  //  Serial.println("Certificate mis-match");
    ;
  }

  // Note: setup() must finish within approx. 1s, or the the watchdog timer
  // will reset the chip. Hence don't put too many requests in setup()
  // ref: https://github.com/esp8266/Arduino/issues/34
  
  //Serial.print("Requesting URL: ");
  //Serial.println(url);

  client.printRedir(url, host, googleRedirHost);
  //Serial.println("==============================================================================");
  
 /// client.printRedir(url2, host, googleRedirHost);
  //Serial.println("==============================================================================");

}

void loop() {
  HTTPSRedirect client(httpsPort);
  if (!client.connected())
    client.connect(host, httpsPort);
       
    delay(250);
    reintentos++;     
     
    // convert float to char 
    char outstr1[15];
    float valor = regBank.get(40001);    Holding Registers   0 - 1 
    dtostrf(valor,4, 2, outstr1);   //float to char  4 numero de caracteres  3 cifras sin espacio
    String cadena = outstr1;   // char to string

     if (reintentos>=12){   
       cadena.replace(".", ",");
       url = String("/macros/s/") + GScriptId + "/exec?value="+cadena ;     
       client.printRedir(url, host, googleRedirHost);
       reintentos=0;   
      }
            
    slave.run();
    

}

 
