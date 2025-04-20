/*
 * File:   pca9685.c
 * Author: Naghm Ayman Omar
 *
 * Created on 29 October 2024, 17:05
 */

#include <avr/io.h>
#include <util/delay.h>
#include "pca9685.h"

uint16_t globalFrequency;
uint8_t globalAddress;

void pca9685_init(uint8_t address, uint16_t freq)
{
    globalFrequency = freq;
    globalAddress = address;

    i2c_init(); 

    /* Select slave device, select MODE1 register, then set AI (auto-increment)
       enable, SLEEP active, and ALLCALL enable */
    i2c_tx_start(MASTER_TRANSMITTER);
    i2c_tx_address(0x40 + address); // 0x40 adds addr MSB (fig 4 in datasheet)
    i2c_tx_byte(0x00); // MODE1 register
    i2c_tx_byte(0b00110001); // set register configuration ( AI=1, SLEEP=1, ALLCALL=1) in mode 1 Register
    i2c_tx_stop();

    _delay_ms(1); // A short delay ensures the PCA9685 has time to enter the sleep state.

    /* Calculate frequency prescalar for usage below. PCA9685 contains a 25 MHz
       internal clock that can be prescaled to achieve the desired output
       frequency. The prescalar can be a number between 0xFF (24 Hz) and 0x03
       (1526 Hz). Multiply frequency by 0.92 to compensate for frequency
       inaccuracy. Declare the variable as volatile to force computation
       where written in source, otherwise compiler will place expression inline
       where it is used (during I2C transmission, causing a brief delay due to
       time it takes to compute result). Note: equation can be optimized
       without needing a float) */
    volatile uint8_t prescalar = (25000000 / ((float)4096 * freq * 0.92)) - 1;

    /* Select slave device, select PRESCALE register, then set output driver
       frequency using prescalar */
    i2c_tx_start(MASTER_TRANSMITTER);
    i2c_tx_address(0x40);
    i2c_tx_byte(0xFE); // PRESCALE register (to activate the slave to get prescaler for output frequency)
    i2c_tx_byte(prescalar); // set register configuration
    i2c_tx_stop();

    _delay_ms(1);

    /* Select slave device, select MODE1 register, then set AI (auto-increment)
       enable, SLEEP disable, and ALLCALL enable */
    i2c_tx_start(MASTER_TRANSMITTER);
    i2c_tx_address(0x40);
    i2c_tx_byte(0x00); // MODE1 register
    i2c_tx_byte(0b10100001); // set register configuration ( Restart=1, AI=1, SLEEP=0, ALLCALL=1) in mode 1 Register
    i2c_tx_stop();

    _delay_ms(1);

    /* Select slave device, select MODE2 register, then set INVRT (inverted
       output) disable, OCH (outputs change on STOP command) enable, OUTDRV
       (output driver configuration) to totem pole output and OUTNE (output not
       enable mode) to 0x00 */
    i2c_tx_start(MASTER_TRANSMITTER);
    i2c_tx_address(0x40);
    i2c_tx_byte(0x01); // Activation of MODE2 register
    i2c_tx_byte(0b00000100); // set register configuration
    i2c_tx_stop();
}

void pca9685_servo(uint8_t servoNum, float angle)
{
    /* Set limits on angle (-90 to 90 degrees) */
    if (angle > 90) {
        angle = 90;
    } else if (angle < -90) {
        angle = -90;
    }

    /* Calculate the pulse duration in microseconds (µs) */
    uint16_t pulse_us = NEUTRAL_PULSE + angle * ((float)(MAX_PULSE - MIN_PULSE) / (2 * MAX_ANGLE));

    /* Convert pulse duration into a value from 0 to 4096, which will repeat every (1 / frequency) * 1000000 µs */
    uint16_t period_us = (float)1000000 / globalFrequency;
    uint16_t count = ((float)pulse_us / period_us) * 4096;

    /* Split the 12-bit count into two 8-bit values */
    uint8_t offLowCmnd = count & 0xFF;         // Lower 8 bits
    uint8_t offHighCmnd = (count >> 8) & 0x0F; // Upper 4 bits

    /* Correctly set the channel register for the given servoNum */
    uint8_t registerBase = SERVO0 + (4 * servoNum); // Calculate base address for each servo

    /* Set the PWM on the servo channel */
    i2c_tx_start(MASTER_TRANSMITTER);
    i2c_tx_address(0x40 + globalAddress);
    i2c_tx_byte(registerBase);       // Set starting register (LEDXX_ON_L for servoNum)
    i2c_tx_byte(0x00);               // LEDXX_ON_L: Start time low byte (always 0 for simplicity)
    i2c_tx_byte(0x00);               // LEDXX_ON_H: Start time high byte
    i2c_tx_byte(offLowCmnd);         // LEDXX_OFF_L: Stop time low byte
    i2c_tx_byte(offHighCmnd);        // LEDXX_OFF_H: Stop time high byte
    i2c_tx_stop();
}
