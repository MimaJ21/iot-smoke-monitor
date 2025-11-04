# IoT Smoke Monitor

Projekt pre ESP32, ktorý monitoruje teplotu, vlhkosť a zadymenie v miestnosti. Dáta sú zobrazované na OLED displeji, publikované na ThingSpeak a pri zadymení sa aktivuje bzučiak + IFTTT webhook.

## Použité komponenty
- ESP32
- DHT11 (teplota, vlhkosť)
- MQ2 (dym)
- OLED 128x32 (I2C)
- Pasívny bzučiak (nastavený na 2 kHz)

## Zapojenie komponentov

| Komponent         | Pin ESP32 | Popis              |
|-------------------|-----------|--------------------|
| DHT11             | GPIO 15   | Digitálny výstup   |
| MQ2               | GPIO 34   | Analógový výstup   |
| OLED 128x32       | GPIO 21   | SDA (I2C dátový)   |
| OLED 128x32       | GPIO 22   | SCL (I2C hodinový) |
| Pasívny bzučiak   | GPIO 13   | PWM výstup (2 kHz) |

> Napájanie OLED, DHT11 a MQ2 senzora je možné z 3.3 V alebo 5 V výstupu ESP32 podľa typu modulu.

## Funkcie
- Webový server s aktuálnymi údajmi
- Zasielanie dát na ThingSpeak
- Webhook na IFTTT pri zadymení ≥ 10 %
- OLED displej s údajmi
- Zvuková signalizácia pomocou pasívneho bzučiaka

## Inštalácia
1. Nahraj kód do ESP32 cez Arduino IDE
2. Vytvor `config.h` podľa `config_example.h` a doplň svoje údaje
3. Pripoj senzory podľa tabuľky vyššie
4. Spusti a sleduj výstupy na OLED a webovej stránke

## Autor
M. Jamrichová