#include "dswpainelpro.h"
#include <Servo.h>
//Para rodar no software A configuração de slots Deve ser o número 1 para rpm e número 2 para a velocidade do veiculo
/*
 * Ligar o servo nos pino
   >9  = Rotação do motor 
   >10 = Velocidade 
 * É totalmente necessário no primeiro uso a configuração dos valores pelo CMD do software se não não vai funcionar !
 * Comandos Configurados:
 *
 * 1. "/set_max_engine_speed <valor>":
 *    - Define o valor máximo da rotação do motor.
 *    - Exemplo: "/set_max_engine_speed 5000" para definir a rotação máxima para 5000 RPM.
 *
 * 2. "/set_max_car_speed <valor>":
 *    - Define o valor máximo da velocidade do veículo.
 *    - Exemplo: "/set_max_car_speed 120" para definir a velocidade máxima para 120 km/h.
 */

// Criação de uma instância da classe DSWPainelPro para controlar e gerenciar o sistema de painel
DSWPainelPro dsw; 
// Instancia dois objetos Servo para controlar o ponteiro de rotação do motor (engine_speed) e o ponteiro de velocidade do veículo (car_speed)
Servo engine_speed;  
Servo car_speed; 

// Variáveis de calibração para os servos, que serão configuradas por meio de comandos (CMD)
// Esses valores são salvos na EEPROM para garantir que sejam persistidos entre reinicializações do Arduino
int engine_speed_c = 0;    // Define o valor máximo do ponteiro de rotação do motor
int car_speed_c = 0;       // Define o valor máximo do ponteiro de velocidade do veículo

// Inicializa o gerenciador de EEPROM do DSWPainelPro
// Atribui as variáveis 'engine_speed_c' e 'car_speed_c' a posições na EEPROM para serem armazenadas e recuperadas automaticamente
void* variaveis[] = { &engine_speed_c, &car_speed_c };  // Ponteiros para as variáveis que serão armazenadas
char tipos[] = { 'i', 'i' };  // Especifica o tipo de dado de cada variável: 'i' para int (inteiro)
dsw_eeprom eepromManager(variaveis, tipos, 2);  // Inicializa o gerenciador de EEPROM com 2 variáveis (ambas inteiros)

// Função de callback para processar comandos recebidos via comunicação serial ou outra interface
// Esta função é chamada sempre que um comando é recebido
void teu_calbeque(String command, int valuer) {
  /*
    Processa comandos recebidos e ajusta as variáveis de calibração de acordo.
    Parâmetros:
      - `command`: O comando recebido (ex: "/set_max_engine_speed" ou "/set_max_car_speed")
      - `valuer`: O valor associado ao comando, que será usado para ajustar as variáveis
     
    Se o comando for reconhecido, a função atualiza a variável correspondente e salva na EEPROM.
    Isso garante que as alterações feitas nas variáveis persistam após reinicializações.
  */
  
  if (command == "/set_max_engine_speed") {
      engine_speed_c = valuer;  // Atualiza o valor máximo de rotação do motor
      eepromManager.eeprom_salvar();  // Salva a nova configuração na EEPROM

  } else if (command == "/set_max_car_speed") {
      car_speed_c = valuer;  // Atualiza o valor máximo de velocidade do carro
      eepromManager.eeprom_salvar();  // Salva a nova configuração na EEPROM
  }
}

void setup() {
  // Associa os servos às portas 9 e 10 do Arduino
  engine_speed.attach(9);  
  car_speed.attach(10);
  
  // Recupera os valores salvos na EEPROM ao inicializar o Arduino
  eepromManager.eeprom_puxar();
  
  // Define a lista de comandos que o sistema é capaz de reconhecer
  String comandos[] = {"/set_max_car_speed", "/set_max_engine_speed"};  // Lista de comandos válidos
  int numComandos = 2;  // Número de comandos na lista
  
  // Inicializa o sistema de gerenciamento de comandos, informando a lista de comandos válidos
  dsw.cmd_vai(comandos, numComandos);
  
  // Registra a função de callback `teu_calbeque`, que será chamada quando um comando for recebido
  dsw.cmd_chamarisco(teu_calbeque);
}

void loop() {
  // Atualiza o sistema de comunicação, verificando se novos comandos ou dados foram recebidos
  dsw.atualizar();
  
  // Obtém os valores de RPM e velocidade (em km/h) recebidos da comunicação
  String rpms = dsw.puxa(0);  // Obtém o valor do primeiro slot (RPM do motor)
  String kmhs = dsw.puxa(1);  // Obtém o valor do segundo slot (velocidade do carro)

  // Converte os valores de strings para inteiros para controlar os servos
  int engine_speed_attv = rpms.toInt();  // Valor de rotação do motor
  int car_speed_attv = kmhs.toInt();     // Valor de velocidade do carro

  // Proteção para evitar que os valores de entrada sejam negativos ou excedam os valores máximos permitidos
  if (engine_speed_attv < 0) {
      engine_speed_attv = 0;  // Garante que o valor mínimo seja 0
  } else if (engine_speed_attv > engine_speed_c) {
      engine_speed_attv = engine_speed_c;  // Limita o valor ao máximo definido
  }

  if (car_speed_attv < 0) {
      car_speed_attv = 0;  // Garante que o valor mínimo seja 0
  } else if (car_speed_attv > car_speed_c) {
      car_speed_attv = car_speed_c;  // Limita o valor ao máximo definido
  }

  // Mapeia os valores de rotação do motor e velocidade do carro para o ângulo dos servos (0 a 180 graus)
  int servo1 = map(engine_speed_attv, 0, engine_speed_c, 0, 180);
  int servo2 = map(car_speed_attv, 0, car_speed_c, 0, 180);

  // Move os servos para os novos ângulos calculados
  engine_speed.write(servo1);  // Move o servo do motor para o novo ângulo
  car_speed.write(servo2);     // Move o servo de velocidade do carro para o novo ângulo
}
