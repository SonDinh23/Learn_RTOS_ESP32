#include <LibProject_1.h>

LibProject_1::LibProject_1()
{
}

void LibProject_1::begin()
{
    libolei2c.begin();
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);

    myservo_1.attach(SERVO_1);
    myservo_2.attach(SERVO_2);
    myservo_3.attach(SERVO_3);
    myservo_4.attach(SERVO_4);

    pinMode(INSOLE_1, INPUT_PULLUP);
    pinMode(INSOLE_2, INPUT_PULLUP);
    rtc.begin();
    if (!rtc.isrunning())
    {
        rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
    }
}

void LibProject_1::screenIntro()
{
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
    // stateMH = 0;
    // libolei2c.display.clearDisplay();
    // vTaskSuspend(NULL);
}

int8_t LibProject_1::updateEncoder() {
    // Read the current state of CLK
    currentStateCLK = digitalRead(CLK);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {

        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(DT) != currentStateCLK) {
            // counter++;
            // Serial.println("cung");
            stateTG = 1;
            rotation = 1;
            // Serial.println(rotation);
        }
        else {
            // Encoder is rotating CW so increment
            // counter--;
            // Serial.println("ngc");
            stateTG = 2;
            rotation = -1;
            // Serial.println(rotation);
        }
    }else {
        rotation = 0;
    }
    

    lastStateCLK = currentStateCLK;
    delay(1);

    return rotation;
}

uint16_t LibProject_1::testInsole_1()
{
    if (digitalRead(INSOLE_1) == 0)
    {
        if (m == 0)
        {
            countInsole_1++;
            m = 1;
            // stateInsoleError = 0;
        }
    }
    else if (digitalRead(INSOLE_1) == 1)
    {
        m = 0;
    }
    return countInsole_1;
}

uint16_t LibProject_1::testInsole_2()
{
    if (digitalRead(INSOLE_2) == 0)
    {
        if (n == 0)
        {
            countInsole_2++;
            n = 1;
            // stateInsoleError = 0;
        }
    }
    else if (digitalRead(INSOLE_2) == 1)
    {
        n = 0;
    }
    return countInsole_2;
}

void LibProject_1::printRtcNow(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute)
{
    if (month != thang)
    {
        libolei2c.printM_D_H_M(30, 20, thang, month);
        thang = month;
    }

    if (day != ngay)
    {
        libolei2c.printM_D_H_M(50, 20, ngay, day);
        ngay = day;
    }

    if (hour != gio)
    {
        libolei2c.printM_D_H_M(83, 20, gio, hour);
        gio = hour;
    }

    if (minute != phut)
    {
        libolei2c.printM_D_H_M(103, 20, phut, minute);
        phut = minute;
    }
}

void LibProject_1::printRtcStart(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute)
{

    if (month != strThang)
    {
        libolei2c.printM_D_H_M(40, 20, strThang, month);
        strThang = month;
    }

    if (day != strNgay)
    {
        libolei2c.printM_D_H_M(60, 20, strNgay, day);
        strNgay = day;
    }

    if (hour != strGio)
    {
        libolei2c.printM_D_H_M(93, 20, strGio, hour);
        strGio = hour;
    }

    if (minute != strPhut)
    {
        libolei2c.printM_D_H_M(113, 20, strPhut, minute);
        strPhut = minute;
    }
}

void LibProject_1::printRunTime(uint8_t hour, uint8_t minute)
{

    if (hour != lastRunGio)
    {
        libolei2c.printM_D_H_M(40, 37, lastRunGio, hour);
        lastRunGio = hour;
    }

    if (minute != lastRunPhut)
    {
        libolei2c.printM_D_H_M(65, 37, lastRunPhut, minute);
        lastRunPhut = minute;
    }
}

void LibProject_1::setServo()
{
    for (int p = ANGLETB; p > ANGLEMIN; p--)
    {
        myservo_1.write(p);
        myservo_2.write(p);
        myservo_3.write(p);
        myservo_4.write(p);
        delay(SPEED);
    }
    delay(1200);
    for (int j = ANGLEMIN; j < ANGLEMAX; j++)
    {
        myservo_1.write(j);
        myservo_2.write(j);
        myservo_3.write(j);
        myservo_4.write(j);
        // libolei2c.printInsole_1(testInsole_1());
        // libolei2c.printInsole_2(testInsole_2());
        delay(SPEED);
    }
    delay(1200);
    for (int r = ANGLEMAX; r > ANGLETB; r--)
    {
        myservo_1.write(r);
        myservo_2.write(r);
        myservo_3.write(r);
        myservo_4.write(r);
        // libolei2c.printInsole_1(testInsole_1());
        // libolei2c.printInsole_2(testInsole_2());
        delay(SPEED);
    }
}

void LibProject_1::setServoTB()
{
    for (int k = ANGLEMIN; k < ANGLETB; k++)
    {
        myservo_1.write(k);
        myservo_2.write(k);
        myservo_3.write(k);
        myservo_4.write(k);
        delay(SPEED);
    }
}

void LibProject_1::screenMenu()
{
    if (firstState) {
        setServoTB();
        libolei2c.display.clearDisplay();
        vTaskDelay(10);
        Serial.println("Menu");
        Serial.println(firstState);
        libolei2c.display.setTextSize(2);
        libolei2c.display.setTextColor(SH110X_WHITE);
        libolei2c.display.setCursor(5, 0);
        libolei2c.display.print(F("InsoleTest"));
        libolei2c.display.drawRect(5, 20, 120, 1, SH110X_WHITE);
        libolei2c.display.setTextSize(1);
        libolei2c.display.setCursor(45, 30);
        libolei2c.display.println(F("Test 1"));
        libolei2c.display.setCursor(45, 52);
        libolei2c.display.println(F("Test 2"));
        firstState = false;
        
    }
}

void LibProject_1::firstTest1()
{
    Serial.println("test1");
    libolei2c.display.clearDisplay();
    libolei2c.display.setCursor(4, 0);
    libolei2c.display.setTextSize(1);
    libolei2c.display.setTextColor(SH110X_WHITE);
    libolei2c.display.print(F("VULCAN AUGEMETICS"));
    libolei2c.display.drawRect(4, 10, 100, 1, SH110X_WHITE);
    libolei2c.display.display();

    libolei2c.display.setTextSize(1);
    libolei2c.display.setTextColor(SH110X_WHITE);
    libolei2c.display.setCursor(0, 20);
    libolei2c.display.print(F("Now:"));

    libolei2c.display.setCursor(43, 20);
    libolei2c.display.print(F("/"));
    libolei2c.display.setCursor(68, 20);
    libolei2c.display.print(F("||"));
    libolei2c.display.setCursor(96, 20);
    libolei2c.display.print(F(":"));

    libolei2c.display.setCursor(75, 37);
    libolei2c.display.print(F("/"));

    libolei2c.display.setTextSize(1);
    libolei2c.display.setCursor(0, 37);
    libolei2c.display.println(F("TSet:"));
    libolei2c.display.setCursor(0, 55);
    libolei2c.display.println(F("L:"));
    libolei2c.display.setCursor(70, 55);
    libolei2c.display.println(F("R:"));
    libolei2c.display.display();

    counter = 0;
    count1 = 0;

    thang = 0;
    ngay = 0;
    gio = 0;
    phut = 0;

    countInsole_1 = 0;
    countInsole_2 = 0;
    libolei2c.printInsole_1(countInsole_1);
    libolei2c.printInsole_2(countInsole_2);
    updateTime();
    firstState = false;
    lastTarget = 0;
}

void LibProject_1::firstTest2()
{
    libolei2c.display.clearDisplay();

    libolei2c.display.setCursor(4, 0);
    libolei2c.display.setTextSize(1);
    libolei2c.display.setTextColor(SH110X_WHITE);
    libolei2c.display.print(F("VULCAN AUGEMETICS"));
    libolei2c.display.drawRect(4, 10, 100, 1, SH110X_WHITE);
    libolei2c.display.display();

    libolei2c.display.setCursor(53, 20);
    libolei2c.display.print(F("/"));
    libolei2c.display.setCursor(76, 20);
    libolei2c.display.print(F("||"));
    libolei2c.display.setCursor(105, 20);
    libolei2c.display.print(F(":"));

    libolei2c.display.setCursor(53, 37);
    libolei2c.display.print(F(":"));
    libolei2c.display.setCursor(76, 37);
    libolei2c.display.print(F("||"));

    libolei2c.display.setTextSize(1);
    libolei2c.display.setTextColor(SH110X_WHITE);
    libolei2c.display.setCursor(0, 20);
    libolei2c.display.print(F("Str.T:"));
    libolei2c.display.setTextSize(1);
    libolei2c.display.setCursor(0, 37);
    libolei2c.display.println(F("Run.T:"));
    libolei2c.display.setCursor(0, 55);
    libolei2c.display.println(F("L:"));
    libolei2c.display.setCursor(70, 55);
    libolei2c.display.println(F("R:"));
    libolei2c.display.display();

    lastRunGio = -1;
    lastRunPhut = -1;

    runGio = 0;
    runPhut = 0;

    strThang = -1;
    strNgay = -1;
    strGio = -1;
    strPhut = -1;

    thangStr = 0;
    ngayStr = 0;
    gioStr = 0;
    phutStr = 0;

    printRtcStart(thangStr, ngayStr, gioStr, phutStr);
    printRunTime(runGio, runPhut);

    tempTime = 0;
    tempTimeStart = 0;
    tempTimeNow = 0;
    tempTimePause = 0;

    minutesPause = 0;
    hourPause = 0;
    dayPause = 0;

    tempRun = 0;
    ul = 0;

    nowDay = 0;
    nowHour = 0;
    nowMinute = 0;

    tempPause = 0;

    tempPause2 = 0;
    firstState = false;
}

void LibProject_1::screenTest1()
{
    // for (;;) {

    if (firstState)
    {
        firstTest1();
        // Serial.println("first");
    }

    while (stateTset)
    {
        // Serial.print("doi");
        // Serial.print("\t");
        // Serial.println(stateOnServer);
        
        switch (stateOnServer)
        {
        case 0:
            Serial.println("thoat");
            stateSend = true;
            printTargetFirst = true;
            stateOnServerMenu = 0;
            break;
        case 1:
            Serial.println("batdau");
            lastTarget = targetSetTest1;
            countT = 0;
            stateTset = false;
            stateStart = false;
            // Serial.println("1");
            break;
        }
        updateTime();
        vTaskDelay(10);
    }
    // Serial.println("2");
    // Serial.println(lastTarget);
    while (countT < lastTarget)
    {
        
        if (printTargetFirst) {
            // Serial.println("3");
            libolei2c.printTargetset(lastTarget);
            printTargetFirst = false;
        }
        updateTime();
        switch (stateOnServer) {
        case 0: // Stop
            Serial.println("Stop");
            countT = 0;
            stateSend = true;
            printTargetFirst = true;
            stateOnServerMenu = 0;
            // libolei2c.display.clearDisplay();
            break;
        case 1: // Start
            // Serial.println("Start");
            tbServo = true;
            libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_BLACK);
            libolei2c.display.display();
            setServo();
            dem1 = ++countT;
            libolei2c.printCountTarget1(dem1);
            if (countT == targetSetTest1) {
                // Serial.println("xong");
                stateChangeSend = true;
                // printTargetFirst = true;
                stateTset = true;
                lastTarget = 0;
                countT = 0;
                vTaskDelay(20);
            }
            break;
        case -1: // Pause
            // Serial.println("Pause");
            libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_WHITE);
            libolei2c.display.display();
            if (tbServo) {
                setServoTB();
                tbServo = false;
            }
            vTaskDelay(5);
            break;
        default:
            // Serial.println("oke");
            printTargetFirst = true;
            stateTset = true;
            lastTarget = 0;
            countT = 0;
            break;
        }
    }
}

void LibProject_1::screenTest2()
{

    if (firstState) {
        firstTest2();
    }
    static bool stateTempStart = true;
    static bool stateTempPause = true;

    switch (stateOnServer) {
    case 0: // Stop
    {
        // Serial.println("Stop");
        stateOnServerMenu = 0;
        stateSend = true;
        break;
    }
    case 1: // Start
    {
        // Serial.println("Start");
        if (stateTempStart)
        {
            now = rtc.now();
            thangStr = now.month();
            ngayStr = now.day();
            gioStr = now.hour();
            phutStr = now.minute();

            printRtcStart(thangStr, ngayStr, gioStr, phutStr);
            tempTimeStart = (((ngayStr * 24) * 60) + (gioStr * 60) + phutStr);
            countInsole_1 = 0;
            countInsole_2 = 0;
            stateTempStart = false;
        }
        now = rtc.now();
        nowDay = now.day();
        nowHour = now.hour();
        nowMinute = now.minute();

        tempTimeNow = (((nowDay * 24) * 60) + (nowHour * 60) + nowMinute);

        if (tempTimePause != 0)
        {
            // tempTimeStart = tempTimeStart - tempTimePause;
            tempPause = tempTimeNow - tempTimePause;
            tempTimePause = 0;
            tempPause2 = tempPause2 + tempPause;
        }
        // Serial.println(tempPause2);
        tempTime = tempTimeNow - tempTimeStart;
        tempRun = tempTime - tempPause2;
        // tempPause = 0;
        //  Serial.println("In thoi gian tru:");
        //  Serial.println(tempRun);
        while (tempRun >= 60)
        {
            tempRun = tempRun - 60;
            ul++;
        }
        // Serial.println(tempRun);
        printRunTime(ul, tempRun);

        libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_BLACK);
        libolei2c.display.display();
        dem2++;
        setServo();
        libolei2c.printCountTarget2(dem2);
        break;
    }
    case -1: // Pause
    {
        // Serial.println("Pause");
        if (stateTempPause)
        {
            now = rtc.now();
            minutesPause = now.minute();
            hourPause = now.hour();
            dayPause = now.day();
            tempTimePause = (((dayPause * 24) * 60) + (hourPause * 60) + minutesPause);
            // Serial.println("In thoi gian pause:");
            // Serial.println(tempTimeStart);
            stateTempPause = false;
        }
        libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_WHITE);
        libolei2c.display.display();
        setServoTB();
        break;
    }
    default:
        break;
    }
}

void LibProject_1::setTargetSetTest1(uint16_t data)
{
    targetSetTest1 = data;
}

uint16_t LibProject_1::getTargetSetTest1()
{
    return targetSetTest1;
}

void LibProject_1::updateTime()
{
    now = rtc.now();
    printRtcNow(now.month(), now.day(), now.hour(), now.minute());
}

bool LibProject_1::getStateCountT()
{
    return stateChangeSend;
}

void LibProject_1::printTargetSet(uint16_t _data)
{
    libolei2c.printTargetset(_data);
}

void LibProject_1::setStateCountT(bool _data)
{
    stateChangeSend = _data;
}

int8_t LibProject_1::getStateOnServerMenu()
{
    return stateOnServerMenu;
}

int8_t LibProject_1::getStateOnServer()
{
    return stateOnServer;
}

void LibProject_1::setStateOnServerMenu(int8_t _data)
{
    stateOnServerMenu = _data;
}

void LibProject_1::setStateOnServer(int8_t _data)
{
    stateOnServer = _data;
}

uint8_t LibProject_1::getButton()
{
    return digitalRead(SW);
}

uint8_t LibProject_1::stateTriangle()
{
    return tamgiac;
}

void LibProject_1::getTriangle()
{
    libolei2c.printTriangle(tamgiac);
}

void LibProject_1::readTriangle()
{
    switch (updateEncoder())
    {
        case 1:
        /* code */
            
            tamgiac = 1;
            // Serial.println(tamgiac);
            break;
        case -1:
            tamgiac = 2;
            // Serial.println(tamgiac);
            break;
        default:
            break;
    }
    
}

int16_t LibProject_1::getCounter()
{   
    if (counter < 0) {
        counter = 0;
        return counter;
    }
    return counter;
    
}

void LibProject_1::setCounter(int8_t _data)
{
    counter = _data;
}

void LibProject_1::setStateStart(bool _state)
{
    stateStart = _state;
}
void LibProject_1::setStatePause(bool _state)
{
    statePause = _state;
}
void LibProject_1::setStateStop(bool _state)
{
    stateStop = _state;
}

void LibProject_1::setFirstScreen(bool state)
{
    firstState = state;
    Serial.print("state first screen: ");
    Serial.println(firstState);
}

bool LibProject_1::getStateStart()
{
    return stateStart;
}
bool LibProject_1::getStatePause()
{
    return statePause;
}
bool LibProject_1::getStateStop()
{
    return stateStop;
}

bool LibProject_1::getStateSend() {
    return stateSend;
}

void LibProject_1::setStateSend(bool data) {
    stateSend = data;
}