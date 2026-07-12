#ifndef DSWEPAINELPRO_H
#define DSWEPAINELPRO_H

#include <Arduino.h>

typedef void (*CommandCallback)(String command, float value);

class DSWPainelPro {
public:
    DSWPainelPro();
    ~DSWPainelPro();

    void vai(long baudRate = 115200);
    void atualizar();
    void slynky(const String& pp);
    void cmd_vai(String commands[], int size);
    float cmd_puxada(String commandName);
    void cmd_chamarisco(CommandCallback callback);
    String puxa(int slot);

private:
    static const int SLOT_COUNT = 20;

    String values[SLOT_COUNT];
    unsigned long lastUpdateTime;
    String* _commands;
    float* _values;
    int _numCommands;
    CommandCallback _callback;

    void displayHelp();
    void processCommand(String input);
    void processTelemetryFrame(String input);
    void resetValues();
    void releaseCommandStorage();
    bool extractCommandAndValue(const String& input, String& command, float& value);
    int findCommandIndex(const String& commandName) const;
    String canonicalizeCommand(const String& text) const;
    String normalizeSlotToken(const String& token) const;
};

class dsw_eeprom {
private:
    void** vars;
    char* types;
    int varCount;

public:
    dsw_eeprom(void* vars[], char types[], int varCount);
    void eeprom_salvar();
    void eeprom_puxar();
};

#endif // DSWEPAINELPRO_H
