#include "mock_lock.hpp"

#define LOCK_TAG "app_lock"


bool mock_login(){ 
    bool login = false; // zmienna symulująca informację z backendu o zalogowaniu się użytkownika 
    return login;
}

bool mock_lock_open(){
    if (mock_login()) {
        return true; 
    }
    else {
        ESP_LOGI(LOCK_TAG, "No RFID card nor correct PIN is provided. Access denied");
        vTaskDelay(2000 / portTICK_PERIOD_MS); 
        return false; 
    }
}