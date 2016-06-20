# Connection PLC fpx Panasonic and Google spreadsheets (Google docs) with ESP8266

Esta prueba permite utilizar un ESP8266 como puente con Google Docs, 
para direccionarlo a una aplicacion industrial se ha creado una rutina como Esclavo Modbus RTU 
para realizar la lectura de un PLC Panasonic, esta rutina funciona con cualquier Controlador que
Soporte Modbus RTU en este caso RS232.

This test allows a ESP8266 as a bridge with Google Docs, to direct it to an industrial
application has created a routine as Modbus Slave RTU for reading a PLC Panasonic, 
this routine works with any controller that supports Modbus RTU in this case RS232 .

Contenido - Content
GoogleDocs_Modbus_PLC.ino  (Modbus Slave RTU)
LoggerPanasonic.gs

HTTPSRedirect.h     --Libreria modificada para utilizar el Serial para Modbus RTU
HTTPSRedirect.cpp   --Librery modified to use the Serial to Modbus RTU
HTTPSRedirect.cpp   --Librery modified to use the Serial to Modbus RTU


# Mas informacion
http://pdacontrolenglish.blogspot.com.co
http://pdacontrol.blogspot.com.co
https://www.youtube.com/c/JhonValenciaPDAcontrol
 
# HTTPSRedirect  Tutorial 
https://youtu.be/5f7wCeD4gB4

HTTPSRedirect  Github 
https://github.com/electronicsguy/ESP8266/tree/master/HTTPSRedirect

Thanks to the creator of the library HTTPSRedirect
Sujay Phadke
electronicsguy