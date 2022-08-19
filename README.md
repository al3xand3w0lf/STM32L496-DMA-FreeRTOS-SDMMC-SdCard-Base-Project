# STM32L496-DMA-FreeRTOS-SDMMC-SdCard-Base-Project
STM32L496 DMA FreeRTOS SDMMC SdCard Base Project
this is my contribution to the community

This code is a fully running STM32L4 project with FreeRtos using a 4 bit wide SDMMC bus with DMA. 
For some reason its a real pain to get SD cards fully running on STM32 uControllers

Additionally I included Segger System View and OZONE project to this base project.

However, the most important peace of code in this project it the "bsp_driver_mm.c" file!
Basically we use only one DMA Channel which we reconfigure before every Read/Write procedure.

you can find the file under FATFS/Target/bsp_driver_mm.c 

In your project just copy "bsp_driver_mm.c" next to "bsp_driver_sd.c" file. 
Since BSP_SD_ReadBlocks and BSP_SD_WriteBlocks are __weak functions my driver will be used instead.

