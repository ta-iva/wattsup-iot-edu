// INA3221: triple-channel, high-side current and bus voltage monitor with I2C interface

// import library
#include <SDL_Arduino_INA3221.h>

// create sensor object from library
SDL_Arduino_INA3221 ina3221;

// create measurement variables
float busVoltage;
float shuntVoltage;
float loadCurrent;
float loadVoltage;

void setup() {
  // start communication over serial line
  Serial.begin(9600);
  // start communication with sensor
  ina3221.begin();
}

void loop() {
  // iterate channels CH1-CH3
  for (int i = 1; i <= 3; i++) {
    // read sensor data
    busVoltage = ina3221.getBusVoltage_V(i);
    shuntVoltage = ina3221.getShuntVoltage_mV(i);
    loadCurrent = ina3221.getCurrent_mA(i);
    // calculate load voltage
    loadVoltage = busVoltage + (shuntVoltage / 1000.0);
    // print data via serial line
    Serial.print("Kanal CH");
    Serial.print(i);
    Serial.println(":");
    Serial.print("Napeti zdroje:     ");
    Serial.print(busVoltage);
    Serial.println(" V");
    Serial.print("Napeti na bocniku: ");
    Serial.print(shuntVoltage);
    Serial.println(" mV");
    Serial.print("Napeti na zatezi:  ");
    Serial.print(loadVoltage);
    Serial.println(" V");
    Serial.print("Proud zatezi:      ");
    Serial.print(loadCurrent);
    Serial.println(" mA");
    Serial.println();
  }
  Serial.println("------------------------------");
  delay(1000);
}