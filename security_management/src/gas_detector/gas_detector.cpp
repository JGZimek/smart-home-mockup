#include "gas_detector.hpp"
#include "esp_log.h"
#include "../mqtt/mqtt.hpp"
#include "../buzzer/buzzer.hpp"

#define GAS_DETECTOR_TAG "app_gas_detector"

#define GAS_ANALOG_PIN 32
#define GAS_DIGITAL_PIN 35

// Macros and variables used for debouncing and tracking how long the alarm has been on.
// It was needed since the state of GAS_DIGITAL_PIN was very unstalbe with the presence of gas.

#define GAS_DETECTION_END_DELAY 3000 // 3 seconds delay to stop the alarm after gas is cleared
unsigned long endTime = {0}; 
unsigned long timeAlarmON = {0};  
unsigned long timeAlarmOFF = {0};  

char printBuffer[100]; // Buffer for printing messages

bool lastSensorValue = false;
bool init_gas_detector()
{
    ESP_LOGI(GAS_DETECTOR_TAG, "Initializing gas detector...");

    pinMode(GAS_ANALOG_PIN, INPUT);
    pinMode(GAS_DIGITAL_PIN, INPUT);

    ESP_LOGI(GAS_DETECTOR_TAG, "Gas detector initialized successfully");

    return true;
}

void handle_gas_detector()
{
    // if it detected gas, and it was not detected before:
    if (digitalRead(GAS_DIGITAL_PIN) == LOW && lastSensorValue == false)
    {
        timeAlarmON = millis(); // Start the alarm time
        ESP_LOGI(GAS_DETECTOR_TAG, "Gas detected!");
        lastSensorValue = true;
        set_buzzer_alarm(lastSensorValue); // Activate the buzzer alarm
        endTime =0; // Reset the end time since gas is detected again
    }

    if (digitalRead(GAS_DIGITAL_PIN) == HIGH){
        // if the sensor stops detecting gas and did before, start the timer
        if (lastSensorValue == true && endTime == 0){ 
            endTime = millis();
        }

        // if the sensor stops detecting gas for GAS_DETECTION_END_DELAY milliseconds, stop the alarm
        if (endTime > 0 && millis() - endTime >= GAS_DETECTION_END_DELAY){
            timeAlarmOFF = millis();
            lastSensorValue = false; 
            set_buzzer_alarm(lastSensorValue);
            sprintf(printBuffer, "Alarm caused by gas detection stopped. It lasted %lu s", (timeAlarmOFF - timeAlarmON) / 1000);
            Serial.println(printBuffer);
            endTime = 0;
        }

    } else{
        endTime = 0; // Reset the end time if gas is detected again
    }
    
}


