// site oficial > https://dsw-wheel.rf.gd/ ////
//Indicando que queremos utilizar a biblioteca/ 
#include <dswpainelpro.h>
DSWPainelPro dsw;
///////////////////////////////////////////////
//Aqui apenas um teste/exemplo de como puxar um valor de um slote simplesmente ele sempre é um valor string !
void setup() {
   
    dsw.vai();// Inicializa ou começa a operação do painel DSW
}

void loop() {
    dsw.atualizar(); // Atualiza os valores Com o que tiver disponível 
    
    // Obtém o valor do slot 1 
    String value = dsw.puxa(0);
   

    delay(1); // Aguarde um tanto 
}
