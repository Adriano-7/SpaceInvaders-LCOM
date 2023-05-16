#include <lcom/lcf.h>
#include "headers/controllers/keyboard_controller.h"
#include "headers/game.h"
#include "headers/devices/keyboard.h"
#include "headers/devices/timer.h"
#include "headers/devices/vbe.h"
#include "headers/devices/graphics.h"

#include "state.h"

extern uint8_t output;

int game_loop(){
	bool running = true;
	enum State state = MENU;

	int ipc_status, r;
	message msg;

	//Keyboard
	bool secondByte = false;
	uint8_t bytes[2];
	uint8_t keyboard_bit_no;

	//Timer
	uint8_t timer_bit_no;

	if(timer_subscribe_int(&timer_bit_no)){
	printf("Error while subscribing timer interrupt\n");
	return 1;
	}

	if(keyboard_subscribe_interrupts(&keyboard_bit_no)){
	printf("Error subscribing keyboard interrupts\n");
	return 1;
	}

	if(map_phys_mem(G_Mode_1024x768)){
	printf("Error mapping the physical to virtual memory"); 
	return 1;
	}

	if(set_graphics_mode(G_Mode_1024x768)){
	printf("Error setting graphics mode\n");
	return 1;
	}


	//2nd Initialize game
	while(running){
	if((r = driver_receive(ANY, &msg, &ipc_status))) {
		printf("driver_receive failed with: %d", r);
		continue;
	}

	if (is_ipc_notify(ipc_status)) {
		switch (_ENDPOINT_P(msg.m_source)) {
		case HARDWARE:
			if (msg.m_notify.interrupts & BIT(keyboard_bit_no)) {
			kbc_ih();
			if(secondByte){
				secondByte=false;
				bytes[1]=output;
				keyboard_controller(state,bytes);
			}
			else{
				bytes[0] = output;
				if(output==0xE0){
				secondByte = true;
				}
				else{
					keyboard_controller(state,bytes);
				}
			}


			}
			if (msg.m_notify.interrupts & BIT(timer_bit_no)){
			timer_int_handler();
			
			}
			break;
			}
		}
	} 


	//3rd Loop/Receive interrupts


	//4th Unsubscribe interrupts
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
