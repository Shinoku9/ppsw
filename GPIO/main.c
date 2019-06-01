#include <LPC21xx.H>

#define LED0_bm 0x00010000
#define LED1_bm 0x00020000
#define LED2_bm 0x00040000
#define LED3_bm 0x00080000

#define BUTTON1_bm 0x0000010
#define BUTTON2_bm 0x0000020
#define BUTTON3_bm 0x0000040
#define BUTTON4_bm 0x0000080

enum ButtonState {RELEASED, PRESSED};
enum KeyboardState {RELASED, BUTTON_1, BUTTON_2, BUTTON_3, BUTTON_4};
enum Step {LEFT, RIGHT};

void Delay(unsigned int uiWaitMs){
	unsigned int uiCounter;
	unsigned int uiCounter2;
	for (uiCounter=0; uiCounter<=uiWaitMs ; uiCounter++){
		for (uiCounter2=0; uiCounter2<7500; uiCounter2++){}
	}
}
//git test
void LedInit(void){
	IO1DIR=IO1DIR|(LED0_bm|LED1_bm|LED2_bm|LED3_bm);
	IO1CLR=LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	IO1SET=LED0_bm;
}

void LedOn(unsigned char ucLedIndeks){
	IO1CLR=LED0_bm|LED1_bm|LED2_bm|LED3_bm;
	switch(ucLedIndeks){
		case 0:
			IO1SET=LED0_bm;
			break;
		case 1:
			IO1SET=LED1_bm;
			break;
		case 2:
			IO1SET=LED2_bm;
			break;
		case 3:
			IO1SET=LED3_bm;
			break;
		default:
			break;
	}
}

void KeyboardInit(void){
	IO0DIR=IO0DIR&(~(BUTTON1_bm|BUTTON2_bm|BUTTON3_bm|BUTTON4_bm));
}	

enum KeyboardState eKeyboardRead(void){
	if ((IO0PIN&BUTTON1_bm)==0){
		return (BUTTON_1);
	}
	else if ((IO0PIN&BUTTON2_bm)==0){
		return (BUTTON_2);
	}
	else if ((IO0PIN&BUTTON3_bm)==0){
		return (BUTTON_3);
	}
	else if ((IO0PIN&BUTTON4_bm)==0){
		return (BUTTON_4);
	}
	return (RELASED);
	
}

void LedStep (enum Step Direction){
	static unsigned int uiDioda;
	
	if (Direction == RIGHT){
		uiDioda++;
	}
	else{
		uiDioda--;
	}
	LedOn(uiDioda%4);
}	

void LedStepLeft(void){
	LedStep(LEFT);
}	

void LedStepRight(void){
	LedStep(RIGHT);
}

int main(){
	LedInit();
	KeyboardInit();
	LedOn(4);
	
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
		Delay(250);
	}
}
