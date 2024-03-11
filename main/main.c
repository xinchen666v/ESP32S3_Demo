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
    
    gpio_config_t io_conf = {};
    LedGpioConfig();

    //下降沿中断
    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    //设置GPIO0的输入寄存器
    io_conf.pin_bit_mask = (1 << KEY_PIN);
    //输入模式
    io_conf.mode = GPIO_MODE_INPUT;
    //使能上拉模式
    io_conf.pull_up_en = 1;
    io_conf.pull_down_en = 0;
    gpio_config(&io_conf);

    //注册中断回调函数
    gpio_install_isr_service(ESP_INTR_FLAG_EDGE);

    //设置GPIO的中断服务函数
    gpio_isr_handler_add(KEY_PIN,gpio_isr_handler,(void*)NULL);

    //使能GPIO模块中断信号
    gpio_intr_enable(KEY_PIN);

    int time = 0;
    while(1)
    {
        printf("time: %d\n",time++);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

}