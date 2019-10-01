
#include "SanUSB1.h"

#pragma interrupt interrupcao

void interrupcao() {
}

void main() {
     
    // Frequ�ncia
    clock_int_4MHz();

    while (1) {
        // Pressionar o bot�o para grava��o
        if (!entrada_pin_e3) {
            Reset();
        }
        
        // Verde
        nivel_alto(pin_a3);
        tempo_ms(2000);
        nivel_baixo(pin_a3);
        
        // Amarelo
        nivel_alto(pin_a2);
        tempo_ms(1000);
        nivel_baixo(pin_a2);
        
        // Vermelho
        nivel_alto(pin_a1);
        tempo_ms(2000);
        nivel_baixo(pin_a1);
    }
    
}


