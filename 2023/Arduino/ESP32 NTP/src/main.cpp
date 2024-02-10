#include <Arduino.h>
#include <WiFi.h>
#include <esp_sntp.h>

void izpisiCas();

void obSinhronizaciji(struct timeval *tv) {

    Serial.println("Sinhronizacija uspela");
    Serial.printf("");
    izpisiCas();
}

void izpisiCas() {
    tm *ura;
    time_t cas = time(nullptr);
    ura = localtime(&cas);

    Serial.printf("Ura je: %02d. %02d. %02d  %02d:%02d:%02d\n", ura->tm_mday, ura->tm_mon + 1, ura->tm_year + 1900, ura->tm_hour, ura->tm_min, ura->tm_sec);
}

void setup() {
    Serial.begin(921600);
    WiFi.begin(WIFI_DEFAULT_SSID, WIFI_DEFAULT_PASSWORD);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
    Serial.printf("SSID: %s, password: %s", WIFI_DEFAULT_SSID, WIFI_DEFAULT_PASSWORD);

    setenv("TZ", "CET-1CEST,M3.5.0,M10.5.0/3", 1);
    tzset();

    esp_sntp_setservername(0, "nether.mojvegovc.si");
    log_i("privzeti sinhronizacijski interval: %d", esp_sntp_get_sync_interval());
    esp_sntp_set_sync_mode(SNTP_SYNC_MODE_SMOOTH);
    esp_sntp_set_time_sync_notification_cb(obSinhronizaciji);
    esp_sntp_init();
}

void loop() {
    time_t cas;
    cas = 0;
    time(&cas);
    Serial.printf("Ura je: %s", ctime(&cas));

    delay(1000);
}