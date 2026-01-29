#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

#define DHTPIN D4
#define DHTTYPE DHT11
#define MQ135 A0

char auth[] = "YOUR_BLYNK_AUTH_TOKEN";
char ssid[] = "YOUR_WIFI_NAME";
char pass[] = "YOUR_WIFI_PASSWORD";

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;

void sendData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  int gas = analogRead(MQ135);

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, gas);
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(2000L, sendData);
}

void loop() {
  Blynk.run();
  timer.run();
}
