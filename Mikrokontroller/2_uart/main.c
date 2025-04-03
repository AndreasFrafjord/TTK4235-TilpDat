#include "uart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h> // For ssize_t


int main(){
    // Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (0 << i);  //dette kan hende ikke fungerer
	}

	GPIO->PIN_CNF[13] = (0 << 0) | (3 << 2);
	GPIO->PIN_CNF[14] = (0 << 0) | (3 << 2);
	// Fill inn the configuration for the remaining buttons 



    uart_init();
    char letter = 0;
    int led_on = 0;

    while (1) {
        if ((GPIO->IN & (1 << 13)) == 0) { 
            uart_send("A");
        } 
        else if ((GPIO->IN & (1 << 14)) == 0) {
            uart_send("B");
        }


		sleep = 10000;
		while(--sleep); // Delay
    }

    if (UART->EVENTS_RXDRDY) { 
        letter = uart_read(); 
        UART->EVENTS_RXDRDY = 0; 

        
        if (led_on) {
            for (int i = 17; i <= 20; i++) {
                GPIO->OUTSET = (1 << i);
            }
            led_on = 0;
        } else {
            for (int i = 17; i <= 20; i++) {
                GPIO->OUTCLR = (1 << i);
            }
            led_on = 1;
        }
    }
    
    return 0;
}




// oppgave 2.2: Pinne nummer P0.08 er merket UART_INT_RX, og pinne nummer P0. 06 
// er merket UART_INT_TX.
