// site oficial > https://dsw-wheel.rf.gd/ //

// Incluindo as bibliotecas necessárias
#include <dswpainelpro.h> // Biblioteca para interface com o painel DSW Painel Pro
#include <Servo.h>        // Biblioteca para controlar servos
// para funcionar no programa defina o slot 1 como rpm !
// Variável para definir o limite máximo de rotação (em RPM) que o motor ou painel pode suportar
int maxima = 5000; // O servo não irá atuar se o valor exceder 5000 RPM
// não que irá estragar ou qualquer coisa assim mas ele vai chegar no limite vai parar simplesmente quando chegar em 5000

// Criando um objeto 'dsw' para controlar o painel DSW Painel Pro
DSWPainelPro dsw;

// Criando um objeto 'teu_servo' para controlar o servo motor
Servo teu_servo;

///////////////////////////////////////////////
void setup() {
    // Anexando o pino 9 para controlar o servo motor
    teu_servo.attach(9); 
    
    // Inicializando o painel DSW Painel Pro para começar a operação
    dsw.vai(); 
}

void loop() {
    // Atualiza os dados mais recentes do painel (slot 0) para o código
    dsw.atualizar(); 
    
    // Obtém o valor armazenado no slot 0 do painel DSW e converte para uma string
    String value = dsw.puxa(0);
    
    // Converte o valor da string para um inteiro
    int var1 = value.toInt();

    // Verifica se o valor de var1 é maior ou igual à rotação máxima permitida
    // Se for, ajusta para o valor máximo definido (5000 RPM)
    if (var1 >= maxima) {
        var1 = maxima;
    } 
    // Caso contrário, se o valor for menor ou igual a 0, ajusta para 0 (rotação mínima)
    else if (var1 <= 0) {
        var1 = 0;
    }

    // Mapeia o valor de 'var1' de 0 a 5000 para 0 a 180 (ângulo de movimento do servo motor)
    int intensity = map(value.toInt(), 0, maxima, 0, 180);
    
    // Envia o valor mapeado para o servo, ajustando seu ângulo de acordo com a rotação
    teu_servo.write(intensity); 

    // Aguarda 1 milissegundo antes de continuar o loop (para não sobrecarregar o processamento)
    delay(1); 
}
