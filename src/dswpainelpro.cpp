#include "dswpainelpro.h"

#include <Arduino.h>
#include <EEPROM.h>

DSWPainelPro::DSWPainelPro()
    : lastUpdateTime(0), _commands(nullptr), _values(nullptr), _numCommands(0), _callback(nullptr) {
    resetValues();
}

DSWPainelPro::~DSWPainelPro() {
    releaseCommandStorage();
}

void DSWPainelPro::vai(long baudRate) {
    Serial.begin(baudRate);
    lastUpdateTime = millis();
    resetValues();
}

void DSWPainelPro::cmd_vai(String commands[], int size) {
    if (commands == nullptr || size <= 0) {
        Serial.println("Erro: lista de comandos invalida.");
        return;
    }

    releaseCommandStorage();

    _commands = new String[size];
    _values = new float[size];
    _numCommands = size;

    for (int i = 0; i < size; ++i) {
        _commands[i] = commands[i];
        _values[i] = 0.0f;
    }

    Serial.print("Comandos configurados: ");
    Serial.println(_numCommands);
}

void DSWPainelPro::atualizar() {
    if (!Serial.available()) {
        return;
    }

    String input = Serial.readStringUntil('\n');
    input.trim();
    if (!input.length()) {
        return;
    }

    if (input.startsWith("/")) {
        if (input.equalsIgnoreCase("/help")) {
            displayHelp();
            return;
        }
        processCommand(input);
        return;
    }

    processTelemetryFrame(input);
}

void DSWPainelPro::processTelemetryFrame(String input) {
    input.trim();
    if (!input.length()) {
        return;
    }

    input.replace(';', ',');

    int slot = 0;
    int start = 0;
    while (slot < SLOT_COUNT && start <= input.length()) {
        int separator = input.indexOf(',', start);
        String token = separator == -1 ? input.substring(start) : input.substring(start, separator);
        values[slot++] = normalizeSlotToken(token);

        if (separator == -1) {
            break;
        }
        start = separator + 1;
    }

    while (slot < SLOT_COUNT) {
        values[slot++] = "0";
    }

    lastUpdateTime = millis();
}

String DSWPainelPro::normalizeSlotToken(const String& token) const {
    String text = token;
    text.trim();
    if (!text.length()) {
        return "0";
    }

    bool hasDigit = false;
    bool hasDecimal = false;
    String normalized;
    normalized.reserve(text.length());

    for (unsigned int i = 0; i < text.length(); ++i) {
        char c = text.charAt(i);
        if ((c == '+' || c == '-') && normalized.length() == 0) {
            normalized += c;
            continue;
        }
        if (c >= '0' && c <= '9') {
            normalized += c;
            hasDigit = true;
            continue;
        }
        if ((c == '.' || c == ',') && !hasDecimal) {
            normalized += '.';
            hasDecimal = true;
            continue;
        }
        if (c == ' ') {
            continue;
        }
        break;
    }

    if (!hasDigit) {
        return "0";
    }

    if (normalized == "-" || normalized == "+" || normalized == "." || normalized == "-." || normalized == "+.") {
        return "0";
    }

    return normalized;
}

String DSWPainelPro::puxa(int slot) {
    if (slot < 0 || slot >= SLOT_COUNT) {
        return "0";
    }
    return values[slot];
}

void DSWPainelPro::slynky(const String& pp) {
    Serial.println(pp);
}

void DSWPainelPro::displayHelp() {
    Serial.println("------------------------");
    Serial.println("Comandos disponiveis:");

    if (_commands == nullptr || _numCommands <= 0) {
        Serial.println("Nenhum comando disponivel.");
    } else {
        for (int i = 0; i < _numCommands; ++i) {
            Serial.print("Comando ");
            Serial.print(i);
            Serial.print(": ");
            Serial.println(_commands[i]);
        }
    }

    Serial.println("Formatos aceitos:");
    Serial.println("/comando valor");
    Serial.println("/comando=valor");
    Serial.println("/comando:valor");
    Serial.println("Maiusculas, espacos, hifens e underscores sao tolerados.");
    Serial.println("------------------------");
}

void DSWPainelPro::processCommand(String input) {
    String command;
    float value = 0.0f;
    if (!extractCommandAndValue(input, command, value)) {
        Serial.println("Formato invalido. Use /comando valor.");
        return;
    }

    int index = findCommandIndex(command);
    if (index < 0) {
        Serial.println("Comando nao encontrado. Digite /help para ver os comandos.");
        return;
    }

    _values[index] = value;
    Serial.print(_commands[index]);
    Serial.print(" atualizado para ");
    Serial.println(value, 3);

    if (_callback != nullptr) {
        _callback(_commands[index], value);
    }
}

bool DSWPainelPro::extractCommandAndValue(const String& input, String& command, float& value) {
    String text = input;
    text.trim();
    if (!text.length()) {
        return false;
    }

    if (text.startsWith("/")) {
        text.remove(0, 1);
    }
    text.trim();

    int separator = -1;
    for (unsigned int i = 0; i < text.length(); ++i) {
        char c = text.charAt(i);
        if (c == ' ' || c == '=' || c == ':') {
            separator = static_cast<int>(i);
            break;
        }
    }

    if (separator < 0) {
        return false;
    }

    command = text.substring(0, separator);
    String rawValue = text.substring(separator + 1);
    command.trim();
    rawValue.trim();
    rawValue.replace(',', '.');

    if (!command.length() || !rawValue.length()) {
        return false;
    }

    value = rawValue.toFloat();
    return true;
}

void DSWPainelPro::cmd_chamarisco(CommandCallback callback) {
    _callback = callback;
}

float DSWPainelPro::cmd_puxada(String commandName) {
    int index = findCommandIndex(commandName);
    if (index < 0 || _values == nullptr) {
        return -1.0f;
    }
    return _values[index];
}

int DSWPainelPro::findCommandIndex(const String& commandName) const {
    if (_commands == nullptr || _numCommands <= 0) {
        return -1;
    }

    String wanted = canonicalizeCommand(commandName);
    for (int i = 0; i < _numCommands; ++i) {
        if (canonicalizeCommand(_commands[i]) == wanted) {
            return i;
        }
    }
    return -1;
}

String DSWPainelPro::canonicalizeCommand(const String& text) const {
    String normalized = text;
    normalized.trim();
    normalized.toLowerCase();

    if (normalized.startsWith("/")) {
        normalized.remove(0, 1);
    }

    normalized.replace(" ", "");
    normalized.replace("_", "");
    normalized.replace("-", "");

    return normalized;
}

void DSWPainelPro::resetValues() {
    for (int i = 0; i < SLOT_COUNT; ++i) {
        values[i] = "0";
    }
}

void DSWPainelPro::releaseCommandStorage() {
    if (_commands != nullptr) {
        delete[] _commands;
        _commands = nullptr;
    }
    if (_values != nullptr) {
        delete[] _values;
        _values = nullptr;
    }
    _numCommands = 0;
}

dsw_eeprom::dsw_eeprom(void* variables[], char typeArray[], int count) {
    varCount = count;
    vars = variables;
    types = typeArray;
}

void dsw_eeprom::eeprom_salvar() {
    int address = 0;

    for (int i = 0; i < varCount; i++) {
        if (types[i] == 'i') {
            int* intVar = (int*)vars[i];
            EEPROM.put(address, *intVar);
            address += sizeof(int);
        } else if (types[i] == 'f') {
            float* floatVar = (float*)vars[i];
            EEPROM.put(address, *floatVar);
            address += sizeof(float);
        }
    }
}

void dsw_eeprom::eeprom_puxar() {
    int address = 0;

    for (int i = 0; i < varCount; i++) {
        if (types[i] == 'i') {
            int* intVar = (int*)vars[i];
            EEPROM.get(address, *intVar);
            address += sizeof(int);
        } else if (types[i] == 'f') {
            float* floatVar = (float*)vars[i];
            EEPROM.get(address, *floatVar);
            address += sizeof(float);
        }
    }
}
