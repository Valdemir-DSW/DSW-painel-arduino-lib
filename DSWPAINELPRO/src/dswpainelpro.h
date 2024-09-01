#ifndef DSWEPAINELPRO_H
#define DSWEPAINELPRO_H

#include <Arduino.h>

class DSWPainelPro {
public:
    DSWPainelPro();
    void vai(long baudRate = 115200);
    void atualizar();  // Função para ser chamada a cada loop()
    void slynky(const String& pp);

    String puxa(int slot);

private:
    String values[20]; // Ajuste conforme necessário para a quantidade de slots
    unsigned long lastUpdateTime; // Tempo da última atualização
    const unsigned long updateInterval = 1000; // Intervalo de atualização em milissegundos
    int index = 0;
    int valor = 0;
    int contador = 0;
};

#endif // DSWEPAINELPRO_H
