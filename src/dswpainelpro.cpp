#include "dswpainelpro.h"
#include <Arduino.h>
#include <EEPROM.h>

DSWPainelPro::DSWPainelPro() : lastUpdateTime(0) {
    // Construtor
}

void DSWPainelPro::vai(long baudRate) {
    Serial.begin(115200);
    // Inicialize a estrutura de dados, se necessário
}
void DSWPainelPro::cmd_vai(String commands[], int size) {
    // Verifica se a lista de comandos é válida e se o tamanho é positivo
    if (commands == nullptr || size <= 0) {
        Serial.println("Erro: Lista de comandos inválida ou tamanho incorreto.");
        return;
    }

    // Libera a memória antiga, se já estiver alocada
    if (_commands != nullptr) {
        delete[] _commands;
        _commands = nullptr;
    }

    // Aloca um novo array para armazenar os comandos
    _commands = new String[size];
    _numCommands = size; // Define o número de comandos

    // Copia os comandos para o array local e inicializa os valores
    for (int i = 0; i < size; i++) {
        _commands[i] = commands[i]; // Copia o comando para o array local
        Serial.print("Comando ");
        Serial.print(i);
        Serial.print(": ");
        Serial.println(_commands[i]);  // Exibe cada comando recebido
        
        delay(500);  // Adiciona um delay de 500 milissegundos (ajuste conforme necessário)
    }

    // Inicializa os valores associados
    _values = new float[size];
    for (int i = 0; i < size; i++) {
        _values[i] = 0.0;
    }

    Serial.println("Comandos configurados com sucesso.");
}



void DSWPainelPro::atualizar() {
    unsigned long currentTime = millis();
    if (Serial.available()) {
    String dados = Serial.readStringUntil('\n');
    if (dados.startsWith("/")) {
        dados.trim();  // Remove espaços em branco extras

      // Verifica se o comando é /help
      if (dados.equals("/help")) {
        displayHelp();
      } else if (dados.startsWith("/")) {
        processCommand(dados);
      } else {
        Serial.println("Comando inválido. Digite /help para obter ajuda.");
      }

     
    }
    else
    {
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

    }
   
  }
}
dsw_eeprom::dsw_eeprom(void* variables[], char typeArray[], int count) {
  varCount = count;
  vars = variables;    // Armazena o array de ponteiros para variáveis
  types = typeArray;   // Armazena os tipos das variáveis (int ou float)
}
void dsw_eeprom::eeprom_salvar() {
 int address = 0;

  for (int i = 0; i < varCount; i++) {
    if (types[i] == 'i') {  // Se for um inteiro
      int* intVar = (int*)vars[i];  // Faz o casting para (int*)
      EEPROM.put(address, *intVar);
      address += sizeof(int);
    } else if (types[i] == 'f') {  // Se for um float
      float* floatVar = (float*)vars[i];  // Faz o casting para (float*)
      EEPROM.put(address, *floatVar);
      address += sizeof(float);
    }
  }
}

void dsw_eeprom::eeprom_puxar() {
  
  int address = 0;

  for (int i = 0; i < varCount; i++) {
    if (types[i] == 'i') {  // Se for um inteiro
      int* intVar = (int*)vars[i];  // Faz o casting para (int*)
      EEPROM.get(address, *intVar);
      address += sizeof(int);
    } else if (types[i] == 'f') {  // Se for um float
      float* floatVar = (float*)vars[i];  // Faz o casting para (float*)
      EEPROM.get(address, *floatVar);
      address += sizeof(float);
    }
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
void DSWPainelPro::displayHelp() {
    Serial.println("------------------------");
    Serial.println("Comandos disponíveis:");

    // Verifica se o array de comandos foi corretamente configurado
    if (_commands == nullptr || _numCommands <= 0) {
        Serial.println("Nenhum comando disponível.");
    } else {
        // Lista os comandos disponíveis
        for (int i = 0; i < _numCommands; i++) {
            Serial.print("Comando ");
            Serial.print(i);
            Serial.print(": ");
            
            // Certifica-se de que o comando não seja uma string vazia
            if (_commands[i].length() > 0) {
                Serial.println(_commands[i]);
            } else {
                Serial.println("[Comando inválido]");
            }
        }
    }

    Serial.println("Disponha de um valor inteiro! Digitando o comando espaço o valor desejado");
    Serial.println("-------------------------");
}

void DSWPainelPro::processCommand(String input) {
  int spaceIndex = input.indexOf(' ');

  if (spaceIndex != -1) {
    // Extrai o comando e o valor  
    String command = input.substring(0, spaceIndex);
    float value = input.substring(spaceIndex + 1).toFloat();

    // Procura o comando na lista de comandos
    for (int i = 0; i < _numCommands; i++) {
      if (command.equals(_commands[i])) {
        _values[i] = value;  // Salva o valor na posição correspondente
        Serial.println(command + " atualizado para " + value);
         if (_callback) {
                    _callback(command, value);
                }
        return;
      }
    }

    Serial.println("Comando não encontrado. Digite /help para ver os comandos disponíveis.");
  } else {
    Serial.println("Formato inválido. Use: /comando valor.");
  }
}
void DSWPainelPro::cmd_chamarisco(CommandCallback callback) {
    _callback = callback;  // Define o callback
}
// Função que retorna o valor associado a um comando
float DSWPainelPro::cmd_puxada(String commandName) {
  for (int i = 0; i < _numCommands; i++) {
    if (commandName.equals(_commands[i])) {
      return _values[i];
    }
  }
  // Se o comando não for encontrado, retorna -1 como valor padrão de erro
  return -1;
}