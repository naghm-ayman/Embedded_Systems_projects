/* 
 * File:   mcal_interrupt_manager.h
 * Author: Naghm Ayman Omar
 *
 * Created on 08 July 2024, 14:30
 */

#ifndef MCAL_INTERRUPT_MANAGER_H
#define	MCAL_INTERRUPT_MANAGER_H

/*section of INCLUDES */

#include"mcal_interrupt_config.h"

/*section of MACRO DECLARATIONS */

/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of FUNCTIONS DECLARATIONS*/
void INT0_ISR(void);
void INT1_ISR(void);
void INT2_ISR(void);

void RB4_ISR(uint8 RB4_source);
void RB5_ISR(uint8 RB5_source);
void RB6_ISR(uint8 RB6_source);
void RB7_ISR(uint8 RB7_source);

void ADC_ISR(void);

void TIMER0_ISR(void);
void TIMER1_ISR(void);
void TIMER2_ISR(void);
void TIMER3_ISR(void);

void CCP1_ISR(void);
void CCP2_ISR(void);

void EUSART_Tx_ISR(void);
void EUSART_Rx_ISR(void);

void SPI_ISR(void);

void  MSSP_I2C_ISR(void);
void  MSSP_I2C_BC_ISR(void);
#endif	/* MCAL_INTERRUPT_MANAGER_H */

