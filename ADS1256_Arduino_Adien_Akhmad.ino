#include "ADS1256.h"
#include <Wire.h>

float clockMHZ = 7.68; // crystal frequency used on ADS1256
float vRef = 2.5;      // voltage reference
float diff_signal_0_1;
float diff_signal_2_3;
float diff_signal_4_5;
float diff_signal_6_7;

long rawConversion_0_1 = 0; // 24-bit raw value
long rawConversion_2_3 = 0; // 24-bit raw value
long rawConversion_4_5 = 0; // 24-bit raw value
long rawConversion_6_7 = 0; // 24-bit raw value

// Construct and init ADS1256 object
ADS1256 adc(clockMHZ, vRef, false); // RESETPIN is permanently tied to 3.3v

#define FREQUENCY_HZ 50
#define INTERVAL_MS (1000 / (FREQUENCY_HZ + 1))

void setup()
{
   Serial.begin(115200);

    // start the ADS1256 with data rate and gain
    // adc.begin(ADS1256_DRATE_30SPS, ADS1256_GAIN_2, false);
    adc.begin(ADS1256_DRATE_60SPS, ADS1256_GAIN_2, false);
}

void loop()
{
    adc.waitDRDY();
    adc.setChannel(0, 1);
    diff_signal_0_1 = adc.readSingle();
    // rawConversion_0_1 = adc.readSingle();
    // diff_signal_0_1 = adc.convertToVoltage(rawConversion_0_1);

    adc.waitDRDY();
    adc.setChannel(2, 3);
    diff_signal_2_3 = adc.readSingle();
    // rawConversion_2_3 = adc.readSingle();
    // diff_signal_2_3 = adc.convertToVoltage(rawConversion_2_3);

    // adc.waitDRDY();
    // adc.setChannel(4, 5);
    // rawConversion_4_5 = adc.readSingle();
    // diff_signal_4_5 = adc.convertToVoltage(rawConversion_4_5);

    rawConversion_6_7 = (diff_signal_0_1 - diff_signal_2_3);
    diff_signal_6_7 = adc.convertToVoltage(rawConversion_6_7);
    // diff_signal_6_7 = (diff_signal_0_1 - diff_signal_2_3);

    // Serial.print(diff_signal_0_1, 10);
    // Serial.print("\t");
    // Serial.print(diff_signal_2_3, 10);
    // Serial.print("\t");
    // Serial.print(diff_signal_4_5, 10);
    // Serial.print("\t");
    Serial.print(diff_signal_6_7, 10);
    Serial.print("\n");
}