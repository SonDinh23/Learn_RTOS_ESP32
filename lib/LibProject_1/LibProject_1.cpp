#include <LibProject_1.h>

LibProject_1::LibProject_1() {

}

void LibProject_1::begin() {
    libolei2c.begin();
    rtc.begin();
    if (!rtc.isrunning()) {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        //rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
}

void LibProject_1::screenIntro() {
    libolei2c.display.clearDisplay();
    libolei2c.display.setTextColor(SH110X_WHITE);
    libolei2c.display.drawRoundRect(0, 0, 128, 64, 8, SH110X_WHITE);
    libolei2c.display.display();
    libolei2c.display.drawBitmap(25, 15, logo, 24, 29, 1);
    libolei2c.display.setTextSize(1);
    libolei2c.display.setCursor(55, 23);
    libolei2c.display.setTextColor(SH110X_WHITE);
    libolei2c.display.print(F("VULCAN"));
    libolei2c.display.setCursor(55, 33);
    libolei2c.display.print(F("AUGMETICS"));
    libolei2c.display.display();
    delay(1);
    lastStateCLK = digitalRead(CLK);
    stateMH = 0;
    Serial.println("alo");
}