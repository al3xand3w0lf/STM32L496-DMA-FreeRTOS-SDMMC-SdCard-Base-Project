/*
 * sdcard.h
 *
 *  Created on: 06.09.2019
 *      Author: michjm
 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

// Includes
#include "main.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include "ff.h"

// Define SD card ID
#define SDCARD_ID 0b00001000

// Define buffer and stack size
//TODO: optimize buffer size
#define SDCARD_TX_BUFFER_SIZE 4096

// Message buffer handle
extern MessageBufferHandle_t sdcardTxBuffer;

// Task handle
extern TaskHandle_t sdcardTxTaskHandle;

// Semaphore handle
extern SemaphoreHandle_t sdCard_gatekeeper;

// Function prototypes
void sdcard_init( void );
void sdcard_deInit( void );
short sdcard_formatSdCard();

FRESULT sdcard_getFilesize( char *fileName, FSIZE_t *filesize );
FRESULT sdcard_read( char *, uint8_t *, UINT, UINT * );
FRESULT sdcard_write( char *, uint8_t *, UINT, UINT * , BYTE );

#endif /* INC_SDCARD_H_ */


