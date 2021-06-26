#include <ESP8266WiFi.h>
#include <NTPClient.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Arduino_JSON.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Fonts/FreeSansBoldOblique9pt7b.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET     -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//=========================================================================================================================================================================================
static const uint8_t image_data_humidity[32] = {
    0x00, 0x00, 
    0x01, 0x00, 
    0x01, 0x80, 
    0x03, 0x80, 
    0x03, 0xc0, 
    0x07, 0xc0, 
    0x0f, 0xe0, 
    0x0f, 0xe0, 
    0x19, 0x70, 
    0x19, 0x78, 
    0x3e, 0xf8, 
    0x3d, 0x18, 
    0x1d, 0xb8, 
    0x1f, 0xf0, 
    0x0f, 0xe0, 
    0x03, 0x80
};
static const uint8_t image_data_windspeed[42] = {
    0x00, 0x00, 0x00, 
    0x01, 0xe0, 0x00, 
    0x01, 0x20, 0x00, 
    0x00, 0x26, 0x00, 
    0x00, 0x6d, 0x00, 
    0x3f, 0x81, 0x00, 
    0x00, 0x01, 0x00, 
    0x7f, 0xff, 0x00, 
    0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 
    0x0f, 0xfc, 0x00, 
    0x00, 0x04, 0x00, 
    0x00, 0x1c, 0x00, 
    0x00, 0x00, 0x00
};

static const uint8_t image_data_sun[200] = {
    0x00, 0x00, 0x18, 0x00, 0x00, 
    0x00, 0x00, 0x3c, 0x00, 0x00, 
    0x00, 0x00, 0x3c, 0x00, 0x00, 
    0x00, 0x70, 0x3c, 0x0e, 0x00, 
    0x00, 0x78, 0x3c, 0x1e, 0x00, 
    0x00, 0x78, 0x3c, 0x1e, 0x00, 
    0x00, 0x3c, 0x3c, 0x3c, 0x00, 
    0x00, 0x3e, 0x3c, 0x3c, 0x00, 
    0x00, 0x1e, 0x00, 0x78, 0x00, 
    0x18, 0x0e, 0x00, 0x70, 0x18, 
    0x3c, 0x00, 0x7e, 0x00, 0x3c, 
    0x3f, 0x01, 0xff, 0x80, 0xfc, 
    0x1f, 0xc7, 0xff, 0xe3, 0xf8, 
    0x07, 0xcf, 0xff, 0xf3, 0xe0, 
    0x03, 0xdf, 0xff, 0xfb, 0xc0, 
    0x00, 0x1f, 0xff, 0xf8, 0x00, 
    0x00, 0x3f, 0xff, 0xfc, 0x00, 
    0x00, 0x3f, 0xff, 0xfc, 0x00, 
    0x00, 0x3f, 0xff, 0xfc, 0x00, 
    0xff, 0x3f, 0xff, 0xfc, 0xff, 
    0xff, 0x3f, 0xff, 0xfc, 0xff, 
    0xff, 0x3f, 0xff, 0xfc, 0xff, 
    0x00, 0x3f, 0xff, 0xfc, 0x00, 
    0x00, 0x3f, 0xff, 0xfc, 0x00, 
    0x00, 0x1f, 0xff, 0xfc, 0x00, 
    0x01, 0x9f, 0xff, 0xf9, 0x80, 
    0x07, 0xcf, 0xff, 0xf3, 0xe0, 
    0x0f, 0xc7, 0xff, 0xe3, 0xf0, 
    0x3f, 0x83, 0xff, 0xc1, 0xfc, 
    0x3e, 0x00, 0xff, 0x00, 0x7c, 
    0x18, 0x0c, 0x00, 0x30, 0x18, 
    0x00, 0x1e, 0x00, 0x78, 0x00, 
    0x00, 0x1e, 0x3c, 0x78, 0x00, 
    0x00, 0x3c, 0x3c, 0x3c, 0x00, 
    0x00, 0x3c, 0x3c, 0x3e, 0x00, 
    0x00, 0x78, 0x3c, 0x1e, 0x00, 
    0x00, 0x70, 0x3c, 0x0e, 0x00, 
    0x00, 0x30, 0x3c, 0x0c, 0x00, 
    0x00, 0x00, 0x3c, 0x00, 0x00, 
    0x00, 0x00, 0x3c, 0x00, 0x00
};

static const uint8_t image_data_sun_fewcloud[200] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 0x00, 
    0x00, 0x00, 0xc0, 0x00, 0x00, 
    0x03, 0x00, 0xc0, 0x00, 0x00, 
    0x03, 0x81, 0xc0, 0x00, 0x00, 
    0x03, 0x81, 0xc0, 0x00, 0x00, 
    0x01, 0xc1, 0x80, 0x00, 0x00, 
    0x00, 0xc0, 0x00, 0x60, 0x00, 
    0x00, 0x0f, 0x81, 0xe0, 0x00, 
    0x00, 0x3f, 0xe3, 0xc0, 0x00, 
    0x00, 0x7f, 0xf3, 0x00, 0x00, 
    0x00, 0xff, 0xf8, 0x00, 0x00, 
    0xf8, 0xff, 0xf8, 0x00, 0x00, 
    0xfd, 0xff, 0xf8, 0x00, 0x00, 
    0x09, 0xff, 0xf8, 0xf0, 0x00, 
    0x01, 0xff, 0xfb, 0xfc, 0x00, 
    0x01, 0xff, 0xf7, 0xfe, 0x00, 
    0x01, 0xff, 0xef, 0xff, 0x00, 
    0x00, 0xfc, 0x1f, 0xff, 0x80, 
    0x00, 0xf3, 0xff, 0xff, 0x80, 
    0x06, 0x6f, 0xff, 0xff, 0xc0, 
    0x1e, 0x0f, 0xff, 0xff, 0xf0, 
    0x3c, 0x1f, 0xff, 0xff, 0xfc, 
    0x30, 0x1f, 0xff, 0xff, 0xfe, 
    0x00, 0x7f, 0xff, 0xff, 0xfe, 
    0x01, 0xff, 0xff, 0xff, 0xff, 
    0x03, 0xff, 0xff, 0xff, 0xff, 
    0x03, 0xff, 0xff, 0xff, 0xff, 
    0x03, 0xff, 0xff, 0xff, 0xff, 
    0x03, 0xff, 0xff, 0xff, 0xff, 
    0x03, 0xff, 0xff, 0xff, 0xff, 
    0x03, 0xff, 0xff, 0xff, 0xfe, 
    0x03, 0xff, 0xff, 0xff, 0xfe, 
    0x01, 0xff, 0xff, 0xff, 0xf8, 
    0x00, 0x7f, 0xff, 0xff, 0xf0, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t image_data_thunder[200] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x07, 0xfc, 0x00, 0x00, 
    0x00, 0x1f, 0xff, 0x00, 0x00, 
    0x00, 0x3f, 0xff, 0x80, 0x00, 
    0x00, 0x7f, 0xff, 0xc0, 0x00, 
    0x00, 0xff, 0xff, 0xc0, 0x00, 
    0x00, 0xff, 0xff, 0xe0, 0x00, 
    0x00, 0x0f, 0xff, 0xec, 0x00, 
    0x07, 0xf7, 0xff, 0xe7, 0x00, 
    0x0f, 0xff, 0xff, 0xf7, 0xc0, 
    0x1f, 0xff, 0xff, 0xff, 0xc0, 
    0x3f, 0xff, 0xff, 0xff, 0xe0, 
    0x3f, 0xff, 0xff, 0xff, 0xe0, 
    0x3f, 0xff, 0xff, 0xff, 0xe0, 
    0x3f, 0xff, 0xff, 0xff, 0xe0, 
    0x3f, 0xff, 0xff, 0xff, 0x80, 
    0x3f, 0xff, 0xff, 0xff, 0x3c, 
    0x3f, 0xff, 0xff, 0xff, 0xfc, 
    0x1f, 0xff, 0xff, 0xff, 0xfe, 
    0x1f, 0xff, 0xff, 0xff, 0xfe, 
    0x0f, 0xff, 0xff, 0xff, 0xfc, 
    0x03, 0xff, 0xff, 0xff, 0xf8, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x01, 0x18, 0x3e, 0x0c, 0x60, 
    0x03, 0x98, 0x3e, 0x0c, 0xe0, 
    0x03, 0xb8, 0x7c, 0x1c, 0xe0, 
    0x07, 0x30, 0x78, 0x1d, 0xc0, 
    0x07, 0x70, 0xff, 0x19, 0xc0, 
    0x07, 0x70, 0xff, 0x39, 0xc0, 
    0x0e, 0x61, 0xff, 0x3b, 0x80, 
    0x0e, 0xe1, 0xfe, 0x33, 0x80, 
    0x0c, 0xe0, 0x3c, 0x73, 0x00, 
    0x0c, 0xc0, 0x38, 0x73, 0x00, 
    0x01, 0xc0, 0x70, 0x60, 0x00, 
    0x01, 0xc0, 0xe0, 0xe0, 0x00, 
    0x01, 0x80, 0xc0, 0xe0, 0x00, 
    0x00, 0x01, 0x80, 0x00, 0x00, 
    0x00, 0x01, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t image_data_cloudy[200] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0xf8, 0x00, 
    0x00, 0x00, 0x01, 0xff, 0x00, 
    0x00, 0x00, 0x03, 0xff, 0xc0, 
    0x00, 0x00, 0x03, 0xff, 0xe0, 
    0x00, 0x0f, 0xc3, 0xff, 0xf0, 
    0x00, 0x3f, 0xf3, 0xff, 0xf8, 
    0x00, 0xff, 0xfc, 0x01, 0xfc, 
    0x01, 0xff, 0xfe, 0xfc, 0xfc, 
    0x01, 0xff, 0xff, 0xff, 0x3c, 
    0x03, 0xff, 0xff, 0xff, 0x98, 
    0x03, 0xff, 0xff, 0xff, 0xd0, 
    0x07, 0xff, 0xff, 0xff, 0xc0, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x1f, 0xff, 0xff, 0xff, 0xf8, 
    0x3f, 0xff, 0xff, 0xff, 0xfc, 
    0x3f, 0xff, 0xff, 0xff, 0xfc, 
    0x7f, 0xff, 0xff, 0xff, 0xfe, 
    0x7f, 0xff, 0xff, 0xff, 0xfe, 
    0x7f, 0x07, 0xff, 0xff, 0xfe, 
    0x7e, 0x78, 0x7f, 0xff, 0xfe, 
    0x7d, 0xff, 0x3f, 0xff, 0xfe, 
    0x79, 0xff, 0xdf, 0xff, 0xfe, 
    0x3b, 0xff, 0xe7, 0xff, 0xfc, 
    0x33, 0xff, 0xf3, 0xff, 0xfc, 
    0x0f, 0xff, 0xf9, 0xff, 0xf8, 
    0x0f, 0xff, 0xfd, 0xff, 0xe0, 
    0x0f, 0xff, 0xfc, 0x00, 0x00, 
    0x0f, 0xff, 0xfc, 0x00, 0x00, 
    0x0f, 0xff, 0xfc, 0x00, 0x00, 
    0x07, 0xff, 0xf8, 0x00, 0x00, 
    0x01, 0xff, 0xe0, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00
};

static const uint8_t image_data_moon[200] = {
    0x00, 0x38, 0x00, 0x00, 0x00, 
    0x00, 0x7c, 0x00, 0x00, 0x00, 
    0x01, 0xf8, 0x00, 0x00, 0x00, 
    0x01, 0xf8, 0x00, 0x00, 0x40, 
    0x07, 0xf8, 0x08, 0x01, 0xc0, 
    0x0f, 0xf0, 0x08, 0x00, 0xc0, 
    0x0f, 0xf0, 0x1f, 0x00, 0x80, 
    0x1f, 0xf0, 0x3e, 0x00, 0x00, 
    0x3f, 0xe0, 0x0c, 0x00, 0x00, 
    0x3f, 0xe0, 0x04, 0x00, 0x00, 
    0x3f, 0xe0, 0x00, 0x00, 0x00, 
    0x7f, 0xe0, 0x00, 0x00, 0x00, 
    0x7f, 0xf0, 0x00, 0x00, 0x00, 
    0xff, 0xf0, 0x00, 0x00, 0x00, 
    0xff, 0xf0, 0x00, 0x00, 0x00, 
    0xff, 0xf0, 0x00, 0x00, 0x00, 
    0xff, 0xf8, 0x00, 0xc6, 0x00, 
    0xff, 0xf8, 0x00, 0x7c, 0x00, 
    0xff, 0xf8, 0x00, 0x7c, 0x00, 
    0xff, 0xfc, 0x00, 0x3c, 0x00, 
    0xff, 0xfe, 0x00, 0x3e, 0x00, 
    0xff, 0xfe, 0x00, 0x62, 0x00, 
    0xff, 0xff, 0x00, 0x40, 0x00, 
    0xff, 0xff, 0x80, 0x00, 0x00, 
    0xff, 0xff, 0xc0, 0x00, 0x00, 
    0x7f, 0xff, 0xf0, 0x00, 0x00, 
    0x7f, 0xff, 0xf8, 0x00, 0x02, 
    0x3f, 0xff, 0xff, 0x00, 0x1f, 
    0x3f, 0xff, 0xff, 0xe0, 0xff, 
    0x3f, 0xff, 0xff, 0xff, 0xff, 
    0x1f, 0xff, 0xff, 0xff, 0xfe, 
    0x0f, 0xff, 0xff, 0xff, 0xfc, 
    0x0f, 0xff, 0xff, 0xff, 0xfc, 
    0x07, 0xff, 0xff, 0xff, 0xf8, 
    0x03, 0xff, 0xff, 0xff, 0xf0, 
    0x01, 0xff, 0xff, 0xff, 0xe0, 
    0x00, 0x7f, 0xff, 0xff, 0x80, 
    0x00, 0x3f, 0xff, 0xff, 0x00, 
    0x00, 0x07, 0xff, 0xfc, 0x00, 
    0x00, 0x01, 0xff, 0xe0, 0x00
};
static const uint8_t image_data_moon_fewcloud[200] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x08, 0x00, 0x00, 
    0x00, 0x00, 0x0e, 0x00, 0x00, 
    0x00, 0x00, 0x0f, 0x00, 0x00, 
    0x00, 0x00, 0x07, 0x00, 0x00, 
    0x00, 0x00, 0x0f, 0x80, 0x00, 
    0x00, 0x00, 0x0f, 0x80, 0x00, 
    0x00, 0x00, 0x0f, 0xc0, 0x00, 
    0x00, 0x00, 0x0f, 0xc0, 0x00, 
    0x00, 0x00, 0x1f, 0xc0, 0x00, 
    0x00, 0x00, 0x1f, 0xc0, 0x00, 
    0x00, 0x00, 0x3f, 0xc0, 0x00, 
    0x00, 0x00, 0x7f, 0xc0, 0x00, 
    0x00, 0x00, 0xff, 0x80, 0x00, 
    0x00, 0x03, 0xff, 0x80, 0x00, 
    0x00, 0x0f, 0xf0, 0x00, 0x00, 
    0x00, 0xff, 0xe7, 0xc0, 0x00, 
    0x00, 0xff, 0xcf, 0xe0, 0x00, 
    0x00, 0x3f, 0x9f, 0xf0, 0x00, 
    0x00, 0x0f, 0x1f, 0xf0, 0x00, 
    0x00, 0x00, 0xff, 0xfe, 0x00, 
    0x00, 0x00, 0xff, 0xff, 0x00, 
    0x00, 0x00, 0xff, 0xff, 0x00, 
    0x00, 0x00, 0xff, 0xfe, 0x00, 
    0x00, 0x00, 0xff, 0xff, 0xc0, 
    0x00, 0x00, 0x7f, 0xff, 0xc0, 
    0x00, 0x00, 0x1f, 0xff, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00
};
static const uint8_t image_data_rain[200] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x1f, 0x80, 0x00, 
    0x00, 0x00, 0x3f, 0xe0, 0x00, 
    0x00, 0x00, 0x60, 0x70, 0x00, 
    0x00, 0x00, 0xc6, 0x30, 0x00, 
    0x00, 0x1f, 0xff, 0xf8, 0x00, 
    0x00, 0x3f, 0xff, 0xf8, 0x00, 
    0x00, 0x73, 0xff, 0xf8, 0x00, 
    0x00, 0xe7, 0xff, 0xff, 0x00, 
    0x00, 0xcf, 0xff, 0xff, 0x80, 
    0x00, 0xdf, 0xff, 0xf9, 0xc0, 
    0x00, 0xff, 0xff, 0xfc, 0xe0, 
    0x01, 0xff, 0xff, 0xfe, 0x60, 
    0x03, 0xff, 0xff, 0xff, 0x60, 
    0x07, 0xff, 0xff, 0xff, 0x60, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xff, 0xe0, 
    0x07, 0xff, 0xff, 0xff, 0xc0, 
    0x03, 0xff, 0xff, 0xff, 0x80, 
    0x01, 0xff, 0xff, 0xff, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x60, 0x08, 0x02, 0x00, 
    0x00, 0x60, 0x18, 0x06, 0x00, 
    0x00, 0xf0, 0x3c, 0x07, 0x00, 
    0x00, 0xf0, 0x3c, 0x0f, 0x00, 
    0x00, 0xf2, 0x3c, 0x4f, 0x00, 
    0x00, 0x63, 0x18, 0xc6, 0x00, 
    0x00, 0x07, 0x81, 0xe0, 0x00, 
    0x00, 0x07, 0x81, 0xe0, 0x00, 
    0x00, 0x07, 0x81, 0xe0, 0x00, 
    0x00, 0x03, 0x00, 0xc0, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00
};


//=========================================================================================================================================================================================

String get_data(String link);
String getDate();
void drawIcon();

const char *ssid     = "Abhi's wifi";
const char *password = "zappp10000";

const long utcOffsetInSeconds = 19800;
char daysOfTheWeek[7][12] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);

uint32_t forecast = 0;
String jsonBuffer,curr_time,location,icon,description;
double temperature, t_max, wind_s;
int humidity;
String weather_link = "http://api.openweathermap.org/data/2.5/weather?q=Pune&appid=85ab1507a0a5ec77465d0e7ea6cb8bb4";
unsigned long lastTime = 0;
unsigned long timerDelay = 10000;

/***************************************************************************************************************************************************************************/

void setup() {
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  delay(2000);

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
}

/***************************************************************************************************************************************************************************/

void loop() {
  timeClient.update();
  String currentDay = daysOfTheWeek[timeClient.getDay()]+String(" ");
  curr_time = timeClient.getFormattedTime();
//============================================================================================================================================================================
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(50,0);
  display.print(currentDay);
//============================================================================================================================================================================ 
  display.setTextSize(1);
  display.setTextColor(WHITE);
//  display.setCursor(75,10);
  display.println(curr_time);
//============================================================================================================================================================================ 
  if ((millis() - lastTime) > timerDelay) {
    jsonBuffer = get_data(weather_link);
    Serial.println(jsonBuffer);
    JSONVar myObject = JSON.parse(jsonBuffer);
    if (JSON.typeof(myObject) == "undefined") {
      Serial.println("Parsing input failed!");
    }
    temperature = (double)myObject["main"]["temp"];
    t_max = (double)myObject["main"]["temp_max"];
    location = (const char*)myObject["name"];
    humidity = int(myObject["main"]["humidity"]);
    wind_s = (double)myObject["wind"]["speed"];
    icon = (const char*)myObject["weather"][0]["icon"];
    description = (const char*)myObject["weather"][0]["main```````````````"];
    Serial.println(icon);
    lastTime = millis();
  }
  display.setTextSize(1);
  display.setFont(&FreeSansBoldOblique9pt7b);
  display.setCursor(0,12);
  display.println(location);
  display.setTextSize(2);
  display.setFont();
  display.setCursor(0,16);
  display.print(temperature-273.00,1);
  display.print((char)247); // degree symbol 
  display.println("C");
  display.setTextSize(1);
  display.setCursor(0,36);
  display.print("Max: ");
  display.print(t_max-273.00,1);
  display.print((char)247); // degree symbol 
  display.println("C");
  display.drawBitmap(0,48,image_data_humidity,14,16,1);
  display.setCursor(16,52);
  display.print(humidity);
  display.drawBitmap(29,48,image_data_windspeed,17,14,1);
  display.setCursor(49,52);
  display.print(wind_s,1);
  display.print("  ");
  display.print(description);
  drawIcon();
  display.display();
  delay(1000);
}

/***************************************************************************************************************************************************************************/

String get_data(String link){
  String payload;
  if(WiFi.status()== WL_CONNECTED){
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, link)){

      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          payload = http.getString();
          Serial.println(payload);
          return payload;
        }
      }
      else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        payload = "request failed";
        return payload;
      }

      http.end();
    } 
    else {
      Serial.printf("[HTTP} Unable to connect\n");
      payload = "connection failed";
      return payload;
    }
  }
}

/***************************************************************************************************************************************************************************/
void drawIcon() {
  if (icon.equals("01d")) {
    // 01d - Sun
  display.drawBitmap(78,14,image_data_sun,40,40,1);
  } else if (icon.equals("01n")) {
    // 01d - Sun - night
  display.drawBitmap(78,14,image_data_moon,40,40,1);
  } else if (icon.equals("02d")) {
    // 02d - Cloud, sun
  display.drawBitmap(78,14,image_data_sun_fewcloud,40,40,1);
  } else if (icon.equals("02n")) {
    // 02d - Cloud, sun - night
  display.drawBitmap(78,14,image_data_moon_fewcloud,40,40,1);
  } else if ( (icon.equals("03d"))||(icon.equals("03n"))  ) {
    // 03d - Cloud
  display.drawBitmap(78,14,image_data_cloudy,40,40,1);
  } else if ( (icon.equals("04d"))  ) {
    // 04d - Cloud, second cloud
  display.drawBitmap(78,14,image_data_cloudy,40,40,1);
  } else if ( (icon.equals("04n"))  ) {
    // 04d - Cloud, second cloud - night
  display.drawBitmap(78,14,image_data_cloudy,40,40,1);
  } else if ( (icon.equals("09d"))  ) {
    // 09d - Clouds, rain
  display.drawBitmap(78,14,image_data_rain,40,40,1);
  } else if ( (icon.equals("09n"))  ) {
    // 09d - Clouds, rain - night
  display.drawBitmap(78,14,image_data_rain,40,40,1);
  } else if ( (icon.equals("10d"))  ) {
    // 10d - Clouds, sun, rain
  display.drawBitmap(78,14,image_data_rain,40,40,1);
  } else if ( (icon.equals("10n"))  ) {
    // 10d - Clouds, sun, rain - night
  display.drawBitmap(78,14,image_data_rain,40,40,1);
  } else if ( (icon.equals("11d"))  ) {
    // 11d - Clouds, lightning
  display.drawBitmap(78,14,image_data_thunder,40,40,1);
  } else if ( (icon.equals("11n"))  ) {
    // 11d - Clouds, lightning - night
  display.drawBitmap(78,14,image_data_thunder,40,40,1);
  } else if ( (icon.equals("13d"))   ||  (icon.equals("13n"))  ) {
    // 13d - Snow
  display.drawBitmap(78,14,image_data_sun,40,40,1);
  } else {
    // 50d - Fog
  display.drawBitmap(78,14,image_data_sun,40,40,1);
  }
}
