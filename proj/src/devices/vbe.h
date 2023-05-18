#ifndef _LCOM_VBE_H_
#define _LCOM_VBE_H_

#define TX_AH 0x00
#define TX_AL 0x03
#define TX_AX 0x0003
#define TX_BX 0x0000
#define TX_INTNO 0x10

#define GR_AH 0x4f
#define GR_AL 0x02
#define GR_AX 0x4f02
#define GR_BX(submode) (submode | BIT(14))
#define GR_INTNO 0x10

#define DIRECT_COLOR_MODE 0x06

#define G_Mode_1024x768 0x105
#define G_Mode_800x600 0x115

#endif
