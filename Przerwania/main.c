#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

void Automat (void){
	
	enum LedState {DIRECTION_LEFT, STOP, DIRECTION_RIGHT};
	enum LedState eLedState = STOP;
	
	switch(eLedState){
		case DIRECTION_LEFT:
			if(eKeyboardRead() == BUTTON_2){
				eLedState = STOP;
			}
			else{
				Led_StepLeft();
				eLedState = DIRECTION_LEFT;
			}
			break;
		case STOP:
			if(eKeyboardRead() == BUTTON_1){
				eLedState = DIRECTION_RIGHT;
			}
			else if(eKeyboardRead() == BUTTON_3){
				eLedState = DIRECTION_LEFT;
			}
			else{
				eLedState = STOP;
			}
			break;
		case DIRECTION_RIGHT:
			if(eKeyboardRead() == BUTTON_2){
				eLedState = STOP;
			}
			else{
				Led_StepRight();
				eLedState = DIRECTION_RIGHT;
			}
			break;
	}
}

int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	Timer1Interrupts_Init(2000, &Automat);

	while(1){
	 	iMainLoopCtr++;
	}
}
