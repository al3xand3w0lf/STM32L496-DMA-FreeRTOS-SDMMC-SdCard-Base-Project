# STM32L496-DMA-FreeRTOS-SDMMC-SdCard-Base-Project

STM32L496 DMA FreeRTOS SDMMC SdCard Base Project
this is my contribution to the community.
Sadly for some reason STM makes it a really painfull to get SD cards fully running on STM32L4 uControllers.

Here you find two fully running STM32L4 projects with FreeRtos using a 4 bit wide SDMMC bus with DMA including my driver.
Created via STM32CubeMX 6.6.1 and edited with STM32CubeIDE. These examples remain fullyconfigurable and editable with CubeMX.

[The STM496 Disco example runs on the STM32L4G-DISO board from STM.](https://www.st.com/en/evaluation-tools/32l496gdiscovery.html)

The STML496VG example is for my self designed boad. On this STML496VG example I added Segger System View and OZONE to this base RTOS project.

However, the most important peace of code in this project it the **_bsp_driver_mmaw.c_** file!
Basically we use only one DMA Channel which we reconfigure before every Read/Write procedure.
Please open these projects in STM32CubeMX and check how i configured the DMA.

you can find the:
**_bsp_driver_mmaw.c_**
file under **SRC** and in the examples under **FATFS/Target/bsp_driver_mmaw.c**

In your project just copy "bsp_driver_mmaw.c" next to "bsp_driver_sd.c" file.
Since BSP_SD_ReadBlocks and BSP_SD_WriteBlocks are \_\_weak functions and my driver will be used instead.

As allways its the users responsibility to read through the code for full understanding

The Folder "JUST_BECAUSE" contains SD Card DMA RTOS project which are working out of the Box configured with CubeMX
