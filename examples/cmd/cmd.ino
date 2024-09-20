#include "dswpainelpro.h"

DSWPainelPro dsw;

// Função de callback que será chamada quando um comando for recebido
void meuCallback(String command, int valuer) {
  /*
  essa disponibiliza de 2 variáveis uma do comando que foi validado e um valor inteiro do valor
  pode ver que logo abaixo a gente verificou se o comando é "/led" e depois foi dado outro exemplo de como usar o comando
  ""cmd_puxada""  que retorna um valor float do comando selecionado dentro dele por uma string 
  Apenas para exemplificar mas como a gente já precisa do valor como inteiro a gente podia apenas usar
  ""valuer"" aqui no caso que foi definido com a variável de retorno de valor do callback
  >PLUS esse CMD nao necessita realmente do proprietário dentro do aplicativo o do próprio Arduino IDE ele já funcionará
  */

   if (command == "/led"){
      analogWrite(13, (int)dsw.cmd_puxada("/led"));
      eepromManager.eeprom_salvar();
      /*
aproveitando o embalo vamos apresentar a função ""slynky"" que serve para você fazer um retorno personalizado para o prompt de comando
você pode enviar qualquer string de apenas  strings
      */
   dsw.slynky(" o valor do LED foi atualizado com sucesso!! > exemplo de uso da função slynky !!<");
   
   }
}

void setup() {
   
    pinMode(13, OUTPUT); // Configura o pino 13 como saída (Esse pino Além de ser o pino digital 13 também é conectado a um LED que tem a letra "L" na placa )
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    String comandos[] = {"/start", "/stop", "/reset","/led"};
    int numComandos = 4;
    // inicia a funcionalidade do prompt de comando !
    // definindo os comandos numa lista e o número de comandos
    dsw.cmd_vai(comandos, numComandos);
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Registra a função de callback
    // esse "callback" é uma função que você pode declarar que quando um comando for validado ou seja o software
    // enviou um comando que existe ele irá chamar uma função se você quiser claro você pode ver abaixo que foi definido uma função
    //""meuCallback"" que nesse código foi criado no início
    dsw.cmd_chamarisco(meuCallback);
}

void loop() {
  // atualiza os valores mais recentes enviados do Software
    dsw.atualizar();
}
