#include <LPC21xx.H>
#include "led.h"
#include "keyboard.h"

//zadanie 1
//enum LedState {LED_LEFT, LED_RIGHT};
//enum LedState eLedState = LED_LEFT;

//zadanie 2
//enum LedState {STATE0, STATE1, STATE2, STATE3, STATE4, STATE5};
//enum LedState eLedState = STATE0;

//zadanie 3
//enum LedState {DIRECTION_RIGHT, DIRECTION_LEFT};
//enum LedState eLedState = DIRECTION_RIGHT;

//zadanie 4 i 5
//enum LedState {DIRECTION_RIGHT, STOP};
//enum LedState eLedState = DIRECTION_RIGHT;

//zadanie 6
enum LedState {DIRECTION_RIGHT, DIRECTION_LEFT, STOP};
enum LedState eLedState = STOP;

unsigned char ucMoveCounter;

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
//		ZADANIE 1
//		
//		switch(eLedState){
//			case LED_LEFT:
//				eLedState=LED_RIGHT;
//				LedStepRight();
//				break;
//			case LED_RIGHT:
//				eLedState=LED_LEFT;
//				LedStepLeft();
//				break;
//		}
//		Delay(250);
	
		
//		ZADANIE 2
//		
//		switch(eLedState){
//			case STATE0:
//				eLedState = STATE1;
//				LedStepLeft();
//				break;
//			case STATE1:
//				eLedState = STATE2;
//				LedStepLeft();
//				break;
//			case STATE2:
//				eLedState = STATE3;
//				LedStepLeft();
//				break;
//			case STATE3:
//				eLedState = STATE4;
//				LedStepRight();
//				break;
//			case STATE4:
//				eLedState = STATE5;
//				LedStepRight();
//				break;
//			case STATE5:
//				eLedState = STATE0;
//				LedStepRight();
//				break;
//		}	
//		Delay(250);


//		ZADANIE 3
//		
//		switch(eLedState){
//			case DIRECTION_RIGHT:
//				if (ucMoveCounter == 3){
//					ucMoveCounter = 0;
//					eLedState = DIRECTION_LEFT;
//				}
//				else if (ucMoveCounter++ != 3){
//					LedStepRight();
//				}
//				break;
//			case DIRECTION_LEFT:
//				if (ucMoveCounter == 3){
//					ucMoveCounter = 0;
//					eLedState = DIRECTION_RIGHT;
//				}
//				else if (ucMoveCounter++ != 3){
//					LedStepLeft();
//				}
//				break;
//		}	
//		Delay(250);


//		ZADANIE 4
//		
//		switch(eLedState){
//			case DIRECTION_RIGHT:
//				if (ucMoveCounter == 3){
//					ucMoveCounter = 0;
//					eLedState = STOP;
//				}
//				else if (ucMoveCounter++ != 3){
//					LedStepRight();
//				}
//				break;
//			case STOP:
//				break;					
//		}
//		Delay(250);


//		MODYFIKACJA ZADANIA 4

//		switch(eLedState){
//			case DIRECTION_RIGHT:
//				if (ucMoveCounter == 3){
//					ucMoveCounter=0;
//					eLedState = STOP;
//				}
//				else if (ucMoveCounter++ != 3){
//					LedStepRight();
//					eLedState = DIRECTION_RIGHT;
//				}
//				break;
//			case STOP:
//				if (eKeyboardRead() == BUTTON_1){
//					eLedState = DIRECTION_RIGHT;
//				}
//				else{
//					eLedState = STOP;
//				}
//				break;
//		}
//		Delay(250);
//	}
		
		
//		ZADANIE 5
//
//	switch(eLedState){
//		case DIRECTION_RIGHT:
//			if (eKeyboardRead() == BUTTON_1){
//				eLedState = STOP;
//			}
//			else{
//				LedStepRight();
//				eLedState = DIRECTION_RIGHT;
//			}
//			break;
//		case STOP:
//			if (eKeyboardRead() == BUTTON_2){
//				eLedState = DIRECTION_RIGHT;
//			}
//			else{
//				eLedState = STOP;
//			}
//			break;
//		}
//		Delay(100);
		
		
//		ZADANIE 6
//
		switch(eLedState){
			case DIRECTION_LEFT:
				if(eKeyboardRead() == BUTTON_2){
					eLedState = STOP;
				}
				else{
					LedStepLeft();
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
					LedStepRight();
					eLedState = DIRECTION_RIGHT;
				}
				break;
			}
			Delay(100);		
	}
}
