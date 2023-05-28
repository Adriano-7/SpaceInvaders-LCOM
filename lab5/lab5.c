#include <lcom/lcf.h>

#include <lcom/lab5.h>

#include <stdint.h>
#include <stdio.h>

#include "video.h"
#include "keyboard.h"

extern uint8_t scancode;
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
    //Put in the mode
    video_set_mode(mode);

    sleep(delay);

    //Go back to text mode
    vg_exit();
    return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

    //1. Map the video memory to the process' address space
    if(map_phys_mem(mode)){
        printf("Error mapping physical memory\n");
        return 1;
    }

    //2. Change to video mode
    if(video_set_mode(mode)){
        printf("Error setting video mode\n");
        return 1;
    }

    //3. Draw the rectangle
    color = correctColor(color);
    if(video_draw_rectangle(x, y, width, height, color)){
        printf("Error drawing rectangle\n");
        return 1;
    }

    //4. Wait for a key to be pressed
    int ipc_status, r;
    message msg;

    uint8_t keyboard_bit_no;
    if(keyboard_subscribe_int(&keyboard_bit_no)){
        printf("Error subscribing keyboard\n");
        return 1;
    }

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
                        keyboard_parse_output();
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

    //5. Go back to text mode
    if(vg_exit()){
        printf("Error exiting video mode\n");
        return 1;
    }

    return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
    //1. Map the video memory to the process' address space
    if(map_phys_mem(mode)) {printf("Error mapping the physical to virtual memory"); return 1;}

    //2. change the video mode to that in its argument
    if(video_set_mode(mode)) {printf("Error setting graphics mode\n"); return 1;}

    //3. draw a rectangle
    if(video_draw_pattern(no_rectangles, first, step)) {printf("Error drawing the pattern of rectangles\n"); return 1;}

    //4. Wait for a key to be pressed
    int ipc_status, r;
    message msg;

    uint8_t keyboard_bit_no;
    if(keyboard_subscribe_int(&keyboard_bit_no)){
        printf("Error subscribing keyboard\n");
        return 1;
    }

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
                        keyboard_parse_output();
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

    //5. Go back to text mode
    if(vg_exit())  {printf("Error exiting video mode\n"); return 1;}
                          
    return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  //1. map the video memory to the process' address space
  if(map_phys_mem(VIDEO_1024x768_MODE)) {printf("Error mapping the physical to virtual memory"); return 1;}

  //2. change the video mode to that in its argument
  if(video_set_mode(VIDEO_1024x768_MODE)) {printf("Error setting graphics mode\n"); return 1;}

  //3. draw the xpm
  if(video_draw_xpm(xpm, x, y)) {printf("Error drawing the xpm\n"); return 1;}

    //4. Wait for a key to be pressed
    int ipc_status, r;
    message msg;

    uint8_t keyboard_bit_no;
    if(keyboard_subscribe_int(&keyboard_bit_no)){
        printf("Error subscribing keyboard\n");
        return 1;
    }

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
                        keyboard_parse_output();
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

    //5. Go back to text mode
    if(vg_exit()) {printf("Error returning to text mode\n"); return 1;}

    return 0;
}
int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {
    //1. map the video memory to the process' address space
    if(map_phys_mem(VIDEO_1024x768_MODE)) {printf("Error mapping the physical to virtual memory"); return 1;}

    //2. change the video mode to that in its argument
    if(video_set_mode(VIDEO_1024x768_MODE)) {printf("Error setting graphics mode\n"); return 1;}

    //3. draw the xpm
    uint16_t x = xi;
    uint16_t y = yi;
    bool verticalMovement = (xi == xf);
    bool positiveMovement = (verticalMovement) ? (yf > yi) : (xf > xi);
    int frameCounter=0;
    int timeFrame=sys_hz()/fr_rate;

    xpm_image_t img;
    xpm_load(xpm, XPM_INDEXED, &img);
    if(video_draw_xpm(xpm, x, y)) return 1;

    int ipc_status, r;
    message msg;

    uint8_t keyboard_bit_no, timer_bit_no;

    if(timer_subscribe_int(&timer_bit_no)){
      printf("Error while subscribing timer interrupt\n");
      return 1;
    }

    if(keyboard_subscribe_int(&keyboard_bit_no)){
      printf("Error subscribing keyboard interrupts\n");
      return 1;
    }

    while(scancode != KEY_ESC_BREAK){
      if((r = driver_receive(ANY, &msg, &ipc_status))) {
        printf("driver_receive failed with: %d", r);
        continue;
      }

      if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
          case HARDWARE:
            if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
                keyboard_int_handler();
                keyboard_parse_output();
            }

            if (msg.m_notify.interrupts & BIT(0)){
              timer_int_handler();
                  
              if(timer_counter%timeFrame==0){
                uint16_t oldX = x; uint16_t oldY = y;

                if(coordinates_update(&x, &y, xf, yf, speed, &frameCounter, verticalMovement, positiveMovement)){
                  if(erase_screen(oldX, oldY, img)) {printf("Error erasing the screen\n"); return 1;}
                  if(video_draw_xpm(xpm, x, y)) {printf("Error drawing the xpm\n"); return 1;}
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

    if(keyboard_unsubscribe_int()){
      printf("Error unsubscribing keyboard interrupts\n");
      return 1;
    }

    //5. Go back to text mode
    if(vg_exit()) return 1;

    return 0;
}
