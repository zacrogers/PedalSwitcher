#include <stdlib.h>
#include <SPI.h>
#include <SD.h>

char serial;
File myFile;      
     
void setup()
{    
  Serial.begin(9600);
    while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  if (!SD.begin(4)) 
  {
    return;
  }

  
}

void loop()
{
  if(Serial.available() > 0)
  {
      serial = Serial.read();
      Serial.println(serial, HEX);
      
      if(serial != -1)
      {
        myFile = SD.open("test.txt", FILE_WRITE);
        
        if (myFile) 
        {
          myFile.println(serial);
          myFile.close();
        }
      }
   } 
}
