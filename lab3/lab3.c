#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>
#include "keyboard.h"

extern uint8_t output;
extern int count_sys_inb;
extern int timer_counter; 

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
  int ipc_status, r;
  message msg;

  bool make, secondByte = false;
  uint8_t bytes[2];

  uint8_t keyboard_bit_no;

  if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
    printf("kbd_test_scan() -> Error subscribing keyboard interrupts\n");
    return 1;
  }
kbd_print_scancode(make, 2, by)
  while(output != BREAK_ESC){
    if((r = driver_receive(ANY, &msg, &ipc_status))) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
            kbc_ih();
            make = !(output & BREAK_CODE);

            if(secondByte){
              secondByte=false;
              bytes[1]=output;
              kbd_print_scancode(make, 2, bytes);
            }
            else{
              bytes[0] = output;
              if(output == TWO_BYTES){
                secondByte = true;
              }
              else kbd_print_scancode(make, 1, bytes);
            }
          }
          break;
      }
    } 
  }

  if(keyboard_unsubscribe_interrupts()){
    printf("kbd_test_scan() -> Error unsubscribing keyboard interrupt's\n");
    return 1;
  }

  return kbd_print_no_sysinb(count_sys_inb);
}

int(kbd_test_poll)() {
  bool make, secondByte = false;
  uint8_t bytes[2];
  uint8_t st;

  while(output != BREAK_ESC){
    if(read_KBC_status(&st)){
      printf("kbd_test_poll() -> Error reading KBC status\n");
      return 1;
    }

    if((st & FULL_OUT_BUFFER) && !(st & AUX)){
      kbc_ih();
      make = !(output & BREAK_CODE);

      if(secondByte){
        secondByte=false;
        bytes[1]=output;
        kbd_print_scancode(make, 2, bytes);
      }
      else{
        bytes[0] = output;
        if(output==TWO_BYTES){
          secondByte = true;
        }
        else kbd_print_scancode(make, 1, bytes);
      }
    }
  }

  if(keyboard_restore()){
    printf("kbd_test_poll() -> Error restoring keyboard interrupts\n");
    return 1;
  }

  return kbd_print_no_sysinb(count_sys_inb);
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status, r;
  message msg;

  bool make, secondByte = false;
  uint8_t bytes[2];
  uint8_t keyboard_bit_no, timer_bit_no;
  int idle_time = n;

  if(timer_subscribe_int(&timer_bit_no)){
    printf("Error while subscribing timer interrupt\n");
    return 1;
  }

  if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
    printf("Error subscribing keyboard interrupts\n");
    return 1;
  }

  while(idle_time > 0 && (output != BREAK_ESC)){
    if((r = driver_receive(ANY, &msg, &ipc_status))) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
            kbc_ih();
            make = !(output & BIT(7));
            if(secondByte){
              secondByte=false;
              bytes[1]=output;
              kbd_print_scancode(make, 2, bytes);
            }
            else{
              bytes[0] = output;
              if(output==0xE0){
                secondByte = true;
              }
              else kbd_print_scancode(make, 1, bytes);
            }
            idle_time = n;
            timer_counter = 0;
          }

          if (msg.m_notify.interrupts & BIT(timer_bit_no)){
            timer_int_handler();
                
            if(timer_counter%60 == 0){
              idle_time--;
              timer_print_elapsed_time();
            }
          }
          break;

        default:
           break;
      }
    } 
  }

  if(timer_unsubscribe_int()){
    printf("Error while unsubscribing timer interrupt\n");
    return 1;
  }

  if(keyboard_unsubscribe_interrupts()){
    printf("Error unsubscribing keyboard interrupts\n");
    return 1;
  }

  return 0;
}
