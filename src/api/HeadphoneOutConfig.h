#ifndef _WM8721_HeadphoneOutConfig_H
#define _WM8721_HeadphoneOutConfig_H

#include "wm8731_api.h"

struct HeadphoneOutConfig_s {
    unsigned HPVOL      : 7; // Headphone Output Volume Control
    unsigned LZCEN      : 1; // Zero Cross Detect Enable
    unsigned HPBOTH     : 1; // Simultanious Load of LHPVOL/RHPVOL and LZCEN/RZCEN
};

typedef struct HeadphoneOutConfig_s HeadphoneOutConfig;

void HeadphoneOutConfig_init(HeadphoneOutConfig *config);

unsigned int HeadphoneOutConfig_build(HeadphoneOutConfig *config);

static inline void HeadphoneOutConfig_send_left(HeadphoneOutConfig* cfg) {
  WM8731_CMD(WM8731_REG_LHPHONE_OUT, HeadphoneOutConfig_build(cfg));
}

static inline void HeadphoneOutConfig_send_right(HeadphoneOutConfig* cfg) {
  WM8731_CMD(WM8731_REG_RHPHONE_OUT, HeadphoneOutConfig_build(cfg));
}

uint convertNormalizedVolume(uint vol);

#endif // HeadphoneOutConfig