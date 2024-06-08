/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file   fatfs.c
  * @brief  Code for fatfs applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
#include "fatfs.h"
#include "main.h"
#include <string.h>

uint8_t retSD;    /* Return value for SD */
char SDPath[4];   /* SD logical drive path */
FATFS SDFatFS;    /* File system object for SD logical drive */
FIL SDFile;       /* File object for SD */

/* USER CODE BEGIN Variables */

/* USER CODE END Variables */

void MX_FATFS_Init(void)
{
  /*## FatFS: Link the SD driver ###########################*/
  retSD = FATFS_LinkDriver(&SD_Driver, SDPath);
  /* USER CODE BEGIN Init */
  /* additional user code for init */
  /* USER CODE END Init */
}

void WriteToSDCARD(const char* data)
{
	//FRESULT res;  //FatFs function common result code
	uint32_t byteswritten;  //File write / read counts

	 SCB_DisableDCache();

	     // Save to SD card
	     if (f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
	     {
	         if (f_open(&SDFile, "GAME.TXT", FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
	         {
	             f_write(&SDFile, data, strlen(data), (void*)&byteswritten);

	             f_close(&SDFile);
	         }
	         else
	         {

	         }
	         f_mount(NULL, (TCHAR const*)"", 0);
	     }
	     else
	     {
	         // Handle the error (mount failed)
	     }
	SCB_EnableDCache();

}

char* ReadFromSDCARD(void)
{
    FRESULT res;  // FatFs function common result code
    uint32_t bytesread;  // File read count
    FILINFO fileInfo;
    char* buffer = NULL;

    SCB_DisableDCache();

    // Mount the filesystem
    if (f_mount(&SDFatFS, (TCHAR const*)SDPath, 0) == FR_OK)
    {
        // Open the file for reading
        if (f_open(&SDFile, "GAME.TXT", FA_READ) == FR_OK)
        {
            // Get file size
            res = f_stat("GAME.TXT", &fileInfo);
            if (res == FR_OK)
            {
                // Allocate memory for the file content
                buffer = (char*)malloc(fileInfo.fsize + 1); // +1 for null terminator
                if (buffer != NULL)
                {
                    // Read the file into the buffer
                    res = f_read(&SDFile, buffer, fileInfo.fsize, (UINT*)&bytesread);
                    if (res == FR_OK && bytesread == fileInfo.fsize)
                    {
                        buffer[bytesread] = '\0'; // Null-terminate the string
                    }
                    else
                    {
                        // Handle read error
                        free(buffer);
                        buffer = NULL;
                    }
                }
            }
            else
            {
                // Handle stat error
            }
            f_close(&SDFile);
        }
        else
        {
            // Handle the error (file open failed)
        }
        f_mount(NULL, (TCHAR const*)"", 0);
    }
    else
    {
        // Handle the error (mount failed)
    }

    SCB_EnableDCache();
    return buffer;
}
/**
  * @brief  Gets Time from RTC
  * @param  None
  * @retval Time in DWORD
  */
DWORD get_fattime(void)
{
  /* USER CODE BEGIN get_fattime */
  return 0;
  /* USER CODE END get_fattime */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */
