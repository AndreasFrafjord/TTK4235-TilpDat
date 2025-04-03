#include "uart.h"
#include "gpio.h"
#include <stdint.h>
#include <stdio.h>

int main() {
    // Konfigurer LED-matrisen som utganger og slå den av
    for (int i = 17; i <= 20; i++) {
        GPIO->DIRSET = (1 << i);  // Sett som utgang
        GPIO->OUTCLR = (1 << i); // Start med LED-matrisen av
    }

    // Konfigurer knappene som innganger med pull-up
    GPIO->PIN_CNF[13] = (0 << 0) | (3 << 2); // SW1
    GPIO->PIN_CNF[14] = (0 << 0) | (3 << 2); // SW2

    // Initialiser UART
    uart_init();

    int led_on = 0;  // Variabel for å holde styr på LED-status
    int sleep = 0;

    while (1) {
        // Sjekk om SW1 (P0.13) er trykket
        if ((GPIO->IN & (1 << 13)) == 0) { 
            uart_send('A'); // Send bokstaven 'A' via UART
        } 
        // Sjekk om SW2 (P0.14) er trykket
        else if ((GPIO->IN & (1 << 14)) == 0) {
            uart_send('B'); // Send bokstaven 'B' via UART
        }

        // Sjekk om data er mottatt via UART
        if (UART->EVENTS_RXDRDY) {  // Sjekk om data er mottatt
            UART->EVENTS_RXDRDY = 0; // Nullstill RXDRDY

            // Skru på eller av LED-matrisen basert på nåværende status
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

        // Forsinkelse for å unngå rask toggling
        sleep = 10000;
        while (--sleep);
    }

    return 0; // Dette nås aldri, men kan stå som formalitet
}

// oppgave 2.2: Pinne nummer P0.08 er merket UART_INT_RX, og pinne nummer P0. 06 
// er merket UART_INT_TX.
