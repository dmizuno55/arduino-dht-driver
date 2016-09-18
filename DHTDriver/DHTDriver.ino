#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void sendData(char* data);
char* convertToJSON(float t, float h);

void setup() {
  Serial.begin(115200);
  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    sendData("{\"error\": \"Failed to read from DHT sensor!\"}");
    return;
  }

  sendData(convertToJSON(t, h));
}

void sendData(char* data) {
  Serial.println(data);
}

char* convertToJSON(float t, float h) {
  char json[256];
  char formatedT[10];
  char formatedH[10];

  dtostrf(t, 4, 2, formatedT);
  dtostrf(h, 4, 2, formatedH);
  sprintf(json, "{\"temperature\": %s,\"humdity\": %s}", formatedT, formatedH);

  return json;
}
