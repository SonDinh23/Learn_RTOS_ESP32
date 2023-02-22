#include <LibProject_1.h>

LibProject_1::LibProject_1() {

}

void LibProject_1::begin() {
    libolei2c.begin();
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);

    myservo.attach(SERVO);

    pinMode(INSOLE_1, INPUT_PULLUP);
    pinMode(INSOLE_2, INPUT_PULLUP);
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
    Serial.println("alo1");
    delay(1);
    lastStateCLK = digitalRead(CLK);
    stateMH = 0;
    Serial.println("alo2");
    //vTaskSuspend(NULL);
}

uint8_t LibProject_1::updateEncoder() {
    // Read the current state of CLK
    currentStateCLK = digitalRead(CLK);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK && currentStateCLK == 1) {

        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(DT) != currentStateCLK) {
            counter++;
            stateTG = 1;
        } else {
        // Encoder is rotating CW so increment
            counter--;
            stateTG = 2;
        }
    }
    // Remember last CLK state
    lastStateCLK = currentStateCLK;
    delay(1);
    return stateTG;
}

uint16_t LibProject_1::testInsole_1() {
    if (digitalRead(INSOLE_1) == 0) {
        if (m == 0) {
            countInsole_1++;
            m = 1;
            stateInsoleError = 0;
        }
    } else if (digitalRead(INSOLE_1) == 1) {
        m = 0;
    }
    return countInsole_1;
}

uint16_t LibProject_1::testInsole_2() {
    if (digitalRead(INSOLE_2) == 0) {
        if (n == 0) {
            countInsole_2++;
            n = 1;
            stateInsoleError = 0;
        }
    } else if (digitalRead(INSOLE_2) == 1) {
        n = 0;
    }
    return countInsole_2;
}

void LibProject_1::printRtcNow(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute) {
    if (month != thang) {
        libolei2c.printM_D_H_M(30, 20, thang, month);
        thang = month;
    }

    if (day != ngay) {
        libolei2c.printM_D_H_M(50, 20, ngay, day);
        ngay = day;
    }

    if (hour != gio) {
        libolei2c.printM_D_H_M(83, 20, gio, hour);
        gio = hour;
    }

    if (minute != phut) {
        libolei2c.printM_D_H_M(103, 20, phut, minute);
        phut = minute;
    }
}

void LibProject_1::printRtcStart(uint8_t month, uint8_t day, uint8_t hour, uint8_t minute) {

    if (month != strThang) {
        libolei2c.printM_D_H_M(40, 20, strThang, month);
        strThang = month;
    }

    if (day != strNgay) {
        libolei2c.printM_D_H_M(60, 20, strNgay, day);
        strNgay = day;
    }

    if (hour != strGio) {
        libolei2c.printM_D_H_M(93, 20, strGio, hour);
        strGio = hour;
    }

    if (minute != strPhut) {
        libolei2c.printM_D_H_M(113, 20, strPhut, minute);
        strPhut = minute;
    }
}

void LibProject_1::printRunTime( uint8_t hour, uint8_t minute) {

    if (hour != lastRunGio) {
        libolei2c.printM_D_H_M(40, 37, lastRunGio, hour);
        lastRunGio = hour;
    }

    if (minute != lastRunPhut) {
        libolei2c.printM_D_H_M(65, 37, lastRunPhut, minute);
        lastRunPhut = minute;
    }
}

void LibProject_1::setServo() {
    for (int p = ANGLETB; p > ANGLEMIN; p--) {
        myservo.write(p);
        delay(SPEED);
    }
    for (int j = ANGLEMIN; j < ANGLEMAX; j++) {
        myservo.write(j);
        libolei2c.printInsole_1(testInsole_1());
        libolei2c.printInsole_2(testInsole_2());
        delay(SPEED);
    }
    for (int r = ANGLEMAX; r > ANGLETB; r--) {
        myservo.write(r);
        libolei2c.printInsole_1(testInsole_1());
        libolei2c.printInsole_2(testInsole_2());
        delay(SPEED);
    }
}

void LibProject_1::setServoTB() {
    for (int k = ANGLEMIN; k < ANGLETB; k++) {
        myservo.write(k);
        delay(SPEED);
    }
}

void LibProject_1::screenMenu() {
    //vTaskSuspend(task_)
    setServoTB();
    // //display.drawBitmap(0, 50, logo16_glcd_bmp, 12, 14, 1);
    // Firebase.setString(firebaseDate, path + "/btnStart1", 0);
    // Firebase.setString(firebaseDate, path + "/btnPause1", 0);
    // Firebase.setString(firebaseDate, path + "/btnStop1", 0);

    // Firebase.setString(firebaseDate, path + "/btnStart2", 0);
    // Firebase.setString(firebaseDate, path + "/btnPause2", 0);
    // Firebase.setString(firebaseDate, path + "/btnStop2", 0);

    // Firebase.setInt(firebaseDate, path + "/countdata1", 0);
    // Firebase.setInt(firebaseDate, path + "/countdata2", 0);
    
    libolei2c.display.clearDisplay();
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
    libolei2c.display.display();
    for (;;) {
        Serial.println("alo");
        int8_t tamgiac = updateEncoder();
        libolei2c.printTriangle(tamgiac);
        //Serial.println("alo3");
        if (digitalRead(SW) == 0) {
            stateMH = tamgiac;
            break;
        }
    }
    Serial.println("no");
    
}

void LibProject_1::screenTest1() {
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
    uint32_t lastTime = millis();
    uint32_t lastTimeA = millis();
    uint32_t lastTimeB = millis();
    uint32_t lastTimeC = millis();
    uint32_t lastTimeD = millis();
    uint32_t lastTimeE = millis();
    uint32_t lastTimeF = millis();
    uint32_t lastTimeG = millis();
    uint32_t lastTimeH = millis();
    uint32_t lastTimeI = millis();
  
    uint8_t stateStartTest1 = 0;
    uint8_t statePauseTest1 = 0;
    bool statePauseBool = false;
    
    DateTime now = rtc.now();

    thang = 0;
    ngay = 0;
    gio = 0;
    phut = 0;
    
    countInsole_1 = 0;
    countInsole_2 = 0;
    libolei2c.printInsole_1(countInsole_1);
    libolei2c.printInsole_2(countInsole_2);
    
    for (;;) {

        now = rtc.now();
        printRtcNow(now.month(), now.day(), now.hour(), now.minute());
        
        updateEncoder();

        // if(updateEncoder() == 1 || updateEncoder() == 2) {
        //     if (counter < 0) counter = 0;
        //     count1 = counter * 100;
        //     data = count1;
        // }else{
        //     count1 = countT;
        // }
        if (counter < 0) counter = 0;
        count1 = counter * 100;
        libolei2c.printTargetset(count1);
        data = count1;
        

        while (digitalRead(SW) == 0) {
            if(millis() - lastTimeF > 80) {
                stateStartTest1++;
                Serial.println(stateStartTest1);
                lastTimeF = millis();
            }
            
            countInsole_1 = 0;
            countInsole_2 = 0;
        }
        
        if(stateStart1 == 1) {
            stateStartTest1 = 2;
            countInsole_1 = 0;
            countInsole_2 = 0;
        }

        if ((stateStartTest1 >= 1) && (stateStartTest1 < 5)) {
            //Serial.println("alo");
            // stateStart1 = 0;
            stateStartTest1 = 0;
        
            dem1 = 0;
            for (int i = 0; i < data; i++) {
                stateStart1 = 0;
                now = rtc.now();
                printRtcNow(now.month(), now.day(), now.hour(), now.minute());

                setServo();
                countInsole_1_1 = testInsole_1();
                countInsole_2_1 = testInsole_2();
                // Serial.println(testInsole_1());
                // Serial.println(testInsole_2());

                //setServoTB();
                //delayMicroseconds(200);
                dem1++;
                libolei2c.printCountTarget1(dem1);
                
                if ((digitalRead(INSOLE_1) == 1) && (digitalRead(INSOLE_2) == 1)) {
                    if (millis() - lastTimeG > 400) {
                        stateInsoleError++;
                        lastTimeG = millis();
                    }
                    if (stateInsoleError > 5) {
                        stateInsoleError = 5;
                        break;
                    }
                }

                if (stateInsoleError == 5) {
                    statePauseBool = true;

                    setServoTB();

                    while (statePauseBool == true) {
                        libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_WHITE);
                        libolei2c.display.display();

                        if(statePause1 == 1) {
                            statePauseTest1 = 0;
                            statePause1 = 0;
                            //Firebase.setInt(firebaseDate, path + "/btnPause1", 0);
                            break;
                        }

                        if(stateStop1 == 1) {
                            statePauseTest1 = 0;
                            stateStartTest1 = 7;
                            stateStop1 = 0;
                            //Firebase.setInt(firebaseDate, path + "/btnStop1", 0);
                            break;
                        }

                        while (digitalRead(SW) == 0) {
                            if (millis() - lastTimeH > 400) {
                                statePauseBool = false;
                                stateInsoleError = 0;
                                stateStartTest1++;
                                lastTimeH = millis();
                            }
                        }
                    }
                    libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, 0);
                    libolei2c.display.display();
                }

                if(stateStop1 == 1) {
                    stateStartTest1 = 7;
                    stateStop1 = 0;
                    //Firebase.setString(firebaseDate, path + "/btnStop1", 0);
                    break;
                }
                if(statePause1 == 1) {
                    statePauseTest1 = 1;
                    //break;
                }

                while (digitalRead(SW) == 0) {
                    statePauseTest1 = 1;
                }

                if (statePauseTest1 == 1) {
                    statePause1 = 0;
                    statePauseBool = true;

                    setServoTB();

                    while (statePauseBool == true) {
                        libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_WHITE);
                        libolei2c.display.display();

                        now = rtc.now();
                        printRtcNow(now.month(), now.day(), now.hour(), now.minute());

                        if(statePause1 == 1) {
                            statePauseTest1 = 0;
                            statePause1 = 0;
                            //Firebase.setString(firebaseDate, path + "/btnPause1", 0);
                            break;
                        }
                        
                        if(stateStop1 == 1) {
                            statePauseTest1 = 0;
                            stateStartTest1 = 7;
                            stateStop1 = 0;
                            //Firebase.setString(firebaseDate, path + "/btnStop1", 0);
                            break;
                        }

                        while (digitalRead(SW) == 0) {
                            if (millis() - lastTimeI > 300) {
                                statePauseBool = false;
                                statePauseTest1 = 0;
                                stateStartTest1++;
                                Serial.println(stateStartTest1);
                                lastTimeI = millis();
                            }
                        }
                    }
                    libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_BLACK);
                    libolei2c.display.display();
                }
                if (stateStartTest1 >= 5) {
                    break;
                }
            }
            setServoTB();
        }
        if (stateStartTest1 >= 5) {
            stateMH = 0;
            break;
        }
    }
}

void LibProject_1::screenTest2() {
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

    uint32_t lastTime = millis();
    uint32_t lastTimeA = millis();
    uint32_t lastTimeB = millis();
    uint32_t lastTimeC = millis();
    uint32_t lastTimeD = millis();
    uint32_t lastTimeE = millis();
    uint32_t lastTimeF = millis();
    uint32_t lastTimeG = millis();
    uint32_t lastTimeH = millis();
    uint32_t lastTimeI = millis();


    DateTime now = rtc.now();

    uint8_t stateStartTest2 = 0;
    uint8_t statePauseTest2 = 0;
    bool statePauseBool = false;

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

    uint16_t tempTime = 0;
    uint16_t tempTimeStart = 0;
    uint16_t tempTimeNow = 0;
    uint16_t tempTimePause = 0;

    uint16_t minutesPause = 0;
    uint16_t hourPause = 0;
    uint16_t dayPause = 0;

    tempRun = 0;
    ul = 0;

    uint16_t nowDay = 0;
    uint16_t nowHour = 0;
    uint16_t nowMinute = 0;

    uint16_t tempPause = 0;

    uint16_t tempPause2 = 0;

    // String x;
    // String y;
    // String z;

    // int8_t w;
    // int8_t e;
    // int8_t h;

    while (true) {

        now = rtc.now();

        while (digitalRead(SW) == 0) {
            if(millis() - lastTime > 200) {
                stateStartTest2++;
                //Serial.println(stateStartTest2);
                lastTime = millis();
            }

            now = rtc.now();

            thangStr = now.month();
            ngayStr = now.day();
            gioStr = now.hour();
            phutStr = now.minute();

            printRtcStart(thangStr, ngayStr, gioStr, phutStr);
            tempTimeStart = (((ngayStr*24)*60) + (gioStr*60) + phutStr);
            countInsole_1 = 0;
            countInsole_2 = 0;
            //Serial.println("In thoi gian start:");
            //Serial.println(tempTimeStart);
        }

        // if(millis() - lastTimeA > 1000) {
        //     if(Firebase.getString(firebaseDate, path + "/btnStart2")) x = firebaseDate.stringData();
        //     w = x.toInt();
        //     //Serial.println(w);
        //     lastTimeA = millis();
        // }

        if(stateStart2 == 1) {
            stateStartTest2 = 2;

            now = rtc.now();

            thangStr = now.month();
            ngayStr = now.day();
            gioStr = now.hour();
            phutStr = now.minute();

            printRtcStart(thangStr, ngayStr, gioStr, phutStr);
            tempTimeStart = (((ngayStr*24)*60) + (gioStr*60) + phutStr);

            countInsole_1 = 0;
            countInsole_2 = 0;
        }

        if ((stateStartTest2 >= 1) && (stateStartTest2 < 5)) {
            stateStart2 = 0;
            //Firebase.setString(firebaseDate, path + "/btnStart2", 0);
            stateStartTest2 = 0;
            dem2 = 0;

            for (;;) {
                //if(millis() - lastTime > 50) {
                    now = rtc.now();
                    nowDay = now.day();
                    nowHour = now.hour();
                    nowMinute = now.minute();

                    tempTimeNow = (((nowDay*24)*60) + (nowHour*60) + nowMinute);

                    if(tempTimePause != 0) {
                        // tempTimeStart = tempTimeStart - tempTimePause;
                        tempPause = tempTimeNow - tempTimePause;
                        tempTimePause = 0;
                        tempPause2 = tempPause2 + tempPause; 
                    }
                    //Serial.println(tempPause2);
                    tempTime = tempTimeNow - tempTimeStart;
                    tempRun = tempTime - tempPause2;
                    // tempPause = 0;
                    //  Serial.println("In thoi gian tru:");
                    //  Serial.println(tempRun);
                    while(tempRun >= 60) {
                        tempRun = tempRun - 60;
                        ul++;
                    }
                    //Serial.println(tempRun);
                    printRunTime(ul, tempRun);
                    //lastTime = millis();
                //}

                // if(millis() - lastTimeI > 500) {
                //     Firebase.setInt(firebaseDate, path + "/runtimeH", ul);
                //     Firebase.setInt(firebaseDate, path + "/runtimeM", tempRun);
                //     lastTimeI = millis();
                // }
        

                setServo();
                countInsole_1_2 = testInsole_1();
                countInsole_2_2 = testInsole_2();
                // if(millis() - lastTimeB > 1000) {
                //     Firebase.setInt(firebaseDate, path + "/datacount2R", testInsole_1());
                //     Firebase.setInt(firebaseDate, path + "/datacount2L", testInsole_2());
                //     lastTimeB = millis();
                // }

                dem2++;
                // if(millis() - lastTimeC > 2000) {
                //     Firebase.setInt(firebaseDate, path + "/countdata2", dem2);
                //     lastTimeC = millis();
                // }
                libolei2c.printCountTarget2(dem2);

                if ((digitalRead(INSOLE_1) == 1) && (digitalRead(INSOLE_2) == 1)) {
                  if(millis() - lastTimeG > 400) {
                    stateInsoleError++;
                    //Serial.println(stateInsoleError);
                    lastTimeG = millis();
                  }
                  if(stateInsoleError > 5) {
                    stateInsoleError = 5;
                    Serial.println("out");
                    break;
                  }
                }

                if (stateInsoleError == 5) {
                  statePauseBool = true;

                  setServoTB();

                  while (statePauseBool == true) {
                    libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_WHITE);
                    libolei2c.display.display();

                    // if(Firebase.getString(firebaseDate, path + "/btnPause2")) y = firebaseDate.stringData();
                    // e = y.toInt();
                    // //Serial.println(e);
                    if(statePause2 == 1) {
                      statePauseTest2 = 0;
                      statePause2 = 0;
                      //Firebase.setString(firebaseDate, path + "/btnPause2", 0);
                      break;
                    }

                    // if(Firebase.getString(firebaseDate, path + "/btnStop2")) z = firebaseDate.stringData();
                    // h = z.toInt();
                    // //Serial.println(h);
                    if(stateStop2 == 1) {
                      statePauseTest2 = 0;
                      stateStartTest2 = 7;
                      stateStop2 = 0;
                      //Firebase.setString(firebaseDate, path + "/btnStop2", 0);
                      break;
                    }

                    while (digitalRead(SW) == 0) {
                      if(millis() - lastTimeH > 400) {
                        statePauseBool = false;
                        stateInsoleError = 0;
                        stateStartTest2++;
                        lastTimeH = millis();
                      }
                    }
                  }
                  libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, 0);
                  libolei2c.display.display();
                }

                //Serial.println("chao");
                // if(millis() - lastTimeD > 500) {
                //     if(Firebase.getString(firebaseDate, path + "/btnPause2")) y = firebaseDate.stringData();
                //     e = y.toInt();
                //     //Serial.println(e);
                //     lastTimeD = millis();
                // }
                if(statePause2 == 1) {
                    statePauseTest2 = 1;
                }

                // if(millis() - lastTimeE > 500) {
                //     if(Firebase.getString(firebaseDate, path + "/btnStop2")) z = firebaseDate.stringData();
                //     h = z.toInt();
                //     //Serial.println(h);
                if(stateStop2 == 1) {
                    stateStartTest2 = 7;
                    stateStop2 = 0;
                        //Firebase.setString(firebaseDate, path + "/btnStop2", 0);
                    break;
                }
                //     lastTimeE = millis();
                // }        

                while (digitalRead(SW) == 0) {
                    statePauseTest2 = 1;
                }

                if (statePauseTest2 == 1) {
                    statePause2 = 0;
                    //Firebase.setString(firebaseDate, path + "/btnPause2", 0);
                    statePauseBool = true;

                    setServoTB();

                    now = rtc.now();
                    minutesPause = now.minute();
                    hourPause = now.hour();
                    dayPause = now.day();

                    tempTimePause = (((dayPause*24)*60) + (hourPause*60) + minutesPause);
                    //Serial.println("In thoi gian pause:");
                    //Serial.println(tempTimeStart);

                    while (statePauseBool == true) {
                        libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, SH110X_WHITE);
                        libolei2c.display.display();

                        // if(Firebase.getString(firebaseDate, path + "/btnPause2")) y = firebaseDate.stringData();
                        // e = y.toInt();
                        // //Serial.println(e);
                        if(statePause2 == 1) {
                            statePauseTest2 = 0;
                            statePause2 = 0;
                            //Firebase.setString(firebaseDate, path + "/btnPause2", 0);
                            break;
                        }

                        // if(Firebase.getString(firebaseDate, path + "/btnStop2")) z = firebaseDate.stringData();
                        // h = z.toInt();
                        // //Serial.println(h);
                        if(stateStop2 == 1) {
                            statePauseTest2 = 0;
                            stateStartTest2 = 7;
                            stateStop2 = 0;
                            //Firebase.setString(firebaseDate, path + "/btnStop2", 0);
                            break;
                        }

                        while (digitalRead(SW) == 0) {
                            if(millis() - lastTimeF > 300) {
                                statePauseBool = false;
                                statePauseTest2 = 0;
                                stateStartTest2++;
                                Serial.println(stateStartTest2);
                                lastTimeF = millis();
                            }
                        }
                    }
                    libolei2c.display.drawBitmap(115, 0, logo16_glcd_bmp, 12, 14, 0);
                    libolei2c.display.display();
          
                }
                if (stateStartTest2 > 5) {
                    break;
                }
            }
            setServoTB();
        } else if (stateStartTest2 > 5) {
            stateMH = 0;
            break;
        }
    }
}