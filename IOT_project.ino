#define BLYNK_TEMPLATE_ID "TMPL3Bes6xlP7"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "xReJLDz75RsoWiAk622HzT2ACy7iu4h3"

#define BLYNK_PRINT Serial
#include <WiFi.h>
//#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp32.h> 
#include <DHT.h>


char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "";
char pass[] = "";

BlynkTimer timer;


#define DHTPIN 4 //Connect Out pin to D2 in NODE MCU
#define DHTTYPE DHT11  
#define relay1_pin 26
int relay1_state = 0;
DHT dht(DHTPIN, DHTTYPE);
#define button1_vpin V2


BLYNK_CONNECTED() {
  Blynk.syncVirtual(button1_vpin);
}

BLYNK_WRITE(button1_vpin) {
  relay1_state = param.asInt();
  digitalWrite(relay1_pin, relay1_state);
}

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
    Blynk.virtualWrite(V0, t);
    Blynk.virtualWrite(V1, h);
    Serial.print("Temperature : ");
    Serial.print(t);
    Serial.print("Humidity : ");
    Serial.println(h);
}
void setup()
{   
  
  Serial.begin(115200);
  
  pinMode(relay1_pin, OUTPUT);
  
  digitalWrite(relay1_pin, HIGH);
  

  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(100L, sendSensor);
 
  }

void loop()
{
  Blynk.run();
  timer.run();
 }