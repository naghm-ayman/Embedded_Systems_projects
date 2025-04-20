/*
 * File:   Main.c
 * Author: Naghm Ayman Omar
 *
 * Created on 29 October 2024, 17:05
 */

#include "main.h"

#define NUM_SERVOS 15
#define ZERO_INIT  0

uint8_t servo_angles[NUM_SERVOS] = {ZERO_INIT};
char Receive_Str[45];  // Adjusted buffer size to handle larger strings if needed

/**
 * Parses a received string containing servo angles (comma-separated)
 * and converts them to integers stored in the servo_angles array.
 *
 * @param str The received string from UART (e.g., "30,45,90,...").
 */
void parseServoAngles(const char *str);

int main(void) {
    uint8_t pca9685Address = 0x00; // Default PCA9685 address (adjust if needed)
    uint16_t pwmFrequency = 50;   // 50 Hz for servo motors
    uint8_t s_num_counter = 0;

    // Initialise PCA9685
    pca9685_init(pca9685Address, pwmFrequency);
    // Initialise UART Module
    UART_Init();

    // Set all servos to 0 degrees initially
    for (s_num_counter = 0; s_num_counter < NUM_SERVOS; s_num_counter++) {
        pca9685_servo(s_num_counter, ZERO_INIT);
    }

    while (1) {
        // Receive servo angles from UART
        UART_ReceiveString((uint8_t *)Receive_Str, sizeof(Receive_Str));

        // Parse received string into servo_angles array
        parseServoAngles(Receive_Str);

        // Set all servos to the parsed angles
        for (s_num_counter = 0; s_num_counter < NUM_SERVOS; s_num_counter++) {
            pca9685_servo(s_num_counter, servo_angles[s_num_counter]);
            _delay_ms(150);  // Add delay to prevent abrupt movements
        }
    }

    return 0;
}
void parseServoAngles(const char *str) {
    uint8_t L_Counter = 0;
    char *token;
    char TempStr[45];
    
    // Make a copy of the input string to avoid modifying the original
    strncpy(TempStr, str, sizeof(TempStr) - 1);
    TempStr[sizeof(TempStr) - 1] = '\0';  // Ensure null termination

    // Use strtok to split the string by commas
    token = strtok(TempStr, ",");
    while (token != NULL && L_Counter < NUM_SERVOS) {
        servo_angles[L_Counter] = (uint8_t)atoi(token);  // Convert string to integer
        token = strtok(NULL, ",");              // Get the next token
        L_Counter++;
    }

    // Fill remaining angles with ZERO_INIT if fewer angles are provided
    for (; L_Counter < NUM_SERVOS; L_Counter++) {
        servo_angles[L_Counter] = ZERO_INIT;
    }
}