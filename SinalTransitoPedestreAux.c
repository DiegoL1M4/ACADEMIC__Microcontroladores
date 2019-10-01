
#include "SanUSB1.h" // https://www.youtube.com/watch?v=klucfceoTtA

#pragma interrupt interrupcao //Tem que estar aqui ou dentro do firmware.c

int setseg[10]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10}; //Vetor com 10 //elementos que desenham de 0 a 9
int i, z, dezena, unidade;  //índice dezena,unidade (ponteiro)

void interrupcao() {
}

void tempo() {
    for (i=10;i>=0;i--) {
        for(z=0;z<15;z++){
            dezena=i/10;  //dezena recebe o número inteiro da divisão por 10
            unidade=i%10; //unidade recebe o resto  da divisão por 10 

            nivel_alto(pin_a4);  //pin_a0 aciona transistor do comum das dezenas
            nivel_baixo(pin_a5);    //pin_a3 aciona transistor do comum das unidades
            PORTB = setseg[dezena]; //A porta B recebe o desenho do número das dezenas apontado pela //variável dezena
            tempo_ms(10);             

            nivel_alto(pin_a5);  //selecionei a unidade
            nivel_baixo(pin_a4);   
            PORTB = setseg[unidade]; //A porta B recebe o desenho do número das unidades apontado //pela variável unidade
            tempo_ms(10);
        }
    }
    nivel_baixo(pin_a5);
}

void botao(int tempo) {
    int i;
    for(i = 0; i < tempo*10; i++) {
        if (!entrada_pin_e3) {
            return 0;
        }
        tempo_ms(100);
    }   
}

void main() {
     
    // Frequência
    clock_int_4MHz();
    
    PORTB= 0b00000000;
    TRISB=0x00;   // porta B como saída.

    while (1) {
        // Verde
        nivel_alto(pin_a3);
        
        // Vermelho (Pedestre)
        nivel_alto(pin_c1);
            
        botao(5); //////////////////////////////
        
        // Verde
        nivel_baixo(pin_a3);

        // Amarelo
        nivel_alto(pin_a2);
        tempo_ms(2000);
        nivel_baixo(pin_a2);

        // Vermelho
        nivel_alto(pin_a1);


        // Vermelho (Pedestre)
        nivel_baixo(pin_c1);
        // Verde (Pedestre)
        nivel_alto(pin_c2);

        tempo();

        // Verde (Pedestre)
        nivel_baixo(pin_c2);
        // Vermelho
        nivel_baixo(pin_a1);

        // Pressionar o botão para gravação
        if (!entrada_pin_e3) {
            Reset();
        }
        
    }
    
}
