// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>

#include <stdint.h>
#include <stdio.h>

#include "mouse.h"

extern uint8_t mouse_out;
extern struct packet pkt;
extern int timer_counter; 

// Any header files included below this line should have been created by you
int main(int argc, char *argv[]){
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need/ it]
  lcf_trace_calls("/home/lcom/labs/lab4/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab4/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(mouse_test_packet)(uint32_t cnt){
  int ipc_status;
  message msg;

  uint8_t mouse_bit_no;

  // Configure the mouse
  if (enable_data_report()){
    printf("Error while enabling the mouse data report\n");
    return 1;
  }

  if (mouse_subscribe_int(&mouse_bit_no)){
    printf("Error while subscribing the mouse interrupts\n");
    return 1;
  }

  while (cnt > 0){
    if (driver_receive(ANY, &msg, &ipc_status)){
      printf("driver_receive failed");
      continue;
    }

    if (is_ipc_notify(ipc_status)){
      switch (_ENDPOINT_P(msg.m_source)){
      case HARDWARE:
        if (msg.m_notify.interrupts & BIT(mouse_bit_no)){
          mouse_ih();

          if(mouse_parse_output()){            
            mouse_build_packet();
            mouse_print_packet(&pkt);
            cnt--;
          }
        }
      }
    }
  }

  if (disable_data_report()){
    printf("Error while disabling the mouse data report\n");
    return 1;
  }

  if (mouse_unsubscribe_int()){
    printf("Error while unsubscribing the mouse interrupts\n");
    return 1;
  }

  return 0;
}

int(mouse_test_async)(uint8_t idle_time){
 int ipc_status;
  message msg;

  uint8_t mouse_bit_no, timer_bit_no;

  if (enable_data_report()){
    printf("Error while enabling the mouse data report\n");
    return 1;
  }

  if (mouse_subscribe_int(&mouse_bit_no)){
    printf("Error while subscribing the mouse interrupts\n");
    return 1;
  }

  if(timer_subscribe_int(&timer_bit_no)){
    printf("Error while subscribing timer interrupt\n");
    return 1;
  }

  uint8_t aux_idle_time = idle_time;

  while (aux_idle_time > 0){
    if (driver_receive(ANY, &msg, &ipc_status)){
      printf("driver_receive failed");
      continue;
    }

    if (is_ipc_notify(ipc_status)){
      switch (_ENDPOINT_P(msg.m_source)){
      case HARDWARE:
        if (msg.m_notify.interrupts & BIT(mouse_bit_no)){
          mouse_ih();

          if(mouse_parse_output()){
            mouse_build_packet();
            mouse_print_packet(&pkt);
          }
          aux_idle_time = idle_time;
        }

        if (msg.m_notify.interrupts & BIT(timer_bit_no)){
          timer_int_handler();

          if(timer_counter%sys_hz() == 0){
            aux_idle_time--;
            timer_print_elapsed_time();
          }
        }
        break;
      }
    }
  }

  if (disable_data_report()){
    printf("Error while disabling the mouse data report\n");
    return 1;
  }

  if(timer_unsubscribe_int()){
    printf("Error while unsubscribing timer interrupt\n");
    return 1;
  }

  if (mouse_unsubscribe_int()){
    printf("Error while unsubscribing the mouse interrupts\n");
    return 1;
  }

  return 0;
}

int(mouse_test_gesture)(uint8_t x_len, uint8_t tolerance){
  /* To be completed */
  printf("%s: under construction\n", __func__);
  return 1;
}

int(mouse_test_remote)(uint16_t period, uint8_t cnt){
  /* This year you need not implement this. */
  printf("%s(%u, %u): under construction\n", __func__, period, cnt);
  return 1;
}
