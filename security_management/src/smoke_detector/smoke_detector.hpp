#pragma once
#include <Arduino.h>

/**
 * @brief Initializes the smoke detector.
 *
 * Configures the GPIO pins used for controlling the sensor.
 * @return true if initialization was successful, false otherwise.
 */
bool init_smoke_detector();

/**
 * @brief Handles the smoke detecting sensors.
 *
 * This function should be called periodically to manage the smoke detector inputs.
 */
void handle_smoke_detector();