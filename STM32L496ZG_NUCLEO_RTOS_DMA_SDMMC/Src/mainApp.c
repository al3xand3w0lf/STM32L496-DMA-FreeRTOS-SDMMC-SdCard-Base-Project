/*
 * mainApp.c
 *
 *  Created on: 15.08.2019
 *      Author: michjm
 */

// Includes
#include <options.h>
#include "main.h"
#include "usb_device.h"
#include "mainApp.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "sdcard.h"
#include "rtc.h"
#include "button.h"
#include "terminal.h"



// Define stack sizes
// TODO: adapt size
//#define MAINAPP_STACK_SIZE 4096 // Stack size in words
#define MAINAPP_STACK_SIZE 512  // Stack size in words
#define SYNCRTC_STACK_SIZE 128  // Stack size in words

// Maximum number of buffered events
// TODO: adapt size
#define EVENT_QUEUE_SIZE 10

// Double click speed (in ms and ticks)
#define BUTTON_DOUBLE_TIMEOUT_MS 300
TickType_t BUTTON_DOUBLE_TIMEOUT;



// Allowed application states of FSM
typedef enum {
  STATE_IDLE = 0U, STATE_MSD,
} state_t;

// Current and previous application state
state_t MAINAPP_STATE;
state_t PREVAPP_STATE;

// Event queue handle
QueueHandle_t eventQueueHandle = NULL;

// Task handles
TaskHandle_t mainAppTaskHandle = NULL;
TaskHandle_t blinkyLedTaskHandle = NULL;


// External peripheral handles
extern TIM_HandleTypeDef htim1;
extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart3;




// Function prototypes for the tasks
void mainAppTask( void * pvParameters );
void blinkyLedTask( void * pvParameters );


// Function prototypes for changing the app state
void start_idle( void );
void start_msd( void );
void stop_msd( void );
void vApplicationIdleHook(void);

void printHeader();


uint32_t freeHeap = 0;


/* ====================================================================
 * @brief  Idle Hook funktion, sleep here in idle mode
 * @param  None
 * @retval None
 * ==================================================================== */
void vApplicationIdleHook( void )
{
	if( MAINAPP_STATE != STATE_MSD)
		__WFI();
}



/* ====================================================================
 * @brief  Initialize the main app
 * @param  None
 * @retval None
 * ==================================================================== */
void mainApp_start( void )
{

  BaseType_t ret;

  // Compute button double click timeout in ticks
  BUTTON_DOUBLE_TIMEOUT = pdMS_TO_TICKS( BUTTON_DOUBLE_TIMEOUT_MS );

  // Create event queue
  eventQueueHandle = xQueueCreate( EVENT_QUEUE_SIZE, sizeof(event_t) );
  vQueueAddToRegistry( eventQueueHandle, "Event queue" ); // TODO: remove for release

  // Initialize all peripherals here
  terminal_init( &hlpuart1 );
  button_init();
  sdcard_init();
  printHeader();
  cli_init();
  freeHeap = xPortGetFreeHeapSize();

  MAINAPP_STATE = STATE_IDLE;

  ret = xTaskCreate( blinkyLedTask, "Blinky LED task", MAINAPP_STACK_SIZE, NULL, 1, &blinkyLedTaskHandle );
  if ( ret != pdPASS ) for ( ;; ) {
  }

  // Create main app task
  ret = xTaskCreate( mainAppTask, "MainApp task", MAINAPP_STACK_SIZE, NULL, 1, &mainAppTaskHandle );
  if ( ret != pdPASS ) for ( ;; ) {
  }



}




/* ====================================================================
 * @brief  Blinky LE task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ==================================================================== */
void blinkyLedTask( void * pvParameters )
{

  if(DEVICE_STATUS.sdcard == DEVICE_OKAY){
	  for ( ;; ) {
			HAL_GPIO_WritePin(LED_NUCLEO_RED_GPIO_Port  , LED_NUCLEO_RED_Pin  , SET   );
			HAL_GPIO_WritePin(LED_NUCLEO_BLUE_GPIO_Port , LED_NUCLEO_BLUE_Pin , RESET );
			HAL_GPIO_WritePin(LED_NUCLEO_GREEN_GPIO_Port, LED_NUCLEO_GREEN_Pin, RESET );
			vTaskDelay( pdMS_TO_TICKS( 150 ) );

			HAL_GPIO_WritePin(LED_NUCLEO_RED_GPIO_Port  , LED_NUCLEO_RED_Pin  , RESET   );
			HAL_GPIO_WritePin(LED_NUCLEO_BLUE_GPIO_Port , LED_NUCLEO_BLUE_Pin , SET   );
			HAL_GPIO_WritePin(LED_NUCLEO_GREEN_GPIO_Port, LED_NUCLEO_GREEN_Pin, RESET   );
			vTaskDelay( pdMS_TO_TICKS( 150 ) );

			HAL_GPIO_WritePin(LED_NUCLEO_RED_GPIO_Port  , LED_NUCLEO_RED_Pin  , RESET   );
			HAL_GPIO_WritePin(LED_NUCLEO_BLUE_GPIO_Port , LED_NUCLEO_BLUE_Pin , RESET   );
			HAL_GPIO_WritePin(LED_NUCLEO_GREEN_GPIO_Port, LED_NUCLEO_GREEN_Pin, SET   );
			vTaskDelay( pdMS_TO_TICKS( 150 ) );

			HAL_GPIO_WritePin(LED_NUCLEO_RED_GPIO_Port  , LED_NUCLEO_RED_Pin  , RESET   );
			HAL_GPIO_WritePin(LED_NUCLEO_BLUE_GPIO_Port , LED_NUCLEO_BLUE_Pin , SET );
			HAL_GPIO_WritePin(LED_NUCLEO_GREEN_GPIO_Port, LED_NUCLEO_GREEN_Pin, RESET );
			vTaskDelay( pdMS_TO_TICKS( 150 ) );


		  }
  }
  else{
	  for ( ;; ) {
			HAL_GPIO_WritePin(LED_NUCLEO_RED_GPIO_Port  , LED_NUCLEO_RED_Pin  , SET   );
			HAL_GPIO_WritePin(LED_NUCLEO_BLUE_GPIO_Port , LED_NUCLEO_BLUE_Pin , RESET );
			HAL_GPIO_WritePin(LED_NUCLEO_GREEN_GPIO_Port, LED_NUCLEO_GREEN_Pin, RESET );
			vTaskDelay( pdMS_TO_TICKS( 250 ) );

			HAL_GPIO_WritePin(LED_NUCLEO_RED_GPIO_Port  , LED_NUCLEO_RED_Pin  , RESET   );
			HAL_GPIO_WritePin(LED_NUCLEO_BLUE_GPIO_Port , LED_NUCLEO_BLUE_Pin , RESET   );
			HAL_GPIO_WritePin(LED_NUCLEO_GREEN_GPIO_Port, LED_NUCLEO_GREEN_Pin, RESET   );
			vTaskDelay( pdMS_TO_TICKS( 250 ) );
		  }
  }
}


/* ====================================================================
 * @brief  Main application task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ==================================================================== */
void mainAppTask( void * pvParameters )
{
  // Current event
  event_t event, event2;

  // Main event loop
  for ( ;; ) {

    // Wait for a new event (no timeout here)
    xQueueReceive( eventQueueHandle, &event, portMAX_DELAY );

    // Check for button double click (wait for a new EVENT_BUTTON_SHORT)
    if ( event == EVENT_BUTTON_SHORT ) {
		  BaseType_t ret = xQueuePeek( eventQueueHandle, &event2, BUTTON_DOUBLE_TIMEOUT );
		  if ( ret == pdTRUE && event2 == EVENT_BUTTON_SHORT ) {
			xQueueReceive( eventQueueHandle, &event2, portMAX_DELAY ); // Remove second press from queue
			event = EVENT_BUTTON_DOUBLE;
		  }
    }

    // maybe do something here
    if ( event == EVENT_BUTTON_LONG ) {
		  //TODO: maybe do something here
    	  __NOP();
		  continue;
    }

    // maybe do something here
    if (event == EVENT_BUTTON_DOUBLE) {
		  //TODO: maybe do something here
    	  __NOP();
		  continue;
    }


    // Update USB connection status
    if ( HAL_GPIO_ReadPin( USB_CONNECT_GPIO_Port, USB_CONNECT_Pin ) == GPIO_PIN_SET )
    	USB_STATUS = USB_CONNECTED;
    else
    	USB_STATUS = USB_NOT_CONNECTED;


    // ==========================================================================
    // Handle events depending on state
    // ==========================================================================
    switch ( MAINAPP_STATE ) {

		case STATE_IDLE:
		  // Short press while connected -> start MSD mode
		  if ( event == EVENT_BUTTON_SHORT && USB_STATUS == USB_CONNECTED )
			  start_msd();

		  // Medium press -> start record mode
		  if ( event == EVENT_BUTTON_MEDIUM )
			  __NOP();


		  break;

		case STATE_MSD:

		  // Short press -> stop MSD mode
		  if ( event == EVENT_BUTTON_SHORT )
			  stop_msd();

		  // Disconnection from USB port -> stop MSD mode
		  if ( event == EVENT_USB_CONNECTION && USB_STATUS == USB_NOT_CONNECTED )
			  stop_msd();

		  break;

		default:
		  break;
    	}

  }

  // Delete task
  vTaskDelete( NULL );

}


/* ====================================================================
 * @brief  Start MSD mode
 * @param  None
 * @retval None
 * ==================================================================== */
void start_msd( void )
{

  if (( (MAINAPP_STATE == STATE_IDLE)) && USB_STATUS == USB_CONNECTED ){
	  MX_USB_DEVICE_Init();
	  to_terminal("> USB Mass Storage mode, please wait a bit...\r\n");
	  MAINAPP_STATE = STATE_MSD;
  	  }
  else{
	  if ( USB_STATUS != USB_CONNECTED )
		  __NOP(); //to_terminal("> USB Not Connected\r\n\r\n" );
	  else{
		  __NOP();
		  }
	  }
}

/* ====================================================================
 * @brief  Stop MSD mode
 * @param  None
 * @retval None
 * ==================================================================== */
void stop_msd( void )
{

  if ( MAINAPP_STATE == STATE_MSD){
	  MX_USB_DEVICE_DeInit();
	  MAINAPP_STATE = STATE_IDLE;
	  to_terminal("> USB Mass Storage disabled\r\n");
  	  }
  else
	  to_terminal("> USB Mass Storage was not enabled\r\n");

}




/* ====================================================================
 * @brief  Print HEader
 * @param  None
 * @retval None
 * ==================================================================== */
void printHeader(){

    to_terminal("\r\n\r\n");
	to_terminal(" ------------------------------------\r\n");
	to_terminal("\r\n");
	to_terminal("\r\n");
	to_terminal("  STM32496ZG Nucleo Board\r\n");
	to_terminal("     - RTOS\r\n");
	to_terminal("     - UART DMA\r\n");
	to_terminal("     - DMA SDMMC\r\n");
	to_terminal("     - CLI terminal\r\n");
	to_terminal("     - Segger System Vie\r\n");
	to_terminal("\r\n");
	to_terminal("  Created by:\r\n");
	to_terminal("     Alexander Wolf\r\n");
	to_terminal("\r\n");
	to_terminal("\r\n");
	to_terminal(" ------------------------------------\r\n");
	to_terminal("\r\n");
	to_terminal("> ");

}

