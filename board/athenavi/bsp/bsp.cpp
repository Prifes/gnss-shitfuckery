#include "bsp.h"
#include "gpio.h"
// #include "i2c.h"
// #include "spi.h"
#include "usart.h"
#include "stm32f4xx_hal.h"
#include "dma.h"

extern "C" void SystemClock_Config(void);

namespace board {
void Initialize() {
    received = 0;

    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    // MX_SPI1_Init();
    // MX_I2C1_Init();
    MX_DMA_Init();
    MX_USART3_UART_Init();
}

void LED_Toggle(){
    HAL_GPIO_TogglePin(LED_GPIO_Port, LED_Pin);
}

void Delay(uint32_t delay){
    HAL_Delay(delay);
}

bool GNSS_TX_UBX(const uint8_t* buffer, uint16_t size){
    uint8_t ck_a = 0, ck_b = 0;
    uint8_t output[size + 2];
    // Copy sync chars
    output[0] = buffer[0];
    output[1] = buffer[1];
    for (size_t i = 2; i < size; ++i) { // Skip sync chars
        output[i] = buffer[i]; // Copy payload
        ck_a += buffer[i];
        ck_b += ck_a;
    }
    // Add checksum chars
    output[size] = ck_a;
    output[size + 1] = ck_b;
    return HAL_UART_Transmit(&huart3, output, size + 2, 1000) == HAL_OK;
}

bool GNSS_Start_RX(uint8_t* buffer, uint16_t maxSize){
    return HAL_UARTEx_ReceiveToIdle_DMA(&huart3, buffer, maxSize) == HAL_OK;
}

}  // namespace board

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size){
    received = 1;
    idx = Size;
    UNUSED(huart);
}