#include <pic18f46k20.h>
#include "mcc_generated_files/mcc.h"

// Function to set the duty cycle value
void PWM_Duty_cycle(uint16_t DC_val);

// --[ Pin Definitions ]--
#define Rev RB0   // Reverse Direction Button
#define LV0 RB1   // 0% Speed Button
#define LV1 RB2   // 50% Speed Button
#define LV2 RB3   // 75% Speed Button
#define LV3 RB4   // 100% Speed Button

void main(void)
{
    // Initialize the device
    SYSTEM_Initialize();

    // Configure input pull-ups for buttons on PORTB
    INTCON2bits.RBPU = 0;   // Enable PORTB pull-ups (if not already enabled)
    TRISB = 0x1F;           // Set RB0 to RB4 as input for buttons
    TRISD0 = 0;             // Set RD0 as output for motor direction
    TRISD1 = 0;             // Set RD1 as output for motor direction

    PORTDbits.RD0 = 0;      // Initial motor direction
    PORTDbits.RD1 = 1;

    // Configure PWM
    CCP1CONbits.CCP1M = 0x0C; // Set CCP1 to PWM mode
    TRISC2 = 0;               // Set CCP1/PWM output pin RC2 as output

    // Set PWM Frequency to approximately 2kHz
    PR2 = 124;

    // Set Timer2 prescaler to 1:4 for a more stable frequency
    T2CONbits.T2CKPS = 0x01;

    // Enable Timer2
    T2CONbits.TMR2ON = 1;

    uint8_t direction = 0; // 0 for forward, 1 for reverse

    while (1)
    {
        // Reverse direction when Rev button is pressed
        if (Rev) 
        {
            direction = !direction; // Toggle direction
            PORTDbits.RD0 = direction;
            PORTDbits.RD1 = !direction;
            __delay_ms(500); // Debounce delay
        }

        // Set motor speed based on button press
        if (LV0) // 0% Duty Cycle (stop motor)
        {
            PWM_Duty_cycle(0);
            __delay_ms(100); // Debounce delay
        }
        if (LV1) // 50% Duty Cycle
        {
            PWM_Duty_cycle(512);
            __delay_ms(100); // Debounce delay
        }
        if (LV2) // 75% Duty Cycle
        {
            PWM_Duty_cycle(768);
            __delay_ms(100); // Debounce delay
        }
        if (LV3) // 100% Duty Cycle
        {
            PWM_Duty_cycle(1023);
            __delay_ms(100); // Debounce delay
        }

        __delay_ms(10);  // Small delay to reduce simulation overload
    }
}

// Function to set the PWM duty cycle
void PWM_Duty_cycle(uint16_t DC_val)
{
    if (DC_val < 1024)
    {
        CCP1CONbits.DC1B = DC_val & 0x03; // Least significant 2 bits
        CCPR1L = DC_val >> 2;             // Most significant 8 bits
    }
}
