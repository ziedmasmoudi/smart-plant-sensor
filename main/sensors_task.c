#include "sensors_task.h"

#include "esp_system.h"
#include "esp_log.h"
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/i2c_master.h"

#include "AHT20.h"

#define I2C_MASTER_SCL_IO           11                      /* GPIO number used for I2C master clock */
#define I2C_MASTER_SDA_IO           10                      /* GPIO number used for I2C master data  */
#define I2C_MASTER_PORT             0                       /* Sets the I2C port used by the controller */
#define I2C_MASTER_GLITCH_PERIOD    7                       /* Sets the glitch period of master bus */
#define I2C_MASTER_CLOCK_SOURCE     I2C_CLK_SRC_DEFAULT     /* Selects the source clock for I2C bus */
#define I2C_MASTER_PULL_UP          true                    /* Enable internal pullups */

static const char *TAG = __FILE__;

esp_err_t i2c_init(i2c_master_bus_handle_t *p_bus_handle);

void sensors_task(void *pvParameter)
{
    i2c_master_bus_handle_t bus_handle;
    i2c_init(&bus_handle);

    i2c_master_dev_handle_t AHT20_handle;
    AHT20_init(&bus_handle, &AHT20_handle);

    vTaskDelay( 40 / portTICK_PERIOD_MS );
    
    while (1)
    {
        uint8_t temperature;
        AHT20_read_temperature(&AHT20_handle, &temperature);
        ESP_LOGI(TAG, "Temperature: %iC", temperature);
        uint8_t humidity;
        AHT20_read_humidity(&AHT20_handle, &humidity);
        ESP_LOGI(TAG, "Humidity: %i%%", humidity);

        vTaskDelay( 500 / portTICK_PERIOD_MS );
    }
    vTaskDelete(NULL);
}

/**
 * @brief sensor initialization
 */
esp_err_t i2c_init(i2c_master_bus_handle_t *p_bus_handle)
{
    i2c_master_bus_config_t i2c_mst_config = {
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .i2c_port = I2C_MASTER_PORT,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .glitch_ignore_cnt = I2C_MASTER_GLITCH_PERIOD,
        .flags.enable_internal_pullup = I2C_MASTER_PULL_UP,
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&i2c_mst_config, p_bus_handle));

    return ESP_OK;
}
