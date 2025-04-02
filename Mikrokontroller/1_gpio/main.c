#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t LATCH;
	volatile uint32_t DETECTMODE;
	volatile uint32_t RESERVED1[0x76];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;

void button_init(){ 
	GPIO->PIN_CNF[13] = (0 << 0) | (3 << 2);
	GPIO->PIN_CNF[14] = (0 << 0) | (3 << 2);
	// Fill inn the configuration for the remaining buttons 
}

int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons -> see button_init()


	button_init();


	int sleep = 0;
    while (1) {
        if ((GPIO->IN & (1 << 13)) == 0) { 
            for (int i = 17; i <= 20; i++) {
                GPIO->OUTSET = (0 << i);
            }
        } 
        else if ((GPIO->IN & (1 << 14)) == 0) { 
            for (int i = 17; i <= 20; i++) {
                GPIO->OUTCLR = (1 << i);
            }
        }

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}


//oppgave 1.2: pinnene SW1 (button 1) og SW2 (button 2) er henholdsvis tilkoblet pin Po.13 og Po.14. 
//fra kretsskjemaet ser vi at disse pinnene er logisk høye så lenge de ikke er trykket ned.
//Når de trykkes ned, blir de koblet til jord og dermed logisk lave. 

//oppgave 1.3: Baseadressen til GPIO-modulen er 0x50000000.