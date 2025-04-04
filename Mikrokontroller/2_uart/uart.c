#include <stdint.h>
#include "uart.h"
#include "gpio.h"







 void uart_init(){
    GPIO -> PIN_CNF[8] = 0 | (1 << 2); // RXD (recive data)
    GPIO -> PIN_CNF[6] = 1 | (1 << 2); // TXD (transmit data)

    UART -> PSELRXD = 8; // RXD pin
    UART -> PSELTXD = 6; // TXD pin

    UART -> BAUDRATE = 0x00275000; // From the datasheet, 9600 baud
    UART -> PSELRTS = 0xFFFFFFFF; // No flow control
    UART -> PSELCTS = 0xFFFFFFFF; // No flow control

    UART -> ENABLE = 4; // Enable the UART

    UART -> TASKS_STARTRX = 1; // Start receiving    
 }

 void uart_send(char letter){
    UART -> TASKS_STARTTX = 1; // Start transmitting
    UART -> TXD = letter;

    while((UART -> EVENTS_TXDRDY) == 0); // Wait for the TXDRDY event
    UART -> EVENTS_TXDRDY = 0; // Clear the TXDRDY event

    //UART -> TASKS_STOPTX = 1; // stop transmitting
 }

 char uart_read() {
    if (UART->EVENTS_RXDRDY == 0) {
        return '\0'; // Ingen data tilgjengelig
    }
    UART->EVENTS_RXDRDY = 0; // Nullstill RXDRDY-hendelsen
    char data = UART->RXD;
    return data; // Returner mottatt data
}