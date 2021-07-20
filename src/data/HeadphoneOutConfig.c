#include "HeadphoneOutConfig.h"

void HeadphoneOutConfig_init(HeadphoneOutConfig *config) {
    config->HPVOL  = 0x79;
    config->LZCEN  = 0;
    config->HPBOTH = 0;
}

unsigned int HeadphoneOutConfig_build(HeadphoneOutConfig *config) {
    unsigned int temp = 0;
    int offset = 0;

    temp |= config->HPVOL   << offset; offset += 7;
    temp |= config->LZCEN   << offset; offset += 1;
    temp |= config->HPBOTH  << offset;

    return temp;
}