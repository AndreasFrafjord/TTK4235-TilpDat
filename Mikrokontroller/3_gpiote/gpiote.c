#include "gpiote.h"
#include "gpio.h"


void gpiote_init() {
    // Konfigurer GPIOTE-kanal 0 for BUTTON 1 (P0.13)
    GPIOTE->CONFIG[0] =  1 |  // Mode: Event
                        (13 << 8) | // Pin: P0.13 (BUTTON 1)
                        (2 << 16);  // Polarity: HiToLo (høy til lav)

    // GPIOTE-> EVENTS_IN[0] = 0;
    // LED 1
    GPIOTE->CONFIG[1] =  3|  // Mode: Task
                        (17 << 8) | // Pin: P0.17
                        (3 << 16);  // Polarity: Toggle

    // Led 2
    GPIOTE->CONFIG[2] =  3 |  // Mode: Task
                        (18 << 8) | // Pin: P0.18
                        (3 << 16);  // Polarity: Toggle

    // Led 3
    GPIOTE->CONFIG[3] =  3 |  // Mode: Task
                        (19 << 8) | // Pin: P0.19
                        (3 << 16);  // Polarity: Toggle

    // Led 4
    GPIOTE->CONFIG[4] =  3 |  // Mode: Task
                        (20 << 8) | // Pin: P0.20
                        (3 << 16);  // Polarity: Toggle


}