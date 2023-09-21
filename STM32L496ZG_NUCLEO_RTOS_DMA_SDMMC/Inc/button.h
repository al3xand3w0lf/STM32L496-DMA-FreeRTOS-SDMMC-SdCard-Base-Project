/*
 * button.h
 *
 *  Created on: 15.08.2019
 *      Author: michjm
 *      Author: awolf
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

// Includes
#include "FreeRTOS.h"
#include "task.h"

// Task handle
extern TaskHandle_t buttonTaskHandle;

// Function prototypes
void button_init( void );
void button_deInit( void );

#endif /* INC_BUTTON_H_ */
