/*
 * bsp_driver_mm.c
 *
 *  Created on: 29.07.2019
 *      Author: michjm
 *      Author: alexw
 */

// Includes
#include "bsp_driver_sd.h"

// SD card and DMA handles
extern SD_HandleTypeDef hsd1;
extern DMA_HandleTypeDef hdma_sdmmc1;


/* ====================================================================
 * @brief  Configure DMA to transmit or receive
 *         only one channel for TX/RX, see MX_SDMMC1_SD_Init
 * @param  direction: Channel direction
 * @retval Status
 * ==================================================================== */
HAL_StatusTypeDef SD_DMAConfig( uint32_t direction )
{

  // Set transmit direction
  hdma_sdmmc1.Init.Direction = direction;

  // Stop any DMA activity
  HAL_DMA_Abort( &hdma_sdmmc1 );

  // Deinit DMA
  HAL_DMA_DeInit( &hdma_sdmmc1 );

  // Initialize DMA
  return HAL_DMA_Init( &hdma_sdmmc1 );
}


/**
  * @brief  Reads block(s) from a specified address in an SD card, in DMA mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  ReadAddr: Address from where data is to be read
  * @param  NumOfBlocks: Number of SD blocks to read
  * @retval SD status
  */
uint8_t BSP_SD_ReadBlocks_DMA( uint32_t *pData, uint32_t ReadAddr, uint32_t NumOfBlocks )
{
  uint8_t sd_state = MSD_OK;
  uint32_t direction = DMA_PERIPH_TO_MEMORY;

  // Set DMA channel direction to receive
  if ( hsd1.hdmarx->Init.Direction != direction ) sd_state = SD_DMAConfig( direction );

  // Read block(s) in DMA transfer mode
  if ( sd_state != HAL_OK || HAL_SD_ReadBlocks_DMA( &hsd1, (uint8_t *) pData, ReadAddr, NumOfBlocks ) != HAL_OK ) {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}


/**
  * @brief  Writes block(s) to a specified address in an SD card, in DMA mode.
  * @param  pData: Pointer to the buffer that will contain the data to transmit
  * @param  WriteAddr: Address from where data is to be written
  * @param  NumOfBlocks: Number of SD blocks to write
  * @retval SD status
  */
uint8_t BSP_SD_WriteBlocks_DMA( uint32_t *pData, uint32_t WriteAddr, uint32_t NumOfBlocks )
{
  uint8_t sd_state = MSD_OK;
  uint32_t direction = DMA_MEMORY_TO_PERIPH;

  // Set DMA channel direction to transmit
  if ( hsd1.hdmatx->Init.Direction != direction ) sd_state = SD_DMAConfig( direction );

  // Read block(s) in DMA transfer mode
  if ( sd_state != HAL_OK || HAL_SD_WriteBlocks_DMA( &hsd1, (uint8_t *) pData, WriteAddr, NumOfBlocks ) != HAL_OK ) {
    sd_state = MSD_ERROR;
  }

  return sd_state;
}



