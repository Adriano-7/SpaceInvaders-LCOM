#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  if(lsb==NULL){printf("Lsb is a null pointer\n"); return 1;}
  *lsb = (uint8_t) val;
  return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  if(msb==NULL){printf("Msb is a null pointer\n"); return 1;}
  *msb = (uint8_t) (val >> 8);
  return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
  if(value==NULL){printf("Value is a null pointer\n"); return 1;}
  uint32_t val;
  if(sys_inb(port, &val)){printf("Error reading from the port\n"); return 1;}

  util_get_LSB(val, value);
  
  return 0;
}
