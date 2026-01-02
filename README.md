# IoT Monitor zadymenia / IoT Smoke Monitor

## Popis / Description
**Slovensky:**  
Projekt pre ESP32, ktorý monitoruje teplotu, vlhkosť a zadymenie v miestnosti. Dáta sú zobrazované na OLED displeji, zhromažďované a publikované na ThingSpeak. Pri zadymení sa aktivuje bzučiak a odošle sa IFTTT webhook.  

**English:**  
Project for ESP32 that monitors temperature, humidity, and smoke levels in a room. Data are displayed on an OLED screen, collected and published to ThingSpeak. When smoke is detected, a buzzer is activated and an IFTTT webhook is triggered.  

---

## Použité komponenty / Components
- ESP32  
- DHT11 (teplota, vlhkosť / temperature, humidity)  
- MQ2 (dym / smoke)  
- OLED 128x32 (I2C)  
- Pasívny bzučiak / passive buzzer (nastavený na 2kHz / set to 2 kHz)  

---

## Zapojenie komponentov / Wiring

| Komponent / Component | Pin ESP32 | Popis / Description |
|-----------------------|-----------|---------------------|
| DHT11                 | GPIO 15   | Digitálny výstup / Digital output |
| MQ2                   | GPIO 34   | Analógový výstup / Analog output |
| OLED 128x32           | GPIO 21   | SDA (I2C dátový / data) |
| OLED 128x32           | GPIO 22   | SCL (I2C hodinový / clock) |
| Pasívny bzučiak / Passive buzzer | GPIO 13 | PWM výstup (2 kHz) / PWM output (2 kHz) |

> **Poznámka / Note:** Napájanie OLED, DHT11 a MQ2 senzora je možné z 3.3 V alebo 5 V výstupu ESP32 podľa typu modulu.  
> Power supply for OLED, DHT11, and MQ2 sensor can be from 3.3 V or 5 V ESP32 output depending on module type.  

---

## Funkcie / Features
- Webový server s aktuálnymi údajmi / Web server with live data  
- Zasielanie dát na ThingSpeak / Data publishing to ThingSpeak  
- Webhook na IFTTT pri zadymení ≥ 10 % / IFTTT webhook when smoke ≥ 10%  
- OLED displej s údajmi / OLED display with data  
- Zvuková signalizácia pomocou pasívneho bzučiaka / Acoustic alarm via passive buzzer  

---

## Inštalácia / Installation
1. Nahraj kód do ESP32 cez Arduino IDE  
   Upload the code to ESP32 via Arduino IDE  
2. Doplň svoje údaje do `config.h` .
   Add your credentials to `config.h` .
3. Pripoj senzory podľa tabuľky vyššie  
   Connect sensors according to the table above  
4. Spusti a sleduj výstupy na OLED a webovej stránke  
   Run and monitor outputs on OLED and web interface  

---

## Screenshoty / Screenshots
**Slovensky:** Ukážky aplikácie, zapojenia a výstupov.  
**English:** Application, wiring, and output previews.  

[Poster-AirMonitoringSystem.jpg](images/Poster-AirMonitoringSystem.jpg)  
[01_IoT_AirMonitoringSystem.jpg](images/01_IoT_AirMonitoringSystem.jpg)  
[02_Schematic.jpg](images/02_Schematic.jpg)  
[03_DisplayScreen.jpg](images/03_DisplayScreen.jpg)  
[04_ESP32-NODEMCU-ESP-32S-pinout.jpg](images/04_ESP32-NODEMCU-ESP-32S-pinout.jpg)  
[05_ThingSpeak_DataCollection.jpg](images/05_ThingSpeak_DataCollection.jpg)  
[06_IFTTTapplet.jpg](images/06_IFTTTapplet.jpg)  
[07_SmokeAlert-EmailMessage.jpg](images/07_SmokeAlert-EmailMessage.jpg)  

---

## Autor / Author
M. Jamrichová



