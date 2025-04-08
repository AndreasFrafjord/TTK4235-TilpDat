#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"


int main() {
    button_init();
    gpiote_init(); 
    ppi_init();
    while (1) {
        
    }
    return 0;
}