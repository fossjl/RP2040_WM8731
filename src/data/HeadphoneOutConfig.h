#ifndef _WM8721_HeadphoneOutConfig_H
#define _WM8721_HeadphoneOutConfig_H

struct HeadphoneOutConfig_s {
    unsigned HPVOL      : 7; // Headphone Output Volume Control
    unsigned LZCEN      : 1; // Zero Cross Detect Enable
    unsigned HPBOTH     : 1; // Simultanious Load of LHPVOL/RHPVOL and LZCEN/RZCEN
};

typedef struct HeadphoneOutConfig_s HeadphoneOutConfig;

void HeadphoneOutConfig_init(HeadphoneOutConfig *config);

unsigned int HeadphoneOutConfig_build(HeadphoneOutConfig *config);

#endif // HeadphoneOutConfig