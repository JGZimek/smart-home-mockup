#pragma once
#include <Arduino.h>

/**
 * @brief Initializes the gas detector.
 *
 * Configures the GPIO pins used for controlling the sensor.
 * @return true if initialization was successful, false otherwise.
 */
bool init_gas_detector();

/**
 * @brief Handles the gas detecting sensors.
 *
 * This function should be called periodically to manage the gas detector inputs.
 */
void handle_gas_detector();