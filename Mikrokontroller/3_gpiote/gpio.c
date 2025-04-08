#include "gpio.h"

void button_init(){ 
	
    for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
        if (i == 17 || i == 19){
            GPIO -> OUTCLR = (1 << i); // Sett P0.17 og P0.18 lav (LED på)
        }else {
            GPIO->OUTSET = (1 << i); // Sett P0.18 og P0.20 høy (LED av)
        }
		
	}
    GPIO->PIN_CNF[13] = (0 << 0) | (3 << 2);
}