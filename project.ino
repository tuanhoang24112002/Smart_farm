#define BLYNK_TEMPLATE_ID "TMPL6xis-WkOy"
#define BLYNK_TEMPLATE_NAME "ESP8266"
#define BLYNK_AUTH_TOKEN "P-NYeS-MFcM_0jwphYC6WwLAA6FiqraV"
#define BLYNK_PRINT Serial
#include <DHT.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;
double h,t;
int on_off_pump;

char ssid[] = "Tuan Hoang";
char pass[] = "24112002";
DHT dht(2, DHT11); 
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  dht.begin();
  Blynk.begin(BLYNK_AUTH_TOKEN,ssid,pass);
  pinMode(D0,OUTPUT);
  
  

}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
  h = dht.readHumidity();
  t = dht.readTemperature(false);
  int value = analogRead(A0);
  delay(100);
  float moisture = map(value,0,1023,100,0);

  // Serial.print("Soil moisture: ");
  Serial.print(moisture);
  Serial.println("%");
  // // Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println("%");
  // // Serial.print("temperature: ");
  Serial.print(t);
  Serial.println(" Celcius Degree");
  Blynk.virtualWrite(V1,t);
  Blynk.virtualWrite(V2,h);
  Blynk.virtualWrite(V3,moisture);


  if((moisture<10.0) || (on_off_pump==1))
  {
    digitalWrite(D0,HIGH);

  }
  else{
    digitalWrite(D0,LOW);
  }
}
BLYNK_WRITE(V0)
{
  on_off_pump = param.asInt();
}
