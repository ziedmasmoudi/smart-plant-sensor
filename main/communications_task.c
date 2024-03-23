#include "communications_task.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


#include "bluetooth.h"

void communications_task(void *pvParameter)
{
    ESP_ERROR_CHECK(bluetooth_init());
    while (1)
    {
        vTaskDelay( 500 / portTICK_PERIOD_MS );
    }
    vTaskDelete(NULL);
}
