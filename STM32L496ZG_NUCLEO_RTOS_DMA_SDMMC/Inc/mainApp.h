/*
 * mainApp.h
 *
 *  Created on: 15.08.2019
 *      Author: michjm
 */

#ifndef INC_MAINAPP_H_
#define INC_MAINAPP_H_

// Includes
#include "sys/_stdint.h"
#include "FreeRTOS.h"
#include "queue.h"
#include "task.h"

// ==========================================================================
// ALLOWED EVENTS
// ==========================================================================
typedef enum {
  EVENT_BUTTON_SHORT = 0U,
  EVENT_BUTTON_MEDIUM,
  EVENT_BUTTON_LONG,
  EVENT_BUTTON_DOUBLE,
  EVENT_USB_CONNECTION,
} event_t;
// ==========================================================================



// Task handle
extern TaskHandle_t powerMonitorTaskHandle;

// Event queue handle
extern QueueHandle_t eventQueueHandle;

// Function prototypes
void mainApp_start( void );


#endif /* INC_MAINAPP_H_ */
