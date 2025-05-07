#include <string.h>
#include "bsp/bsp.h"
#include "semihosting.h"
#include "semihosting_stream.h"

#define BUFFERSIZE 512

static constexpr uint8_t DISABLE_GLL[9] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x01, 0x00};
static constexpr uint8_t DISABLE_GSV[9] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x03, 0x00};
static constexpr uint8_t DISABLE_RMC[9] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x04, 0x00};
static constexpr uint8_t DISABLE_VTG[9] = {0xB5, 0x62, 0x06, 0x01, 0x03, 0x00, 0xF0, 0x05, 0x00};
// static constexpr uint8_t DISABLE_TXT[10] = {0xB5, 0x62, 0x06, 0x02, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00};
static constexpr uint8_t CFG_RATE[12] = {0xB5, 0x62, 0x06, 0x08, 0x06, 0x00, 0xC8 /*delay (ms)*/, 0x00, 0x01, 0x00, 0x01, 0x00};

uint8_t received = 0;
uint16_t idxPrev = 0;
uint16_t idx = 0;

int main() {
    board::Initialize();
    SemihostingInit();
    mcu::semi << "New run\n";

    uint8_t RxBuffer[BUFFERSIZE];
    memset(RxBuffer, 0, BUFFERSIZE);
    std::string RxString;

    board::GNSS_TX_UBX(DISABLE_GLL, sizeof(DISABLE_GLL));
    board::GNSS_TX_UBX(DISABLE_GSV, sizeof(DISABLE_GSV));
    board::GNSS_TX_UBX(DISABLE_RMC, sizeof(DISABLE_RMC));
    board::GNSS_TX_UBX(DISABLE_VTG, sizeof(DISABLE_VTG));
    // board::GNSS_TX_UBX(DISABLE_TXT, sizeof(DISABLE_TXT));
    board::GNSS_TX_UBX(CFG_RATE, sizeof(CFG_RATE));
    board::Delay(100);
    board::GNSS_Start_RX(RxBuffer, BUFFERSIZE);

    while (true) {
        if (received) {
            RxString.clear();

            if(idx < idxPrev){ // Buffer overflow
                for(uint16_t i = idxPrev; i < BUFFERSIZE; i++){
                    RxString.push_back(RxBuffer[i]);
                }
                for(uint16_t i = 0; i < idx; i++){
                    RxString.push_back(RxBuffer[i]);
                }
            }
            else{
                for(uint16_t i = idxPrev; i < idx; i++){
                    RxString.push_back(RxBuffer[i]);
                }
            }
            idxPrev = idx;
            mcu::semi << RxString.c_str();
            received = 0;
        }
    }
}

