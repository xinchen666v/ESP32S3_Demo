#include "bsp_uart.h"


/**
 * @函数说明        uart_init_config
 * @传入参数        uart_port = 串口号
 *                      可选参数：UART_NUM_0,UART_NUM_1,UART_NUM_2
 *                 baud_rate = 串口波特率
 *                 tx_pin = 发送引脚
 *                 rx_pin = 接收引脚
 * @函数返回        无
*/

void uart_init_config(uart_port_t uart_port,uint32_t baud_rate,int tx_pin,int rx_pin)
{
    //定义 串口配置结构体，必须赋初始值，否则无法实现（所以0没有什么意义，只是随便赋初始值）
    uart_config_t uart_config={0};
    //设置串口配置参数
    uart_config.baud_rate = baud_rate;
    uart_config.data_bits = UART_DATA_8_BITS;
    uart_config.parity = UART_PARITY_DISABLE;
    uart_config.stop_bits = UART_STOP_BITS_1;
    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;

    //将以上参数加载到串口1的寄存器
    uart_param_config(uart_port, &uart_config);
    //绑定引脚 RTS和CTS不使用
    uart_set_pin(uart_port,tx_pin,rx_pin,UART_PIN_NO_CHANGE,UART_PIN_NO_CHANGE);

    //安装串口驱动程序
    uart_driver_install(uart_port,200,200,0,NULL,0);
}

/**
 * @函数说明        串口2接收任务
 * @传入参数        无
 * @函数返回        无
 * @函数说明        请通过xTaskCreate创建该任务
 */
void uart2_rx_task(void)
{
    uint8_t rx_data[200] = {0};
    uint8_t temp[50] = {0};
    while(1)
    {
        //接收串口数据收到的数据长度
        int rx_bytes = uart_read_bytes(UART_NUM_2,rx_data,200,10 / portTICK_PERIOD_MS);
        if(rx_bytes > 0)
        {
            rx_data[rx_bytes] = 0;

            //输出接收的数据的长度
            sprintf((const char*)temp,"uart2 string length: %d\r\n",rx_bytes);
            uart_write_bytes(UART_NUM_2,(const char*)temp,strlen((const char*)temp));
            //通过串口2输出接受到的数据
            uart_write_bytes(UART_NUM_2,(const char*)"uart2 received :",strlen("uart2 received :"));
            uart_write_bytes(UART_NUM_2,(const char*)rx_data,strlen((const char*)rx_data));
            //UART环缓冲区刷新，丢弃UART RX缓冲区的所有数据，准备下次接收
            uart_flush(UART_NUM_2);
        }
    }
}
