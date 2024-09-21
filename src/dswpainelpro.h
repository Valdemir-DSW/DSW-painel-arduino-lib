#ifndef DSWEPAINELPRO_H
#define DSWEPAINELPRO_H

#include <Arduino.h>
typedef void (*CommandCallback)(String command, int value);

class DSWPainelPro {
public:
    DSWPainelPro();
    void vai(long baudRate = 115200);
    void atualizar();  // Função para ser chamada a cada loop()
    void slynky(const String& pp);
    void cmd_vai(String commands[], int size);   // Inicia com uma lista de comandos personalizada
    float  cmd_puxada(String commandName);        // Retorna o valor associado a um comando
    void cmd_chamarisco(CommandCallback callback);
    String puxa(int slot);

private:
    String values[20]; // Ajuste conforme necessário para a quantidade de slots
    unsigned long lastUpdateTime; // Tempo da última atualização
    const unsigned long updateInterval = 1000; // Intervalo de atualização em milissegundos
    int index = 0;
    int valor = 0;
    int contador = 0;
        String* _commands;                         // Lista de comandos personalizada
    float* _values;                              // Lista de valores para cada comando
    int _numCommands;                          // Número de comandos
    void displayHelp();                        // Exibe a lista de comandos disponíveis
    void processCommand(String input);         // Processa um comando recebido
     CommandCallback _callback;    // Ponteiro para função callback
};
class dsw_eeprom {
  private:
    void** vars;      // Array de ponteiros genéricos para as variáveis
    char* types;      // Array de tipos ('i' para int, 'f' para float)
    int varCount;     // Quantidade de variáveis

  public:
  
    dsw_eeprom(void* vars[], char types[], int varCount);  // Construtor com variáveis e tipos
    void eeprom_salvar();                                  // Função para salvar na EEPROM
    void eeprom_puxar();                                // Função para carregar da EEPROM
};
#endif // DSWEPAINELPRO_H
