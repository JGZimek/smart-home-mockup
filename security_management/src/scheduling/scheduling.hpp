#pragma once

#include <Arduino.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "../network/wifi/wifi.hpp"
#include "../network/mqtt/mqtt.hpp"
#include "../network/button/button.hpp"
#include "../network/access_point/access_point.hpp"

#include "../buzzer/buzzer.hpp"
#include "../fire_sensor/fire_sensor.hpp"
#include "../pir/pir.hpp"
#include "../reed_relay/reed_relay.hpp"
#include "../smoke_detector/smoke_detector.hpp"
#include "../tilt_sensor/tilt_sensor.hpp"

/* Task priorities */
#define WIFI_TASK_PRIORITY 3
#define MQTT_TASK_PRIORITY 1
#define BUTTON_TASK_PRIORITY 2

#define PIR_TASK_PRIORITY 4
#define BUZZER_TASK_PRIORITY 1
#define FIRE_SENSOR_TASK_PRIORITY 2
#define SMOKE_DETECTOR_TASK_PRIORITY 3
#define REED_RELAY_TASK_PRIORITY 5 // to be improved later
#define TILT_SENSOR_TASK_PRIORITY 6

/* Core assignments */
#define WIFI_TASK_CORE 0
#define MQTT_TASK_CORE 1
#define BUTTON_TASK_CORE 0

#define PIR_TASK_CORE 0
#define BUZZER_TASK_CORE 1
#define FIRE_SENSOR_TASK_CORE 0
#define SMOKE_DETECTOR_TASK_CORE 1
#define REED_RELAY_TASK_CORE 0
#define TILT_SENSOR_TASK_CORE 1

/* Task stack size */
#define WIFI_TASK_STACK_SIZE 4096
#define MQTT_TASK_STACK_SIZE 4096
#define BUTTON_TASK_STACK_SIZE 4096

#define PIR_TASK_STACK_SIZE 4096
#define BUZZER_TASK_STACK_SIZE 4096
#define FIRE_SENSOR_TASK_STACK_SIZE 4096
#define SMOKE_DETECTOR_TASK_STACK_SIZE 4096
#define REED_RELAY_TASK_STACK_SIZE 4096
#define TILT_SENSOR_TASK_STACK_SIZE 4096

/* Event frequencies in ms */
#define WIFI_EVENT_FREQUENCY 1000
#define MQTT_EVENT_FREQUENCY 1000
#define BUTTON_EVENT_FREQUENCY 100

#define PIR_EVENT_FREQUENCY 100
#define BUZZER_EVENT_FREQUENCY 100
#define FIRE_SENSOR_EVENT_FREQUENCY 100
#define SMOKE_DETECTOR_EVENT_FREQUENCY 100
#define REED_RELAY_EVENT_FREQUENCY 100
#define TILT_SENSOR_EVENT_FREQUENCY 100

/**
 * @brief Setup function for the ESP32.
 *
 * This function initializes the ESP32 hardware and software components.
 *
 * @return true if setup was successful, false otherwise
 */
esp_setup();

/**
 * @brief Initializes the scheduling system.
 *
 * This function sets up the FreeRTOS tasks for the different modules.
 *
 * @return true if initialization was successful, false otherwise.
 */
bool init_scheduling();

/**
 * @brief Task that handles WiFi connection.
 *
 * This task is responsible for handling the WiFi connection.
 *
 * @param pvParameters Task parameters
 */
void wifiTask(void *pvParameters);

/**
 * @brief Task that handles MQTT connection.
 *
 * This task is responsible for handling the MQTT connection.
 *
 * @param pvParameters Task parameters
 */
void mqttTask(void *pvParameters);

/**
 * @brief Task that handles button.
 *
 * This task is responsible for handling the button.
 *
 * @param pvParameters Task parameters
 */
void buttonTask(void *pvParameters);

/**
 * @brief Task that handles PIR sensor.
 *
 * This task is responsible for handling the PIR sensor.
 *
 * @param pvParameters Task parameters
 */
void pirTask(void *pvParameters);

/**
 * @brief Task that handles buzzer.
 *
 * This task is responsible for handling the buzzer.
 *
 * @param pvParameters Task parameters
 */
void buzzerTask(void *pvParameters);

/**
 * @brief Task that handles fire sensor.
 *
 * This task is responsible for handling the fire sensor.
 *
 * @param pvParameters Task parameters
 */
void fireSensorTask(void *pvParameters);

/**
 * @brief Task that handles gas detector.
 *
 * This task is responsible for handling the gas detector.
 *
 * @param pvParameters Task parameters
 */
void smokeDetectorTask(void *pvParameters);

/**
 * @brief Task that handles reed relay.
 *
 * This task is responsible for handling the reed relay.
 *
 * @param pvParameters Task parameters
 */
void reedRelayTask(void *pvParameters);

/**
 * @brief Task that handles tilt sensor.
 *
 * This task is responsible for handling the tilt sensor.
 *
 * @param pvParameters Task parameters
 */
void tiltSensorTask(void *pvParameters);
