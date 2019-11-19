
#include <BlynkSimpleEsp8266.h>

#include<ESP8266WiFi.h>
#include "WiFiClient.h"
#include "PubSubClient.h"
#include "DHTesp.h"
#include <Servo.h>
Servo servo;
  

int sensor_pin=A0;



int ldr=D5;
char auth[] = "PwsxPNgiCXat8WW9Z1D-TOjGirHd-VcE";

//#define dht_apin 02
DHTesp dht;

char* ssid="WiFi";
char* password="PASSword11089";
WiFiClient client;


int pump_pin=D3;

void setup()
{
Blynk.begin(auth,ssid,password);
Serial.begin(115200);
Serial.println("connecting to.....");
Serial.println(ssid);
WiFi.begin(ssid,password);
while (WiFi.status() !=WL_CONNECTED)
{
  delay(500);
  Serial.println(".");
}
Serial.println(" ");
Serial.println("WiFi connected");
dht.setup(02,DHTesp::DHT11);

servo.attach(05);   //servo connected to D1
pinMode(pump_pin,OUTPUT); //Pump connecteod to D3
pinMode(ldr,INPUT);

}
void loop()
{
  Blynk.run();
  delay(2000);
  Serial.println(analogRead(sensor_pin));
  float moisture_percentage;
  moisture_percentage=(100.00-((analogRead(sensor_pin)/1023.00)*100));
  Serial.println("soil moisture");
  if(moisture_percentage<=30)
  {
    digitalWrite(D3,HIGH);
    delay(1000);
  }else{
    digitalWrite(D3,LOW);
  }
  
  Serial.println(moisture_percentage);
  float humidity=dht.getHumidity();
  
  float temperature=dht.getTemperature();
  Serial.println("Humidity=");
  Serial.println(humidity);
  delay(2000);
  Serial.println("Temperature=");
  Serial.println(temperature);
  if(temperature>30)
  {
    servo.write(90);
  }else{
    servo.write(0);
  }
  delay(1000);
  Serial.println("ldr value");
  Serial.println(digitalRead(ldr));
  Blynk.virtualWrite(V4,humidity);
  Blynk.virtualWrite(V5,temperature);
  Blynk.virtualWrite(V6,moisture_percentage); 
  Blynk.virtualWrite(V7,ldr); 
 
 
 
 /* delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("waiting for WiFi to turn on");
  WiFi.softAP(ssid,password);
  Serial.println("AP is.......");
  Serial.println(WiFi.softAPIP());
  Serial.println(ssid);
  Serial.println("WiFi module connected");
 */ 
}
