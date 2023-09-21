/*
 * button.c
 *
 *  Created on: 15.08.2019
 *      Author: michjm
 *      Author: awolf
 */

// Includes
#include <options.h>
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "mainApp.h"

// Press durations (ms)
#define SHORT_DURATION 10
#define MEDIUM_DURATION 1000
#define LONG_DURATION 5000

// Define stack size
// TODO: adapt size
#define BUTTON_STACK_SIZE 128 // Stack size in words

// Task handle
TaskHandle_t buttonTaskHandle;

// Function prototypes
void buttonTask( void * pvParameters );

/* ====================================================================
 * @brief  Initialize button
 * @param  None
 * @retval None
 * ==================================================================== */
void button_init( void )
{
  // Create button handling task
  BaseType_t ret;
  ret = xTaskCreate( buttonTask, "Button task", BUTTON_STACK_SIZE, NULL, 1, &buttonTaskHandle );
  if ( ret != pdPASS ) for ( ;; ) { }

  // Set button status
  DEVICE_STATUS.button = DEVICE_OKAY;
}

/* ====================================================================
 * @brief  Deinitialize button
 * @param  None
 * @retval None
 * ==================================================================== */
void button_deInit( void )
{
  // Delete button handling task
  vTaskDelete( buttonTaskHandle );

  // Set button status
  DEVICE_STATUS.button = DEVICE_FAIL;
}

/* ====================================================================
 * @brief  Button task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ==================================================================== */
void buttonTask( void * pvParameters )
{
  // Button press status, press duration, button event
  uint16_t state = 1;
  uint16_t duration = 0;
  event_t evt;

  // Endless loop
  for ( ;; ) {

    // Clear all pending events and wait for new button press event
    xTaskNotifyStateClear( NULL );
    xTaskNotifyWait( 0x00, 0x00, NULL, portMAX_DELAY );

    // Reset state and press duration
    state = 1;
    duration = 0;

    // De-bounce and check if pressed or released
    while ( 1 ) {
      state = (state << 1) | HAL_GPIO_ReadPin( BUTTON_1_GPIO_Port, BUTTON_1_Pin ); // Shift to left and set bit[0] to GPIO
      if ( state == 0xFFFF ) break;                                                // 16 ones  -> pressed
      if ( state == 0x0000 ) break;                                                // 16 zeros -> released
      vTaskDelay( pdMS_TO_TICKS( 1 ) );
    }

    // Skip button released event
    if ( state == 0x0000 ) continue;

    // Check button (in 10 ms steps) for release
    while ( 1 ) {
      if ( !HAL_GPIO_ReadPin( BUTTON_1_GPIO_Port, BUTTON_1_Pin ) || duration > LONG_DURATION ) break;
      duration += 10;
      vTaskDelay( pdMS_TO_TICKS( 10 ) );
    }

    // Set press duration
    if ( duration < MEDIUM_DURATION ) evt = EVENT_BUTTON_SHORT;
    else if ( duration > LONG_DURATION ) evt = EVENT_BUTTON_LONG;
    else evt = EVENT_BUTTON_MEDIUM;

    // Enqueue button press event
    xQueueSend( eventQueueHandle, &evt, portMAX_DELAY );
  }

  // Delete task
  vTaskDelete( NULL );
}





