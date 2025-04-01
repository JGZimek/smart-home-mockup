#pragma once

#include <Arduino.h>
#include "esp_log.h"
#include <ESP32Servo.h>
#include "../mock_lock/mock_lock.hpp"

/**
 * @brief Initializes a Micro Servo using for door opening functionality.
 *
 * 
 */
bool init_door();

/**
 * @brief Handles the servo logic.
 *
 * 
 */
void handle_door();

/**
 * @brief Opens the door (turning the serwo to a specyfic angle).
 */
void open_door();

/**
 * @brief Closes the door (turning the serwo to primal angle).
 */
void close_door();