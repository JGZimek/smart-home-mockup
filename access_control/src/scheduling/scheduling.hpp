#pragma once

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "../wifi/wifi.hpp"
#include "../rfid/rfid.hpp"
#include "../pinpad/pinpad.hpp"
#include "../buzzer/buzzer.hpp"
#include "../pir/pir.hpp"
#include "../mqtt/mqtt.hpp"

/* Task priorities */
#define WIFI_TASK_PRIORITY 0
#define RFID_TASK_PRIORITY 1
#define PINPAD_TASK_PRIORITY 2
#define BUZZER_TASK_PRIORITY 3
#define PIR_TASK_PRIORITY 4
#define MQTT_TASK_PRIORITY 5

/* Core assignments */
#define WIFI_CORE 0
#define RFID_CORE 1
#define PINPAD_CORE 0
#define BUZZER_CORE 1
#define PIR_CORE 1
#define MQTT_CORE 0

/* Task stack size */
#define WIFI_TASK_STACK_SIZE 4096
#define RFID_TASK_STACK_SIZE 4096
#define PINPAD_TASK_STACK_SIZE 4096
#define BUZZER_TASK_STACK_SIZE 4096
#define PIR_TASK_STACK_SIZE 4096
#define MQTT_TASK_STACK_SIZE 4096

/* Event frequencies in ms */
#define WIFI_RECONNECT_FREQ 1000
#define RFID_READ_FREQ 300
#define PINPAD_READ_FREQ 100
#define BUZZER_READ_FREQ 300
#define PIR_READ_FREQ 300
#define MQTT_READ_FREQ 100

/**
 * @brief Sets up the ESP32 system, initializes components, and starts scheduling.
 *
 * This function initializes the hardware and software components
 * for the application.
 */
bool esp_setup();

/**
 * @brief Initializes the scheduling system.
 *
 * This function sets up the FreeRTOS tasks for the different modules.
 *
 * @return true if initialization was successful, false otherwise.
 */
bool init_scheduling();

/**
 * @brief Task to handle network module activities.
 *
 * This task manages WiFi connections and other network-related functionalities.
 *
 * @param pvParameters Pointer to parameters passed to the task.
 */
void wifiTask(void *pvParameters);

/**
 * @brief Task to handle RFID module activities.
 *
 * This task manages RFID card reading and processing.
 *
 * @param pvParameters Pointer to parameters passed to the task.
 */
void rfidTask(void *pvParameters);

/**
 * @brief Task to handle pinpad module activities.
 *
 * This task manages pinpad keypresses and PIN entry.
 *
 * @param pvParameters Pointer to parameters passed to the task.
 */
void pinpadTask(void *pvParameters);

/**
 * @brief Task to handle buzzer module activities.
 *
 * This task manages buzzer beeps and sequences.
 *
 * @param pvParameters Pointer to parameters passed to the task.
 */
void buzzerTask(void *pvParameters);

/**
 * @brief Task to handle PIR sensor module activities.
 *
 * This task manages PIR sensor readings and motion detection.
 *
 * @param pvParameters Pointer to parameters passed to the task.
 */
void pirTask(void *pvParameters);

/**
 * @brief Task to handle MQTT module activities.
 *
 * This task manages MQTT communication with the backend.
 *
 * @param pvParameters Pointer to parameters passed to the task.
 */
void mqttTask(void *pvParameters);