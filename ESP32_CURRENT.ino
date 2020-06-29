const int vp=32;// set the analog read pin to 32
long lastsample=0;
long samplesum=0;
long samplecount=0;
float vpc=0.8056; // for esp 32(12bit ADC)3300mv is measured in steps of 0.8056mV which is 3300mV/(2^12) which is 3300/4096 

#define BLYNK_PRINT Serial 
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
char auth[] = " "; // get blynk auth token from your registered email

char ssid[] = " "; // Enter your WiFi SSID
char pass[] = " "; // Enter your wifi password
void setup() 
{
Serial.begin(115200);
Blynk.begin(auth, ssid, pass);
}

void loop() {
Blynk.run();
if(millis()>lastsample+1) //take a sample every milisecond
{
  samplesum=samplesum+sq(analogRead(vp)-1810); 
  samplecount++;
  lastsample=millis();
}
if(samplecount==500)
{
  float mean=(samplesum)/500;
  float mean1=sqrt(mean);
  float mv=mean1*vpc;
  float current=mv*0.01590;
  Serial.println("The current is:" +String(current));// open serial monitor to observe current reading
  Blynk.virtualWrite(V4,current); // open blynk app to observe current reading
  samplecount=0;
  samplesum=0;
}
}
