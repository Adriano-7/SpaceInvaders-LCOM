#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"

extern uint8_t scancode;
extern uint8_t kbd_bytes[2];
extern int kbd_bytesCounter;

extern int timer_counter;

extern int count_sys_inb;

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

    uint8_t keyboard_bit_no;
    if(keyboard_subscribe_int(&keyboard_bit_no)){
        printf("Error subscribing keyboard\n");
        return 1;
    }

    bool make;

    while(scancode != KEY_ESC_BREAK){
        if((r = driver_receive(ANY, &msg, &ipc_status)) != 0){
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if(is_ipc_notify(ipc_status)){
            switch(_ENDPOINT_P(msg.m_source)){
                case HARDWARE:
                    if(msg.m_notify.interrupts & BIT(keyboard_bit_no)){
                        keyboard_int_handler();
                        if(keyboard_parse_output()){
                            make = !(scancode & KEYBOARD_SCANCODE_BREAK);
                            kbd_print_scancode(make, kbd_bytesCounter+1, kbd_bytes);
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if(keyboard_unsubscribe_int()){
        printf("Error unsubscribing keyboard\n");
        return 1;
    }

    return kbd_print_no_sysinb(count_sys_inb);
}

int(kbd_test_poll)() {
    uint8_t st;
    bool make;
    while(scancode != KEY_ESC_BREAK){
        if(keyboard_get_status(&st)){
            printf("Error getting keyboard status\n");
            return 1;
        }

        if((st & KEYBOARD_ST_OBF) && !(st & KEYBOARD_ST_AUX)){
            keyboard_int_handler();
            if(keyboard_parse_output()){
                make = !(scancode & KEYBOARD_SCANCODE_BREAK);
                kbd_print_scancode(make, kbd_bytesCounter+1, kbd_bytes);
            }
        }
    }

    //missing the keyboard_restore function

    return kbd_print_no_sysinb(count_sys_inb);
}

int(kbd_test_timed_scan)(uint8_t n) {
  int ipc_status, r;
  message msg;

  uint8_t keyboard_bit_no, timer_bit_no;
  int idle_time = n;

  if(timer_subscribe_int(&timer_bit_no)){
    printf("Error while subscribing timer interrupt\n");
    return 1;
  }

  if(keyboard_subscribe_int(&keyboard_bit_no)){
    printf("Error subscribing keyboard interrupts\n");
    return 1;
  }
    
    bool make;
  while(idle_time > 0 && (scancode != KEY_ESC_BREAK)){
    if((r = driver_receive(ANY, &msg, &ipc_status))) {
      printf("driver_receive failed with: %d", r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
            keyboard_int_handler();
            if(keyboard_parse_output()){
                make = !(scancode & KEYBOARD_SCANCODE_BREAK);
                kbd_print_scancode(make, kbd_bytesCounter+1, kbd_bytes);
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

  if(keyboard_unsubscribe_int()){
    printf("Error unsubscribing keyboard interrupts\n");
    return 1;
  }

  return 0;
}
