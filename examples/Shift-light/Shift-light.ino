#include <dswpainelpro.h>

DSWPainelPro dsw;

void setup() {

    dsw.vai();
    pinMode(13, OUTPUT); // Configura o pino como saída
}

void loop() {
    dsw.atualizar(); // Atualiza os valores Com o que tiver disponível 
    
    // Obtém o valor do slot 0 e imprime
    String value = dsw.puxa(0);
   int intensity = value.toInt();
   int libata = 0;
   if (intensity >= 1244){
         libata = 255;
   }else{
     libata = 0;
   }
    
    // Ajusta a intensidade do LED
    analogWrite(13, libata);

    delay(1); // Aguarde um tanto 
}
