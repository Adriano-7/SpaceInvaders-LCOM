#include <lcom/lcf.h>

#include <stdint.h>

int count_sys_inb = 0;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb==NULL){printf("util_get_LSB() -> Lsb is nullptr\n"); return 1;}

  *lsb = (uint8_t) val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb==NULL){printf("util_get_MSB() -> Msb is nullptr\n"); return 1;}

  *msb = (uint8_t) val >> 8;
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if(value==NULL){printf("util_sys_inb() -> Value passed is nullptr\n"); return 1;}

  uint32_t value_32;
  if(sys_inb(port, &value_32)){printf("Error while reading from port 0x%x\n", port); return 1;}
  *value = (uint8_t) value_32;

  count_sys_inb++;
  return 0;
}
