#include "video.h"

struct minix_mem_range mem_range;
unsigned int vram_base;
unsigned int vram_size;

vbe_mode_info_t mode_info;
uint8_t *video_mem;
uint16_t BytesPerPixel;

int (video_set_mode)(uint16_t mode){
    reg86_t reg86;

    memset(&reg86, 0, sizeof(reg86));
    reg86.intno = 0x10; //BIOS video services
    reg86.ah = 0x4F; //Invoking VBE function
    reg86.al = 0x02; //Set VBE mode
    reg86.bx = BIT(14) | mode; //Bit 14 set in order to set the linear frame buffer model

    if(sys_int86(&reg86)) {
        printf("Error calling sys_int86\n");
        return 1;
    }

    return 0;
}

int (video_exit_mode)(){
    reg86_t reg86;

    memset(&reg86, 0, sizeof(reg86));
    reg86.intno = 0x10; //BIOS video services
    reg86.ah = 0x00;
    reg86.al = 0x03; //CGA mode(used by Minix to return to text mode)

    if(sys_int86(&reg86)) {
        printf("Error calling sys_int86\n");
        return 1;
    }

    return 0;  
}

int (map_phys_mem) (uint16_t mode){
    memset(&mode_info, 0, sizeof(mode_info));
    if(vbe_get_mode_info(mode, &mode_info)){
        printf("Error retrieving the mode info\n");
        return 1;
    }

    BytesPerPixel = (mode_info.BitsPerPixel+7) / 8;

    vram_base = mode_info.PhysBasePtr;
    vram_size = mode_info.XResolution * mode_info.YResolution * BytesPerPixel;

    mem_range.mr_base = vram_base;
    mem_range.mr_limit = vram_base + vram_size;

    if(sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mem_range)){
        printf("Error adding the memory range\n");
        return 1;
    }

    video_mem = vm_map_phys(SELF, (void *) mem_range.mr_base, vram_size);
    if(video_mem == MAP_FAILED){
        printf("Error mapping the physical memory\n");
        return 1;
    }

    return 0;
}

int (video_get_index)(uint16_t x, uint16_t y){
    return (y*mode_info.XResolution + x) * BytesPerPixel;
}

int (video_draw_pixel)(uint16_t x, uint16_t y, uint32_t color){
    if(x >= mode_info.XResolution || y >= mode_info.YResolution || x < 0 || y < 0){
        printf("Error: pixel out of bounds\n");
        return 1;
    }
    
    if(memcpy(&video_mem[video_get_index(x, y)], &color, BytesPerPixel) == NULL){
        printf("Error drawing the pixel\n");
        return 1;
    }
    return 0;
}


int (video_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
    for(unsigned i=0; i<len; i++){
        if(video_draw_pixel(x+i, y, color)) {
            printf("Error drawing pixel (%d, %d)\n", x+i, y);
            return 1;
        }
    }
    return 0;
}

int (video_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
    for(unsigned j=0; j<height; j++){
        if(video_draw_hline(x, y+j, width, color)){
            printf("Error drawing hline y=%d\n", y+j);
            return 1;
        }
    }
    return 0;
}

int (video_draw_xpm)(xpm_image_t img, uint8_t* img_colors, uint16_t x, uint16_t y){
  if(img_colors==NULL){
    printf("img_colors is nullptr\n");
    return 1;
  }

  for(int i=0; i<img.height; i++){
    for(int j=0; j<img.width; j++){
      if(video_draw_pixel(x+j, y+i, *img_colors++)) {printf("Error drawing pixel (%d, %d) of the xpm\n", x+j, y+i); return 1;}
    }
  }

  return 0;
}

int (erase_screen)(){
  if(video_draw_rectangle(0, 0, mode_info.XResolution, mode_info.YResolution, 0)) {printf("Error erasing screen\n"); return 1;}
  return 0;
}
