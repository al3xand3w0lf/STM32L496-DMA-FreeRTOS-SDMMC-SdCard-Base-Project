/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "fatfs.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAINAPP_STACK_SIZE 512  // Stack size in words
#define SYNCRTC_STACK_SIZE 128  // Stack size in words
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
osThreadId startTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

// Task handles
TaskHandle_t LedGreenTaskHandle = NULL;
TaskHandle_t LedBlueTaskHandle = NULL;

// Function prototypes for the tasks
void LedBlueTask( void * pvParameters );
void LedGreenTask( void * pvParameters );


/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of startTask */
  osThreadDef(startTask, StartDefaultTask, osPriorityNormal, 0, 1000);
  startTaskHandle = osThreadCreate(osThread(startTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  // Create main app task


  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the startTask thread.
  * @param  argument: Not used
  * @retval None
  */

uint8_t SD_FileOperationsTest();

/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	//static int cnt = 0;
  volatile uint8_t result = 10;

  result = SD_FileOperationsTest();


  if(result == FR_OK){


	  BaseType_t ret;
	  ret = xTaskCreate( LedBlueTask, "Led Blue task", MAINAPP_STACK_SIZE, NULL, 1, &LedBlueTaskHandle );
	  if ( ret != pdPASS ) for ( ;; ) {
	  }

	  // Create RTC synchronization task
	  ret = xTaskCreate( LedGreenTask, "Led Green task", SYNCRTC_STACK_SIZE, NULL, 1, &LedGreenTaskHandle );
	  if ( ret != pdPASS ) for ( ;; ) {
	  }

	  vTaskDelete( NULL );
  }

  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(LED_R_GPIO_Port,LED_R_Pin);
    osDelay(200);
  }
  /* USER CODE END StartDefaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */



/**
 *  AW
  * @brief  Initializes SD Card and keeps it linked
  * 		SD Card is not UNLINKED from now on!
  * @param  None
  * @retval 0 == all fine
  * 		1+ == errors
  */

uint8_t SD_FileOperationsTest()
{
  FRESULT res;
  uint32_t byteswritten, bytesread;                     // File write/read counts
  uint8_t wtext[] = "STM32L496 AW: This is AW working with FatFs uSD + DMA + FreeRTOS + USB"; // File write buffer
  uint8_t rtext[100];                                   // File read buffer
  char fileNameIntern[40] = "STM32_AW_extendendFilename.TXT";


  // Register the file system object to the FatFs module /
  if(f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
  {
    // Create and Open a new text file object with write access
    //if(f_open(&SDFile, "STM32_AW.TXT", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
    if(f_open(&SDFile, fileNameIntern, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
    {
      // Write data to the text file
      res = f_write(&SDFile, wtext, sizeof(wtext), (void *)&byteswritten);

      if((byteswritten > 0) && (res == FR_OK))
      {
        // Close the open text file
        f_close(&SDFile);

        // Open the text file object with read access
        if(f_open(&SDFile, fileNameIntern, FA_READ) == FR_OK)
        {
          // Read data from the text file
          res = f_read(&SDFile, rtext, sizeof(rtext), (void *)&bytesread);

          if((bytesread > 0) && (res == FR_OK))
          {
            // Close the open text file
           res = f_close(&SDFile);
           if(res == FR_OK)
        	 // res = f_unlink( fileNameIntern);	// deleting File

            // Compare read data with the expected data
            if((bytesread == byteswritten)  && (res == FR_OK) )
            {
              // Success of the demo: no error occurrence
              return FR_OK;
            }
          }
        }
      }
    }
  }
  // Error
  // FATFS_UnLinkDriver(USERPath);
  return res;
}




/* ====================================================================
 * @brief  Main application task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ==================================================================== */
void LedBlueTask( void * pvParameters )
{

  // Main event loop
  for ( ;; ) {
	  HAL_GPIO_TogglePin(LED_B_GPIO_Port,LED_B_Pin);

	  osDelay(3);
  }

  // Delete task
  vTaskDelete( NULL );

}



/* ====================================================================
 * @brief  Main application task
 * @param  *pvParameters: Task parameters (unused)
 * @retval None
 * ==================================================================== */
void LedGreenTask( void * pvParameters )
{

  // Main event loop
  for ( ;; ) {

	  HAL_GPIO_TogglePin(LED_G_GPIO_Port,LED_G_Pin);
	  osDelay(1);
  }

  // Delete task
  vTaskDelete( NULL );

}
/* USER CODE END Application */
