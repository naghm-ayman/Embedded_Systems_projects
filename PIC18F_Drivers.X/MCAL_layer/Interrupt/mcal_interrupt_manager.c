/* 
 * File:   mcal_interrupt_manager.c
 * Author: Naghm Ayman Omar
 *
 * Created on 08 July 2024, 14:30
 */

#include"mcal_interrupt_manager.h"

uint8 RB4_FLAG = 1, RB5_FLAG = 1, RB6_FLAG = 1, RB7_FLAG = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
void __interrupt() InterruptMangerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{
        /*nothing*/
    }
}
void __interrupt(low_priority) InterruptMangerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{
        /*nothing*/
    }
}
#else
void __interrupt() InterruptMangerHigh(void){
                       /*=========== INTx EXTERNAL INTERRUPT STARTS =============*/
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }
    else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }
    else{
        /*nothing*/
    }
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }
    else{
        /*nothing*/
    }
                   /*=========== INTx EXTERNAL INTERRUPT ENDS =============*/
    
                   /*========== PORT B RBx EXTERNAL INTERRUPT STARTS =======*/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_HIGH) && (RB4_FLAG == 1)){
        RB4_FLAG = 0;
        RB4_ISR(0);
    }
    else{
        /*nothing*/
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_LOW) && (RB4_FLAG == 0)){
        RB4_FLAG = 1;
        RB4_ISR(1);
    }
    else{
        /*nothing*/
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_HIGH) && (RB5_FLAG == 1)){
        RB5_FLAG = 0;
        RB5_ISR(0);
    }
    else{
        /*nothing*/
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_LOW) && (RB5_FLAG == 0)){
        RB5_FLAG = 1;
        RB5_ISR(1);
    }
    else{
        /*nothing*/
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_HIGH) && (RB6_FLAG == 1)){
        RB6_FLAG = 0;
        RB6_ISR(0);
    }
    else{
        /*nothing*/
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_LOW) && (RB6_FLAG == 0)){
        RB6_FLAG = 1;
        RB6_ISR(1);
    }
    else{
        /*nothing*/
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_HIGH) && (RB7_FLAG == 1)){
        RB7_FLAG = 0;
        RB7_ISR(0);
    }
    else{
        /*nothing*/
    }
     if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_LOW) && (RB7_FLAG == 0)){
        RB7_FLAG = 1;
        RB7_ISR(1);
    }
    else{
        /*nothing*/
    }
                 /*=========== PORT B RBx EXTERNAL INTERRUPT ENDS =============*/
    
    
                 /*================ ADC MODULE INTERRUPT STARTS ===============*/
    if((INTERRUPT_ENABLE == PIE1bits.ADIE) && (INTERRUPT_OCCUR == PIR1bits.ADIF)){
        ADC_ISR();
    }
    else{
        
    }
                  /*================ ADC MODULE INTERRUPT ENDS ===============*/
    
                 /*================ TIMERS MODULE INTERRUPT STARTS ===============*/
    if((INTERRUPT_ENABLE == INTCONbits.TMR0IE) && (INTERRUPT_OCCUR == INTCONbits.TMR0IF)){
        TIMER0_ISR();
    }
    else{
        
    }
    
                 
    if((INTERRUPT_ENABLE == (PIE1bits.TMR1IE) && (INTERRUPT_OCCUR == PIR1bits.TMR1IF))){
        TIMER1_ISR();
    }
    else{
        
    }
    
    if((INTERRUPT_ENABLE == (PIE1bits.TMR2IE) && (INTERRUPT_OCCUR == PIR1bits.TMR2IF))){
        TIMER2_ISR();
    }
    else{
        
    }
    
    if((INTERRUPT_ENABLE == (PIE2bits.TMR3IE) && (INTERRUPT_OCCUR == PIR2bits.TMR3IF))){
       TIMER3_ISR();
    }
    else{
        
    }
    
                 /*================ TIMERS MODULE INTERRUPT ENDS ===============*/
    
                /*================ CPP MODULE INTERRUPT STARTS ===============*/
    if((INTERRUPT_ENABLE == PIE1bits.CCP1IE) && (INTERRUPT_OCCUR == PIR1bits.CCP1IF)){
        CCP1_ISR();
    }
    else{
        
    }
    
    if((INTERRUPT_ENABLE == PIE2bits.CCP2IE) && (INTERRUPT_OCCUR == PIR2bits.CCP2IF)){
        CCP2_ISR();
    }
    else{
        
    }
              /*================ CCP MODULE INTERRUPT ENDS ===============*/
    
             /*================ EUSART MODULE INTERRUPT STARTS ===============*/
    if((INTERRUPT_ENABLE == PIE1bits.TXIE) && (INTERRUPT_OCCUR == PIR1bits.TXIF)){
        EUSART_Tx_ISR();
    }
    else{
        
    }
    
    if((INTERRUPT_ENABLE == PIE1bits.RCIE) && (INTERRUPT_OCCUR == PIR1bits.RCIF)){
        EUSART_Rx_ISR();
    }
    else{
        
    }
              /*================ EUSART MODULE INTERRUPT ENDS ===============*/
    
             /*================ MSSP (SPI/I2C) MODULE INTERRUPT STARTS ===============*/
    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
       SPI_ISR();
    }
    else{
        
    }
    

    if((INTERRUPT_ENABLE == PIE1bits.SSPIE) && (INTERRUPT_OCCUR == PIR1bits.SSPIF)){
       MSSP_I2C_ISR();
    }
    else{
        
    }
    if((INTERRUPT_ENABLE == PIE2bits.BCLIE) && (INTERRUPT_OCCUR == PIR2bits.BCLIF)){
       MSSP_I2C_BC_ISR();
    }
    else{
        
    }
    
              /*================ MSSP (SPI/I2C) MODULE INTERRUPT ENDS ===============*/
}
#endif