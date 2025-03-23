#pragma once

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "../network/wifi/wifi.hpp"
#include "../network/mqtt/mqtt.hpp"
#include "../network/button/button.hpp"
#include "../network/access_point/access_point.hpp"

#include "../rfid/rfid.hpp"
#include "../pinpad/pinpad.hpp"
#include "../energy_monitor/energy_monitor.hpp"

/* Task priorities */
#define WIFI_TASK_PRIORITY 3
#define MQTT_TASK_PRIORITY 1
#define BUTTON_TASK_PRIORITY 2

#define ENERGY_MONITOR_TASK_PRIORITY 4
#define RFID_TASK_PRIORITY 1
#define PINPAD_TASK_PRIORITY 2

/* Core assignments */
#define WIFI_TASK_CORE 0
#define MQTT_TASK_CORE 1
#define BUTTON_TASK_CORE 0

#define ENERGY_MONITOR_TASK_CORE 1
#define RFID_TASK_CORE 0
#define PINPAD_TASK_CORE 1

/* Task stack size */
#define WIFI_TASK_STACK_SIZE 4096
#define MQTT_TASK_STACK_SIZE 4096
#define BUTTON_TASK_STACK_SIZE 4096

#define ENERGY_MONITOR_TASK_STACK_SIZE 4096
#define RFID_TASK_STACK_SIZE 4096
#define PINPAD_TASK_STACK_SIZE 4096

/* Event frequencies in ms */
#define WIFI_EVENT_FREQUENCY 1000
#define MQTT_EVENT_FREQUENCY 1000
#define BUTTON_EVENT_FREQUENCY 100

#define ENERGY_MONITOR_EVENT_FREQUENCY 1000
#define RFID_EVENT_FREQUENCY 100
#define PINPAD_EVENT_FREQUENCY 100

/**
 * @brief Setup function for the ESP32.
 *
 * This function initializes the ESP32 hardware and software components.
 *
 * @return true if setup was successful, false otherwise
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
 * @brief Task function for handling WiFi events.
 *
 * This function is responsible for handling WiFi events in the background.
 *
 * @param pvParameters pointer to task-specific data structure
 */
void wifiTask(void *pvParameters);

/**
 * @brief Task function for handling MQTT events.
 *
 * This function is responsible for handling MQTT events in the background.
 *
 * @param pvParameters pointer to task-specific data structure
 */
void mqttTask(void *pvParameters);

/**
 * @brief Task function for handling button events.
 *
 * This function is responsible for handling button events in the background.
 *
 * @param pvParameters pointer to task-specific data structure
 */
void buttonTask(void *pvParameters);

/**
 * @brief Task function for handling energy monitor events.
 *
 * This function is responsible for handling energy monitor events in the background.
 *
 * @param pvParameters pointer to task-specific data structure
 */
void energyMonitorTask(void *pvParameters);

/**
 * @brief Task function for handling RFID events.
 *
 * This function is responsible for handling RFID events in the background.
 *
 * @param pvParameters pointer to task-specific data structure
 */
void rfidTask(void *pvParameters);

/**
 * @brief Task function for handling pinpad events.
 *
 * This function is responsible for handling pinpad events in the background.
 *
 * @param pvParameters pointer to task-specific data structure
 */
void pinpadTask(void *pvParameters);