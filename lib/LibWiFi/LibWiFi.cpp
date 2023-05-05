#include <LibWiFi.h>

LibWiFi::LibWiFi(){}
bool LibWiFi::checkConnect() {
    if (WiFi.status() == WL_CONNECTED) return true;
    return false;
}

void LibWiFi::setupWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD) {
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    uint8_t x = 0;
    while(WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        x++;
        if(x == 15) {
            Serial.println("Disconnect");
            break; 
        }
        delay(300);
    }
    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connection");
    }
}

void LibWiFi::setupFB(String FIREBASE_AUTH, String FIREBASE_HOST) {
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);
    if(!Firebase.beginStream(firebaseDate, path)) {
        Serial.println("Reason: "+firebaseDate.errorReason());
        Serial.println();
    }
}

void LibWiFi::sendStrdata(String keyFB, String data) {
    Firebase.setString(firebaseDate, path + keyFB, data);
}

void LibWiFi::sendIntdata(String keyFB, int data) {
    Firebase.setInt(firebaseDate, path + keyFB, data);
}

void LibWiFi::sendFloatdata(String keyFB, float data) {
    Firebase.setFloat(firebaseDate, path + keyFB, data);
}

int32_t LibWiFi::getIntdata(String keyFB) {
    int32_t x;
    if(Firebase.getInt(firebaseDate, path + keyFB)) x = firebaseDate.intData();
    return x;
}

String LibWiFi::getStrdata(String keyFB) {
    static String temp = "";
    if(Firebase.getString(firebaseDate, path + keyFB)) {
        temp = firebaseDate.stringData();
    }
    return temp;
}

float_t LibWiFi::getFloatdata(String keyFB) {
    float_t x;
    if(Firebase.getFloat(firebaseDate, path + keyFB)) x = firebaseDate.floatData();
    return x;
}

