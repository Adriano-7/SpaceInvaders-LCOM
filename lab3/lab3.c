#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "i8042.h"
#include "keyboard.h"
#include "util.h"

extern uint8_t output;
extern int timer_counter;
uint8_t cnt = 0;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}



int(kbd_test_scan)() {
  int ipc_status;
  message msg;
  uint8_t bit_no;

  bool ReadSecond = false;
  uint8_t bytes[2];
  int r;

  int irq_keyboard_set = BIT(1);

  if(keyboard_subscribe_interrupts(&bit_no)){
      printf("Error while calling subscribing the keyboard interrupts\n");
      return 1;
  }


  while(output != BREAK_ESC) { 
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed");
        continue;
      }
      
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & irq_keyboard_set) {
            kbc_ih();
            if(ReadSecond){
              ReadSecond = false;
              bytes[1] = output;
              kbd_print_scancode(!(output & BIT(7)), 2, bytes);
            }
            else{
              bytes[0] = output;
              if(output == TWO_BYTES){
                  ReadSecond = true;
              }
              else
                kbd_print_scancode(!(output & BIT(7)), 1, bytes);
              
            } 
          }
          break;
        default:
          break;
        } 
      } 
  }

  if(keyboard_unsubscribe_interrupts()){
    printf("Error Unsubscribing to keyboard interruptions\n");
    return 1;
  }

  kbd_print_no_sysinb(cnt);
  return 0;
}

int(kbd_test_poll)() {
  uint8_t st;
  bool ReadSecond = false;
  uint8_t bytes[2];

  while(output != BREAK_ESC) { 
      /*Ler o status*/
      read_KBC_status(&st);

      /*Verificar se o output buffer está cheio e o AUX está a 0*/
      if((st & FULL_OUT_BUFFER) && !(st & AUX)){
        kbc_ih();
        if(ReadSecond){
              ReadSecond = false;
              bytes[1] = output;
              kbd_print_scancode(!(output & BIT(7)), 2, bytes);
            }
        else{
          bytes[0] = output;
          if(output == TWO_BYTES){
              ReadSecond = true;
          }
          else{kbd_print_scancode(!(output & BIT(7)), 1, bytes);}
        } 
      }
  }

  keyboard_restore();
  kbd_print_no_sysinb(cnt);

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status;
  message msg;
  uint8_t bit_no_timer, bit_no_keyboard;

  bool ReadSecond = false;
  uint8_t bytes[2];
  int r;

  int irq_set_keyboard = BIT(1);
  int irq_set_timer = BIT(0);
  uint8_t time = n;

  if(timer_subscribe_int(&bit_no_timer)) {
    printf("Error while calling subscribing the timer\n");
    return 1;
  }
      

  if(keyboard_subscribe_interrupts(&bit_no_keyboard)){
      printf("Error while calling subscribing the keyboard interrupts\n");
      return 1;
  }


  while(time > 0 && output != BREAK_ESC) { 
      if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed");
        continue;
      }
      
      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if(msg.m_notify.interrupts & irq_set_timer){
            timer_int_handler();
            if(timer_counter % 60 == 0){
              time--;
              if(time == 0){
                printf("Time's up!\n");
                break;
              }
            }
          }

          if (msg.m_notify.interrupts & irq_set_keyboard) {
            kbc_ih();
            if(ReadSecond){
              ReadSecond = false;
              bytes[1] = output;
              kbd_print_scancode(!(output & BIT(7)), 2, bytes);
            }
            else{
              bytes[0] = output;
              if(output == TWO_BYTES){
                  ReadSecond = true;
              }
              else
                kbd_print_scancode(!(output & BIT(7)), 1, bytes);
              
            } 
          }
          break;
        default:
          break;
        } 
      } 
  }

  if(timer_unsubscribe_int()) {
    printf("Error while calling timer_unsubscribe_int\n");
    return 1;
  }


  if(keyboard_unsubscribe_interrupts()){
    printf("Error Unsubscribing to keyboard interruptions\n");
    return 1;
  }

  kbd_print_no_sysinb(cnt);
  return 0;
}
