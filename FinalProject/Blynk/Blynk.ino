/*************************************************************
  Download latest Blynk library here:
    https://github.com/blynkkk/blynk-library/releases/latest

  Blynk is a platform with iOS and Android apps to control
  Arduino, Raspberry Pi and the likes over the Internet.
  You can easily build graphic interfaces for all your
  projects by simply dragging and dropping widgets.

    Downloads, docs, tutorials: http://www.blynk.cc
    Sketch generator:           http://examples.blynk.cc
    Blynk community:            http://community.blynk.cc
    Follow us:                  http://www.fb.com/blynkapp
                                http://twitter.com/blynk_app

  Blynk library is licensed under MIT license
  This example code is in public domain.

 *************************************************************

  You can use this sketch as a debug tool that prints all incoming values
  sent by a widget connected to a Virtual Pin 1 in the Blynk App.

  App project setup:
    Slider widget (0...100) on V1
 *************************************************************/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ec8cd63bb6b84743b937ca8380efae9f";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Rachels rMBP";
char pass[] = "syclone6505";

int flag = 0;
int finishedFlag = 1;

//WidgetLED led1(V2);

// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V2)
{
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  // You can also use:
  // String i = param.asStr();
  // double d = param.asDouble();
  Serial.print("V1 Slider value is: "); 
  Serial.println(pinValue);

  

  if(pinValue == 1){
     digitalWrite(D0, HIGH);
  }
  else{
     digitalWrite(D0, LOW);
  }
}

void notifyOnButtonPress()
{
  // Invert state, since button is "Active LOW"
  int isButtonPressed = !digitalRead(D2);
  if (isButtonPressed) {
    Serial.println("Button is pressed.");

    // Note:
    //   We allow 1 notification per 15 seconds for now.
    Blynk.notify("SYSTEM ALARMED");
  }
}

void setup()
{
  // Debug console

  pinMode(D0, OUTPUT);

  
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);

  pinMode(D2, INPUT_PULLUP  );
  // Attach pin 2 interrupt to our handler
  attachInterrupt(digitalPinToInterrupt(D2), notifyOnButtonPress, CHANGE);

}

void loop()
{
  Blynk.run();
}

