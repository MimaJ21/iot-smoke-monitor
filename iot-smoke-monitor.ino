#include <WiFi.h>
#include <WebServer.h>
#include <DHT.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <time.h>
#include <HTTPClient.h>
#include "config.h"

// OLED 128x32
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Senzory a výstupy
#define DHTPIN 15
#define DHTTYPE DHT11
#define MQ2PIN 34
#define BUZZERPIN 13

DHT dht(DHTPIN, DHTTYPE);
WebServer server(80);

// Stavová premenná pre webhook
bool webhookSent = false;

String getFormattedTime() {
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    return "Neznámy čas";
  }
  char buffer[30];
  strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", &timeinfo);
  return String(buffer);
}

void handleRoot() {
  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int smokeRaw = analogRead(MQ2PIN);
  float smokePercent = map(smokeRaw, 0, 4095, 0, 100);
  String currentTime = getFormattedTime();

  String html = "<!DOCTYPE html><html><head><meta charset='UTF-8'>";
  html += "<meta http-equiv='refresh' content='5'>";
  html += "<title>Monitor</title>";
  html += "<style>body { font-family: Arial; text-align: center; }</style></head><body>";
  html += "<h1>Stav miestnosti</h1>";
  html += "<p>Teplota: " + String(temp, 2) + "&deg;C</p>";
  html += "<p>Vlhkosť: " + String(hum, 0) + "%</p>";
  html += "<p>Dym: " + String(smokePercent, 2) + "%</p>";
  html += "<p style='margin-top:30px; font-size:14px;'>Posledná aktualizácia: " + currentTime + "</p>";
  html += "</body></html>";

  server.send(200, "text/html", html);
}

void sendToThingSpeak(float temp, float hum, float smoke) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    String url = String(THINGSPEAK_URL) + "?api_key=" + THINGSPEAK_API_KEY +
                 "&field1=" + String(temp, 2) +
                 "&field2=" + String(hum, 0) +
                 "&field3=" + String(smoke, 2);
    http.begin(url);
    http.GET();
    http.end();
  }
}

void sendIFTTTWebhook(float smokePercent) {
  String wifiStatus = (WiFi.status() == WL_CONNECTED) ? "Pripojené / Connected" : "Odpojené / Disconnected";
  String timestamp = getFormattedTime();

  HTTPClient webhook;
  webhook.begin(IFTTT_WEBHOOK_URL);
  webhook.addHeader("Content-Type", "application/json");

  String json = "{\"value1\":\"" + String(smokePercent, 2) + "\"," +
                "\"value2\":\"Wi-Fi: " + wifiStatus + "\\nThingSpeak: " + timestamp + "\"," +
                "\"value3\":\"Webhook odoslaný / sent at " + timestamp + "\"}";
  int code = webhook.POST(json);
  Serial.println("Webhook odoslaný, kód: " + String(code));
  webhook.end();
}

void setup() {
  Serial.begin(115200);
  dht.begin();
  pinMode(BUZZERPIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED chyba");
    while (true);
  }
  display.clearDisplay();
  display.display();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Pripájam sa na WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi pripojené");

  configTime(3600, 0, "pool.ntp.org", "time.nist.gov");

  server.on("/", handleRoot);
  server.begin();
}

void loop() {
  server.handleClient();

  float temp = dht.readTemperature();
  float hum = dht.readHumidity();
  int smokeRaw = analogRead(MQ2PIN);
  float smokePercent = map(smokeRaw, 0, 4095, 0, 100);

  if (smokePercent >= 10) {
    for (int i = 0; i < 3; i++) {
      tone(BUZZERPIN, 2000);
      delay(1000);
      noTone(BUZZERPIN);
      delay(500);
    }

    if (!webhookSent) {
      sendIFTTTWebhook(smokePercent);
      webhookSent = true;
    }
  } else {
    noTone(BUZZERPIN);
    webhookSent = false;
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.print("T: ");
  display.print(temp, 2);
  display.print("C  H: ");
  display.print(hum, 0);
  display.print("%");

  display.setCursor(0, 12);
  display.print("Dym: ");
  display.print(smokePercent, 2);
  display.print("%");

  display.setCursor(0, 24);
  display.print("IoT - M. JAMRICHOVA");

  display.display();

  sendToThingSpeak(temp, hum, smokePercent);

  delay(20000);
}