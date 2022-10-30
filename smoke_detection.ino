
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_PRINT Serial    
char auth[] = "Ieq2eYNfPS1W0eSIuoCYpf8Xs36iaps2"; 

char ssid[] = "Redmif"; 
char pass[] = "123456789"; 

SimpleTimer timer;
 
int mq2 = A0; 
int data = 0; 
int buzzer = 4;
int led_green = 14;
int led_red = 12; 


void setup() 
{
pinMode(buzzer, OUTPUT);
pinMode(mq2, INPUT);
pinMode(led_green, OUTPUT);
pinMode(led_red, OUTPUT);
digitalWrite(led_green, LOW);
digitalWrite(led_red, LOW);

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(1000L, getSendData);
}
 
void loop() 
{
  timer.run();
  Blynk.run();
}
 
void getSendData()
{
data = analogRead(mq2); 
Serial.print("Gas Level: ");
Serial.println(data);
Blynk.virtualWrite(V2, data);
 
  if (data > 450 )
  {
    digitalWrite(led_green, LOW);
digitalWrite(led_red, HIGH);
digitalWrite(buzzer, HIGH);
Blynk.notify("Alert: Smoke Detected");
Blynk.email("Alert!!!" , " Smoke Detected");
delay(500);
digitalWrite(buzzer, LOW);
  }else
{
digitalWrite(buzzer, LOW);
digitalWrite(led_green, HIGH);
digitalWrite(led_red, LOW);
}

}
