#include "door.hpp"



Servo doorServo;
int servoPIN = 22; // GPIO pin connected to the servo
int servoClosed = 0; // initial position of the servo
int servoOpen = 150; // final position of the servo

int buttonDoor = 5; // GPIO pin for button trigger
bool isOpen = false;

#define DOOR_TAG "app_door"
int currentPoz = 0;

bool init_door()
{
    pinMode(buttonDoor, INPUT_PULLUP);
    doorServo.attach(servoPIN);
    doorServo.write(servoClosed); // initial position of the servo is set to closed
    ESP_LOGI(DOOR_TAG, "Door servo is initialized on pin %d", servoPIN);
    return true;
}

void open_door()
{
    Serial.println("Opening door");
    for(; currentPoz <= servoOpen; currentPoz += 2)
    {
        doorServo.write(currentPoz);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    isOpen = true;
}

void close_door()
{
     Serial.println("Closing door");
    for(; currentPoz >= servoClosed; currentPoz -= 2)
    {
        doorServo.write(currentPoz);
        vTaskDelay(10 / portTICK_PERIOD_MS);
    }
    isOpen = false;
}

void handle_door()
{


    if (digitalRead(buttonDoor) == LOW && !isOpen && mock_lock_open()){
        open_door();
    }
    if (digitalRead(buttonDoor) == LOW && isOpen && mock_lock_open()){
        close_door();
    }
}