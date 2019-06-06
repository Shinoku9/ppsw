#include "led.h"
#include "keyboard.h"
#include "timer.h"

int main(){
	LedInit();
	KeyboardInit();
	InitTimer0Match0(1000000);
		
	while(1){
		LedStepLeft();
		WaitOnTimer0Match0();
	}
}	
