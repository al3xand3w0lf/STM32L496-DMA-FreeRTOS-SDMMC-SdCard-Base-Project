/*
 * terminal.h
 *
 *  Created on: 17.08.2019
 *      Author: michjm
 *      Author: awolf
 */

#ifndef INC_TERMINAL_H_
#define INC_TERMINAL_H_

// Includes
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"

// Define terminal ID
#define TERMINAL_ID 0b00000001

// Define buffer sizes
//TODO: optimize buffer sizes

#define TERMINAL_RX_BUFFER_SIZE 4096
#define TERMINAL_TX_BUFFER_SIZE 4096

// Message buffer handle
extern MessageBufferHandle_t terminalTxBuffer;

// Task handles
extern TaskHandle_t terminalTxTaskHandle;
extern TaskHandle_t terminalRxTaskHandle;

// Function prototypes
void terminal_init( UART_HandleTypeDef *huart );
void terminal_deInit( void );

void to_terminal( const char * );



#endif /* INC_TERMINAL_H_ */
