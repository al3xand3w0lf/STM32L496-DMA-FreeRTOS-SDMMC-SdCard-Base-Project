# STM32L496-DMA-FreeRTOS-SDMMC-SdCard-Base-Project

STM32L496 DMA FreeRTOS SDMMC SdCard Base Project. This is my contribution to the community.
Sadly for some reason STM makes it a really painfull to get SD cards fully running on STM32L4 uControllers.

This project is made and configured for a STM32 NUCLEO-L496ZG board, if you use that board you can start right away developing your Applicaiton.

In this Repository you find one fully running STM32L4 projects with FreeRtos using a 4 bit wide SDMMC bus with DMA including my driver plus much more:

- FreeRTOS
- SD Card SDMMC 4bit DMA
- UART DMA
- USB Mass Storage ( switchover activated via Button or Terminal Comand)
- [FreeRTOS CLI Terminal](https://freertos.org/FreeRTOS-Plus/FreeRTOS_Plus_CLI/FreeRTOS_Plus_Command_Line_Interface.html)
- [Segger System View](https://www.segger.com/products/development-tools/systemview/)

Created via STM32CubeMX 5.3 and edited with STM32CubeIDE. These examples remain fully configurable and editable with CubeMX 5.3. and STM32CubeIDE. Newer CubeMX versions will break the code.

Additionally you find Gerber PCB Files for a SD CArd shield for Nucleo 144 Boards inclusive a BOM List.

### Important:

1. Download CubeMX 5.3 - on which this project is based - if you want to edit uC configuration
2. in STM32 Cube IDE change toolchain in project settings to "GNU Tools for STM32 (10.3-21.10)
3. Don't forget Pull Up Resistors in Datalines to your SD Card

However, important peace of code in this project it the **_bsp_driver_mmaw.c_** file!
Basically we use only one DMA Channel which we reconfigure before every Read/Write procedure.

you can find the:
**_bsp_driver_mmaw.c_**
file under **SRC** and in the examples under: **FATFS/Target/bsp_driver_mmaw.c**

In your project just copy "bsp_driver_mmaw.c" next to "bsp_driver_sd.c" file.
Then put a \_\_weak before BSP_SD_ReadBlocks and BSP_SD_WriteBlocks which will cause the driver to be used.

If you want to use Segger System View you have to convert your ST-Link to Segger J-link with: ST-Link Reflash Utility

[ST-Link Reflash Utility](https://www.segger.com/products/debug-probes/j-link/models/other-j-links/st-link-on-board/)

As allways its the users responsibility to read through the code for full understanding.
