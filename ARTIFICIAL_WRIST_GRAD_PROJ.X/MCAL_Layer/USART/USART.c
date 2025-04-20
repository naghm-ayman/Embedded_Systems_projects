
/*
 * File:   USART.c
 * Author: Naghm Ayman Omar
 *
 * Created on 29 October 2024, 17:05
 */
#include "USART.h"
#include <inttypes.h>

/****************************Pointer to functions to be assigned to ISR*********************************/

static void (*UART_RX_Fptr)(void);
static void (*UART_TX_Fptr)(void);

/********************************************initialization **********************************************/

/************************* Array of  UBRR values ***************************/
const uint16 BaudRateArray[TOTAL_SPEED_MODE][TOTAL_CPU_F][TOTAL_BAUD_RATE] = { {
		{ 103, 51, 25, 16, 12, 8 }, { 207, 103, 51, 34, 25, 16 }, { 416, 207,
				103, 68, 51, 34 } }, { { 207, 103, 51, 34, 25, 16 }, { 416, 207,
		103, 68, 51, 34 }, { 832, 416, 207, 138, 103, 68 } } };

void UART_Init(void) {
	uint8_t UCSRC_var = 0;
	uint16 UBRR_var = 0;
	/***************************** transmission speed***************************/
#if (SPEED_MODE==NORMAL_SPEED)
	CLEAR_BIT(UCSRA, U2X);
#elif (SPEED_MODE==DOUBLE_SPEED)
	SET_BIT(UCSRA,U2X);
	#endif

//******************set URSEL to write data to UCSRC register***************/
	SET_BIT(UCSRC_var, URSEL);

//********************************synch***********************************/
#if (SYNCH_MODE==SYNCH)
	 SET_BIT(UCSRC_var,UMSEL)
	 #elif (SYNCH_MODE==ASYNCH)
	CLEAR_BIT(UCSRC_var, UMSEL);
#endif
	//*****************************parity mode*******************************/

#if (PARITY_MODE==NO_PARITY)
	CLEAR_BIT(UCSRC_var, UPM0);
	CLEAR_BIT(UCSRC_var, UPM1);
#elif (PARITY_MODE==EVEN_PARITY)
	CLEAR_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
	#elif (PARITY_MODE==ODD_PARITY)
	SET_BIT(UCSRC_var,UPM0);
	SET_BIT(UCSRC_var,UPM1);
	#endif
//************************Data bits*******************************/
#if (N_DATA_BITS==_5_DATA_BITS)
	CLEAR_BIT(UCSRC_var,UCSZ0);
	CLEAR_BIT(UCSRC_var,UCSZ1);
	CLEAR_BIT(UCSRC_var,UCSZ2);
	#elif (N_DATA_BITS==_6_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	CLEAR_BIT(UCSRC_var,UCSZ1);
	CLEAR_BIT(UCSRC_var,UCSZ2);
    #elif (N_DATA_BITS==_7_DATA_BITS)
    CLEAR_BIT(UCSRC_var,UCSZ0);
    SET_BIT(UCSRC_var,UCSZ1);
    CLEAR_BIT(UCSRB,UCSZ2);
	#elif (N_DATA_BITS==_8_DATA_BITS)
	SET_BIT(UCSRC_var, UCSZ0);
	SET_BIT(UCSRC_var, UCSZ1);
	CLEAR_BIT(UCSRB, UCSZ2);
#elif (N_DATA_BITS==_9_DATA_BITS)
	SET_BIT(UCSRC_var,UCSZ0);
	SET_BIT(UCSRC_var,UCSZ1);
	SET_BIT(UCSRB,UCSZ2);
	#endif
//************************Stop bits*******************************/
#if (N_STOP_BITS==ONE_STOP_BIT)
	CLEAR_BIT(UCSRC_var, USBS);
#elif (N_STOP_BITS==TWO_STOP_BIT)
	SET_BIT(UCSRC_var,USBS);
#endif
//*****************set UCSRC value   *******************************/
	UCSRC = UCSRC_var;

//************************Baud rate *******************************/

	UBRR_var = BaudRateArray[SPEED_MODE][CPU_F][BUAD_RATE];
	UBRRH = (uint8_t) (UBRR_var >> 8);
	UBRRL = (uint8_t) UBRR_var;

//************************Enable  *******************************/
//enable UART  receiver.
	SET_BIT(UCSRB, RXEN);
//enable UART  transmitter .
	SET_BIT(UCSRB, TXEN);
}

/*****************************************Interrupt functions*********************************************/

/* Enables RX interrupt */
void UART_RX_InterruptEnable(void) {
	SET_BIT(UCSRB, RXCIE);
}
/* Disables RX interrupt */
void UART_RX_InterruptDisable(void) {
	CLEAR_BIT(UCSRB, RXCIE);
}
/* Enables TX interrupt */
void UART_TX_InterruptEnable(void) {
	SET_BIT(UCSRB, TXCIE);
}
/* disables TX interrupt */
void UART_TX_InterruptDisable(void) {
	CLEAR_BIT(UCSRB, TXCIE);
}
/*****************************************Set Call Back Functions*********************************************/
void UART_RX_SetCallBack(void (*LocalFptr)(void)) {
	UART_RX_Fptr = LocalFptr;
}

void UART_TX_SetCallBack(void (*LocalFptr)(void)) {
	UART_TX_Fptr = LocalFptr;
}
/***********************************************ISR ************************************************************/
ISR(USART_RXC_vect) {
	if (UART_RX_Fptr) {
		UART_RX_Fptr();
	}
}

ISR(USART_TXC_vect) {
	if (UART_TX_Fptr) {
		UART_TX_Fptr();
	}
}

/****************************************Send and receive functions with no ckecking********************************/

void UART_SendByteNoBlock(uint8_t data) {
	UDR = data;
}

uint8_t UART_ReceiveByteNoBlock(void) {
	return UDR;
}
/****************************************Send and receive functions with polling     ********************************/
void UART_SendByte(uint8_t data) {
	/*UDRE flag is set when the buffer is empty and ready
	 for transmitting a new byte so wait until this flag is set to one
	 and it will cleared by hardware when u write  new data to puffer.*/
	while (!(READ_BIT(UCSRA, UDRE)))
		;
	UDR = data;
}

uint8_t UART_ReceiveByte(void) {
	/*RXC flag is set when the UART receive data so  wait until this flag is set to one
	 and it will cleared by hardware when u read the data*/
	while (!(READ_BIT(UCSRA, RXC)))
		;
	return UDR;
}

void UART_SendString(sint8_t *str) {
	uint8_t count = 0;
	while (str[count] != '\0') {
		UART_SendByte(str[count]);
		count++;
	}
}
void UART_SendHex(uint32 Num) {
	unsigned char buffer[20];
	snprintf(buffer, sizeof(buffer), "%08" PRIX32, Num);
	UART_SendString((sint8_t*) buffer);
}

uint8_t UART_Receive_NoBlock(uint8_t *pdata) {
	uint8_t status = 0;
	if (READ_BIT(UCSRA, RXC)) {
		*pdata = UDR;
		status = 1;
	} else {
		status = 0;
	}
	return status;
}

void UART_ReceiveWord(uint16_t *value) {
    uint8_t byte1 = UART_ReceiveByte();  // Receive the first byte
    uint8_t byte2 = UART_ReceiveByte();  // Receive the second byte
    
    // Combine the two bytes into a 16-bit integer (big-endian)
    *value = (byte1 << 8) | byte2;
}

void UART_ReceiveString(uint8_t *str, uint8_t maxLength) {
    uint8_t i = 0;
    uint8_t receivedChar;

    // Loop to receive characters
    while (i < (maxLength - 1)) {  // Reserve space for null terminator
        receivedChar = UART_ReceiveByte();  // Receive a single character
        
        // Check for termination character (e.g., newline or null character)
        if (receivedChar == '\n' || receivedChar == '\0') {
            break;
        }

        // Store the received character in the string
        str[i++] = receivedChar;
    }

    // Null-terminate the string
    str[i] = '\0';
}
