/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "sensors_task.h"

static const char *TAG = __FILE__;

void app_main(void)
{
    xTaskCreate(&sensors_task, "sensors_task", 2048, NULL, 5, NULL);
}