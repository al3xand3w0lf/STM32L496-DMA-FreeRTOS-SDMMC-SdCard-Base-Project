/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    stm32l4xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32l4xx_it.h"
#include "FreeRTOS.h"
#include "task.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "mainApp.h"
#include "button.h"
#include "terminal.h"
#include "stm32l4xx_hal_uart.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
 
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_OTG_FS;
extern DMA_HandleTypeDef hdma_lpuart_rx;
extern DMA_HandleTypeDef hdma_lpuart_tx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_usart3_tx;
extern UART_HandleTypeDef hlpuart1;
extern UART_HandleTypeDef huart3;
extern RTC_HandleTypeDef hrtc;
extern DMA_HandleTypeDef hdma_sdmmc1;
extern SD_HandleTypeDef hsd1;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim2;

/* USER CODE BEGIN EV */
extern uint8_t terminalRxBuffer[TERMINAL_RX_BUFFER_SIZE];
/* USER CODE END EV */

/******************************************************************************/
/*           Cortex-M4 Processor Interruption and Exception Handlers          */ 
/******************************************************************************/
/**
  * @brief This function handles Non maskable interrupt.
  */
void NMI_Handler(void)
{
  /* USER CODE BEGIN NonMaskableInt_IRQn 0 */

  /* USER CODE END NonMaskableInt_IRQn 0 */
  /* USER CODE BEGIN NonMaskableInt_IRQn 1 */

  /* USER CODE END NonMaskableInt_IRQn 1 */
}

/**
  * @brief This function handles Hard fault interrupt.
  */
void HardFault_Handler(void)
{
  /* USER CODE BEGIN HardFault_IRQn 0 */

  /* USER CODE END HardFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_HardFault_IRQn 0 */
    /* USER CODE END W1_HardFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Memory management fault.
  */
void MemManage_Handler(void)
{
  /* USER CODE BEGIN MemoryManagement_IRQn 0 */

  /* USER CODE END MemoryManagement_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_MemoryManagement_IRQn 0 */
    /* USER CODE END W1_MemoryManagement_IRQn 0 */
  }
}

/**
  * @brief This function handles Prefetch fault, memory access fault.
  */
void BusFault_Handler(void)
{
  /* USER CODE BEGIN BusFault_IRQn 0 */

  /* USER CODE END BusFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_BusFault_IRQn 0 */
    /* USER CODE END W1_BusFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Undefined instruction or illegal state.
  */
void UsageFault_Handler(void)
{
  /* USER CODE BEGIN UsageFault_IRQn 0 */

  /* USER CODE END UsageFault_IRQn 0 */
  while (1)
  {
    /* USER CODE BEGIN W1_UsageFault_IRQn 0 */
    /* USER CODE END W1_UsageFault_IRQn 0 */
  }
}

/**
  * @brief This function handles Debug monitor.
  */
void DebugMon_Handler(void)
{
  /* USER CODE BEGIN DebugMonitor_IRQn 0 */

  /* USER CODE END DebugMonitor_IRQn 0 */
  /* USER CODE BEGIN DebugMonitor_IRQn 1 */

  /* USER CODE END DebugMonitor_IRQn 1 */
}

/******************************************************************************/
/* STM32L4xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32l4xx.s).                    */
/******************************************************************************/

/**
  * @brief This function handles DMA1 channel2 global interrupt.
  */
void DMA1_Channel2_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel2_IRQn 0 */

  /* USER CODE END DMA1_Channel2_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_tx);
  /* USER CODE BEGIN DMA1_Channel2_IRQn 1 */

  /* USER CODE END DMA1_Channel2_IRQn 1 */
}

/**
  * @brief This function handles DMA1 channel3 global interrupt.
  */
void DMA1_Channel3_IRQHandler(void)
{
  /* USER CODE BEGIN DMA1_Channel3_IRQn 0 */

  /* USER CODE END DMA1_Channel3_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_usart3_rx);
  /* USER CODE BEGIN DMA1_Channel3_IRQn 1 */

  /* USER CODE END DMA1_Channel3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[9:5] interrupts.
  */
void EXTI9_5_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI9_5_IRQn 0 */

  /* USER CODE END EXTI9_5_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_9);
  /* USER CODE BEGIN EXTI9_5_IRQn 1 */

  /* USER CODE END EXTI9_5_IRQn 1 */
}

/**
  * @brief This function handles TIM2 global interrupt.
  */
void TIM2_IRQHandler(void)
{
  /* USER CODE BEGIN TIM2_IRQn 0 */

  /* USER CODE END TIM2_IRQn 0 */
  HAL_TIM_IRQHandler(&htim2);
  /* USER CODE BEGIN TIM2_IRQn 1 */

  /* USER CODE END TIM2_IRQn 1 */
}

/**
  * @brief This function handles USART3 global interrupt.
  */
void USART3_IRQHandler(void)
{
  /* USER CODE BEGIN USART3_IRQn 0 */

  /* USER CODE END USART3_IRQn 0 */
  HAL_UART_IRQHandler(&huart3);
  /* USER CODE BEGIN USART3_IRQn 1 */

  /* USER CODE END USART3_IRQn 1 */
}

/**
  * @brief This function handles EXTI line[15:10] interrupts.
  */
void EXTI15_10_IRQHandler(void)
{
  /* USER CODE BEGIN EXTI15_10_IRQn 0 */

  /* USER CODE END EXTI15_10_IRQn 0 */
  HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_13);
  /* USER CODE BEGIN EXTI15_10_IRQn 1 */

  /* USER CODE END EXTI15_10_IRQn 1 */
}

/**
  * @brief This function handles RTC alarm interrupt through EXTI line 18.
  */
void RTC_Alarm_IRQHandler(void)
{
  /* USER CODE BEGIN RTC_Alarm_IRQn 0 */

  /* USER CODE END RTC_Alarm_IRQn 0 */
  HAL_RTC_AlarmIRQHandler(&hrtc);
  /* USER CODE BEGIN RTC_Alarm_IRQn 1 */

  /* USER CODE END RTC_Alarm_IRQn 1 */
}

/**
  * @brief This function handles SDMMC1 global interrupt.
  */
void SDMMC1_IRQHandler(void)
{
  /* USER CODE BEGIN SDMMC1_IRQn 0 */

  /* USER CODE END SDMMC1_IRQn 0 */
  HAL_SD_IRQHandler(&hsd1);
  /* USER CODE BEGIN SDMMC1_IRQn 1 */

  /* USER CODE END SDMMC1_IRQn 1 */
}

/**
  * @brief This function handles TIM7 global interrupt.
  */
void TIM7_IRQHandler(void)
{
  /* USER CODE BEGIN TIM7_IRQn 0 */

  /* USER CODE END TIM7_IRQn 0 */
  HAL_TIM_IRQHandler(&htim7);
  /* USER CODE BEGIN TIM7_IRQn 1 */

  /* USER CODE END TIM7_IRQn 1 */
}

/**
  * @brief This function handles DMA2 channel4 global interrupt.
  */
void DMA2_Channel4_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel4_IRQn 0 */

  /* USER CODE END DMA2_Channel4_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_sdmmc1);
  /* USER CODE BEGIN DMA2_Channel4_IRQn 1 */

  /* USER CODE END DMA2_Channel4_IRQn 1 */
}

/**
  * @brief This function handles USB OTG FS global interrupt.
  */
void OTG_FS_IRQHandler(void)
{
  /* USER CODE BEGIN OTG_FS_IRQn 0 */

  /* USER CODE END OTG_FS_IRQn 0 */
  HAL_PCD_IRQHandler(&hpcd_USB_OTG_FS);
  /* USER CODE BEGIN OTG_FS_IRQn 1 */

  /* USER CODE END OTG_FS_IRQn 1 */
}

/**
  * @brief This function handles DMA2 channel6 global interrupt.
  */
void DMA2_Channel6_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel6_IRQn 0 */

  /* USER CODE END DMA2_Channel6_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_lpuart_tx);
  /* USER CODE BEGIN DMA2_Channel6_IRQn 1 */

  /* USER CODE END DMA2_Channel6_IRQn 1 */
}

/**
  * @brief This function handles DMA2 channel7 global interrupt.
  */
void DMA2_Channel7_IRQHandler(void)
{
  /* USER CODE BEGIN DMA2_Channel7_IRQn 0 */

  /* USER CODE END DMA2_Channel7_IRQn 0 */
  HAL_DMA_IRQHandler(&hdma_lpuart_rx);
  /* USER CODE BEGIN DMA2_Channel7_IRQn 1 */

  /* USER CODE END DMA2_Channel7_IRQn 1 */
}

/**
  * @brief This function handles LPUART1 global interrupt.
  */
void LPUART1_IRQHandler(void)
{
  /* USER CODE BEGIN LPUART1_IRQn 0 */
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  // UART idle interrupt triggered
  if ( __HAL_UART_GET_FLAG( &hlpuart1, UART_FLAG_IDLE ) ) {

	// Position of DMA write pointer in ring buffer
	volatile uint32_t position = TERMINAL_RX_BUFFER_SIZE - hdma_lpuart_rx.Instance->CNDTR;

	// Send position as notification value to terminal task
	xTaskNotifyFromISR( terminalRxTaskHandle, position, eSetValueWithOverwrite, &xHigherPriorityTaskWoken );

	// Clear interrupt idle flag
	__HAL_UART_CLEAR_IDLEFLAG( &hlpuart1 );
  }
  /* USER CODE END LPUART1_IRQn 0 */
  HAL_UART_IRQHandler(&hlpuart1);
  /* USER CODE BEGIN LPUART1_IRQn 1 */
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
  /* USER CODE END LPUART1_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/**
  * @brief Tx Transfer completed callback.
  * @param huart UART handle.
  * @retval None
  */
void HAL_UART_TxCpltCallback( UART_HandleTypeDef *huart )
{
  // Track IRQ entry for SystemView
  //  SEGGER_SYSVIEW_RecordEnterISR();
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  // Notify task when transmission is complete
  if ( huart == &hlpuart1     ) {
    xTaskNotifyFromISR( terminalTxTaskHandle, 0, eNoAction, &xHigherPriorityTaskWoken );
  }

  // Switch to higher priority task if necessary
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );

  // Track ISR exit for SystemView
  //  SEGGER_SYSVIEW_RecordExitISR();

}


/**
 * @brief  EXTI line detection callback.
 * @param  GPIO_Pin: Specifies the port pin connected to corresponding EXTI line.
 * @retval None
 */
void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin )
{
  BaseType_t xHigherPriorityTaskWoken = pdFALSE;

  // USB connection changed
  if ( GPIO_Pin == USB_CONNECT_Pin ) {
    event_t evt = EVENT_USB_CONNECTION;
    xQueueSendFromISR( eventQueueHandle, &evt, &xHigherPriorityTaskWoken );
  }

  // Button press
  else if ( GPIO_Pin == BUTTON_1_Pin ) {
    xTaskNotifyFromISR( buttonTaskHandle, 0, eNoAction, &xHigherPriorityTaskWoken );
  }

  // Switch to higher priority task if necessary
  portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}



/**
 * @brief  UART error callback.
 * @param  huart UART handle.
 * @retval None
 */
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
     uint32_t error_code = huart->ErrorCode;
     if (0U != (error_code & (HAL_UART_ERROR_DMA | HAL_UART_ERROR_ORE )))
     {
             /*!< DMA transfer error      */
             /*!< Overrun error           */
             /* Blocking errors. Transmission is stopped. Inform the caller*/
             //tty->error = ERR_IO;
     }
     if (0U != (error_code & (HAL_UART_ERROR_NE | HAL_UART_ERROR_FE | HAL_UART_ERROR_PE)))
     {
             /*!< Noise error             */
             /*!< Frame error             */
             /*!< Parity error            */
             /* None-blocking errors. Transmission keeps going and we can
              * ignore them. The higher level protocol can handle
              * corrupted bytes. */
			 //HAL_UART_Abort(huart);
			 // hdma_lpuart_rx.Instance->CNDTR = TERMINAL_RX_BUFFER_SIZE; // reset Ring Buffer counter
			 //OPTIONS.error = ERR_NOISE;
    	     //huart->ErrorCode= HAL_UART_ERROR_NONE;   // reset error, keep on going
    	     __NOP();
     }
}

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
