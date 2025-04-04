#include "uart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>
#include <sys/types.h> 



ssize_t _write(int fd, const void *buf, size_t count){
    char * letter = (char *)(buf);
    for(int i = 0; i < count; i++){
    uart_send(*letter);
    letter++;
    }

    return count;
}

void button_init(){ 
	GPIO->PIN_CNF[13] = 0 | (3 << 2); // button 1
	GPIO->PIN_CNF[14] = 0 | (3 << 2); // button 2
    GPIO->PIN_CNF[15] = 0 | (3 << 2); // button 3
}


int main() {
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i); 
        GPIO->OUTCLR = (1 << i); // skrur dette leddmatrisen av eller på???
    }

    uart_init();
    button_init(); 

    //int led_on = 1; 
    int sleep = 0;
    char A = 'A';
    char B = 'B';

    while (1) {
        if ((GPIO->IN & (1 << 13)) == 0) {  //sjekker om button 1 er trykket
            iprintf("Button 1 pressed: Sending 'A'\n");
            uart_send(A); 
        } 
        else if ((GPIO->IN & (1 << 14)) == 0) { //sjekker om button 2 er trykket
            iprintf("Button 2 pressed: Sending 'B'\n");
            uart_send(B); 
        }
        else if ((GPIO->IN & (1 << 14)) == 0) {
            iprintf("The average grade in TTK%d was in %d was: %c\n\r",4235,2022,B);
        }
        
        char received = uart_read();
        if (received != '\0') {  // Sjekk om noe data er mottatt
            if (GPIO-> OUT & (1 << 17)) {
                for (int i = 17; i <= 20; i++) { // Slå av alle LED-ene
                    GPIO->OUTSET = (1 << i);
                }
                //led_on = 0;
            } else {
                for (int i = 17; i <= 20; i++) { // Slå på alle LED-ene
                    GPIO->OUTCLR = (1 << i);
                }
                //led_on = 1;
            }
        }

        sleep = 10000;
        while (--sleep);
    }

    return 0; 
}

// oppgave 2.2: Pinne nummer P0.08 er merket UART_INT_RX, og pinne nummer P0. 06 
// er merket UART_INT_TX.
