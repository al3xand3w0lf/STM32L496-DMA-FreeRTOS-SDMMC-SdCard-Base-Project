# STM32L496-DMA-FreeRTOS-SDMMC-SdCard-Base-Project
STM32L496 DMA FreeRTOS SDMMC SdCard Base Project
this is my contribution to the community. 
Sadly for some reason STM makes it a really painful to get SD cards fully running on STM32L4 uControllers.

This codes are two fully running STM32L4 projects with FreeRtos using a 4 bit wide SDMMC bus with DMA. 
Created via STM32CubeMX 6.6.1 and edited with STM32CubeIDE. These examples remain fully 
configurable and editable with CubeMX.

The STM496 Disco example runs on the STM32L4G-DISO board from STM.
The STML496VG example is for my self designed boad. On this STML496VG example I added Segger System View and OZONE to this base RTOS project.

However, the most important peace of code in this project it the ***bsp_driver_mmaw.c*** file!
Basically we use only one DMA Channel which we reconfigure before every Read/Write procedure.

you can find the file under SRC and in the examples under FATFS/Target/bsp_driver_mmaw.c 

In your project just copy "bsp_driver_mmaw.c" next to "bsp_driver_sd.c" file. 
Since BSP_SD_ReadBlocks and BSP_SD_WriteBlocks are __weak functions my driver will be used instead.

As allways its the users responsibility to read through the code for full understanding
