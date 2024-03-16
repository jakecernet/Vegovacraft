#include <Arduino.h>
#include <Preferences.h>

Preferences preferences;

RTC_DATA_ATTR int reset_stevec = 0;

esp_sleep_wakeup_cause_t razlogBujenja() {
    auto razlog = esp_sleep_get_wakeup_cause();

    switch (razlog) {
    case ESP_SLEEP_WAKEUP_TIMER:
        Serial.println("bujenje iz spanja zaradi šasovnika");
        break;
    case ESP_SLEEP_WAKEUP_GPIO:
        Serial.println("bujenje iz spanja zaradi GPIO");
        break;
    case ESP_SLEEP_WAKEUP_ULP:
        Serial.println("bujenje iz spanja zaradi ULP");
        break;
    default:
        Serial.println("bujenje iz spanja zaradi neznanega razloga");
        break;
    }
    return razlog;
}

int reset_po_n_sekundah = 0;

void setup() {
    Serial.begin(921600);
    Serial.printf("število resetov: %d\n", reset_stevec);
    reset_stevec++;

    preferences.begin("aplikacija");
    if (preferences.isKey("nastavitev")) {
        Serial.println("beremo ključe");
        reset_po_n_sekundah = preferences.getInt("nastavitev", -1);
        Serial.printf("resetirali bomo po %d sekundah\n", reset_po_n_sekundah);
    } else {
        Serial.println("brišem vse ključe");
        preferences.clear();
        preferences.putInt("nastavitev", 20);
    }
    preferences.end();

    /* esp_sleep_enable_timer_wakeup(10 * 1e6);
    Serial.println("spanje");
    esp_deep_sleep_start(); */
}

int i;

void loop() {
    Serial.printf("i je sedaj %d\n", i++);
    if (i > 20){
        esp_restart();
    }
    esp_sleep_enable_timer_wakeup(1e6);
    esp_light_sleep_start();
}