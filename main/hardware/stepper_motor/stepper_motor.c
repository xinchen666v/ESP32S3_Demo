#include "stepper_motor.h"

#define NUM_MOTOR_PINS 4

// 定义电机引脚
const gpio_num_t motor_pins[NUM_MOTOR_PINS] = {MOTOR_A, MOTOR_B, MOTOR_C, MOTOR_D};

// 四相八拍模式的步进序列
int half_step_sequence[][NUM_MOTOR_PINS] = {
    {1, 0, 0, 0},
    {1, 1, 0, 0},
    {0, 1, 0, 0},
    {0, 1, 1, 0},
    {0, 0, 1, 0},
    {0, 0, 1, 1},
    {0, 0, 0, 1},
    {1, 0, 0, 1}
};

/*
 * @函数说明        MOTOR的初始化
*/
void motor_init(void)
{
    gpio_config_t gpio_init_struct = {0};

    for (int i = 0; i < NUM_MOTOR_PINS; ++i)
    {
        esp_rom_gpio_pad_select_gpio(motor_pins[i]);
    }

    gpio_init_struct.intr_type = GPIO_INTR_DISABLE;
    gpio_init_struct.mode = GPIO_MODE_OUTPUT;
    gpio_init_struct.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_init_struct.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_init_struct.pin_bit_mask = 0;

    for (int i = 0; i < NUM_MOTOR_PINS; ++i)
    {
        gpio_init_struct.pin_bit_mask |= (1ULL << motor_pins[i]);
    }

    gpio_config(&gpio_init_struct);

    gpio_set_level(motor_pins[0] | motor_pins[1] | motor_pins[2] | motor_pins[3], 0);
}

void motor_move(int sequence[][NUM_MOTOR_PINS], int num_steps)
{
    for (int step = 0; step < num_steps; ++step)
    {
        for (int i = 0; i < NUM_MOTOR_PINS; ++i)
        {
            gpio_set_level(motor_pins[i], sequence[step][i]);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // 延时10ms
    }
}

void motor_forward(void)
{
    motor_move(half_step_sequence, 8);
}

void motor_backward(void)
{
    // 逆向运动的步进序列与正向相同，只是反向遍历
    for (int step = 7; step >= 0; --step)
    {
        for (int i = 0; i < NUM_MOTOR_PINS; ++i)
        {
            gpio_set_level(motor_pins[i], half_step_sequence[step][i]);
        }
        vTaskDelay(10 / portTICK_PERIOD_MS);  // 延时10ms
    }
}
