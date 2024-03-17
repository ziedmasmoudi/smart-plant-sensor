idf_component_register(SRCS "main.c" 
                            "sensors_task.c" 
                            "bluetooth.c"
                            "gatt_svr.c"
                            "./drivers/AHT20.c" 
                    INCLUDE_DIRS "drivers")
