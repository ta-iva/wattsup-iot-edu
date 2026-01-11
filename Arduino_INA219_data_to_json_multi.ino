#include <Wire.h>
#include <Adafruit_INA219.h>

#define ADDR1 0x40
#define ADDR2 0x41

Adafruit_INA219 ina219a(ADDR1);
Adafruit_INA219 ina219b(ADDR2);

void setup() {
  Serial.begin(9600);
  ina219a.begin();
  ina219b.begin();
  ina219a.setCalibration_16V_400mA();
  ina219b.setCalibration_16V_400mA();
}

String getSensorDataJSON(Adafruit_INA219 &sensor, const char *sensorName) {
  float napetiVstup = sensor.getBusVoltage_V();
  float napetiBocnik = sensor.getShuntVoltage_mV();
  float napetiZatez = napetiVstup + (napetiBocnik / 1000);
  float proud = sensor.getCurrent_mA();

  // Vytvoření JSON stringu pro jeden senzor
  String json = "";
  json += "\"" + String(sensorName) + "\": {";
  json += "\"napetiVstup\": " + String(napetiVstup, 2) + ",";
  json += "\"napetiBocnik\": " + String(napetiBocnik, 2) + ",";
  json += "\"napetiZatez\": " + String(napetiZatez, 2) + ",";
  json += "\"proud\": " + String(proud, 2);
  json += "}";

  return json;
}

void loop() {
  // Sestavení kompletního JSON objektu
  String jsonOutput = "{";
  jsonOutput += getSensorDataJSON(ina219a, "INA219a") + ",";
  jsonOutput += getSensorDataJSON(ina219b, "INA219b");
  jsonOutput += "}";

  // Odeslání JSON na sériovou linku
  Serial.println(jsonOutput);

  // Pauza před dalším měřením
  delay(1000);
}
