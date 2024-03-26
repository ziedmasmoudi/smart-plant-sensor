#pragma once

#include "nimble/ble.h"
#include "modlog/modlog.h"

/* Environmental Sensing configuration */
#define GATT_ES_UUID                            0x181A
#define GATT_ES_TEMPERATURE_UUID                0x181A
#define GATT_DEVICE_INFO_UUID                   0x180A
#define GATT_MANUFACTURER_NAME_UUID             0x2A29
#define GATT_MODEL_NUMBER_UUID                  0x2A24

extern uint16_t es_temp_handle;

struct ble_hs_cfg;
struct ble_gatt_register_ctxt;

void gatt_svr_register_cb(struct ble_gatt_register_ctxt *ctxt, void *arg);
int gatt_svr_init(void);
