/*
 * options.c
 *
 *  Created on: 08.09.2019
 *      Author: michjm
 */

// Includes
#include <options.h>
#include "sdcard.h"
#include "string.h"
#include "stdio.h"


// ==========================================================================
// FIRMWARE AND SERIAL NUMBER
// ==========================================================================
const uint8_t FW_VERSION = 1;
const uint8_t FW_VERSION_SUB = 00;



// ==========================================================================
// DEVICE STATUS
// ==========================================================================

// Device status
device_status_t DEVICE_STATUS;




// USB connection status
usb_status_t USB_STATUS;

// ==========================================================================
// OPTIONS
// ==========================================================================

// MRAM addresses for MRAM test and to store the options
// TODO: somehow define option area and data area (in case data should be stored on MRAM)
const uint16_t MRAM_ADDRESS_TST = 0x7FF9;
const uint16_t MRAM_ADDRESS_OPT = 0x7FE4;

// Options
options_t OPTIONS;

/* ====================================================================
 * @brief  Initialize all options
 * @param  None
 * @retval None
 * ==================================================================== */
void options_init( void )
{
  // Device status

  DEVICE_STATUS.button = DEVICE_FAIL;
  DEVICE_STATUS.led2 = DEVICE_FAIL;
  DEVICE_STATUS.sdcard = DEVICE_FAIL;
  DEVICE_STATUS.terminal = DEVICE_FAIL;

  // USB connection status
  USB_STATUS = USB_NOT_CONNECTED;

  // Options
  OPTIONS.device_name[0]   = 0x00;
  OPTIONS.device_serial[0] = 0x00;
  OPTIONS.file_name[0]     = 0x00;

  strcpy(OPTIONS.device_name, "Hallo World");  // Init Device name

  uint64_t value = 0;
  sprintf( OPTIONS.device_serial, "%d", (int)value );

}

/* ====================================================================
 * @brief  Read options from MRAM or SD Card
 * @param  None
 * @retval None
 * ==================================================================== */
void options_read( void )
{
	char *result_ptr = 0;
	uint8_t buffer[2000], stn_out[10];
	FSIZE_t filesize = 0;
	UINT *nRead = 0;
	FRESULT res = FR_DISK_ERR;
	uint8_t i = 0;

	if(DEVICE_STATUS.sdcard == DEVICE_OKAY){
		if(xSemaphoreTake(sdCard_gatekeeper, 1000)){
			__NOP();
		}
		xSemaphoreGive(sdCard_gatekeeper);
	  }


}

/* ====================================================================
 * @brief  Write options to MRAM
 * @param  None
 * @retval None
 * ==================================================================== */
void options_write( void )
{
	  UINT nWrite;
	  char textWrite[200] = "";
	  char fileName[] = "config.txt";

	  if(xSemaphoreTake(sdCard_gatekeeper, 1000)){
		  __NOP();
		  xSemaphoreGive(sdCard_gatekeeper);
	  }
}
