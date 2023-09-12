/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-08     WangShun     first version
 */

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <ezButton.h>

#define LED A5
#define SCREEN_ADDRESS 0x3c
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define BLACK SH110X_BLACK
#define WHITE SH110X_WHITE

#define BUTTON_PIN A1

Adafruit_SH1106G display = Adafruit_SH1106G(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
ezButton button(BUTTON_PIN);

void setup(void) {
    pinMode(LED, OUTPUT);
    Serial.begin(115200);

    /// Start I2C communication
    if (!display.begin(SCREEN_ADDRESS)) {
        Serial.println(F("SH110X allocation failed"));
        for (;;)
            ;  // Don't proceed, loop forever
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println("WELCOME!");
    display.display();

    button.setDebounceTime(50);
}

void loop(void) {
//    digitalWrite(LED, !digitalRead(LED));
//    delay(100);
    button.loop();

    if (button.isPressed()) {
        Serial.println("Button pressed :D");
    }
}
