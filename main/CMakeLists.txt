idf_component_register(SRCS "main.c"
                            "hardware/led/bsp_led.c"
                            "hardware/key/bsp_key.c"
                            "hardware/stepper_motor/stepper_motor.c"
                            "hardware/uart/bsp_uart.c"
                    INCLUDE_DIRS 
                            "."
                            "hardware/led"
                            "hardware/key"
                            "hardware/stepper_motor"
                            "hardware/uart"
                            )