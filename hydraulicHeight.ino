
#include "Arduino.h"

#define VOLTAGE_SENSOR A0
#define PIN_WORKSWITCH 2


const float R1 = 30000.0f;  // R1 has 30 kOhm
const float R2 = 7500.0f;   // R2 has 7,5 kOhm

// Arduino max input voltage on analog input
// -> since its powered with 5V, its 5V
// If the arduino is powered with 3.3V,
// then this has to be changed
const float MAX_VIN = 5.0f; 

// limit value for "workswitch on"
const float VOLTAGE_IN_WORKPOSITION = 4.0f;

void setup(){
   Serial.begin(9600);
   pinMode(VOLTAGE_SENSOR, INPUT);
   pinMode(LED_BUILTIN, OUTPUT);
   pinMode(PIN_WORKSWITCH, OUTPUT);
}
void loop(){
    float vout = (analogRead(VOLTAGE_SENSOR) * MAX_VIN) / 1024.0f;
    float vin = vout / (R2/(R1+R2)); 

    Serial.print("Eingangsspannung ");
    Serial.print(vin,2);
    Serial.print("V");

    if(vin >= VOLTAGE_IN_WORKPOSITION){
        // we are in workswitch position -> singalize via builtin led
        // and power output to AGOpen steer arduino
        digitalWrite(LED_BUILTIN, HIGH);
        digitalWrite(PIN_WORKSWITCH, LOW);
        Serial.print("  Workswitch is ON");
    }
    else
    {
        // we are NOT in workswitch position
        digitalWrite(LED_BUILTIN, LOW);
        digitalWrite(PIN_WORKSWITCH, HIGH);
        Serial.print("  Workswitch is OFF");
    }
    Serial.println("");
    delay(500);
}