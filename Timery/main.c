#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"
#include "timer.h"

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
	InitTimer0Match0(1000000);
		
	while(1){
		LedStepLeft();
		WaitOnTimer0Match0();
	}
}	
