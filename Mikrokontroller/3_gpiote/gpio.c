#include "gpio.h"

void button_init(){ 
	GPIO->PIN_CNF[13] = (0 << 0) | (3 << 2);

    GPIO->PIN_CNF[17] = 1; 
    GPIO->PIN_CNF[18] = 1; 
    GPIO->PIN_CNF[19] = 1; 
    GPIO->PIN_CNF[20] = 1; 

    GPIO->OUTCLR = (1 << 17); // Sett P0.17 lav (LED av)
    GPIO->OUTCLR = (1 << 18); // Sett P0.18 lav (LED av)
    GPIO->OUTCLR = (1 << 19); // Sett P0.19 lav (LED av)
    GPIO->OUTCLR = (1 << 20); // Sett P0.20 lav (LED av)

    GPIO -> OUTSET = (1 << 17); // Sett P0.17 høy (LED på)
}