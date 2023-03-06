#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

static int hook_id = 0;
int counter = 0;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
  uint8_t st;
  if(timer_get_conf(timer, &st)){
      printf("Error getting config from timer %d\n", timer);
      return 1;
  }

  uint8_t control_word;

  switch (timer){
      case 0:
          control_word = (TIMER_SEL0 | TIMER_LSB_MSB | (st & 0x0F)); 
          break;
      case 1:
          control_word = (TIMER_SEL1 | TIMER_LSB_MSB | (st & 0x0F)); 
          break;
      case 2:
          control_word = (TIMER_SEL2 | TIMER_LSB_MSB | (st & 0x0F)); 
          break;
  }

  if(sys_outb(TIMER_CTRL, control_word)){
      printf("Error writing to timer control register\n");
      return 1;
  }

  uint16_t counter = TIMER_FREQ / freq;
  uint8_t lsb, msb;
  util_get_LSB(counter, &lsb);
  util_get_MSB(counter, &msb);

  if(sys_outb(TIMER_0 + timer, lsb)) {printf("Error writing lsb to timer %d\n", timer); return 1;}
  if(sys_outb(TIMER_0 + timer, msb)) {printf("Error writing msb to timer %d\n", timer); return 1;}

  return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
    if(bit_no==NULL) return 1;

    *bit_no = hook_id;
    if(sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &hook_id)){
        printf("Error while sys_irqsetpolicy\n");
        return 1;
    }
  return 0;
}

int (timer_unsubscribe_int)() {
  if(sys_irqrmpolicy(&hook_id)){
    printf("Error while calling sys_irqrmpolicy\n");
    return 1;
  }
  return 0;
}

void (timer_int_handler)() {
    counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
    if(sys_outb(TIMER_CTRL, TIMER_RB_SEL(timer) | TIMER_RB_COUNT_ | TIMER_RB_CMD)){
        printf("Error in writing to timer control register\n");
        return 1;
    }

    if(util_sys_inb(TIMER_0 + timer, st)){
        printf("Error reading config from timer %d\n", timer);}

    return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st,
                        enum timer_status_field field) {
  
  union timer_status_field_val val;
  uint8_t mode;

  switch (field){
      case tsf_all:
          val.byte = st;
          break;

      case tsf_initial:
          mode = (st & (BIT(4) | BIT(5))) >> 4;

          if(mode==BIT(0)){val.in_mode=LSB_only;}
          else if(mode==BIT(1)){val.in_mode=MSB_only;}
          else if(mode== (BIT(0) | BIT(1))){val.in_mode=MSB_after_LSB;}
          else{val.in_mode = INVAL_val;}
          break;

      case tsf_mode:
          mode = (st & (BIT(1) | BIT(2) | BIT(3))) >> 1;
          if(mode==6){val.count_mode=2;}
          else if(mode==7){val.count_mode=3;}
          else{val.count_mode=mode;}
          break;

      case tsf_base:
          val.bcd = st & 1;
          break;

    default:
      printf("Invalid field\n");
      return 1;
  }

  return timer_print_config(timer, field, val);
}
