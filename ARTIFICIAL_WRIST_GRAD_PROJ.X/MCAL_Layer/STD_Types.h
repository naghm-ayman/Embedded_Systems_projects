/*
 * STD_Types.h
 *
 * Created on 29 October 2024, 17:05
 *  Author: Naghm Ayman Omar
 */ 


#ifndef STD_TYPES_H_
#define STD_TYPES_H_
/*-------------------- Section of INCLUDES --------------------------- */
#include"compiler.h"
/*-------------------- section of DATA TYPE DECLARATIONS --------------------------- */
typedef unsigned char  uint8_t;
typedef unsigned short uint16;
typedef unsigned int   uint32;
typedef unsigned long  uint64;

typedef signed char  sint8_t;
typedef signed short sint16;
typedef signed int   sint32;
typedef signed long  sint64;

typedef float		float32;
typedef double		float64;


#define		   NULL	 0

/*Bit manipulation operations*/
#define SET_BIT(REG, BIT)        (REG |= (1 << BIT))
#define CLEAR_BIT(REG, BIT)      (REG &= ~(1 << BIT))
#define TOGGLE_BIT(REG, BIT)     (REG ^= (1 << BIT))
#define GET_BIT(REG, BIT)        ((REG >> BIT) & 0x1)
#define READ_BIT(REG,BIT)        ((REG) & (1<<BIT))

#endif /* STD_TYPES_H_ */