/*
 * sdcard.c
 *
 *  Created on: 06.09.2019
 *      Author: michjm
 */

// Includes
#include <options.h>
#include "sdcard.h"
#include "FreeRTOS.h"
#include "task.h"
#include "message_buffer.h"
#include "ff.h"
#include "fatfs.h"
#include "bsp_driver_sd.h"
#include "rtc.h"
#include "stdio.h"
#include "string.h"


// Define stack size
// TODO: optimize stack sizes
#define SDCARD_TX_STACK_SIZE 1500  // Stack size in words

// Task handle
TaskHandle_t sdcardTxTaskHandle = NULL;

// Message buffer handle
MessageBufferHandle_t sdcardTxBuffer = NULL;

// sdCardSemaphoreHandle
SemaphoreHandle_t sdCard_gatekeeper = NULL;

// Function prototypes for the task
//void sdcardTxTask( void *pvParameters );

// Other function prototypes
status_t sdcard_test( void );
void sdcard_newfile( void );

/* ====================================================================
 * @brief  Initialize the SD card
 * @param  None
 * @retval None
 * ==================================================================== */
void sdcard_init( void )
{
  // Set SD card status
  DEVICE_STATUS.sdcard = DEVICE_OKAY;

  // Create message buffer
  sdcardTxBuffer = xMessageBufferCreate( SDCARD_TX_BUFFER_SIZE );

  // create a mutex for SdCard protection - create first, will be used in following functions
  sdCard_gatekeeper = xSemaphoreCreateMutex();

  // Check if SD card is correctly inserted
  if ( BSP_SD_IsDetected() != SD_PRESENT ) {
    DEVICE_STATUS.sdcard = DEVICE_FAIL;
    return;
  } else {

    // Initialize FAT file system
    MX_FATFS_Init();

    // Mount file system
    if ( f_mount( &SDFatFS, SDPath, 0 ) != FR_OK )
    	DEVICE_STATUS.sdcard = DEVICE_FAIL;
  }

  // Test SD card and file system
  if ( DEVICE_STATUS.sdcard == DEVICE_OKAY )
	  DEVICE_STATUS.sdcard = sdcard_test();

  // SD card is not ready
  if ( DEVICE_STATUS.sdcard == DEVICE_FAIL ) {
    f_mount( NULL, SDPath, 0 );
    FATFS_UnLinkDriver( SDPath );
    return;
  }

  /*
  // Create TX task
  BaseType_t ret;
  ret = xTaskCreate( sdcardTxTask, "SDcard TX", SDCARD_TX_STACK_SIZE, NULL, 1, &sdcardTxTaskHandle );
  if ( ret != pdPASS ) for ( ;; ) {
  }
  */

}

/* ====================================================================
 * @brief  Deinitialize the SD card
 * @param  None
 * @retval None
 * ==================================================================== */
void sdcard_deInit( void )
{
  // Delete message buffer
  vMessageBufferDelete( sdcardTxBuffer );

  // delete semaphore protection
  vSemaphoreDelete( sdCard_gatekeeper );

  // Delete TX task
  vTaskDelete( sdcardTxTaskHandle );

  // Unmount file system
  f_mount( NULL, SDPath, 0 );

  // Unlink driver
  FATFS_UnLinkDriver( SDPath );

  // Set status
  DEVICE_STATUS.sdcard = DEVICE_FAIL;
}

/* ====================================================================
 * @brief  SD card transmit (TX) task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ====================================================================
void sdcardTxTask( void * pvParameters )
{
  // Number of received bytes
  FRESULT res;
  size_t nBytes = 0;

  // Local buffer
  uint8_t buffer[SDCARD_TX_BUFFER_SIZE];

  // Endless loop
  for ( ;; ) {
    // Wait for new data to arrive
    nBytes = xMessageBufferReceive( sdcardTxBuffer, buffer, SDCARD_TX_BUFFER_SIZE, portMAX_DELAY );



    strcpy(OPTIONS.file_name, "halloW.txt");  // Init Device name

    // Write bytes to SD card
    UINT nWrite = 0;
    res = sdcard_write( OPTIONS.file_name, buffer, nBytes, &nWrite ,  FA_OPEN_APPEND | FA_WRITE );
    if(res != FR_OK){
    	  DEVICE_STATUS.sdcard = DEVICE_FAIL;
    }
  }

  // Delete task
  vTaskDelete( NULL );
}
*/



/* ====================================================================
 * @brief  Read bytes from SD card
 * @param  fileName: Name of file
 *         buffer  : Read buffer
 *         nToRead : Number of bytes to read
 *         nRead   : Numbe rof bytes actually read
 * @retval File function return code
 * ==================================================================== */
FRESULT sdcard_getFilesize( char *fileName, FSIZE_t *filesize )
{
  FRESULT res = FR_DISK_ERR;
  FIL fp;

  volatile FSIZE_t filesize_intern = 0;

  // Read data from file
  res = f_open( &fp, fileName, FA_READ );
  if ( res == FR_OK ) {

	  filesize_intern = f_size(&fp);
	  *filesize = filesize_intern;
	  //res = f_read( &fp, buffer, nToRead, nRead );
    f_close( &fp );
  }

  return res;
}





/* ====================================================================
 * @brief  Read bytes from SD card
 * @param  fileName: Name of file
 *         buffer  : Read buffer
 *         nToRead : Number of bytes to read
 *         nRead   : Numbe rof bytes actually read
 * @retval File function return code
 * ==================================================================== */
FRESULT sdcard_read( char *fileName, uint8_t *buffer, UINT nToRead, UINT *nRead )
{
  FRESULT res = FR_DISK_ERR;
  FIL fp;

  // Set read characters to zero
  *nRead = 0;

  // Read data from file
  res = f_open( &fp, fileName, FA_READ );
  if ( res == FR_OK ) {
    res = f_read( &fp, buffer, nToRead, nRead );
    f_close( &fp );
  }

  // Return status
  return res;
}

/* ====================================================================
 * @brief  Write bytes to SD card
 * @param  fileName: Name of file
 *         buffer  : Write buffer
 *         nToWrite: Number of bytes to write
 *         nWrite  : Numbe rof bytes actually written
 * @retval File function return code
 * ==================================================================== */
FRESULT sdcard_write( char *fileName, uint8_t *buffer, UINT nToWrite, UINT *nWrite, BYTE mode )
{
  FRESULT res = FR_DISK_ERR;

  // Set written characters to zero
  *nWrite = 0;

  // Write data to file
  //res = f_open( &OPTIONS.fp, fileName, FA_OPEN_APPEND | FA_WRITE );
  res = f_open( &OPTIONS.fp, fileName, mode );
  if ( res == FR_OK ) {
    res = f_write( &OPTIONS.fp, buffer, nToWrite, nWrite );
    f_close( &OPTIONS.fp );
  }

  // Return status
  return res;
}






/* ====================================================================
 * @brief  format Sd card
 * @param  None
 * @retval SD card status
 * ==================================================================== */
short sdcard_formatSdCard( )
{
  uint8_t workBuffer[2 * _MAX_SS];

  if(f_mkfs(SDPath, FM_ANY, 0, workBuffer, sizeof(workBuffer)) != FR_OK)
	  return DEVICE_FAIL;
  return DEVICE_OKAY;

}



/* ====================================================================
 * @brief  Test file operations on SD card
 * @param  None
 * @retval SD card status
 * ==================================================================== */
status_t sdcard_test( )
{
  FRESULT res = FR_DISK_ERR;
  UINT nWrite, nRead;
  uint8_t textWrite[] = "This is Alex working with SD card file System";
  uint8_t textRead[50];
  char fileName[] = "HalloWord.txt";

  // Write data
  res = sdcard_write( fileName, textWrite, sizeof(textWrite), &nWrite ,  FA_OPEN_APPEND | FA_WRITE );

  // Read data
  if ( res == FR_OK )
	  res = sdcard_read( fileName, textRead, sizeof(textWrite), &nRead );

  // Delete file and compare number of bytes
  if ( res == FR_OK ) {
    res = f_unlink( fileName );
    if ( nRead == nWrite )
    	return DEVICE_OKAY;
  }

  // Something went wrong
  return DEVICE_FAIL;
}

