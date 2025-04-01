#include "scheduling.hpp"

#define SCHEDULING_TAG "app_scheduling"

TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t mqttTaskHandle = NULL;
TaskHandle_t buttonTaskHandle = NULL;

TaskHandle_t pirTaskHandle = NULL;
TaskHandle_t buzzerTaskHandle = NULL;
TaskHandle_t fireSensorTaskHandle = NULL;
TaskHandle_t smokeDetectorTaskHandle = NULL;
TaskHandle_t reedRelayTaskHandle = NULL;
TaskHandle_t tiltSensorTaskHandle = NULL;

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

    if (!init_pir())
    {
        ESP_LOGE(SCHEDULING_TAG, "PIR initialization failed.");
        return false;
    }

    if (!init_buzzer())
    {
        ESP_LOGE(SCHEDULING_TAG, "Buzzer initialization failed.");
        return false;
    }

    if (!init_fire_sensor())
    {
        ESP_LOGE(SCHEDULING_TAG, "Fire sensor initialization failed.");
        return false;
    }

    if (!init_smoke_detector())
    {
        ESP_LOGE(SCHEDULING_TAG, "Smoke detector initialization failed.");
        return false;
    }

    if (!init_reed_relay())
    {
        ESP_LOGE(SCHEDULING_TAG, "Reed relay initialization failed.");
        return false;
    }

    if (!init_tilt_sensor())
    {
        ESP_LOGE(SCHEDULING_TAG, "Tilt sensor initialization failed.");
        return false;
    }

    if (!init_scheduling())
    {
        ESP_LOGE(SCHEDULING_TAG, "Scheduling initialization failed.");
        return false;
    }

    ESP_LOG(SCHEDULING_TAG, "ESP32 system setup completed.");
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
        pirTask,
        "pir_task",
        PIR_TASK_STACK_SIZE,
        NULL,
        PIR_TASK_PRIORITY,
        &pirTaskHandle,
        PIR_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create PIR task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        buzzerTask,
        "buzzer_task",
        BUZZER_TASK_STACK_SIZE,
        NULL,
        BUZZER_TASK_PRIORITY,
        &buzzerTaskHandle,
        BUZZER_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create buzzer task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        fireSensorTask,
        "fire_sensor_task",
        FIRE_SENSOR_TASK_STACK_SIZE,
        NULL,
        FIRE_SENSOR_TASK_PRIORITY,
        &fireSensorTaskHandle,
        FIRE_SENSOR_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create fire sensor task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        smokeDetectorTask,
        "smoke_detector_task",
        SMOKE_DETECTOR_TASK_STACK_SIZE,
        NULL,
        SMOKE_DETECTOR_TASK_PRIORITY,
        &smokeDetectorTaskHandle,
        SMOKE_DETECTOR_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create smoke detector task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        reedRelayTask,
        "reed_relay_task",
        REED_RELAY_TASK_STACK_SIZE,
        NULL,
        REED_RELAY_TASK_PRIORITY,
        &reedRelayTaskHandle,
        REED_RELAY_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create reed relay task.");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        tiltSensorTask,
        "tilt_sensor_task",
        TILT_SENSOR_TASK_STACK_SIZE,
        NULL,
        TILT_SENSOR_TASK_PRIORITY,
        &tiltSensorTaskHandle,
        TILT_SENSOR_TASK_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create tilt sensor task.");
        return false;
    }

    ESP_LOGI(SCHEDULING_TAG, "Scheduling initialized successfully");
    return true;
}

void wifiTask(void *pvParameters)
{
    while (1)
    {
        wifiManager.handle();
        vTaskDelay(WIFI_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void mqttTask(void *pvParameters)
{
    while (1)
    {
        mqttManager.handle();
        vTaskDelay(MQTT_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void buttonTask(void *pvParameters)
{
    while (1)
    {
        button.handle();
        vTaskDelay(BUTTON_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void pirTask(void *pvParameters)
{
    while (1)
    {
        handle_pir();
        vTaskDelay(PIR_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void buzzerTask(void *pvParameters)
{
    while (1)
    {
        handle_buzzer();
        vTaskDelay(BUZZER_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void fireSensorTask(void *pvParameters)
{
    while (1)
    {
        handle_fire_sensor();
        vTaskDelay(FIRE_SENSOR_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void gasDetectorTask(void *pvParameters)
{
    while (1)
    {
        handle_smoke_detector();
        vTaskDelay(SMOKE_DETECTOR_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void reedRelayTask(void *pvParameters)
{
    while (1)
    {
        handle_reed_relay();
        vTaskDelay(REED_RELAY_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}

void tiltSensorTask(void *pvParameters)
{
    while (1)
    {
        handle_tilt_sensor();
        vTaskDelay(TILT_SENSOR_EVENT_FREQUENCY / portTICK_PERIOD_MS);
    }
}
