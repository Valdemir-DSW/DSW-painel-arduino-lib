#include "dswpainelpro.h"
#include <Arduino.h>
DSWPainelPro::DSWPainelPro() : lastUpdateTime(0) {
    // Construtor
}

void DSWPainelPro::vai(long baudRate) {
    Serial.begin(115200);
    // Inicialize a estrutura de dados, se necessário
}

void DSWPainelPro::atualizar() {
    unsigned long currentTime = millis();
    if (Serial.available()) {
    String dados = Serial.readStringUntil('\n');
    int valor = 0;
    int contador = 0;

    // Analisa a string recebida e armazena os valores na lista
    for (int i = 0; i < dados.length(); i++) {
      char c = dados.charAt(i);
      if (c == ',') {
        values[contador++] = valor;
        valor = 0;
      } else {
        valor = valor * 10 + (c - '0');
      }
    }
    values[contador] = valor;  // Adiciona o último valor

    index = (index + 1) % 20;  // Atualiza o índice para a próxima posição

    // Aqui você pode adicionar código para processar os valores recebidos
    // Exemplo: Serial.print("Valor 0: "); Serial.println(valores[0]);
  }
}


String DSWPainelPro::puxa(int slot) {
    if (slot < 0 || slot >= 20) {
        return "0000";
    }
    return values[slot];
}

void DSWPainelPro::slynky(const String& pp) {
    Serial.println(pp);  // Imprime a String na serial
    // Não retorna nada, pois a função é void
}
