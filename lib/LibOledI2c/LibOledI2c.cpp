#include <LibOledI2c.h>

LibOledI2c::LibOledI2c() {

}

void LibOledI2c::begin() {
    delay(1);
    display.begin(i2c_Address, true);
}

void LibOledI2c::printTriangle(uint8_t st) {
    if (st == 1) {
        display.fillTriangle(10, 50, 10, 60, 20, 55, SH110X_BLACK);
        display.display();
        display.fillTriangle(10, 30, 10, 40, 20, 35, SH110X_WHITE);
        display.display();
    } else if (st == 2) {
        display.fillTriangle(10, 50, 10, 60, 20, 55, SH110X_WHITE);
        display.display();
        display.fillTriangle(10, 30, 10, 40, 20, 35, SH110X_BLACK);
        display.display();
    }
}

void LibOledI2c::printTargetset(int16_t countTargetset) {
    static int16_t lastCountTargetset = -1;
    if (lastCountTargetset != countTargetset) {
        // in lastCount1 mau nen
        display.setCursor(30, 37);
        display.setTextColor(SH110X_BLACK);
        display.print(lastCountTargetset);
        display.display();
        // in count1 mau mong muon
        display.setCursor(30, 37);
        display.setTextColor(SH110X_WHITE);
        display.print(countTargetset);
        display.display();
        lastCountTargetset = countTargetset;
    }
}

void LibOledI2c::targetCount(uint8_t x, uint8_t y, uint16_t valuelast, uint16_t value) {
    display.setCursor(x, y);
    display.setTextColor(SH110X_BLACK);
    display.print(valuelast);
    display.display();
    // in count1 mau mong muon
    display.setCursor(x, y);
    display.setTextColor(SH110X_WHITE);
    display.print(value);
    display.display();
}

void LibOledI2c::printCountTarget1(int16_t demTarget) {
    static int16_t lastDemTargetset = -1;

    if (lastDemTargetset != demTarget) {
        // in lastCount1 mau nen
        targetCount(83, 37, lastDemTargetset, demTarget);
        lastDemTargetset = demTarget;
    }
}

void LibOledI2c::printCountTarget2(int16_t demTarget) {
    static int16_t lastDemTargetset1 = -1;

    if (lastDemTargetset1 != demTarget) {
        // in lastCount1 mau nen
        targetCount(90, 37, lastDemTargetset1, demTarget);
        lastDemTargetset1 = demTarget;
    }
}

void LibOledI2c::printInsole_1(uint16_t countIns1) {
    static int16_t lastCount1 = -1;
    //Serial.println(countIns1);
    if (lastCount1 != countIns1) {
        // in lastCount1 mau nen
        display.setCursor(12, 55);
        display.setTextColor(SH110X_BLACK);
        display.print(lastCount1);
        display.display();
        // in count1 mau mong muon
        display.setCursor(12, 55);
        display.setTextColor(SH110X_WHITE);
        display.print(countIns1);
        display.display();
        lastCount1 = countIns1;
    }
}

void LibOledI2c::printInsole_2(uint16_t countIns2) {
    static int16_t lastCount2 = -1;

    if (lastCount2 != countIns2) {
    // in lastCount1 mau nen
        display.setCursor(82, 55);
        display.setTextColor(SH110X_BLACK);
        display.print(lastCount2);
        display.display();
    // doi mau mong muon
        display.setCursor(82, 55);
        display.setTextColor(SH110X_WHITE);
        display.print(countIns2);
        display.display();
        lastCount2 = countIns2;
    }
}

void LibOledI2c::printM_D_H_M(uint8_t x, uint8_t y, uint16_t lastValue, uint16_t value) {
    display.setCursor(x, y);
    display.setTextColor(SH110X_BLACK);
    display.print(lastValue);
    display.display();
    // doi mau mong muon
    display.setCursor(x, y);
    display.setTextColor(SH110X_WHITE);
    display.print(value);
    display.display();
}