/************************************************************************************************
 * Alzhaimer Finder 
 * Project in Embedded Systems
 * Authors : 
 * Logothetis Fragkoulis 
 * Apostolos Bailakis 
 * 
 * Electrical and Computer Engineering 
 * Technical University of Crete
 * Department :HMMY
 * Lesson: Embedded -Cyber Phusical Systems 
 * 
 */

/*************************************************************************************************
 * For this project we used Teensy 3.2 Development Bord ,which it has 3
 * hardware serial inputs/outputs  using UART (Universal Asychronous Receiver Trasmitter).
 * We used RX1,TX1( Pins 0 ,1) and RX2,TX2 (Pins 9,10).
 * 
 * We Control each devise with the adove:
 * RX1,TX1( Pins 0 ,1)-->Gsm Sim900
 * 
 * RX2,TX2 (Pins 9,10)--->Gps GY-NEO6MV2 
 * 
 * 
 * ***********************************************************************************************
 */

//___________________________________Libraries and Member variables_________________________//
#include <TinyGPS++.h>
char incoming_char;
TinyGPSPlus gps;
int counter=0;
const int GPSen = 5 ;
const int ledPin = 13;
String textForSMS;
double lat_gps,lng_gps ;
int val;
float input_voltage = 0.0;


//___________________________________Arduino Setup Function________________________________//
void setup()
{
  Serial.begin(38400); //Teensy 3.2 works great with usb baudrates 
  Serial2.begin(9600);//Default Baudrate for Gps 
  Serial1.begin(19200);//Best baudrate for Sim900
  pinMode(GPSen, OUTPUT);
  pinMode(ledPin, OUTPUT);
   pinMode(6, OUTPUT);
   SIM900power();
}
//___________________________________Arduino Loop Function__________________________________//
void loop()
{
  
  
  // This sketch displays information every time a new sentence is correctly encoded.

  
  while (Serial1.available()>0)
  {
     incoming_char=Serial1.read(); 
     Serial.print(incoming_char);
    if(incoming_char=='@'){
      digitalWrite(GPSen, LOW);
      digitalWrite(ledPin, HIGH);   // set the LED on
      delay(17000);
      counter=0;
      Serial.println(counter);
      while(counter!=-1){
        
       
  while (Serial2.available() > 0 && counter!=-1){
    
    if (gps.encode(Serial2.read())){
      
    
      counter=displayInfo();
       val = analogRead(0);
      Serial.print("analog 0 is: ");
      Serial.println(val);
      input_voltage = ((1024.0-(float)val) / 1024.0)*100; 
      input_voltage = 100.0-input_voltage;
      
              
      }
  }
  
  

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS detected: check wiring."));
    while(true);
  }
  }
  }
  }
}

int  displayInfo()
{
  
  counter++;
//terminal condition 
  if(counter==56){
  
    counter=-1;
    textForSMS = "Alzhaimer Finder: http://www.google.com/maps/place/";
    textForSMS.concat(lat_gps);
    textForSMS = textForSMS + ",";
    textForSMS.concat(lng_gps);
    textForSMS = textForSMS + "  **Battery  : ";
     textForSMS.concat(input_voltage);
     textForSMS = textForSMS + " %";
     Serial.println("");
    Serial.println(textForSMS);
    sendSMS(textForSMS) ; 

    return counter;
    }


   Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(gps.location.lat(), 6);
    lat_gps=(gps.location.lat());
    Serial.print(F(","));
    Serial.print(gps.location.lng(), 6);
    lng_gps=(gps.location.lng());
  }
  else
  {
    lat_gps=0.000;
    lng_gps=0.000;
    Serial.print(F("INVALID"));
  }

  Serial.print(F("  Date/Time: "));
  if (gps.date.isValid())
  {
    Serial.print(gps.date.month());
    Serial.print(F("/"));
    Serial.print(gps.date.day());
    Serial.print(F("/"));
    Serial.print(gps.date.year());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.print(F(" "));
  if (gps.time.isValid())
  {
    if (gps.time.hour() < 10) Serial.print(F("0"));
    Serial.print(gps.time.hour());
    Serial.print(F(":"));
    if (gps.time.minute() < 10) Serial.print(F("0"));
    Serial.print(gps.time.minute());
    Serial.print(F(":"));
    if (gps.time.second() < 10) Serial.print(F("0"));
    Serial.print(gps.time.second());
    Serial.print(F("."));
    if (gps.time.centisecond() < 10) Serial.print(F("0"));
    Serial.print(gps.time.centisecond());
  }
  else
  {
    Serial.print(F("INVALID"));
  }

  Serial.println();
  return counter;
}

//__________Software equivalent of pressing the GSM shield "power" button_____//
void SIM900power()
{
digitalWrite(6, HIGH);
delay(1000);
digitalWrite(6, LOW);
delay(7000);
}

///___________________________________Sms Sent____________________________//

void sendSMS(String message)
{
digitalWrite(GPSen, HIGH);
digitalWrite(ledPin, LOW);    // set the LED off

Serial1.print("AT+CMGF=1\r"); // AT command to send SMS message
delay(100);
Serial1.println("AT + CMGS = \"+000000000000\""); // recipient's mobile number, in international format
delay(100);
Serial1.println(message); // message to send
delay(100);
Serial1.println((char)26); // End AT command with a ^Z, ASCII code 26
delay(100);
Serial1.println();
delay(5000); // give module time to send SMS


}

