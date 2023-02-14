#ifndef LIB_WIFI   
#define LIB_WIFI

#include <WiFi.h>
#include <FirebaseESP32.h>


class LibWiFi
{
private:
    /* data */
    String path = "/";

    FirebaseData firebaseDate;
public:
    LibWiFi(/* args */);
    void setupWiFi(const char* WIFI_SSID, const char* WIFI_PASSWORD);
    void setupFB(String FIREBASE_HOST, String FIREBASE_AUTH);
    
    // send data to firebase
    void sendStrdata(String keyFB, String data);
    void sendIntdata(String keyFB, int data);
    void sendFloatdata(String keyFB, float data);

    // give data to firebase
    int32_t getIntdata(String keyFB);
    String getStrdata(String keyFB);
    float_t getFloatdata(String keyFB);

    
};

// LibWiFi::LibWiFi(/* args */)
// {
// }

// LibWiFi::~LibWiFi()
// {
// }


#endif