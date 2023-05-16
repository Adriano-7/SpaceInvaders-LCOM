#include <lcom/lcf.h>
#include "headers/game.h"
#include "headers/devices/graphics.h"


int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/g5/proj/trace.txt");
  
  lcf_log_output("/home/lcom/labs/g5/proj/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  return lcf_cleanup();
}

int proj_main_loop(int argc, char *argv[]) {
  if(map_phys_mem(G_Mode_1024x768)){
    printf("Error mapping phys memmory\n");
    return 1;
  }
  if(set_graphics_mode(G_Mode_1024x768)){
    printf("Error setting graphics mode\n");
    return 1;
  }

  if (game_loop()) {
    printf("Error entering game loop\n");
    return 1;
  }

  return 0;
}
