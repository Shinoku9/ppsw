#include <LPC21xx.H>
#include "servo.h"
#include "led.h"
#include "timer_interrupts.h"

#define CALIB_BUTTON (1<<4)
#define DETECTOR_bm (1<<10)
#define OFFSET_POS 12

enum DetectorState {ACTIVE, INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS, OFFSET};

struct Servo
{
	enum ServoState eState;
	unsigned int uiCurrentPosition;
	unsigned int uiDesiredPosition;
};
struct Servo sServo;

void DetectorInit(void){
	IO0DIR = (IO0DIR & ~(DETECTOR_bm));
}

enum DetectorState eReadDetector(void){
	if ((IO0PIN & CALIB_BUTTON)==0){
		return ACTIVE;
	}
	else{
		return INACTIVE;
	}
}

void Automat (void){
	switch(sServo.eState){
		case CALLIB:
			if(eReadDetector()==INACTIVE){
				Led_StepLeft();
				sServo.eState = CALLIB;
			}
			else{
				sServo.uiCurrentPosition=0;
				sServo.eState = OFFSET;
			}
			break;
		case OFFSET:
			if(sServo.uiCurrentPosition == OFFSET_POS){
				sServo.uiCurrentPosition=0;
				sServo.uiDesiredPosition=0;
				sServo.eState = IDLE;
			}
			else {
				Led_StepRight();
				sServo.uiCurrentPosition++;
				sServo.eState = OFFSET;
			}
			break;
		case IDLE:
			if(sServo.uiCurrentPosition == sServo.uiDesiredPosition){
				sServo.eState = IDLE;
			}
			else{
				sServo.eState = IN_PROGRESS;
			}
			break;
		case IN_PROGRESS:
			if(sServo.uiCurrentPosition != sServo.uiDesiredPosition){
				if(sServo.uiCurrentPosition < sServo.uiDesiredPosition){
					Led_StepRight();
					sServo.uiCurrentPosition++;
				}
				else if (sServo.uiCurrentPosition > sServo.uiDesiredPosition){
					Led_StepLeft();
					sServo.uiCurrentPosition--;
				}
				sServo.eState = IN_PROGRESS;
			}
			else{
				sServo.eState = IDLE;
			}
			break;
	}
}

void ServoCallib(void){
	sServo.eState = CALLIB;
}

void ServoInit(unsigned int uiServoFrequency){
	LedInit();
	DetectorInit();
	ServoCallib();
	Timer0Interrupts_Init(1000000/uiServoFrequency, &Automat);
}

void ServoGoTo(unsigned int uiPosition){
	sServo.uiDesiredPosition = uiPosition;
}
