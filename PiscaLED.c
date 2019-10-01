#include "SanUSB1.h" 

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c

void interrupcao() {
}

void main() {
    
    // Frequência
    clock_int_4MHz();

    while (1) {
        // Pressionar o botão para gravação
        if (!entrada_pin_e3) {
            Reset();
        }
        
        // Pisca o LED
        inverte_saida(pin_b7);
        tempo_ms(100);
    }
    
}


