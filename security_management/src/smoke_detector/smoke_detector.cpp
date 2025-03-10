#include "smoke_detector.hpp"
#include "esp_log.h"
#include "../mqtt/mqtt.hpp"
#include "../buzzer/buzzer.hpp"

#define SMOKE_DETECTOR_TAG "app_smoke_detector"

#define SMOKE_DETECTOR_PIN 32 // GPIO pin where the smoke detector is connected

char communicator[100]; 
float smoke_level = 0.0;
bool init_smoke_detector()
{
    ESP_LOGI(SMOKE_DETECTOR_TAG, "Initializing smoke detector sensor...");

    pinMode(SMOKE_DETECTOR_PIN, INPUT);   // Configure the smoke detector pin as an input
    ESP_LOGI(SMOKE_DETECTOR_TAG, "Buzzer initialized on GPIO %d", SMOKE_DETECTOR_PIN);
    return true;
}

void handle_smoke_detector()
{
    smoke_level = analogRead(SMOKE_DETECTOR_PIN);
    sprintf(communicator, "Smoke level: %.2f", smoke_level);
    Serial.println(communicator);
}