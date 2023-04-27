#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "graphics.h"
#include "keyboard.h"

extern uint8_t output;
extern vbe_mode_info_t mode_info;

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
    printf("Error changing to graphics mode\n");
    return 1;
  }

  sleep(delay);

  if(vg_exit()){
    printf("Error returning to text mode\n");
    return 1;
  }
  return 0;
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
  //1. map the video memory to the process' address space
  if(map_phys_mem(mode)){
    printf("Error mapping video memory to the process address space\n");
    return 1;
  }

  //2. Change the video mode to that in its argument
  if(set_graphics_mode(mode)){
    printf("Error changing to the graphics mode\n");
    return 1;
  }

  //3. Draw a rectangle
  if(vg_draw_rectangle(x, y, width, height, color)){
    printf("Error drawing rectangle\n");
    return 1;
  }

  //4. Reset the video mode to Minix's default text mode and return, upon receiving the break code of the ESC key (0x81)
  wait_esq();

  if(vg_exit()){
    printf("Error returning to text mode\n");
    return 1;
  }
  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if(map_phys_mem(mode)){
    printf("Error mapping video memory to the process address space\n");
    return 1;
  }

  if(set_graphics_mode(mode)){
    printf("Error changing to the graphics mode\n");
    return 1;
  }

  uint16_t height = mode_info.YResolution / no_rectangles;
  uint16_t width = mode_info.XResolution / no_rectangles;
  uint32_t  color;

  for(unsigned row=0; row < no_rectangles; row++){
    for(unsigned col=0; col < no_rectangles; col++){
      color = get_color(row, col, step, first, no_rectangles);
      if(vg_draw_rectangle(col*width, row*height, width, height, color)){
        printf("Error drawing rectangle\n");
        return 1;
      }
    }
  }

  wait_esq();

  if(vg_exit()){
    printf("Error returning to text mode\n");
    return 1;
  }
  return 0;
}


int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if(map_phys_mem(0x105)){
    printf("Error mapping video memory to the process address space\n");
    return 1;
  }

  if(set_graphics_mode(0x105)){
    printf("Error changing to the graphics mode\n");
    return 1;
  }

  if(draw_xpm(xpm, x, y)){
    printf("Error drawing xpm\n");
    return 1;
  }

  wait_esq();

  if(vg_exit()){
    printf("Error returning to text mode\n");
    return 1;
  }
  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
