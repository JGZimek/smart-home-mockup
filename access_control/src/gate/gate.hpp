#pragma once

#include <Arduino.h>
#include "esp_log.h"
#include <ESP32Servo.h>
#include "../mock_lock/mock_lock.hpp"


/**
 * @brief Initializes a Micro Servo using for car gate opening functionality.
 *
 * 
 */
bool init_gate();

/**
 * @brief Handles the servo logic.
 *
 * 
 */
void handle_gate();

/**
 * @brief Opens the gate (turning the motor on for a specyfic period of time).
 */
void open_gate();

/**
 * @brief Closes the gate (turning the motor on the opposite direction).
 */
void close_gate();