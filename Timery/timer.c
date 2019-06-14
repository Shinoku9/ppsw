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
	
	while(T0TC < (uiTime*FREQ_PCLK)){} //zadziala, ale okres wykonywania petli while musialby byc mniejszy od zegara w mikrokontrolerze(czestotliwosc petli > czestotliwosc zegara) 
		//jesli czestotliwosc petli < czestotliwosc zegara, to moze przeskoczyc wartosc uiTime
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

//wpisanie 1 powoduje zmiane stanu rejestru na przeciwny (jak bylo 1, zmienia na 0; jak bylo 1 zmienia na 0), nie mozna sumy logicznej, bo wczesniej moga byc inne 1 i po sumie logicznej moga zmienic swoj stan
//co powoduje reset timera oraz ustawienie flagi przerwania
//co i kiedy resetuje i ustawia flage przerwania
//
//RESET - ustawienie bitu RESET_ON_MR0 w rejestrze MCR (liczenie impulsów od poczatku do momentu wyrownania z wartoscia wpisana w T0MR0 i po tym czasie sie resetuje)
//
//
//FLAGA - ustawienie bitu MR0_INTERRUPT w rejestrze MCR (po osiagnieciu wartosci wpisanej w T0MR0 spowoduje przerwanie)
