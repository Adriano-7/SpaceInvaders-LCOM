#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include "graphics.h"
#include "keyboard.h"

extern uint8_t output;
extern vbe_mode_info_t mode_info;
extern int timer_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if(set_graphics_mode(mode)){
    printf("Error setting graphics mode\n");
    return 1;
  }

  sleep(delay);

  if(vg_exit()){
    printf("Error exiting graphics mode\n");
    return 1;
  }

  return 1;
}

int(wait_esq)(){
  int ipc_status, r;
  message msg;
  uint8_t keyboard_bit_no;

  if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
    printf("Error subscribing keyboard interrupts\n");
    return 1;
  }
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
            break;
          }
        default:
          break;
      }
    } 
  }

  if(keyboard_unsubscribe_interrupts()){
    printf("Error unsubscribing keyboard interrupt's\n");
    return 1;
  }
  return 0;
}


int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {
  if(map_phys_mem(mode)){
    printf("Error mapping physical memory\n");
    return 1;
  }

  if(set_graphics_mode(mode)){
    printf("Error setting graphics mode\n");
    return 1;
  }

  if(vg_draw_rectangle(x, y, width, height, color)){
    printf("Error drawing rectangle\n");
    return 1;
  }

  wait_esq();

  if(vg_exit()){
    printf("Error exiting graphics mode\n");
    return 1;
  }
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if(map_phys_mem(mode)){
    printf("Error mapping physical memory\n");
    return 1;
  }
  
  if(set_graphics_mode(mode)){
    printf("Error setting graphics mode\n");
    return 1;
  }

  if(vg_draw_pattern(no_rectangles, first, step)){
    printf("Error drawing pattern\n");
    return 1;
  }

  wait_esq();

  if(vg_exit()){
    printf("Error exiting graphics mode\n");
    return 1;
  }
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {
  if((xi != xf) && (yi != yf)){
    printf("The movement should be either horizontal or vertical not both");
  }

  if(map_phys_mem(G_Mode_1024x768)){
    printf("Error mapping physical memory\n");
    return 1;
  }

  if(set_graphics_mode(G_Mode_1024x768)){
    printf("Error setting graphics mode\n");
    return 1;
  }

  int ipc_status, r;
  message msg;

  bool make, secondByte = false;
  uint8_t bytes[2];
  uint8_t keyboard_bit_no, timer_bit_no;

  if(timer_subscribe_int(&timer_bit_no)){
    printf("Error while subscribing timer interrupt\n");
    return 1;
  }

  if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
    printf("Error subscribing keyboard interrupts\n");
    return 1;
  }

  uint16_t x=xi;
  uint16_t y=yi;

  int frameCounter=0;
  int timeFrame=sys_hz()/fr_rate;

  bool verticalMovement = yi != yf;
  bool positiveMovement = (verticalMovement && yi < yf) || (!verticalMovement && xi < xf);

  xpm_image_t img;
  xpm_load(xpm, XPM_INDEXED, &img);
  draw_xpm(xpm, xi, yi);

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
            make = !(output & BIT(7));
            if(secondByte){
              secondByte=false;
              bytes[1]=output;
            }
            else{
              bytes[0] = output;
              if(output==0xE0){
                secondByte = true;
              }
            }
          }

          if (msg.m_notify.interrupts & BIT(0) && (x != xf || y != yf)){
            timer_int_handler();

            if(timer_counter%timeFrame==0){
              uint16_t oldX = x;
              uint16_t oldY = y;
              if(speed>0){
                if(pos_speed_update(verticalMovement, positiveMovement, &x, &y, xf, yf, speed)){
                  erase_screen(oldX, oldY, img);
                  draw_xpm(xpm, x, y);
                }
              }
              else{
                if(neg_speed_update(verticalMovement, positiveMovement, &x, &y, xf, yf, speed, &frameCounter)){
                  erase_screen(oldX, oldY, img);
                  draw_xpm(xpm, x, y);
                }
              }
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


  if(vg_exit()){
    printf("Error exiting graphics mode\n");
    return 1;
  }
  return 0;
}


int(video_test_controller)() {
  return 1;
}
