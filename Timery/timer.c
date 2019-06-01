#include <LPC21xx.H>
#include "timer.h"

#define FREQ_PCLK 15

#define mCOUNTER_ENABLE 0x00000001
#define mCOUNTER_RESET 0x00000002
#define mMR0_INTERRUPT    0x00000001
#define mRESET_ON_MR0     0x00000002
#define mINTERRUPT_ON_MR0 0x00000001


void InitTimer0(void){
	T0TCR = mCOUNTER_ENABLE;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR = T0TCR | mCOUNTER_RESET;
	T0TCR = T0TCR & mCOUNTER_ENABLE;	
	
	while(T0TC < (uiTime*FREQ_PCLK)){}
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0TCR = T0TCR | mCOUNTER_RESET;
	T0TCR = T0TCR & (~mCOUNTER_RESET);
	T0TCR = T0TCR | mCOUNTER_ENABLE;
	T0MCR = T0MCR | mMR0_INTERRUPT | mRESET_ON_MR0;
	T0MR0 = (iDelayTime*FREQ_PCLK);
}

void WaitOnTimer0Match0(){
	while(T0IR!=(T0IR | mMR0_INTERRUPT)){}
	T0IR |= mINTERRUPT_ON_MR0;
}
