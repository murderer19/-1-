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


  if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
    Serial.println(sensorstring);                     //send that string to the PC's serial monitor
    /*                                                //uncomment this section to see how to convert the pH reading from a string to a float 
    if (isdigit(sensorstring[0])) {                   //if the first character in the string is a digit
      pH = sensorstring.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
      if (pH >= 7.0) {                                //if the pH is greater than or equal to 7.0
        Serial.println("high");                       //print "high" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH <= 6.999) {                              //if the pH is less than or equal to 6.999
        Serial.println("low");                        //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
    }
    */
    sensorstring = "";                                //clear the string
    sensor_string_complete = false;                   //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
  }
}
