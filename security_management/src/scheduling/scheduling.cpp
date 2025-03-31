#include "scheduling.hpp"

#define SCHEDULING_TAG "app_scheduling"

TaskHandle_t wifiTaskHandle = NULL;
TaskHandle_t mqttTaskHandle = NULL;
TaskHandle_t pirTaskHandle = NULL;
TaskHandle_t buzzerTaskHandle = NULL;
TaskHandle_t fireSensorTaskHandle = NULL;
TaskHandle_t gasDetectorTaskHandle = NULL;

bool security_setup()
{
    ESP_LOGI(SCHEDULING_TAG, "Setting up security management...");

    // if (!init_wifi())
    // {
    //     ESP_LOGE(SCHEDULING_TAG, "Failed to initialize WiFi");
    //     return false;
    // }

    // if (!init_mqtt())
    // {
    //     ESP_LOGE(SCHEDULING_TAG, "Failed to initialize MQTT");
    //     return false;
    // }

    // if (!init_pir())
    // {
    //     ESP_LOGE(SCHEDULING_TAG, "Failed to initialize PIR");
    //     return false;
    // }

    // if (!init_buzzer())
    // {
    //     ESP_LOGE(SCHEDULING_TAG, "Failed to initialize Buzzer");
    //     return false;
    // }

    // if (!init_fire_sensor())
    // {
    //     ESP_LOGE(SCHEDULING_TAG, "Failed to initialize Fire Sensor");
    //     return false;
    // }

    if (!init_gas_detector())
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to initialize Gas Detector");
        return false;
    }

    if (!init_scheduling())
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to initialize scheduling");
        return false;
    }
    return true;
}

bool init_scheduling()
{
    ESP_LOGI(SCHEDULING_TAG, "Initializing scheduling...");

    BaseType_t result;

    result = xTaskCreatePinnedToCore(
        wifiTask,
        "Wifi Task",
        WIFI_TASK_STACK_SIZE,
        NULL,
        WIFI_TASK_PRIORITY,
        &wifiTaskHandle,
        WIFI_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Network Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        mqttTask,
        "MQTT Task",
        MQTT_TASK_STACK_SIZE,
        NULL,
        MQTT_TASK_PRIORITY,
        &mqttTaskHandle,
        MQTT_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create MQTT Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        pirTask,
        "PIR Task",
        PIR_TASK_STACK_SIZE,
        NULL,
        PIR_TASK_PRIORITY,
        &pirTaskHandle,
        PIR_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create PIR Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        buzzerTask,
        "Buzzer Task",
        BUZZER_TASK_STACK_SIZE,
        NULL,
        BUZZER_TASK_PRIORITY,
        &buzzerTaskHandle,
        BUZZER_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Buzzer Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        fireSensorTask,
        "Fire Sensor Task",
        FIRE_SENSOR_TASK_STACK_SIZE,
        NULL,
        FIRE_SENSOR_TASK_PRIORITY,
        &fireSensorTaskHandle,
        FIRE_SENSOR_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Fire Sensor Task");
        return false;
    }

    result = xTaskCreatePinnedToCore(
        gasDetectorTask,
        "Gas Detector Task",
        GAS_DETECTOR_TASK_STACK_SIZE,
        NULL,
        GAS_DETECTOR_TASK_PRIORITY,
        &gasDetectorTaskHandle,
        GAS_DETECTOR_CORE);

    if (result != pdPASS)
    {
        ESP_LOGE(SCHEDULING_TAG, "Failed to create Gas Detector Task");
        return false;
    }

    ESP_LOGI(SCHEDULING_TAG, "Scheduling initialized successfully");

    return true;
}

void wifiTask(void *pvParameters)
{
    while (1)
    {
        // handle_wifi();
        vTaskDelay(WIFI_RECONNECT_FREQ / portTICK_PERIOD_MS);
    }
}

void mqttTask(void *pvParameters)
{
    while (1)
    {
        // handle_mqtt();
        vTaskDelay(MQTT_READ_FREQ / portTICK_PERIOD_MS);
    }
}

void pirTask(void *pvParameters)
{
    while (1)
    {
        // handle_pir();
        vTaskDelay(PIR_READ_FREQ / portTICK_PERIOD_MS);
    }
}

void buzzerTask(void *pvParameters)
{
    while (1)
    {
        // handle_buzzer();
        vTaskDelay(BUZZER_READ_FREQ / portTICK_PERIOD_MS);
    }
}

void fireSensorTask(void *pvParameters)
{
    while (1)
    {
        // handle_fire_sensor();
        vTaskDelay(FIRE_SENSOR_READ_FREQ / portTICK_PERIOD_MS);
    }
}

void gasDetectorTask(void *pvParameters)
{
    while (1)
    {
        handle_gas_detector();
        vTaskDelay(GAS_DETECTOR_READ_FREQ / portTICK_PERIOD_MS);
    }
}
