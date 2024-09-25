#include "dswpainelpro.h"
//Para usar no software deve estar configurado o slot 1 comoRPM
 /*
     Essa programação totalmente necessita pré configurar os valores para ficar bem calibrado pelo CMD do software DSW
      
      Comandos disponíveis:
      
      1. "/brightness" 
         - Descrição: Define o brilho do LED.
         - Valores aceitáveis: 0 a 255 (0 = desligado, 255 = totalmente aceso)
      
      2. "/point"
         - Descrição: Define o ponto de ativação do LED.
         - Valores aceitáveis: 0 a ♾ (onde o LED acenderá se a intensidade for maior ou igual a este valor em velocidade do jogo)
      
      3. "/mode"
         - Descrição: Define o modo de operação do LED.
         - Valores aceitáveis:
           - 1: Brilho fixo
           - 2: Piscar
     >Foi utilizado o LED no pingo 13 está configurado no pino 13 que por coincidência é o mesmo pino onde tem um LED original do Arduino  o que tem a letra L     
    */
// Criação de uma instância da classe DSWPainelPro para controle e gerenciamento do sistema
DSWPainelPro dsw; 

// Variáveis de controle para o LED no modo de piscar, com o objetivo de evitar perda de dados entre ciclos de programa
unsigned long previousMillis = 0;  // Armazena o último tempo em que o LED foi atualizado
const long interval = 244;  // Intervalo em milissegundos para piscar o LED (0,244 segundos)

// Variáveis de configuração e calibração que podem ser modificadas por comandos (CMD)
// Estes valores são armazenados e recuperados da EEPROM para garantir a persistência após desligamentos
int power = 0;    // Controle de potência/brilho do LED
int mode = 0;     // Modo de operação do LED (1: Brilho fixo, 2: Piscar)
int point = 0;    // Ponto de ativação do LED com base na intensidade recebida

// Inicialização do gerenciador de EEPROM do DSWPainelPro
// Aqui, associamos as variáveis `power`, `mode`, e `point` às posições de memória para serem salvas e recuperadas
void* variaveis[] = { &power , &mode , &point  }; // Ponteiros para as variáveis que desejamos armazenar
char tipos[] = { 'i', 'i', 'i' };  // Definimos os tipos das variáveis: "i" para int, "f" para float
dsw_eeprom eepromManager(variaveis, tipos, 3);  // Inicializa o gerenciador de EEPROM com 3 variáveis

// Função de callback que será chamada quando um comando for recebido
void meuCallback(String command, int valuer) {
  /*
    Esta função trata os comandos recebidos e ajusta as variáveis de configuração.
    `command`: o comando recebido (como "/brightness" ou "/point").
    `valuer`: o valor associado ao comando, que será usado para atualizar as variáveis.
    
    A função verifica o comando recebido e, dependendo do comando, ajusta a variável correspondente.
    Após cada ajuste, as variáveis são salvas na EEPROM para garantir que as alterações persistam após reinicializações.
  */
  
  if (command == "/brightness") {
      power = valuer;  // Atualiza a variável de brilho
      eepromManager.eeprom_salvar();  // Salva a nova configuração na EEPROM
  } else if (command == "/point") {
      point = valuer;  // Atualiza o ponto de ativação do LED
      eepromManager.eeprom_salvar();  // Salva a nova configuração na EEPROM
  } else {
      mode = valuer;  // Atualiza o modo de operação
      eepromManager.eeprom_salvar();  // Salva a nova configuração na EEPROM
  }
}

void setup() {
  // Carrega os valores salvos da EEPROM ao iniciar o Arduino
  eepromManager.eeprom_puxar();
  
  // Configura o pino 13 como saída (LED na placa do Arduino)
  pinMode(13, OUTPUT);
  
  // Lista de comandos que podem ser recebidos via software
  String comandos[] = {"/mode", "/point", "/brightness"};
  int numComandos = 3;
  
  // Inicia o gerenciamento de comandos, fornecendo a lista de comandos válidos
  dsw.cmd_vai(comandos, numComandos);
  
  // Registra a função de callback para tratar comandos recebidos
  // Sempre que um comando for reconhecido, a função `meuCallback` será chamada
  dsw.cmd_chamarisco(meuCallback);
}

void loop() {
  // Atualiza os valores recebidos do software
  dsw.atualizar();
  
  // Obtém o valor do slot 1 e o converte para inteiro
  // Aqui estamos usando esse valor como um exemplo para controlar um LED de Shift Light
  String value = dsw.puxa(0);
  int intensity = value.toInt();  // Converte o valor de string para inteiro
  
  // Controle do LED baseado na intensidade recebida e no modo configurado
  if (intensity >= point) {  // Verifica se a intensidade é maior ou igual ao ponto configurado
    if (mode == 1) {
      analogWrite(13, power);  // Modo 1: Controla o brilho do LED com base na variável `power`
    } else if (mode == 2) {
      led_blink();  // Modo 2: Ativa o piscar do LED
    }
  } else {
    analogWrite(13, 0);  // Se a intensidade for menor que o ponto, desliga o LED
  }
}

// Função que faz o LED piscar em intervalos regulares
void led_blink() {
  unsigned long currentMillis = millis();  // Obtém o tempo atual em milissegundos
  
  // Verifica se o intervalo de tempo já passou desde a última atualização
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Atualiza o tempo anterior com o tempo atual
    
    // Alterna o estado do LED (liga/desliga)
    int ledState = digitalRead(13);
    digitalWrite(13, !ledState);  // Inverte o estado do LED
  }
}
