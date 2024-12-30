//This code exectutes the same result as fsr_communication.ino, however the signal is sent over a bluetooth communication protocol, instead of serial, allowing this communication interface to be wireless//



//calling in libraries used for bluetooth communication//
#include <SPI.h>
#include "Adafruit_BLE_UART.h"

#define ADAFRUITBLE_REQ 10
#define ADAFRUITBLE_RDY 3
#define ADAFRUITBLE_RST 9

Adafruit_BLE_UART BTLEserial = Adafruit_BLE_UART(ADAFRUITBLE_REQ, ADAFRUITBLE_RDY, ADAFRUITBLE_RST);
aci_evt_opcode_t laststatus = ACI_EVT_DISCONNECTED;

//defining variables//
int FsrPin = 0;
int ledPin1 = 15;
int ledPin2 = 16;
int ledPin3 = 17;
int ledPin4 = 18;
int LEDbrightness;
int FsrReading;
int incomingByte = 0;
int bytesAvailable = 0;
int i = 0;
int readSuccess = 0;
int writeCount = 0;

void setup() 
{
  Serial.begin(9600);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(ledPin1, HIGH);
  digitalWrite(ledPin2, HIGH);
  digitalWrite(ledPin3, HIGH);
  digitalWrite(ledPin4, HIGH);
  digitalWrite(13, LOW);
  BTLEserial.begin();
  
  
}

void loop()
{
  FsrReading = analogRead(FsrPin);

  //Serial.print("Analog reading = ");
  if (writeCount == 5000)
  {
    Serial.print(FsrReading);
    writeCount = 0;
  }
  else
  {
    writeCount++;
  }
   // Tell the nRF8001 to do whatever it should be working on.
  BTLEserial.pollACI();
  
  // Ask what is our current status
  aci_evt_opcode_t status = BTLEserial.getState();
  // If the status changed....
  if (status != laststatus)
  {
    // print it out!
    if (status == ACI_EVT_DEVICE_STARTED) 
    {
        Serial.println(F("* Advertising started"));
    }
    if (status == ACI_EVT_CONNECTED) 
    {
        Serial.println(F("* Connected!"));
    }
    if (status == ACI_EVT_DISCONNECTED) 
    {
        Serial.println(F("* Disconnected or advertising timed out"));
    }
    // OK set the last status change to this one
    laststatus = status;
  }
  
  //delay(1000);
  
  if (status == ACI_EVT_CONNECTED)
  {
    if (BTLEserial.available())
    {
      bytesAvailable = Serial.available();

      if (bytesAvailable)
      {
        for (i=0;i<bytesAvailable; i++)
        {
          
            incomingByte = Serial.read();
            readSuccess = 1;
            //digitalWrite(15, HIGH);
            //delay(200);
            //digitalWrite(15, HIGH);
        }

        bytesAvailable=0;
        
        //digitalWrite(13, HIGH);
        //delay(1000);
        //digitalWrite(13, LOW);
        
    
    if (readSuccess == 1)
    {
      /*digitalWrite(13, HIGH);
      delay(1000);
      digitalWrite(13, LOW);*/
        switch ((int)incomingByte)
        {
          case 1:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin4, HIGH);
            break;  
          case 2:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin4, HIGH);
            break;   
          case 3:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
            digitalWrite(ledPin4, HIGH);
            break;         
          case 4:
            digitalWrite(ledPin1, LOW);
            digitalWrite(ledPin2, LOW);
            digitalWrite(ledPin3, LOW);
            digitalWrite(ledPin4, LOW);                    
            break;                                  

          default:
            digitalWrite(ledPin1, HIGH);
            digitalWrite(ledPin2, HIGH);
            digitalWrite(ledPin3, HIGH);
            digitalWrite(ledPin4, HIGH);
            break;
        }
        readSuccess = 0;
    }
  }
 }
}

}
