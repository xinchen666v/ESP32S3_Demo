#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "hardware/led/bsp_led.h"
#include "hardware/key/bsp_key.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>

//中断服务函数
static void IRAM_ATTR gpio_isr_handler(void* arg)
{
    static int cnt = 0;
    cnt++;
    //当中断被触发时，LED状态发生变化
    gpio_set_level(LED_PIN,cnt%2);
}

void app_main(void)
{
    // int cnt = 0;
    // //LED初始化
    // LedGpioConfing();
    // //按键初始化
    // KeyGpioConfig();

    // while(1)
    // {   /*LED_demo*/
    //     // //设置LED点亮
    //     // LedOn();
    //     // vTaskDelay(100 / portTICK_PERIOD_MS);

    //     // //设置LED熄灭
    //     // LedOff();
    //     // vTaskDelay(100 / portTICK_PERIOD_MS);

    //     /*LED+KEY_demo*/
    //     // vTaskDelay(20 / portTICK_PERIOD_MS);
    //     // if(GetKeyValue() == 0)
    //     // {
    //     //     gpio_set_level(LED_PIN,cnt = !cnt);
    // //     }
    // }
    
    
}