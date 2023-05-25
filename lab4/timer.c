#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int timer_hook_id = 0;
int timer_counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t st;
  if(timer_get_conf(timer, &st)){
    printf("timer_set_frequency() -> Error while reading timer %d configuration\n", timer); 
    return 1;
  }

  uint8_t control_word = TIMER_SEL(timer) | (TIMER_LSB_MSB) | (st & 0x0F);
  sys_outb(0x43, control_word);

  uint16_t counting_value = TIMER_FREQ / freq;

  uint8_t val_lsb;
  util_get_LSB(counting_value, &val_lsb);
  sys_outb(REG_TIMER(timer), val_lsb);

  uint8_t val_msb;
  util_get_MSB(counting_value, &val_msb);
  sys_outb(REG_TIMER(timer), val_msb);

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no==NULL){printf("timer_subscribe_int() -> Bit_no is nullptr\n"); return 1;}

  *bit_no = timer_hook_id;

  if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id)){
    printf("timer_subscribe_int() -> Error trying to subscribe timer interrupt's\n"); 
    return 1;
  }
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&timer_hook_id)){
    printf("timer_unsubscribe_int() -> Error trying to unsubscribe timer interrupt's\n"); 
    return 1;
  }
  return 0;
}

void (timer_int_handler)() {
  timer_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  uint8_t RBK = TIMER_RB_CMD | TIMER_RB_COUNT_ | TIMER_RB_SEL(timer);
  sys_outb(REG_TIMER_CTRL, RBK);

  return util_sys_inb(REG_TIMER(timer), st);
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {

  union timer_status_field_val conf;

  switch(field){
    case tsf_all:
      conf.byte = st;
      break;

    case tsf_initial:
      conf.in_mode = (st & TIMER_LSB_MSB)>>4;
      break;

    case tsf_mode:
      st = (st & TIMER_COUNTING_MODE) >> 1;
      if(st==6) conf.count_mode = 2;
      else if(st==7) conf.count_mode = 3;
      else conf.count_mode = st;
      break;

    case tsf_base:
      conf.bcd = st & TIMER_BCD;
      break;
  }
  
  return timer_print_config(timer, field, conf);
}
