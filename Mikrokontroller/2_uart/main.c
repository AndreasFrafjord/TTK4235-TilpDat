#include "uart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>

int main() {
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i); 
        GPIO->OUTCLR = (1 << i); // skrur dette leddmatrisen av eller på???
    }


    GPIO->PIN_CNF[13] = (0 << 0) | (3 << 2); // Button 1
    GPIO->PIN_CNF[14] = (0 << 0) | (3 << 2); // Button 2

    uart_init();

    int led_on = 0; 
    int sleep = 0;

    while (1) {
        if ((GPIO->IN & (1 << 13)) == 0) {  //sjekker om button 1 er trykket
            uart_send('A'); 
        } 
        else if ((GPIO->IN & (1 << 14)) == 0) { //sjekker om button 2 er trykket
            uart_send('B'); 
        }

        if (UART->EVENTS_RXDRDY) {  // Sjekk om noe data er mottatt
            UART->EVENTS_RXDRDY = 0; // Nullstill reciving data

            if (led_on) {
                for (int i = 17; i <= 20; i++) { // Slå av alle LED-ene
                    GPIO->OUTSET = (1 << i);
                }
                led_on = 0;
            } else {
                for (int i = 17; i <= 20; i++) { // Slå på alle LED-ene
                    GPIO->OUTCLR = (1 << i);
                }
                led_on = 1;
            }
        }

        sleep = 10000;
        while (--sleep);
    }

    return 0; 
}

// oppgave 2.2: Pinne nummer P0.08 er merket UART_INT_RX, og pinne nummer P0. 06 
// er merket UART_INT_TX.
