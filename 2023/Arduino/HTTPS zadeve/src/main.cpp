#include <Arduino.h>
#include <HTTPClient.h>
#include <WiFi.h>

char url[] = "https://worldtimeapi.org/api/ip.txt";
HTTPClient http;
bool once = true;

void setup() {
    Serial.begin(921600);
    Serial.printf("SSID: %s\n", WIFI_DEFAULT_SSID);
    Serial.printf("PASS: %s\n", WIFI_DEFAULT_PASSWORD);

    WiFi.begin(WIFI_DEFAULT_SSID, WIFI_DEFAULT_PASSWORD);
}

WiFiClient *stream;

void loop() {
    if (WiFi.isConnected() && once) {
        Serial.println("Connected to WiFi");

        http.begin(url);
        int statusCode = http.GET();
        log_i("Status code: %d\n", statusCode);

        stream = http.getStreamPtr();
        int read = 0;
        int size = http.getSize();
        while (1) {
            if (read < size) {
                int a = stream->read();
                if (a >= 0) {
                    Serial.write(char(a));
                    read++;
                }
            }
            if (read == http.getSize()) {
                Serial.println("Done");
                break;
            }
        }

        http.end();
        once = false;
        Serial.printf("Bytes read: %d\n", read);
        Serial.printf("HTTP response size: %d\n", size);
    }
    delay(1);
}