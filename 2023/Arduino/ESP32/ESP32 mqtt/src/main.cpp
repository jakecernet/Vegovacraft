#include <Arduino.h>
#include <WiFi.h>
#include <mqtt_client.h>

esp_mqtt_client_config_t konfiguracja;
esp_mqtt_client_handle_t klient;

void kajDogaja(void *event_handler_arg, esp_event_base_t event_base, int32_t event_id, void *event_data) {
    esp_mqtt_event_handle_t dogodek = (esp_mqtt_event_handle_t)event_data;
    esp_mqtt_client_handle_t klient = dogodek->client;
    esp_mqtt_event_id_t idDogodka = (esp_mqtt_event_id_t)event_id;

    switch (idDogodka) {
    case MQTT_EVENT_CONNECTED:
        log_i("uspešno povezan");
        break;
    case MQTT_EVENT_DATA:
        Serial.printf("Tema: %.*s, Sporočilo: %.*s\n", dogodek->topic_len, dogodek->topic, dogodek->data_len, dogodek->data);
        break;
    default:
        Serial.println("something happened");
        break;
    }
}

void setup() {
    WiFi.begin(WIFI_DEFAULT_SSID, WIFI_DEFAULT_PASSWORD);
    Serial.begin(921600);
    delay(5000);

    // konfiguracja klienta MQTT
    konfiguracja.client_id = "crnijevESP32";
    konfiguracja.host = "nether.mojvegovc.si";
    konfiguracja.port = 1883;
    konfiguracja.username = "VegovaLjubljana";
    konfiguracja.password = "RSOv";
    konfiguracja.lwt_msg = "crnijevESP32 je umrčkal";
    konfiguracja.lwt_topic = "banana";
    konfiguracja.lwt_retain = true;
    konfiguracja.lwt_msg_len = strlen(konfiguracja.lwt_msg);

    // povezava na MQTT strežnik
    klient = esp_mqtt_client_init(&konfiguracja);
    bool clientStarted = esp_mqtt_client_start(klient);

    // error handler
    esp_mqtt_client_register_event(klient, MQTT_EVENT_ANY, kajDogaja, NULL);

    char message[] = "rnijevESP32 je živ";
    esp_mqtt_client_publish(klient, "banana", message, strlen(message), 0, 1);

    esp_mqtt_client_subscribe(klient, "banana", 0);
}

void loop() {
}