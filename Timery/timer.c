#include <LPC21xx.H>
#include "timer.h"

#define FREQ_PCLK 15

#define COUNTER_ENABLE_bm (1<<0)
#define COUNTER_RESET_bm (1<<1)
#define MR0_INTERRUPT_bm (1<<0)
#define RESET_ON_MR0_bm (1<<1)
#define INTERRUPT_ON_MR0_bm (1<<0)


void InitTimer0(void){
	T0TCR = T0TCR |	COUNTER_ENABLE_bm;
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR = T0TCR | COUNTER_RESET_bm;
	T0TCR = T0TCR & ~COUNTER_RESET_bm;	
	
	while(T0TC < (uiTime*FREQ_PCLK)){}
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MR0 = (iDelayTime*FREQ_PCLK);
	T0MCR = T0MCR | MR0_INTERRUPT_bm | RESET_ON_MR0_bm;
	InitTimer0();
}

void WaitOnTimer0Match0(){
	while(T0IR!=(T0IR | MR0_INTERRUPT_bm)){}
	T0IR |= INTERRUPT_ON_MR0_bm;
}
