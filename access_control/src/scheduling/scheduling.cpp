#include "scheduling.hpp"

#define SCHEDULING_TAG "app_scheduling"

TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t mqttTaskHandle = NULL;
TaskHandle_t buttonTaskHandle = NULL;

TaskHandle_t rfidTaskHandle = NULL;
TaskHandle_t pinpadTaskHandle = NULL;
TaskHandle_t energyMonitorTaskHandle = NULL;

WiFiManager wifiManager;
MqttManager mqttManager;
Button button;

bool esp_setup()
{
    ESP_LOGI(SCHEDULING_TAG, "Setting up ESP32 system...");

    if (!button.begin())
    {
        ESP_LOGE(SCHEDULING_TAG, "Button initialization failed.");
        return false;
    }

    wifiManager.begin();
    mqttManager.begin();

    if (!init_energy_monitor())
    {
        ESP_LOGE(SCHEDULING_TAG, "Energy monitor initialization failed.");
        return false;
    }

    if (!init_RFID())
    {
        ESP_LOGE(SCHEDULING_TAG, "RFID initialization failed.");
        return false;
    }

    if (!init_pinpad())
    {
        ESP_LOGE(SCHEDULING_TAG, "Pinpad initialization failed.");
        return false;
    }

    if (!init_scheduling())
    {
        ESP_LOGE(SCHEDULING_TAG, "Scheduling initialization failed.");
        return false;
    }

    ESP_LOGI(SCHEDULING_TAG, "ESP32 system setup completed.");
    return true;
}

bool init_scheduling()
{
    ESP_LOGI(SCHEDULING_TAG, "Initializing scheduling...");

    BaseType_t result;

    result = xTaskCreatePinnedToCore(
        buttonTask,
        "button_task",
        BUTTON_TASK_STACK_SIZE,
        NULL,
        BUTTON_TASK_PRIORITY,
        &buttonTaskHandle,
        BUTTON_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create button task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        wifiTask,
        "wifi_task",
        WIFI_TASK_STACK_SIZE,
        NULL,
        WIFI_TASK_PRIORITY,
        &wifiTaskHandle,
        WIFI_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create wifi task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        mqttTask,
        "mqtt_task",
        MQTT_TASK_STACK_SIZE,
        NULL,
        MQTT_TASK_PRIORITY,
        &mqttTaskHandle,
        MQTT_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create mqtt task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        rfidTask,
        "rfid_task",
        RFID_TASK_STACK_SIZE,
        NULL,
        RFID_TASK_PRIORITY,
        &rfidTaskHandle,
        RFID_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create rfid task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        pinpadTask,
        "pinpad_task",
        PINPAD_TASK_STACK_SIZE,
        NULL,
        PINPAD_TASK_PRIORITY,
        &pinpadTaskHandle,
        PINPAD_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create pinpad task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        energyMonitorTask,
        "energy_monitor_task",
        ENERGY_MONITOR_TASK_STACK_SIZE,
        NULL,
        ENERGY_MONITOR_TASK_PRIORITY,
        &energyMonitorTaskHandle,
        ENERGY_MONITOR_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create energy monitor task.");
        return false;
    }

    ESP_LOGI(SCHEDULING_TAG, "Scheduling initialized successfully.");
    return true;
}

void wifiTask(void *pvParameters)
{
    while (1)
    {
        handle_wifi();
        vTaskDelay(WIFI_RECONNECT_FREQ / portTICK_PERIOD_MS);
    }
}

void mqttTask(void *pvParameters)
{
    while (1)
    {
        handle_mqtt();
        vTaskDelay(MQTT_RECONNECT_FREQ / portTICK_PERIOD_MS);
    }
}

void buttonTask(void *pvParameters)
{
    while (1)
    {
        handle_button();
        vTaskDelay(BUTTON_EVENT_FREQ / portTICK_PERIOD_MS);
    }
}

void rfidTask(void *pvParameters)
{
    while (1)
    {
        handle_rfid();
        vTaskDelay(RFID_EVENT_FREQ / portTICK_PERIOD_MS);
    }
}

void pinpadTask(void *pvParameters)
{
    while (1)
    {
        handle_pinpad();
        vTaskDelay(PINPAD_EVENT_FREQ / portTICK_PERIOD_MS);
    }
}

void energyMonitorTask(void *pvParameters)
{
    while (1)
    {
        handle_energy_monitor();
        vTaskDelay(ENERGY_MONITOR_EVENT_FREQ / portTICK_PERIOD_MS);
    }
}