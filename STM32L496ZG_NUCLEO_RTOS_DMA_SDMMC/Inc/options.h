/*
 * options.h
 *
 *  Created on: 07.09.2019
 *      Author: michjm
 */

#ifndef INC_OPTIONS_H_
#define INC_OPTIONS_H_

// Includes
#include "sys/_stdint.h"
#include "ff.h"

extern const uint16_t BATT_CAPACITY;
extern const uint16_t BATT_ENERGY;


// ==========================================================================
// FIRMWARE AND SERIAL NUMBER
// ==========================================================================
extern const uint8_t FW_VERSION;
extern const uint8_t FW_VERSION_SUB;

// ==========================================================================
// DEVICE STATUS
// ==========================================================================

// Device status
typedef enum {
  DEVICE_OKAY = 0U, DEVICE_FAIL,
} status_t;

typedef struct {
  status_t button;
  status_t led2;
  status_t terminal;
  status_t sdcard;
} device_status_t;

extern device_status_t DEVICE_STATUS;


// USB connection status
typedef enum {
  USB_CONNECTED = 0U, USB_NOT_CONNECTED,
} usb_status_t;

extern usb_status_t USB_STATUS;

// ==========================================================================
// OPTIONS
// ==========================================================================


// Options
typedef struct {
  char device_name[19];      // EOS device name (8chr and \0)
  char device_serial[9];     // EOS device name (8chr and \0)
  char file_name[50];       // ubx file name (nnnnnnnn_yyyy_mm_dd_H.ubx and \0)
  FIL fp;                   // Handle to open file (else NULL)
  int8_t  error;     		// recent error flags

} options_t;

extern options_t OPTIONS;

// Function prototypes
void options_init( void );
void options_write( void );
void options_read( void );

#endif /* INC_OPTIONS_H_ */
