/*
 * cli.c
 *
 *  Created on: 18.08.2019
 *      Author: michjm
 */

// Includes
#include <options.h>
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "rtc.h"
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOS_CLI.h"
#include "mainApp.h"
#include "sdcard.h"
#include "terminal.h"


void printHeader();


// Command prototypes
static BaseType_t whoami_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t reset_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t sysinfo_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t fsdcard_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t startmsc_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );
static BaseType_t stopmsc_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString );


// Command definitions
static const CLI_Command_Definition_t whoami_def =    { "whoami",
													    "whoami:\r\n Display device information\r\n\r\n",
													     whoami_cmd, 0 };

static const CLI_Command_Definition_t reset_def =    { "reset",
													    "reset:\r\n system software restart\r\n\r\n",
													     reset_cmd, 0 };


static const CLI_Command_Definition_t sysinfo_def =    { "sysinfo",
													     "sysinfo:\r\n Display system information\r\n\r\n",
													     sysinfo_cmd, 0 };



static const CLI_Command_Definition_t fsdcard_def =    { "fsdcard",
													    "fsdcard:\r\n format Sd Card now\r\n\r\n",
													     fsdcard_cmd,
														 0 };

static const CLI_Command_Definition_t startmsc_def = { "startmsc",
														 "startmsc:\r\n mount mass storage device\r\n\r\n",
														 startmsc_cmd,
														 0 };

static const CLI_Command_Definition_t stopmsc_def =  { "stopmsc",
														 "stopmsc:\r\n unmount mass storage device\r\n\r\n",
														 stopmsc_cmd,
														 0 };



/* ====================================================================
 * @brief  Initialize the cli
 * @param  None
 * @retval None
 * ==================================================================== */
void cli_init( void )
{
  // Register all known commands
  FreeRTOS_CLIRegisterCommand( &whoami_def );
  FreeRTOS_CLIRegisterCommand( &reset_def );
  FreeRTOS_CLIRegisterCommand( &sysinfo_def );
  FreeRTOS_CLIRegisterCommand( &fsdcard_def );
  FreeRTOS_CLIRegisterCommand( &startmsc_def );
  FreeRTOS_CLIRegisterCommand( &stopmsc_def );

}

/* ====================================================================
 * @brief  Command: whoami
 * @param  pcWriteBuffer
 * @retval None
 * ==================================================================== */
static BaseType_t whoami_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
  // Clear output buffer
  *pcWriteBuffer = 0x00;

  printHeader();

  // No more data to write
  return pdFALSE;
}




/* ====================================================================
 * @brief  Command: reset
 * @param  pcWriteBuffer
 * @retval None
 * ==================================================================== */
static BaseType_t reset_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
  // Clear output buffer
  *pcWriteBuffer = 0x00;

  NVIC_SystemReset();

  // No more data to write
  return pdFALSE;
}



/* ====================================================================
 * @brief  Command: whoami
 * @param  pcWriteBuffer
 * @retval None
 * ==================================================================== */
static BaseType_t fsdcard_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
  // Clear output buffer
  *pcWriteBuffer = 0x00;

  // Write output to buffer
  strcpy( pcWriteBuffer, "sd format started, please wait ...\r\n" );
  short ret = sdcard_formatSdCard();
  if (ret == DEVICE_OKAY){
	  strcpy( pcWriteBuffer, "format success\r\n" );
	  strcat( pcWriteBuffer, "\r\n\r\n" );
  }
  else{
	  strcpy( pcWriteBuffer, "format ERROR\r\n" );
	  strcat( pcWriteBuffer, "\r\n\r\n" );
  }

  // No more data to write
  return pdFALSE;
}


/* ====================================================================
 * @brief  Command: sysinfo
 * @param  pcWriteBuffer
 * @retval None
 * ==================================================================== */
static BaseType_t sysinfo_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
  static TaskStatus_t *tasks = NULL;
  static UBaseType_t nTasks = 0;
  static UBaseType_t iTask = 0;
  static unsigned long totalRunTime = 0;
  unsigned long percTime;

  // Clear output buffer
  *pcWriteBuffer = 0x00;

  // Function called for the first time
  if ( nTasks == 0 ) {

    // Number of tasks
    nTasks = uxTaskGetNumberOfTasks();

    // Allocate the array containing the task info
    tasks = pvPortMalloc( nTasks * sizeof(TaskStatus_t) );

    // Return error message if memory can not be allocated
    if ( tasks == NULL ) {
      nTasks = 0;
      strcpy( pcWriteBuffer, "Error: Task list could not be generated.\r\n\r\n" );
      return pdFALSE;
    }

    // Get system state
    nTasks = uxTaskGetSystemState( tasks, nTasks, &totalRunTime );

    // Percentage for run time calculation
    totalRunTime /= 100;

    // Header
    strcpy( pcWriteBuffer, "Task name                Run time  Free stack\r\n---------------------------------------------\r\n" );
    return pdTRUE;
  }

  // Avoid division by zero
  if ( totalRunTime > 0 ) {

    // Run time as percentage
    percTime = tasks[iTask].ulRunTimeCounter / totalRunTime;

    // Write the line
    sprintf( pcWriteBuffer, "%-16s%10lu%6lu%%%10d B\r\n", tasks[iTask].pcTaskName, tasks[iTask].ulRunTimeCounter, percTime, tasks[iTask].usStackHighWaterMark
        * 4 );

    // Increase i for next output line and return pdTRUE to indicate remaining tasks
    iTask += 1;
    if ( iTask < nTasks ) return pdTRUE;
  }

  // Get free heap size
  size_t freeHeap = xPortGetFreeHeapSize();
  size_t minHeap = xPortGetMinimumEverFreeHeapSize();

  // Report heap sizes
  char hlp[50];
  strcat( pcWriteBuffer, "---------------------------------------------\r\n" );
  sprintf( hlp, "Free heap         %10d B\r\n", freeHeap );
  strcat( pcWriteBuffer, hlp );
  sprintf( hlp, "Minimum free heap %10d B\r\n", minHeap );
  strcat( pcWriteBuffer, hlp );
  strcat( pcWriteBuffer, "---------------------------------------------\r\n\r\n" );

  // Last task, free memory, reset counter for new command
  vPortFree( tasks );
  nTasks = 0;
  iTask = 0;

  // Return
  return pdFALSE;
}


/* ====================================================================
 * @brief  Command: startmsc
 * @param  pcWriteBuffer
 * @retval None
 * ==================================================================== */
static BaseType_t startmsc_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
  // Clear output buffer
  *pcWriteBuffer = 0x00;

  start_msd();

  // Additional lines to write
  return pdFALSE;
}


/* ====================================================================
 * @brief  Command: stopmsc
 * @param  pcWriteBuffer
 * @retval None
 * ==================================================================== */
static BaseType_t stopmsc_cmd( char *pcWriteBuffer, size_t xWriteBufferLen, const char *pcCommandString )
{
  // Clear output buffer
  *pcWriteBuffer = 0x00;

  stop_msd();

  // Additional lines to write
  return pdFALSE;
}


