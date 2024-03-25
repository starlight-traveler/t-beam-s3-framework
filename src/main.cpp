#define LILYGO_TBeamS3_SUPREME_V3_0
#define HAS_SDCARD
#define HAS_DISPLAY
#define HAS_PMU

#define TX_POWER 22         // Transmit Power (LoRa, dBm)
#define BANDWIDTH 125       // Bandwidth (LoRa, kHz)
#define SPREADING_FACTOR 12 // Spreading Factor (LoRa)
#define CODING_RATE 8       // Coding Rate (LoRa, 4/x)
#define PREAMBLE_LENGTH 12  // Preamble Length (LoRa)

#include <Arduino.h>
#include <RadioLib.h>
#include <U8g2lib.h> // Include U8g2 library for the OLED
#include <SPI.h>
#include <Wire.h>
#include "utilities.h"
#include "boards.h"

// Define the SX1262 module with the specific connections for your board
SX1262 radio = new Module(RADIO_CS_PIN, RADIO_DIO1_PIN, RADIO_RST_PIN, RADIO_BUSY_PIN);

void initializeAndDisplayOLED()
{
  Wire.beginTransmission(0x3C); // Start I2C transmission to check if the OLED is connected
  if (Wire.endTransmission() == 0)
  { // Check if the transmission was successful
    Serial.println("Started OLED");
    u8g2 = new DISPLAY_MODEL(U8G2_R0, U8X8_PIN_NONE); // Initialize the display object
    u8g2->begin();                                    // Begin the display
    u8g2->clearBuffer();                              // Clear the internal buffer
    u8g2->setFlipMode(0);                             // Set flip mode
    u8g2->setFontMode(1);                             // Set font mode to transparent
    u8g2->setDrawColor(1);                            // Set draw color
    u8g2->setFontDirection(0);                        // Set font direction
  }
  else
  {
    Serial.println("OLED initialization failed.");
  }
}

void setup()
{
  Serial.begin(115200);

  Wire.begin(I2C_SDA, I2C_SCL);

  initializeAndDisplayOLED();

  // Initialize SX1262 with custom settings
  Serial.print(F("[SX1262] Initializing ... "));
  int state = radio.begin(915.0, 125.0, SPREADING_FACTOR, CODING_RATE, 0x12, TX_POWER, PREAMBLE_LENGTH, 1.6, false);
  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.println(F("success!"));
  }
  else
  {
    Serial.print(F("failed, code "));
    Serial.println(state);
    while (true)
      ; // halt on failure
  }

  Serial.println(F("OLED display initialized."));

  Serial.println(F("SX1262 radio initialized successfully with custom settings!"));
}

void loop()
{
  char message[] = "Let's Go!";                             // The message to transmit
  int state = radio.transmit(message, strlen(message)); // Transmit the message

  if (state == RADIOLIB_ERR_NONE)
  {
    Serial.print(F("Message sent: "));
    Serial.println(message);

    if (u8g2 != nullptr)
    {                                      // Check if u8g2 is initialized
      u8g2->clearBuffer();                 // Clear the internal memory
      u8g2->setFont(u8g2_font_ncenB08_tr); // Set the font
      u8g2->drawStr(0, 24, message);       // Draw the message on the OLED
      u8g2->sendBuffer();                  // Transfer internal memory to the display
    }
  }
  else
  {
    Serial.print(F("Send failed, code "));
    Serial.println(state);
  }

  delay(1000); // Wait for 1 second before transmitting again
}