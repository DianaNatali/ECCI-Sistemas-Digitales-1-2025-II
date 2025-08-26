#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define BLINK_GPIO 2           // LED en GPIO2 (cambiar según la placa)
#define TAG "BLINK_RTOS"

// Tarea que hace parpadear el LED
static void blinker_task(void *arg) {
    gpio_reset_pin(BLINK_GPIO);
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);

    bool level = false;
    const TickType_t period = pdMS_TO_TICKS(500);

    while (1) {
        gpio_set_level(BLINK_GPIO, level);
        level = !level;
        vTaskDelay(period);  // suspende la tarea y cede CPU
    }
}

// Tarea de diagnóstico
static void heartbeat_task(void *arg) {
    const TickType_t period = pdMS_TO_TICKS(1000);
    while (1) {
        ESP_LOGI(TAG, "FreeRTOS OK, heap: %u bytes", (unsigned) xPortGetFreeHeapSize());
        vTaskDelay(period);
    }
}

void app_main(void) {
    xTaskCreate(blinker_task,   "blinker",   2048, NULL, 5, NULL);
    xTaskCreate(heartbeat_task, "heartbeat", 2048, NULL, 1, NULL);
}
