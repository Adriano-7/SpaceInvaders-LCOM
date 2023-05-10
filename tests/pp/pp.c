// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/pp.h>

#include <stdint.h>

// Any header files included below this line should have been created by you

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/pp/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/pp/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

typedef struct {
 uint16_t x_res; // horizontal resolution
 uint16_t y_res; // vertical resolution
 uint8_t bpp; // bits per pixel
 uint8_t r_sz; // red component size
 uint8_t r_pos; // red component LSB position
 uint8_t g_sz; // green component size
 uint8_t g_pos; // green component LSB position
 uint8_t b_sz; // blue component size
 uint8_t b_pos; // blue component LSB position
 phys_addr_t phys_addr; // video ram base phys address
} lpv_mode_info_t;

enum lpv_dir_t {
 lpv_hor, // horizontal line
 lpv_vert // vertical line
};

uint8_t* frame_buffer;
lpv_mode_info_t mode_info;
unsigned BytesPerPixel;

int map_phys_mem(uint8_t mode){
    //obter informação sobre o modo atual
    if(memset(&mode_info, 0, sizeof(mode_info)) == NULL) {printf("Memset error"); return 1;}

    //calcular a lenght do frame buffer
    BytesPerPixel = (mode_info.b_sz+7) / 8;
    size_t frame_size = mode_info.x_res * mode_info.y_res * BytesPerPixel;

    frame_buffer = video_map_phys(mode_info.phys_addr, frame_size);
    if(frame_buffer==NULL) {printf("Error mapping phys to virtual memory /n");}
}

uint32_t get_color(uint8_t mode, uint32_t color){
    if(mode==1) return color;
    if()
    if(mode==3){
        uint32_t r = (color & 0x1f0000) >> 5;
        uint32_t g = (color & 0x003f00) >> 3;
        uint32_t b = color & 0x00001f;
        return ((r << mode_info.r_pos) | (g << mode_info.g_pos) | b);
    }

    return color;
}

int draw_pixel(uint16_t x, uint16_t y, uint32_t color){
    if (x >= mode_info.x_res || y >= mode_info.y_res || x < 0 || y < 0) return 0;
    int index = ((y*mode_info.x_res)+x)*BytesPerPixel;
    if(memcpy(&frame_buffer[index], &color, BytesPerPixel) == NULL) {printf("Error copying color to frame buffer /n"); return 1;}
    return 0;
}


int pp_test_line(uint8_t mode, enum lpv_dir_t dir, uint16_t x, uint16_t y, uint16_t len, uint32_t color, uint32_t delay){
    if(mode<1 || mode>4) {printf("Invalid mode /n"); return 1;}
    
    //1. Configure to change the mode
     if(lpv_set_mode(mode)) {printf("Error setting the graphic mode/n"); return 1;}

    //2. Map the Frame Buffer
    if(map_phys_mem(mode)) {printf("Error mapping virtual to physical memory /n"); return 1;}

    //3. Draw the line
    uint32_t realColor = get_color(mode, color);
    if(dir==lpv_hor){
        for(int i=0; i<len; i++){
            if(draw_pixel(x+i, y, realColor)){printf("Error drawing pixel /n"); return 1;}
        }
    }
    else{
        for(int i=0; i<len; i++){
            if(draw_pixel(x, y+i, realColor)){printf("Error drawing pixel /n"); return 1;}
        }
    }

    //4. Wait delay seconds
    sleep(delay);

    //5. Switch back to text mode
    if(lpv_set_mode(0)){printf("Error setting the text mode/n"); return 1;}
    return 0;
}