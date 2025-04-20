/* 
 * File:   hal_spi.h
 * Author: Naghm Ayman Omar
 *
 * Created on 09 August 2024, 17:47
 */

#ifndef HAL_SPI_H
#define	HAL_SPI_H

/* --------------------- section of INCLUDES ---------------------*/
#include"pic18f4620.h" 
#include"../mcal_std_types.h"
#include"../../MCAL_layer/GPIO/hal_gpio.h"
#include"../../MCAL_layer/Interrupt/mcal_internal_interrupt.h"

/*--------------------- section of MACRO DECLARATIONS --------------------- */
/* Master Synchronous Serial Port Mode Select bits */
#define SPI_MASTER_MODE_FOSC_4    0  /* SPI Master mode, clock = FOSC/4 */
#define SPI_MASTER_MODE_FOSC_16   1  /* SPI Master mode, clock = FOSC/16 */
#define SPI_MASTER_MODE_FOSC_64   2  /* SPI Master mode, clock = FOSC/64 */
#define SPI_MASTER_MODE_TMR2      3  /* SPI Master mode, clock = TMR2 output/2 */
#define SPI_SLAVE_MODE_SS_ENABLE  4  /* SPI Slave mode, clock = SCK pin, SS pin control enabled */
#define SPI_SLAVE_MODE_SS_DISABLE 5  /* SPI Slave mode, clock = SCK pin, SS pin control disabled, SS can be used as I/O pin */

/* Clock Polarity Select bit */
#define SPI_IDLE_STATE_HIGH_LEVEL  1 /* Idle state for clock is a high level*/
#define SPI_IDLE_STATE_LOW_LEVEL   0 /* Idle state for clock is a low level*/

/* Master Synchronous Serial Port Enable bit */
#define SERIAL_PORT_ENABLE    1   /* Enables serial port and configures SCK, SDO, SDI and SS as serial port pins*/
#define SERIAL_PORT_DISABLE   0   /* Disables serial port and configures these pins as I/O port pins*/

/*  Receive Overflow Indicator bit */
#define SPI_SLAVE_RECEIVE_OVERFLOW_DETECTED      1 
#define SPI_SLAVE_RECEIVE_OVERFLOW_NOT_DETECTED  0

/*  Write Collision Detect bit */
#define SPI_WRITE_COLLISION_DETECTED             1
#define SPI_WRITE_COLLISION_NOT_DETECTED         0 

/*  Buffer Full Status bit (Receive mode only) */
#define SPI_BUFFER_RECEIVE_COMPLETE      1
#define SPI_BUFFER_RECEIVE_NOT_COMPLETE  0 

/*  SPI Clock Select bit */
#define SPI_TRANSMIT_ACTIVE_TO_IDLE  1
#define SPI_TRANSMIT_IDLE_TO_ACTIVE  0 

/* SPI Master mode */
#define SPI_DATA_SAMPLE_AT_END     1
#define SPI_DATA_SAMPLE_AT_MIDDLE  0

/*--------------------- section of MACRO FUNCTIONS DECLARATIONS --------------------- */
#define MSSP_MODULE_ENABLE()     ( SSPCON1bits.SSPEN = 1) /* Enables serial port and configures SCK, SDO, SDI and SS as serial port pins */
#define MSSP_MODULE_DISABLE()    ( SSPCON1bits.SSPEN = 0) /*  Disables serial port and configures these pins as I/O port pins */

/*--------------------- section of DATA TYPE DECLARATIONS --------------------- */
typedef struct{
    uint8 Clock_Polarity : 2; /* Clock Polarity Select */
    uint8 Data_Sample : 2;   /* SPI Sample Select */
    uint8  Clock_Edge : 2;  /* SPI Clock Select */
    uint8 Reserved : 2;
}spi_control_config_t;

typedef struct{
#if SPI_INTERRUPT_FEATURE_ENABLE == INTERRUPT_FEATURE_ENABLE
    void(* SPI_InterruptHandler)(void);
    interrupt_priority_cfg priority;
#endif
    spi_control_config_t spi_config;
    uint8 spi_mode;
}spi_t;
/*--------------------- section of SOFTWARE INTERFACES DECLARATIONS --------------------- */
Std_ReturnType SPI_Init(const spi_t *_spi_cfg);
Std_ReturnType SPI_DeInit(const spi_t *_spi_cfg);

Std_ReturnType SPI_Read_Byte_Blocking(const spi_t *_spi_cfg,const uint8 *_data);
Std_ReturnType SPI_Read_Byte_NonBlocking(const spi_t *_spi_cfg, uint8 *_data);

Std_ReturnType SPI_Send_Byte_Blocking(const spi_t *_spi_cfg,const uint8 _data);
Std_ReturnType SPI_Send_Byte_NonBlocking(const spi_t *_spi_cfg,uint8 _data);
#endif	/* HAL_SPI_H */

