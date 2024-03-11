#include "bsp_key.h"



//配置引脚寄存器
#define GPIO_INPUT_PIN_SEL  (1ULL<<KEY_PIN)

/**
 * @函数说明        按键引脚初始化
 * @传入参数        无
 * @函数返回        无
 */
void KeyGpioConfig(void)
{
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;//禁用中断
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;//选择要配置的IO
    io_conf.mode = GPIO_MODE_INPUT;//输入模式
    io_conf.pull_up_en = 1;//内部上拉
    io_conf.pull_down_en = 0;//内部下拉
    gpio_config(&io_conf);//配置IO
}

/**
 * @函数说明        获取按键引脚上的电平状态
 * @传入参数        无
 * @函数返回        0=按键被按下    1=按键没有被按下
 */
bool GetKeyValue(void)
{
    if(gpio_get_level(KEY_PIN) == 0)
    {
        vTaskDelay(100 / portTICK_PERIOD_MS);//延时10ms
        if(gpio_get_level(KEY_PIN) == 0)
        {
            return 0;
        }
    }
    return 1;
}