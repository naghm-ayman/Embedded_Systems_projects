/* 
 * File:   hal_spi.c
 * Author: Naghm Ayman Omar
 *
 * Created on 09 August 2024, 17:47
 */

#include"hal_spi.h"

inline static void SPI_Interrupt_CFG (const spi_t *_spi_cfg);

#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
static void (*SPI_DefaultInterruptHandler)(void) = NULL;
#endif

Std_ReturnType SPI_Init(const spi_t *_spi_cfg){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _spi_cfg){
         ret= E_NOK;
     }
     else{
       /* Disable the SPI */
         MSSP_MODULE_DISABLE(); 
         
     /* Interrupt Configurations */ 
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
          SPI_Interrupt_CFG(_spi_cfg);
#endif
       /* Enable the SPI */
         MSSP_MODULE_ENABLE(); 
     }
     return(ret);
}
Std_ReturnType SPI_DeInit(const spi_t *_spi_cfg){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _spi_cfg){
         ret= E_NOK;
     }
     else{
          /* Disable the SPI */
         MSSP_MODULE_DISABLE(); 
         /* Interrupt Configurations */ 
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
            SPI_InterruptDisable();
#endif
       
     }
     return(ret);
}

Std_ReturnType SPI_Read_Byte_Blocking(const spi_t *_spi_cfg,const uint8 *_data){
    Std_ReturnType ret = E_OK;
     
     if((NULL == _spi_cfg)|| (NULL == _data)){
         ret= E_NOK;
     }
     else{
       
     }
     return(ret);
}
Std_ReturnType SPI_Read_Byte_NonBlocking(const spi_t *_spi_cfg, uint8 *_data){
    Std_ReturnType ret = E_OK;
     
     if((NULL == _spi_cfg)|| (NULL == _data)){
         ret= E_NOK;
     }
     else{
       
     }
     return(ret);
}

Std_ReturnType SPI_Send_Byte_Blocking(const spi_t *_spi_cfg,const uint8 _data){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _spi_cfg){
         ret= E_NOK;
     }
     else{
       
     }
     return(ret);
}
Std_ReturnType SPI_Send_Byte_NonBlocking(const spi_t *_spi_cfg,uint8 _data){
    Std_ReturnType ret = E_OK;
     
     if(NULL == _spi_cfg){
         ret= E_NOK;
     }
     else{
       
     }
     return(ret);
}

void SPI_ISR(void){
    
}

inline static void SPI_Interrupt_CFG (const spi_t *_spi_cfg){
#if SPI_INTERRUPT_FEATURE_ENABLE==INTERRUPT_FEATURE_ENABLE
    SPI_InterruptEnable();
    SPI_InterruptFlagClear();
    
    SPI_DefaultInterruptHandler = _spi_cfg->SPI_InterruptHandler;
  
/*Configure the Interrupt Priority Levels */
#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE    
         INTERRUPT_PriortyLevelEnable();
    if(Interrupt_High_Priority == _spi_cfg->priority){
            /* Enables all high-priority interrupts */
            INTERRUPT_GlobalInterruptHighEnable();
            SPI_HighPrioritySet();
        }
        else if(Interrupt_Low_Priority == _spi_cfg->priority){
            /* Enables all unmasked peripheral interrupts */
            INTERRUPT_GlobalInterruptLowEnable();
            SPI_LowPrioritySet();
        }
        else{ /* Nothing */ }

#else
        INTERRUPT_GlobalInterruptEnable();
        INTERRUPT_PeripheralInterruptEnable();
#endif   
#endif
}