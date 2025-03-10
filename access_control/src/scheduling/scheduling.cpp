#include "scheduling.hpp"

#define SCHEDULING_TAG "app_scheduling"

TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t rfidTaskHandle = NULL;
TaskHandle_t pinpadTaskHandle = NULL;
TaskHandle_t mqttTaskHandle = NULL;
TaskHandle_t buttonTaskHandle = NULL;
TaskHandle_t doorTaskHandle = NULL;
TaskHandle_t gateTaskHandle = NULL;

Button button(BUTTON_PIN);
AccessPoint accessPoint("ESP_AP", "password123");

bool esp_setup()
{
    button.begin();

    // Sprawdzanie, czy dane WiFi i MQTT już istnieją
    // Preferences preferences;
    // preferences.begin("wifi", true);                              // Tryb odczytu
    // bool isConfigured = preferences.getBool("configured", false); // Flaga konfiguracji
    // preferences.end();

    // WiFi and MQTT setup commented out for the sake of servo implementaiton purposes.
    
    // if (!isConfigured)
    // {
    //     // Brak danych WiFi/MQTT - uruchom tryb Access Point i czekaj na konfigurację
    //     ESP_LOGI(SCHEDULING_TAG, "Device not configured. Starting in Access Point mode...");
    //     accessPoint.run(); // Oczekiwanie na wprowadzenie danych
    // }

    // // Próba połączenia z WiFi
    // ESP_LOGI(SCHEDULING_TAG, "Attempting to connect to WiFi...");
    // if (!init_wifi())
    // {
    //     ESP_LOGW(SCHEDULING_TAG, "Failed to connect to WiFi. WiFi will remain disconnected.");
    // }
    // else
    // {
    //     ESP_LOGI(SCHEDULING_TAG, "Connected to WiFi successfully.");
    // }

    // // Próba połączenia z MQTT, jeśli WiFi jest połączone
    // if (WiFi.status() == WL_CONNECTED)
    // {
    //     ESP_LOGI(SCHEDULING_TAG, "Attempting to connect to MQTT...");
    //     if (!init_mqtt())
    //     {
    //         ESP_LOGW(SCHEDULING_TAG, "Failed to connect to MQTT. Waiting for manual reconfiguration.");
    //     }
    //     else
    //     {
    //         ESP_LOGI(SCHEDULING_TAG, "Connected to MQTT successfully.");
    //     }
    // }

    // // Inicjalizacja pozostałych modułów, jeśli WiFi i MQTT są połączone
    // if (WiFi.status() == WL_CONNECTED && mqtt_connected)
    // {
    //     ESP_LOGI(SCHEDULING_TAG, "WiFi and MQTT connected. Initializing remaining modules...");
    //     if (!initialize_remaining_modules())
    //     {
    //         ESP_LOGE(SCHEDULING_TAG, "Failed to initialize some modules. System halted.");
    //         return false;
    //     }
    //     ESP_LOGI(SCHEDULING_TAG, "All modules initialized successfully!");
    // }

    // wykorzystywana tymczasowo inicjalizacja modułów bez WiFi i MQTT - testowana jest obsługa serwa
        ESP_LOGI(SCHEDULING_TAG, "Initializing remaining modules...");
        if (!initialize_remaining_modules())
        {
            ESP_LOGE(SCHEDULING_TAG, "Failed to initialize some modules. System halted.");
            return false;
        }
        ESP_LOGI(SCHEDULING_TAG, "All modules initialized successfully!");
    return true;
}

bool initialize_remaining_modules()
{
    // Inicjalizacja pozostałych modułów
    if (!init_RFID())
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to initialize RFID");
        return false;
    }

    if (!init_pinpad())
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to initialize Pinpad");
        return false;
    }

    if (!init_door())
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to initialize Door");
        return false;
    }

    if (!init_gate())
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to initialize Gate");
        return false;
    }

    if (!init_scheduling())
    {
        ESP_LOGE(SCHEDULING_TAG, "Scheduling initialization failed. System halted.");
        return false;
    }

    return true;
}

// void wifiTask(void *pvParameters)
// {
//     while (1)
//     {
//         handle_wifi();
//         vTaskDelay(WIFI_RECONNECT_FREQ / portTICK_PERIOD_MS);
//     }
// }

void rfidTask(void *pvParameters)
{
    while (1)
    {
        handle_RFID();
        vTaskDelay(RFID_READ_FREQ / portTICK_PERIOD_MS);
    }
}

void pinpadTask(void *pvParameters)
{
    while (1)
    {
        handle_pinpad();
        vTaskDelay(PINPAD_READ_FREQ / portTICK_PERIOD_MS);
    }
}

// void mqttTask(void *pvParameters)
// {
//     while (1)
//     {
//         handle_mqtt();
//         vTaskDelay(MQTT_READ_FREQ / portTICK_PERIOD_MS);
//     }
// }

void buttonTask(void *pvParameters)
{
    while (1)
    {
        if (button.isLongPressed())
        {
            ESP_LOGI(SCHEDULING_TAG, "Button long press detected. Triggering AP mode...");
            accessPoint.run(); // Ręczne uruchamianie trybu AP
        }
        vTaskDelay(BUTTON_READ_FREQ / portTICK_PERIOD_MS);
    }
}

void doorTask(void *pvParameters)
{
    while (1)
    {
        handle_door();
        vTaskDelay(DOOR_READ_FREQ / portTICK_PERIOD_MS);
    }
}

void gateTask(void *pvParameters)
{
    while (1)
    {
        handle_gate();
        vTaskDelay(GATE_READ_FREQ / portTICK_PERIOD_MS);
    }
}

bool init_scheduling()
{
    ESP_LOGI(SCHEDULING_TAG, "Initializing scheduling...");

    BaseType_t result;

    // result = xTaskCreatePinnedToCore(
    //     wifiTask,
    //     "Wifi Task",
    //     WIFI_TASK_STACK_SIZE,
    //     NULL,
    //     WIFI_TASK_PRIORITY,
    //     &wifiTaskHandle,
    //     WIFI_CORE);

    // if (result != pdPASS)
    // {
    //     ESP_LOGE(SCHEDULING_TAG, "Failed to create Network Task");
    //     return false;
    // }

    result = xTaskCreatePinnedToCore(
        rfidTask,
        "RFID Task",
        RFID_TASK_STACK_SIZE,
        NULL,
        RFID_TASK_PRIORITY,
        &rfidTaskHandle,
        RFID_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create RFID Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        pinpadTask,
        "Pinpad Task",
        PINPAD_TASK_STACK_SIZE,
        NULL,
        PINPAD_TASK_PRIORITY,
        &pinpadTaskHandle,
        PINPAD_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Pinpad Task");
        return false;
    }

    // result = xTaskCreatePinnedToCore(
    //     mqttTask,
    //     "MQTT Task",
    //     MQTT_TASK_STACK_SIZE,
    //     NULL,
    //     MQTT_TASK_PRIORITY,
    //     &mqttTaskHandle,
    //     MQTT_CORE);

    // if (result != pdPASS)
    // {
    //     ESP_LOGE(SCHEDULING_TAG, "Failed to create MQTT Task");
    //     return false;
    // }

    result = xTaskCreatePinnedToCore(
        buttonTask,
        "Button Task",
        BUTTON_TASK_STACK_SIZE,
        NULL,
        BUTTON_TASK_PRIORITY,
        &buttonTaskHandle,
        BUTTON_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Button Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        doorTask,
        "Door Task",
        DOOR_TASK_STACK_SIZE,
        NULL,
        DOOR_TASK_PRIORITY,
        &doorTaskHandle,
        DOOR_CORE);
    
    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Door Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        gateTask,
        "Gate Task",
        GATE_TASK_STACK_SIZE,
        NULL,
        GATE_TASK_PRIORITY,
        &gateTaskHandle,
        GATE_CORE);
    
    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Gate Task");
        return false;
    }
    ESP_LOGI(SCHEDULING_TAG, "Scheduling initialized successfully.");
    return true;
}
