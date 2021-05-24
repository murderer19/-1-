#include <SoftwareSerial.h>                           
#define rx 2                                         
#define tx 3                                          

SoftwareSerial myserial(rx, tx);                      


String inputstring = "";                             
String sensorstring = "";                           
boolean input_string_complete = false;               
boolean sensor_string_complete = false;              
float pH;                                             



void setup() {                                        
  Serial.begin(9600);                               
  myserial.begin(9600);                               
  inputstring.reserve(10);                           
  sensorstring.reserve(30);                          
}


void serialEvent() {                                 
  inputstring = Serial.readStringUntil(13);          
  input_string_complete = true;                       
}


void loop() {                                        

  if (input_string_complete == true) {              
    myserial.print(inputstring);                     
    myserial.print('\r');                           
    inputstring = "";                                
    input_string_complete = false;                 
  }

  if (myserial.available() > 0) {                     
    char inchar = (char)myserial.read();           
    sensorstring += inchar;                           
    if (inchar == '\r') {                             
      sensor_string_complete = true;                  
    }
  }


  if (sensor_string_complete == true) {               
    Serial.println(sensorstring);                     
    /*                                                 
    if (isdigit(sensorstring[0])) {                   
      pH = sensorstring.toFloat();                   
      if (pH >= 7.0) {                                
        Serial.println("high");                      
      }
      if (pH <= 6.999) {                             
        Serial.println("low");                        
      }
    }
    */
    sensorstring = "";                             
    sensor_string_complete = false;                   
  }
}
