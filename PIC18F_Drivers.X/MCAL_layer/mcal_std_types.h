/* 
 * File:   mcal_std_types.h
 * Author: NAGHM.A.O
 *
 * Created on 14 March 2024, 20:11
 */

#ifndef MCAL_STD_TYPES_H
#define	MCAL_STD_TYPES_H

/*section of INCLUDES */
#include"std_libiraries.h"
#include"compiler.h"
/*section of DATA TYPE DECLARATIONS*/
typedef unsigned char   uint8;
typedef unsigned short  uint16;
typedef unsigned long   uint32;
typedef signed char     sint8;
typedef signed short    sint16;
typedef signed long     sint32;

typedef uint8   Std_ReturnType;
typedef uint16  adc_result_t;

/*section of MACRO DECLARATIONS */
#define STD_HIGH        0x01
#define STD_LOW         0x00

#define STD_ON          0x01
#define STD_OFF         0x00

#define STD_ACTIVE      0x01
#define STD_IDLE        0x00

#define config_ENABLE   0x01
#define config_DISABLE  0x00 


#define E_OK       (Std_ReturnType)0x01
#define E_NOK      (Std_ReturnType)0x00

#define ZERO_INIT       0

/*section of MACRO FUNCTIONS DECLARATIONS */

/*section of MACRO DECLARATIONS */

/*section of FUNCTIONS DECLARATIONS */

#endif	/* MCAL_STD_TYPES_H */

