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

/*
 * Converts a normalized volume (0...100) to a volume register value
 */
uint convertNormalizedVolume(uint vol) {
  uint temp;
  if (vol <= 0) {
    temp = 0x0000;
  }
  else if (vol > 100) {
    temp = 80 + 0xAF;
  }
  else {
    temp = (int)(80 * vol/100.0) + 0x00AF;
  }

  return temp;
}