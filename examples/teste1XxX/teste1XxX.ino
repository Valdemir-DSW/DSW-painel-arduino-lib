#include <dswpainelpro.h>

DSWPainelPro dsw;

void setup() {
   
    dsw.vai();
}

void loop() {
    dsw.atualizar(); // Atualiza os valores Com o que tiver disponível 
    
    // Obtém o valor do slot 0 
    String value = dsw.puxa(0);
   

    delay(1); // Aguarde um tanto 
}
