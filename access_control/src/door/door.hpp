#pragma once

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