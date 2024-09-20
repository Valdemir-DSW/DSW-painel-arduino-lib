#include "dswpainelpro.h"

// Variáveis globais para serem armazenadas na EEPROM ( as variáveis que vamos utilizar no nosso exemplo )
int contador = 1234;    // Exemplo de um inteiro
float temperatura = 23.5; // Exemplo de um float

void setup() {
    // Array de variáveis que serão salvas ( aqui vamos colocar o nome das variáveis que nós vamos querer trabalhar)
    void* variaveis[] = { &contador, &temperatura };
    // Array com os tipos dessas variáveis ('i' para int, 'f' para float) | ( faça com respectividade ou seja a definição deve estar na mesma ordem que você definiu o nome das variáveis)
    char tipos[] = { 'i', 'f' };
    // Instancia o objeto para manipular a EEPROM( agora basta chamar a biblioteca com os dados que nós temos definindo nessa ordem a lista de variáveis lista de tipos e também coloque o valor da quantidade de variáveis que você definiu como pode observar nós temos 2 um número 2 foi colocado)
    dsw_eeprom eepromManager(variaveis, tipos, 2);
//=========================================================================================================================================
    // Salva os valores na EEPROM
    eepromManager.eeprom_salvar();
    // toda vez que ela for chamada ela vai pegar o valor das variáveis e salvar na eeprom mesmo que o Arduino for desligado os valores não são perdidos
//=========================================================================================================================================
    // Puxa os valores da EEPROM para as variáveis
    eepromManager.eeprom_puxar();
    // toda vez que acionada ela vai pegar aqueles valores que estão salvo na eeprom e redefinir eles nas variáveis respectivas, aquelas que foram definidas no início do código obvio
//=========================================================================================================================================
                                                                                                                                        /*
sugestão de uso<
você pode usar em conjunto do CMD inclusive foi feito para isso no caso !
Ao receber um novo comando e processado utilize essa biblioteca para salvar
os comandos após processar os comandos chame a função
                        {.eeprom_salvar();}
que ela vai fazer o salvamento e  na função "setup" chame
                        {.eeprom_puxar();}
Que toda vez que o arduino religar ele vai puxar o valor das variáveis na última salvação!
                                                                                                                                        */
}

void loop() {
    // Não é necessário fazer nada no loop para este exemplo
}
