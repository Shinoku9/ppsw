#include <LPC21xx.H>
#include "timer.h"

#define FREQ_PCLK 15

#define COUNTER_ENABLE_bm (1<<0)
#define COUNTER_RESET_bm (1<<1)
#define MR0_INTERRUPT_bm (1<<0)
#define RESET_ON_MR0_bm (1<<1)
#define INTERRUPT_ON_MR0_bm (1<<0)


void InitTimer0(void){
	T0TCR = T0TCR |	COUNTER_ENABLE_bm; //wlaczenie timera
}

void WaitOnTimer0(unsigned int uiTime){
	T0TCR = T0TCR | COUNTER_RESET_bm; //zerowanie timera
	T0TCR = T0TCR & ~COUNTER_RESET_bm;	//zakonczenie resetowania timera
	
	while(T0TC < (uiTime*FREQ_PCLK)){} //petla opozniajaca o wartosc podana w argumencie
}

void InitTimer0Match0(unsigned int iDelayTime){
	T0MR0 = (iDelayTime*FREQ_PCLK); //obliczenie ilosci cykli i wpisanie wartosci do rejestru porownujacego
	T0MCR = T0MCR | (MR0_INTERRUPT_bm | RESET_ON_MR0_bm); //ustawienie bitow odpowiadajacych za resetowanie timera po osiagnieciu wartosci i ustawienie flagi przerwania
	InitTimer0(); //wlaczenie timera
}

void WaitOnTimer0Match0(){
	while((T0IR & MR0_INTERRUPT_bm)==0){} //petla opozniajaca do momentu zapalenia flagi przerwania
	T0IR = INTERRUPT_ON_MR0_bm; //resetowanie przerwania
}



//co powoduje reset timera oraz ustawienie flagi przerwania


//RESET - ustawienie bitu RESET_ON_MR0 w rejestrze MCR (liczenie impulsów od ppczatku do momentu wyrownania z wartoscia wpisana w T0MR0)


//FLAGA - ustawienie bitu MR0_INTERRUPT w rejestrze MCR
