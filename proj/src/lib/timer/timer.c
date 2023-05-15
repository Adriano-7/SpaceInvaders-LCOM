
#include <stdint.h>

#include "timer.h"
#include "i8254.h"



int timer_hook_id = 0;
int timer_counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t st;
  if(timer_get_conf(timer, &st)){
    printf("timer_set_frequency() -> Error getting conf\n");
    return 1;
  }

  uint8_t control_word = (TIMER_SEL(timer) | TIMER_LSB_MSB | (st & 0x0F));

  if(sys_outb(TIMER_CTRL, control_word)){
    printf("timer_set_frequency() -> Error writing control word\n");
    return 1;
  }

  uint16_t val = 1193182/freq;

  uint8_t val_lsb;
  util_get_LSB(val, &val_lsb);
  if(sys_outb(TIMER_REG(timer), val_lsb)){
    printf("timer_set_frequency() -> Error writing lsb count value\n");
    return 1;
  }

  uint8_t val_msb;
  util_get_MSB(val, &val_msb);
  if(sys_outb(TIMER_REG(timer), val_msb)){
    printf("timer_set_frequency() -> Error writing msb count value\n");
    return 1;
  }

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no == NULL){
    printf("timer_subscribe_int() -> bit_no is nullptr\n");
    return 1;
  }

  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id)){
    printf("timer_subscribe_int() -> Error setting policy\n");
    return 1;
  }
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&timer_hook_id)){
    printf("timer_subscribe_int() -> Error removing policy\n");
    return 1;
  }
  return 0;
}

void (timer_int_handler)() {
  timer_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st==NULL){
    printf("timer_get_conf() -> st is nullptr\n");
    return 1;
  }

  uint8_t rbk = (TIMER_RB_CMD) | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  if(sys_outb(TIMER_CTRL, rbk)){
    printf("timer_get_conf() -> Error writing rbk\n");
    return 1;
  }

  if(util_sys_inb(TIMER_REG(timer), st)){
    printf("timer_get_conf() -> Error reading status\n");
    return 1;
  }
  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val conf;
  switch(field){
    case tsf_all:
      conf.byte = st;
      break;
    
    case tsf_initial:
      st = (st & (BIT(5) | BIT(4))) >> 4;
      if(st == 1) conf.in_mode = LSB_only;
      else if(st == 2) conf.in_mode = MSB_only;
      else if (st == 3) conf.in_mode = MSB_after_LSB;
      else conf.in_mode = INVAL_val;
      break;
    
    case tsf_mode:
      st = (st & (BIT(3) | BIT(2) | BIT(1))) >> 1;
      if(st == 6) conf.count_mode = 2;
      else if(st == 7) conf.count_mode = 3;
      else conf.count_mode = st;
      break;
    
    case tsf_base:
      conf.bcd = st & 1;
      break;
  }

  return timer_print_config(timer, field, conf);
}
