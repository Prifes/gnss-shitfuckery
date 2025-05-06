#ifndef BSP_H
#define BSP_H

#include <cstdint>

extern uint8_t received;
extern uint16_t idx;

namespace board {
void Initialize();
void Delay(uint32_t delay);
void LED_Toggle();
bool GNSS_TX_UBX(const uint8_t* buffer, uint16_t size);
bool GNSS_Start_RX(uint8_t* buffer, uint16_t maxSize);
}  // namespace board

#endif  // BSP_H