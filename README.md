# STM32L496-DMA-FreeRTOS-SDMMC-SdCard-Base-Project

STM32L496 DMA FreeRTOS SDMMC SdCard Base Project
this is my contribution to the community.
Sadly for some reason STM makes it a really painfull to get SD cards fully running on STM32L4 uControllers.

- RTOS
- SD Card SDMMC 4bit DMA
- UART DMA
- CLI Terminal
- [Segger System View](https://www.segger.com/products/development-tools/systemview/)

Here you find one fully running STM32L4 projects with FreeRtos using a 4 bit wide SDMMC bus with DMA including my driver plus much more.

Created via STM32CubeMX 5.3 and edited with STM32CubeIDE. These examples remain fully configurable and editable with CubeMX 5.3. and STM32CubeIDE. Newer CubeMX versions will break the code.

### Important:

1. Download CubeMX 5.3 - on which this project is based
2. in STM32 Cube IDE change toolchain in project settings to "GNU Tools for STM32 (10.3-21.10)

However, the most important peace of code in this project it the **_bsp_driver_mmaw.c_** file!
Basically we use only one DMA Channel which we reconfigure before every Read/Write procedure.
Open these projects in STM32CubeMX and check how i configured the DMA.

you can find the:
**_bsp_driver_mmaw.c_**
file under **SRC** and in the examples under: **FATFS/Target/bsp_driver_mmaw.c**

In your project just copy "bsp_driver_mmaw.c" next to "bsp_driver_sd.c" file.
Since BSP_SD_ReadBlocks and BSP_SD_WriteBlocks are \_\_weak functions and my driver will be used instead.

If you want to use Segger System View you have to convert your ST-Link to Segger J-link with: ST-Link Reflash Utility

[ST-Link Reflash Utility](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/)

As allways its the users responsibility to read through the code for full understanding.
