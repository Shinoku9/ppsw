#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

void Delay(unsigned int uiWaitMs){
	unsigned int uiCounter;
	unsigned int uiCounter2;
	for (uiCounter=0; uiCounter<=uiWaitMs ; uiCounter++){
		for (uiCounter2=0; uiCounter2<7500; uiCounter2++){}
	}
}

int main(){
	LedInit();
	KeyboardInit();

	while(1){	
		switch(eKeyboardRead()){
			case BUTTON_1:
				LedStepRight();
				break;
			case BUTTON_2:
				LedStepLeft();
				break;
			case BUTTON_3:
				break;
			case BUTTON_4:
				break;	
			default:
				break;
		}
	}
}
