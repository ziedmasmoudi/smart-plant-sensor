#include "AHT20.h"

#include <stdio.h>
#include <string.h>

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define AHT20_I2C_ADDR      0x38            /* Device I2C address */
#define AHT20_I2C_SCL_FREQ  100000          /* Device SCL frequency in Hz */

static const char *TAG = __FILE__;

esp_err_t AHT20_get_measurement(i2c_master_dev_handle_t *p_dev_handle, uint8_t measurement_buffer[6]);

esp_err_t AHT20_init(i2c_master_bus_handle_t *p_bus_handle, i2c_master_dev_handle_t *p_dev_handle)
{
    i2c_device_config_t dev_cfg = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = AHT20_I2C_ADDR,
        .scl_speed_hz = AHT20_I2C_SCL_FREQ,
    };

    ESP_ERROR_CHECK(i2c_master_bus_add_device(*p_bus_handle, &dev_cfg, p_dev_handle));

    vTaskDelay( 50 / portTICK_PERIOD_MS );

    uint8_t get_status_command_buffer[1] = {0x71};
    uint8_t status_buffer[1] = {0};
    ESP_ERROR_CHECK(i2c_master_transmit_receive(*p_dev_handle, get_status_command_buffer, sizeof(get_status_command_buffer),
                                                            status_buffer, sizeof(status_buffer), -1));

    if ((status_buffer[0] & 0x04) != 0x04)
    {
        uint8_t init_command_buffer[3] = {0xBE, 0x08, 0x00};
        ESP_ERROR_CHECK(i2c_master_transmit(*p_dev_handle, init_command_buffer, sizeof(init_command_buffer), -1));

        vTaskDelay( 10 / portTICK_PERIOD_MS );
    }

    return ESP_OK;
}

esp_err_t AHT20_read_humidity(i2c_master_dev_handle_t *p_dev_handle, uint8_t *humidity)
{
    uint8_t read_buffer[6] = {0};
    
    AHT20_get_measurement(p_dev_handle, read_buffer);
    
    uint32_t humidity_raw = read_buffer[0] << 16 | 
                            read_buffer[1] << 8  |
                            read_buffer[2];
    humidity_raw = humidity_raw >> 4;
    *humidity = (humidity_raw * 100 / 1048576);

    return ESP_OK;
}

esp_err_t AHT20_read_temperature(i2c_master_dev_handle_t *p_dev_handle, uint8_t *temperature)
{    
    uint8_t read_buffer[6] = {0};

    AHT20_get_measurement(p_dev_handle, read_buffer);

    uint32_t temperature_raw = read_buffer[2] << 16 | 
                                read_buffer[3] << 8  |
                                read_buffer[4];
    temperature_raw = temperature_raw & 0x0FFFFF;
    *temperature = (temperature_raw * 200 / 1048576)-50;
    
    return ESP_OK;
}

esp_err_t AHT20_get_measurement(i2c_master_dev_handle_t *p_dev_handle, uint8_t measurement_buffer[6])
{
    uint8_t command_buffer[3] = {0xAC, 0x33, 0x00};
    ESP_ERROR_CHECK(i2c_master_transmit(*p_dev_handle, command_buffer, sizeof(command_buffer), -1));
    vTaskDelay( 80 / portTICK_PERIOD_MS );
    uint8_t buffer[8] = {0};
    ESP_ERROR_CHECK(i2c_master_receive(*p_dev_handle, buffer, 1, -1));

    if ((buffer[0] & 0x80) == 0x00)
        ESP_ERROR_CHECK(i2c_master_receive(*p_dev_handle, buffer, 8, -1));
    memcpy(measurement_buffer, &buffer[1], 6);

    return ESP_OK;
}
