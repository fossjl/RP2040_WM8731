#include "DigitalAudioInterfaceFormat.h"

void DigitalAudioInterfaceFormat_init(DigitalAudioInterfaceFormat *config) {
    config->FORMAT   = I2S;
    config->IWL      = _24_BITS;
    config->LRP      = 0;
    config->LRSWAP   = 0;
    config->MS       = 0;
    config->BCLKINV  = 0;
}

unsigned int DigitalAudioInterfaceFormat_build(DigitalAudioInterfaceFormat *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->FORMAT  << offset; offset += 2;
    temp |= config->IWL     << offset; offset += 2;
    temp |= config->LRP     << offset; offset += 1;
    temp |= config->LRSWAP  << offset; offset += 1;
    temp |= config->MS      << offset; offset += 1;
    temp |= config->BCLKINV << offset;
    
    return temp;
}

