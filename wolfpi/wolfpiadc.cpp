#include <cstdio>
#include <unistd.h>
#include "ADS1X15_TLA2024.h"

ADS1115 ads;  /* Use this for the 16-bit version */
// ADS1015 ads;     /* Use this for the 12-bit version */
// TLA2024 ads;

int DEBUG = 1;
float AIN0vout, AIN1vout, AIN2vout, AIN3vout;
float AIN0cal, AIN1cal, AIN2cal, AIN3cal;
float PGA = 4.096; /* PGA is defined by GAIN setting */

// AIN0 Resistors
float R5 = 10000; // 10k ohms
float R6 = 3000;  // 3k ohms
// AIN1 Resistors
float R7 = 1; // dummy, so we don't divide by 0
float R8 = 1; // dummy, so we don't divide by 0
// AIN2 Resistors
float R9 = 1000; // 1kohm
float R10 = 3740; // 3.74kohm
// AIN3 Resistors
float R12 = 1;
float R13 = 1;

// AIN0 Max Input Voltage
//
// VINmax = (VDD + 0.3) x ((R5 + R6)/R6)
// VINmax = (3.6) x ((13000)/3000)
// VINmax = 15.6VDC
//
// AIN2 Max Input Voltage
//
// VINmax = (VDD + 0.3) x ((R9 + R10)/R10)
// VINmax = (3.6) x ((4740)/3740)
// VINmax = 4.56VDC

int main()
{
    int16_t adc[4];
    int8_t i;

    if (DEBUG) {
        printf("Getting single-ended readings from AIN0..3\n");
        printf("ADC Range: +/- 4.096V (1 bit = 2mV/ADS1015, 0.125mV/ADS1115)\n");
	printf("ADC Max Input: VDD + 0.3 = 3.6VDC\n\n");
    }
  
  // The ADC input range (or gain) can be changed via the following
  // functions, but be careful never to exceed VDD +0.3V max, or to
  // exceed the upper and lower limits if you adjust the input range!
  // Setting these values incorrectly may destroy your ADC!
  //                                                                ADS1015  ADS1115
  //                                                                -------  -------
  // ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
  // 
  // We're using VDD = 3.3V, so we will use GAIN_ONE to get the most resolution, being
  // careful to choose our voltage divider resistors!
    ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV
  // ads.setGain(GAIN_TWO);        // 2x gain   +/- 2.048V  1 bit = 1mV      0.0625mV
  // ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV
  // ads.setGain(GAIN_EIGHT);      // 8x gain   +/- 0.512V  1 bit = 0.25mV   0.015625mV
  // ads.setGain(GAIN_SIXTEEN);    // 16x gain  +/- 0.256V  1 bit = 0.125mV  0.0078125mV
 
    for (i = 0; i < 4; i++) {
        adc[i] = ads.readADC_SingleEnded(i);
	if (DEBUG) {
	    printf("AIN%i: %d\n", i, adc[i]);
	}
    }

    /* Calculate output voltage for AIN0. */
    AIN0vout = (adc[0]*(PGA/32767))*((R5+R6)/R6);
    printf("AIN0vout = %.2f\n", AIN0vout);

    /* Calculate output voltage for AIN1. */
    AIN1vout = (adc[1]*(PGA/32767))*((R7+R8)/R8);
    printf("AIN1vout = %.2f\n", AIN1vout);

    /* Calculate output voltage for AIN2. */
    AIN2vout = (adc[2]*(PGA/32767))*((R9+R10)/R10);
    printf("AIN2vout = %.2f\n", AIN2vout);

    /* Calculate output voltage for AIN3. */
    AIN3vout = (adc[3]*(PGA/32767))*((R12+R13)/R13);
    printf("AIN3vout = %.2f\n", AIN3vout);
}
