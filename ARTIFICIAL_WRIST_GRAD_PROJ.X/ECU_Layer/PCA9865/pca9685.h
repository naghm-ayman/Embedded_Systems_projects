/*
 * File:   pca9685.h
 * Author: Naghm Ayman Omar
 *
 * Created on 29 October 2024, 17:05
 */

#ifndef pca9685_h
#define pca9685_h

#include"../../MCAL_Layer/I2C_BUS/i2c.h"

#define SERVO0 0x06 /*the offset address of the servos then increment each servo by 4*/

#define NEUTRAL_PULSE 1388  // 1.5ms at 0 degrees
#define MAX_PULSE 1861    // 2ms at +90 degrees
#define MIN_PULSE 919     // 1ms at -90 degrees
#define MAX_ANGLE 90

/*
 * Configure PCA9685 slave device
 *
 * Sets the slave device MODE1, PRESCALE (controls the output frequency) and
 * MODE2 register values.
 *
 * Arguments:
 *      address    The PCA9685 hardwired 6-bit slave device address.
 *
 *      freq       Output driver frequency (in Hz). Must be a value between
 *                 24 Hz and 1526 Hz
 */
void pca9685_init(uint8_t address, uint16_t freq);

/*
 * Set the servo horn angle
 *
 * Sets the slave device MODE1, PRESCALE (controls the output frequency) and
 * MODE2 register values.
 *
 * Arguments:
 *      servoNum    The index of the servo motor. A number between 0 and 15.
 *
 *      angle       Angle in degrees. Must be a value between -90 and 90
 *                  degrees.
 */
void pca9685_servo(uint8_t servoNum, float angle);

#endif
