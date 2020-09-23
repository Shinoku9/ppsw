#include "led.h"
#include "keyboard.h"
#include "timer_interrupts.h"

enum LedState {DIRECTION_LEFT, STOP, DIRECTION_RIGHT};
enum LedState eLedState = STOP;

void Automat (void)
{
	if(eLedState == DIRECTION_RIGHT)
	{
		Led_StepRight();
	}
	else if (eLedState == DIRECTION_LEFT)
	{
		Led_StepLeft();
	}
	
	switch(eKeyboardRead())
	{
		case BUTTON_1:
			if (eLedState == STOP)
			{
				eLedState = DIRECTION_RIGHT;
			}
			break;
		case BUTTON_2:
			eLedState = STOP;
			break;
		case BUTTON_3:
			if (eLedState == STOP)
			{
				eLedState = DIRECTION_LEFT;
			}
			break;
		case BUTTON_4:
			break;
		case RELASED:
			break;
	}
}	


int main (){
	unsigned int iMainLoopCtr;
	LedInit();
	KeyboardInit();
	Timer0Interrupts_Init(20000, &Automat); //250000

	while(1){
	 	iMainLoopCtr++;
	}
}
