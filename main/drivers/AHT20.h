#pragma once

#include "esp_err.h"
#include "driver/i2c_master.h"

esp_err_t AHT20_init(i2c_master_bus_handle_t *p_bus_handle, i2c_master_dev_handle_t *p_dev_handle);
esp_err_t AHT20_read_humidity(i2c_master_dev_handle_t *p_dev_handle, uint8_t *humidity);
esp_err_t AHT20_read_temperature(i2c_master_dev_handle_t *p_dev_handle, uint8_t *temperature);
