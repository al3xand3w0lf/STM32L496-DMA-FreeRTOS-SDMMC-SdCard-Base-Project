/*
 * terminal.c
 *
 *  Created on: 17.08.2019
 *      Author: michjm
 *      Author: awolf
 */

// Includes
#include <options.h>
#include "string.h"
#include "terminal.h"
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
//#include "cli.h"
//#include "FreeRTOS_CLI.h"

// Define stack sizes
// TODO: optimize stack sizes
#define TERMINAL_RX_STACK_SIZE 1500  // Stack size in words
#define TERMINAL_TX_STACK_SIZE 1500  // Stack size in words

// Define maximum length of a command and of output
#define MAX_INPUT_SIZE  250  // Maximum length of a command (incl parameters)
#define MAX_OUTPUT_SIZE 250  // Maximum length of a command output

// TODO: Needed, see RX task
extern DMA_HandleTypeDef hdma_lpuart_rx;

// Terminal UART handle
UART_HandleTypeDef *huartTerminal = NULL;

// Task handles
TaskHandle_t terminalTxTaskHandle = NULL;
TaskHandle_t terminalRxTaskHandle = NULL;

// Message buffer handle
MessageBufferHandle_t terminalTxBuffer = NULL;

// Ring buffer for DMA transfer
uint8_t terminalRxBuffer[TERMINAL_RX_BUFFER_SIZE];

// Function prototypes for the tasks
void terminalTxTask( void *pvParameters );
void terminalRxTask( void *pvParameters );

// Other function prototypes
static uint8_t nextMessageByte( void );

/* ====================================================================
 * @brief  Initialize the terminal
 * @param  *huart: Handle to terminal UART
 * @retval None
 * ==================================================================== */
void terminal_init( UART_HandleTypeDef *huart )
{
  // Set status
  DEVICE_STATUS.terminal = DEVICE_FAIL;

  // Store UART handle
  huartTerminal = huart;

  // Create message buffer
  terminalTxBuffer = xMessageBufferCreate( TERMINAL_TX_BUFFER_SIZE );

  // Clear UART idle flag and enable IDLE LINE interrupt
  __HAL_UART_CLEAR_IDLEFLAG( huartTerminal );
  __HAL_UART_ENABLE_IT( huartTerminal, UART_IT_IDLE );

  // Start DMA based data reception
  HAL_UART_Receive_DMA( huartTerminal, terminalRxBuffer, TERMINAL_RX_BUFFER_SIZE );

  // Create RX and TX tasks
  BaseType_t ret;

  ret = xTaskCreate( terminalRxTask, "Terminal RX", TERMINAL_RX_STACK_SIZE, NULL, 1, &terminalRxTaskHandle );
  if ( ret != pdPASS ) for ( ;; ) {
  }


  ret = xTaskCreate( terminalTxTask, "Terminal TX", TERMINAL_TX_STACK_SIZE, NULL, 1, &terminalTxTaskHandle );
  if ( ret != pdPASS ) for ( ;; ) {
  }

  // Set status
  DEVICE_STATUS.terminal = DEVICE_OKAY;
}

/* ====================================================================
 * @brief  Deinitialize the terminal
 * @param  None
 * @retval None
 * ==================================================================== */
void terminal_deInit( void )
{
  // Disable IDLE_LINE interrupt and clear UART idle flag
  __HAL_UART_DISABLE_IT( huartTerminal, UART_IT_IDLE );
  __HAL_UART_CLEAR_IDLEFLAG( huartTerminal );

//  // Disable CM interrupt and clear CM flag
//  __HAL_UART_DISABLE_IT( huartTerminal, UART_IT_CM );
//  huartTerminal->Instance->ICR |= 1 << 17;

// Stop DMA transmission
  HAL_UART_DMAStop( huartTerminal );

  // Delete UART handle
  huartTerminal = NULL;

  // Delete message buffer
  vMessageBufferDelete( terminalTxBuffer );

  // Delete RX and TX tasks
  vTaskDelete( terminalRxTaskHandle );
  vTaskDelete( terminalTxTaskHandle );

  // Set status
  DEVICE_STATUS.terminal = DEVICE_FAIL;
}



/* ====================================================================
 * @brief  Deinitialize the terminal
 * @param  None
 * @retval None
 * ==================================================================== */
void terminal_reset( void )
{
  // Disable IDLE_LINE interrupt and clear UART idle flag
  __HAL_UART_DISABLE_IT( huartTerminal, UART_IT_IDLE );
  __HAL_UART_CLEAR_IDLEFLAG( huartTerminal );

  // Stop DMA transmission
  HAL_UART_DMAStop( huartTerminal );

  //HAL_UART_MspDeInit(huartTerminal);
  //MX_LPUART1_UART_Init();
  // Clear UART idle flag and enable IDLE LINE interrupt
  __HAL_UART_CLEAR_IDLEFLAG( huartTerminal );
  __HAL_UART_ENABLE_IT( huartTerminal, UART_IT_IDLE );

  // Start DMA based data reception
  HAL_UART_Receive_DMA( huartTerminal, terminalRxBuffer, TERMINAL_RX_BUFFER_SIZE );

}


/* ====================================================================
 * @brief  Terminal receive (RX) task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ==================================================================== */
void terminalRxTask( void *pvParameters )
{
  uint32_t len = 0;
  uint8_t nb;
  BaseType_t ret;

  // Command input and output buffers
  char cmdIn[MAX_INPUT_SIZE];
  char cmdOut[MAX_OUTPUT_SIZE];

  // Clear input string buffer
  memset( cmdIn, '\0', MAX_INPUT_SIZE );

  // Print command line character
  to_terminal( "> " );

  // Endless loop
  for ( ;; ) {

		// Get next character from terminal
		nb = nextMessageByte();

		// catch framing error:
		// reset dma and uart in case of framing error
		if(huartTerminal->ErrorCode != HAL_UART_ERROR_NONE){
			HAL_UART_Abort(huartTerminal);
			HAL_DMA_Abort(&hdma_lpuart_rx);
		    // Reset buffer
		    memset( cmdIn, '\0', MAX_INPUT_SIZE );
		    len = 0;
			terminal_reset();
		}
		else{

			// Echo back to terminal
			xMessageBufferSend( terminalTxBuffer, &nb, 1, 0 );

			// End of line detected: execute command
			if ( nb == '\n' || nb == '\r' ) {

			  // Add implicit '\n' to '\r'
			  if ( nb == '\r' ) to_terminal( "\n" );


			  // Execute command and print result
			  if ( len > 0 ) {
				do {
				  ret = FreeRTOS_CLIProcessCommand( cmdIn, cmdOut, MAX_OUTPUT_SIZE );
				  to_terminal( cmdOut );
				} while ( ret != pdFALSE );
			  }


			  // Reset buffer
			  memset( cmdIn, '\0', MAX_INPUT_SIZE );
			  len = 0;

			  // Print command line character
			  to_terminal( "> " );

			// Backspace or ASCII DEL detected
			} else if ( nb == '\b' || nb == 0x7F ) {
			  if ( len > 0 ) cmdIn[--len] = '\0';

			// Normal ASCII character detected
			} else if ( nb >= ' ' && nb <= '~' ) {
			  if ( len < MAX_INPUT_SIZE - 1 ) cmdIn[len++] = nb;
			}
		}
  }

  // Delete task
  vTaskDelete( NULL );
}

/* ====================================================================
 * @brief  Terminal transmit (TX) task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ==================================================================== */
void terminalTxTask( void * pvParameters )
{
  // Number of received bytes
  size_t nBytes = 0;

  // Local buffer
  uint8_t buffer[TERMINAL_TX_BUFFER_SIZE];

  // Endless loop
  for ( ;; ) {
    // Wait for new data to arrive
    nBytes = xMessageBufferReceive( terminalTxBuffer, buffer, TERMINAL_TX_BUFFER_SIZE, portMAX_DELAY );

    // Transmit bytes via DMA
    HAL_UART_Transmit_DMA( huartTerminal, buffer, nBytes );
    // Wait for transmission complete
    xTaskNotifyWait( 0x00, 0x00, NULL, portMAX_DELAY );
  }

  // Delete task
  vTaskDelete( NULL );
}

/* ====================================================================
 * @brief  Read next byte from terminal ring buffer
 * @param  None
 * @retval Next byte
 * ==================================================================== */
static uint8_t nextMessageByte( void )
{
  // Read and write positions
  static uint32_t toRead = 0;
  static uint32_t toWrite = 0;

  // Wait for new bytes to arrive
  if ( toRead == toWrite ) xTaskNotifyWait( 0x00, 0x00, &toWrite, portMAX_DELAY );

  // Read next byte from ring buffer
  uint8_t nextByte = terminalRxBuffer[toRead++];
  if ( toRead == TERMINAL_RX_BUFFER_SIZE ) {
    toRead = 0;
  }

  // Return byte
  return nextByte;
}

/* ====================================================================
 * @brief  Write a string to terminal
 * @param  *str: String
 * @retval None
 * ==================================================================== */
void to_terminal( const char * str )
{
  uint32_t len = strlen( str );

  if ( len > 0 )
	  xMessageBufferSend( terminalTxBuffer, (void * ) str, strlen( str ), 0 );
}

