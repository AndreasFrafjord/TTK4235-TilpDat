#include <stdint.h>
#include "uart.h"
#include "gpio.h"

#define UART ((NRF_UART_REGS*)0x40002000)


 typedef struct {
    volatile uint32_t TASKS_STARTRX;
    volatile uint32_t TASKS_STOPRX;
    volatile uint32_t TASKS_STARTTX; 
    volatile uint32_t TASKS_STOPTX; 
    volatile uint32_t RESERVED0[3];
    volatile uint32_t TASKS_SUSPEND; 
    volatile uint32_t RESERVED1[56];
    volatile uint32_t EVENTS_CTS; 
    volatile uint32_t EVENTS_NCTS;
    volatile uint32_t EVENTS_RXDRDY;
    volatile uint32_t RESERVED2[4];
    volatile uint32_t EVENTS_TXDRDY;
    volatile uint32_t RESERVED3[1];
    volatile uint32_t EVENTS_ERROR;
    volatile uint32_t RESERVED4[7];
    volatile uint32_t EVENTS_RXTO; 
    volatile uint32_t RESERVED5[44];
    volatile uint32_t SHORTS;
    volatile uint32_t RESERVED6[64];
    volatile uint32_t INTENSET;
    volatile uint32_t INTENCLR;
    volatile uint32_t RESERVED7[93];
    volatile uint32_t ERRORSRC;
    volatile uint32_t RESERVED8[31];
    volatile uint32_t ENABLE;
    volatile uint32_t RESERVED9[1];
    volatile uint32_t PSELERTS;
    volatile uint32_t PSELTXD;
    volatile uint32_t PSELCTS;
    volatile uint32_t PSELRXD;
    volatile uint32_t RXD;
    volatile uint32_t TXD; 
    volatile uint32_t RESERVED10[1];
    volatile uint32_t BAUDRATE;
    volatile uint32_t RESERVED11[17];
    volatile uint32_t CONFIG;
 }NRF_UART_REGS;

 void uart_init(){
    GPIO -> PIN_CNF[8] = (0 << 0) | (1 << 2); // RXD (recive data)
    GPIO -> PIN_CNF[6] = (1 << 0) | (1 << 2); // TXD (transmit data)

    UART -> PSELRXD = 8; // RXD pin
    UART -> PSELTXD = 6; // TXD pin

    UART -> BAUDRATE = 0x00275000; // From the datasheet, 9600 baud
    UART -> PSELERTS = 0xFFFFFFFF; // No flow control
    UART -> PSELCTS = 0xFFFFFFFF; // No flow control

    UART -> ENABLE = 4; // Enable the UART

    UART -> TASKS_STARTRX = 1; // Start receiving    
 }

 void uart_send(char letter){
    UART -> TASKS_STARTTX = 1; // Start receiving
    UART -> TXD = letter;

    while((UART -> EVENTS_TXDRDY) == 0); // Wait for the TXDRDY event
    UART -> EVENTS_TXDRDY = 0; // Clear the TXDRDY event

    //UART -> TASKS_STOPTX = 1; // stop transmitting
 }

 void uart_read(){
    UART -> TASKS_STARTRX = 1; // Start receiving
    while((UART -> EVENTS_RXDRDY) == 0); // Wait for the RXDRDY event
    char letter = UART -> RXD; // Read the received data
    UART -> EVENTS_RXDRDY = 0; // Clear the RXDRDY event

    uart_send(letter); // Echo the received data
 }