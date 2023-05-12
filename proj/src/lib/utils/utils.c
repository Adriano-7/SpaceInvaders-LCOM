#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb==NULL){printf("util_get_LSB() -> lsb is nullptr\n"); return 1;}
  *lsb = (uint8_t) val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb==NULL){printf("util_get_MSB() -> msb is nullptr\n"); return 1;}
  *msb = (uint8_t) (val >> 8);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if(value==NULL){printf("util_sys_inb() -> value is nullptr\n"); return 1;}
  uint32_t val_32;

  if(sys_inb(port, &val_32)){
    printf("util_sys_inb() -> Error regarding sys_inb()\n");
    return 1;
  }
  *value = (uint8_t) val_32;
  return 0;
}
