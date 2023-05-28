#include "timer.h"

int timer_hook_id = 0;
int timer_counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint16_t initialValue = TIMER_CLOCK_FREQ / freq;
  uint8_t lsbVal, msbVal;

  if(util_get_LSB(initialValue, &lsbVal)){printf("Error retrieving the lsb of the value\n");return 1;}
  if(util_get_MSB(initialValue, &msbVal)){printf("Error retrieving the msb of the value\n");return 1;}


  uint8_t st;
  if(timer_get_conf(timer, &st)){
    printf("Error retrieving the status\n");
    return 1;
  }

  uint8_t controlWord = (TIMER_CNTRL_WORD_SEL(timer) | TIMER_CNTRL_INIT_LSB_MSB | (st & 0x0F));
  if(sys_outb(TIMER_CNTRL_REG, controlWord)){
    printf("Error writing the control word\n");
    return 1;
  }

  if(sys_outb(TIMER_REG(timer), lsbVal)){
    printf("Error writing the lsb value\n");
    return 1;
  }

  if(sys_outb(TIMER_REG(timer), msbVal)){
    printf("Error writing the msb value\n");
    return 1;
  }

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
  if(bit_no==NULL){printf("Bit_no is a null pointer\n"); return 1;}
  *bit_no = timer_hook_id;
  
  if(sys_irqsetpolicy(TIMER_0_IRQ, IRQ_REENABLE, &timer_hook_id)){
    printf("Error subscribing the timer\n"); 
    return 1;
  }

  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&timer_hook_id)){
    printf("Error unsubscribing the timer\n"); 
    return 1;
  }

  return 0;
}

void (timer_int_handler)() {
  timer_counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
  if(st==NULL){printf("Status is a null pointer\n"); return 1;}

  uint8_t readBackCommand = (TIMER_RBK | TIMER_RBK_NOT_COUNT | TIMER_RBK_SEL(timer));
  if(sys_outb(TIMER_CNTRL_REG, readBackCommand)){
    printf("Error trying to write the rbk\n");
    return 1;
  }

  if(util_sys_inb(TIMER_REG(timer), st)){
    printf("Error reading the timer's register\n");
    return 1;
  }

  return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
  union timer_status_field_val conf;
  switch(field){
    case tsf_all:
      conf.byte = st;
      break;
    
    case tsf_initial:
      st = (st & TIMER_ST_ACCESS) >> 4;
      if(st == 1) conf.in_mode = LSB_only;
      else if(st == 2) conf.in_mode = MSB_only;
      else if (st == 3) conf.in_mode = MSB_after_LSB;
      else conf.in_mode = INVAL_val;
      break;
    
    case tsf_mode:
      st = (st & TIMER_ST_OP_MODE) >> 1;
      if(st == 6) conf.count_mode = 2;
      else if(st == 7) conf.count_mode = 3;
      else conf.count_mode = st;
      break;
    
    case tsf_base:
      conf.bcd = st & TIMER_ST_BCD;
      break;
  }

  return timer_print_config(timer, field, conf);
}
