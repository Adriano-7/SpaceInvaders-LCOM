#include "game.h"

extern uint8_t output;

int game_loop(){
	//bool running = true;
	enum State st = GAME;
	enum State* state = &st;

	int ipc_status, r;
	message msg;

	bool secondByte = false;
	uint8_t bytes[2];
	uint8_t keyboard_bit_no;
	uint8_t timer_bit_no;

	loadXpms();
	Map_t* map =  loadGame();

	if(timer_subscribe_int(&timer_bit_no)){
	printf("Error while subscribing timer interrupt\n");
	return 1;
	}

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
			if(secondByte){
				secondByte=false;
				bytes[1]=output;
				handle_keyboard(state, bytes,map);
			}
			else{
				bytes[0] = output;
				if(output==0xE0){
				secondByte = true;
				}
				else{
				handle_keyboard(state, bytes,map);
				}
			}
			}
			if (msg.m_notify.interrupts & BIT(timer_bit_no)){
				printf("timer interrupt\n");
				timer_int_handler();
				handle_timer(state, map);
			}
			break;
			}
		}
	} 

	destroyMap(map);

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
