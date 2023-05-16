#include <lcom/lcf.h>


int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/proj/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  return lcf_cleanup();
}

//Game Loop
//1st Subscribe interrupts
//2nd Initialize game
//3rd Loop/Receive interrupts
//4th Unsubscribe interrupts