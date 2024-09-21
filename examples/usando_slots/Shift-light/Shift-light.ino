// site oficial > https://dsw-wheel.rf.gd/ ////
//Indicando que queremos utilizar a biblioteca/ 
#include <dswpainelpro.h>
DSWPainelPro dsw;
///////////////////////////////////////////////
void setup() {

    dsw.vai(); // Inicializa ou começa a operação do painel DSW
    pinMode(13, OUTPUT); // Configura o pino 13 como saída (Esse pino Além de ser o pino digital 13 também é conectado a um LED que tem a letra "l" na placa )
}

void loop() {
    dsw.atualizar(); // Atualiza os valores com os dados mais recentes disponíveis no painel 
    
    // Obtém o valor do slot 1 e converte para inteiro (Importante no software configurar algum valor do seu interesse no slot marcado Essa programação no caso foi feita para um shift light então coloque um valor de rotação para esse teste ) )
    String value = dsw.puxa(0);
    
    int intensity = value.toInt();//Converte o valor de string para inteiro 
    
    // Define a variável 'libata' para controlar o LED
    int libata = 0;
    if (intensity >= 1244) {
        libata = 255; // Se a intensidade for maior ou igual a 1244, define brilho máximo
    } else {
        libata = 0; // Caso contrário, desliga o LED
    }
    
    // Ajusta a intensidade do LED no pino 13 usando PWM
    analogWrite(13, libata);

    delay(1); // Pequeno atraso de 1 ms
}
