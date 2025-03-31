#include "smoke_detector.hpp"
#include "esp_log.h"
#include "../mqtt/mqtt.hpp"
#include "../buzzer/buzzer.hpp"

#define SMOKE_DETECTOR_TAG "app_smoke_detector"

#define SMOKE_ANALOG_PIN 32
#define SMOKE_DIGITAL_PIN 35

// Macros and variables used for debouncing and tracking how long the alarm has been on.
// It was needed since the state of SMOKE_DIGITAL_PIN was very unstalbe with the presence of gas.

#define SMOKE_DETECTION_END_DELAY 3000 // 3 seconds delay to stop the alarm after smoke is cleared
unsigned long endTime = {0}; 
unsigned long timeAlarmON = {0};  
unsigned long timeAlarmOFF = {0};  

char printBuffer[100]; // Buffer for printing messages

bool lastSensorValue = false;
bool init_smoke_detector()
{
    ESP_LOGI(SMOKE_DETECTOR_TAG, "Initializing smoke detector...");

    pinMode(SMOKE_ANALOG_PIN, INPUT);
    pinMode(SMOKE_DIGITAL_PIN, INPUT);

    ESP_LOGI(SMOKE_DETECTOR_TAG, "Smoke detector initialized successfully");

    return true;
}

void handle_smoke_detector()
{
    // if it detected gas, and it was not detected before:
    if (digitalRead(SMOKE_DIGITAL_PIN) == LOW && lastSensorValue == false)
    {
        timeAlarmON = millis(); // Start the alarm time
        ESP_LOGI(SMOKE_DETECTOR_TAG, "Smoke detected!");
        lastSensorValue = true;
        set_buzzer_alarm(lastSensorValue); // Activate the buzzer alarm
        endTime =0; // Reset the end time since smoke is detected again
    }

    if (digitalRead(SMOKE_DIGITAL_PIN) == HIGH){
        // if the sensor stops detecting gas and did before, start the timer
        if (lastSensorValue == true && endTime == 0){ 
            endTime = millis();
        }

        // if the sensor stops detecting gas for SMOKE_DETECTION_END_DELAY milliseconds, stop the alarm
        if (endTime > 0 && millis() - endTime >= SMOKE_DETECTION_END_DELAY){
            timeAlarmOFF = millis();
            lastSensorValue = false; 
            set_buzzer_alarm(lastSensorValue);
            sprintf(printBuffer, "Alarm stopped. It lasted %lu s", (timeAlarmOFF - timeAlarmON) / 1000);
            Serial.println(printBuffer);
            endTime = 0;
        }

    } else{
        endTime = 0; // Reset the end time if smoke is detected again
    }
    
}


