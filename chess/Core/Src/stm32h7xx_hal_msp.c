/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : stm32h7xx_hal_msp.c
  * Description        : This file provides code for the MSP Initialization 
  *                      and de-Initialization codes.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
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
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */
extern MDMA_HandleTypeDef hmdma_jpeg_infifo_th;

extern MDMA_HandleTypeDef hmdma_jpeg_outfifo_th;

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN TD */

/* USER CODE END TD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN Define */
 
/* USER CODE END Define */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN Macro */

/* USER CODE END Macro */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* External functions --------------------------------------------------------*/
/* USER CODE BEGIN ExternalFunctions */

/* USER CODE END ExternalFunctions */

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */
/**
  * Initializes the Global MSP.
  */
void HAL_MspInit(void)
{

  /* USER CODE BEGIN MspInit 0 */

  /* USER CODE END MspInit 0 */

  __HAL_RCC_SYSCFG_CLK_ENABLE();

  /* System interrupt init*/
  /* PendSV_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(PendSV_IRQn, 15, 0);

  /* USER CODE BEGIN MspInit 1 */

  /* USER CODE END MspInit 1 */
}

/**
* @brief CRC MSP Initialization
* This function configures the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspInit 0 */

  /* USER CODE END CRC_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_CRC_CLK_ENABLE();
  /* USER CODE BEGIN CRC_MspInit 1 */

  /* USER CODE END CRC_MspInit 1 */
  }

}

/**
* @brief CRC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hcrc: CRC handle pointer
* @retval None
*/
void HAL_CRC_MspDeInit(CRC_HandleTypeDef* hcrc)
{
  if(hcrc->Instance==CRC)
  {
  /* USER CODE BEGIN CRC_MspDeInit 0 */

  /* USER CODE END CRC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CRC_CLK_DISABLE();
  /* USER CODE BEGIN CRC_MspDeInit 1 */

  /* USER CODE END CRC_MspDeInit 1 */
  }

}

/**
* @brief DMA2D MSP Initialization
* This function configures the hardware resources used in this example
* @param hdma2d: DMA2D handle pointer
* @retval None
*/
void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef* hdma2d)
{
  if(hdma2d->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspInit 0 */

  /* USER CODE END DMA2D_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_DMA2D_CLK_ENABLE();
    /* DMA2D interrupt Init */
    HAL_NVIC_SetPriority(DMA2D_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(DMA2D_IRQn);
  /* USER CODE BEGIN DMA2D_MspInit 1 */

  /* USER CODE END DMA2D_MspInit 1 */
  }

}

/**
* @brief DMA2D MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hdma2d: DMA2D handle pointer
* @retval None
*/
void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef* hdma2d)
{
  if(hdma2d->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspDeInit 0 */

  /* USER CODE END DMA2D_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DMA2D_CLK_DISABLE();

    /* DMA2D interrupt DeInit */
    HAL_NVIC_DisableIRQ(DMA2D_IRQn);
  /* USER CODE BEGIN DMA2D_MspDeInit 1 */

  /* USER CODE END DMA2D_MspDeInit 1 */
  }

}

/**
* @brief I2C MSP Initialization
* This function configures the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspInit(I2C_HandleTypeDef* hi2c)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hi2c->Instance==I2C4)
  {
  /* USER CODE BEGIN I2C4_MspInit 0 */

  /* USER CODE END I2C4_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_I2C4;
    PeriphClkInitStruct.I2c4ClockSelection = RCC_I2C4CLKSOURCE_D3PCLK1;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**I2C4 GPIO Configuration
    PD13     ------> I2C4_SDA
    PD12     ------> I2C4_SCL
    */
    GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_12;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_I2C4;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* Peripheral clock enable */
    __HAL_RCC_I2C4_CLK_ENABLE();
  /* USER CODE BEGIN I2C4_MspInit 1 */

  /* USER CODE END I2C4_MspInit 1 */
  }

}

/**
* @brief I2C MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hi2c: I2C handle pointer
* @retval None
*/
void HAL_I2C_MspDeInit(I2C_HandleTypeDef* hi2c)
{
  if(hi2c->Instance==I2C4)
  {
  /* USER CODE BEGIN I2C4_MspDeInit 0 */

  /* USER CODE END I2C4_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_I2C4_CLK_DISABLE();

    /**I2C4 GPIO Configuration
    PD13     ------> I2C4_SDA
    PD12     ------> I2C4_SCL
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_13);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_12);

  /* USER CODE BEGIN I2C4_MspDeInit 1 */

  /* USER CODE END I2C4_MspDeInit 1 */
  }

}

/**
* @brief JPEG MSP Initialization
* This function configures the hardware resources used in this example
* @param hjpeg: JPEG handle pointer
* @retval None
*/
void HAL_JPEG_MspInit(JPEG_HandleTypeDef* hjpeg)
{
  if(hjpeg->Instance==JPEG)
  {
  /* USER CODE BEGIN JPEG_MspInit 0 */

  /* USER CODE END JPEG_MspInit 0 */
    /* Peripheral clock enable */
    __HAL_RCC_JPEG_CLK_ENABLE();

    /* JPEG MDMA Init */
    /* JPEG_INFIFO_TH Init */
    hmdma_jpeg_infifo_th.Instance = MDMA_Channel7;
    hmdma_jpeg_infifo_th.Init.Request = MDMA_REQUEST_JPEG_INFIFO_TH;
    hmdma_jpeg_infifo_th.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
    hmdma_jpeg_infifo_th.Init.Priority = MDMA_PRIORITY_HIGH;
    hmdma_jpeg_infifo_th.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;
    hmdma_jpeg_infifo_th.Init.SourceInc = MDMA_SRC_INC_BYTE;
    hmdma_jpeg_infifo_th.Init.DestinationInc = MDMA_DEST_INC_DISABLE;
    hmdma_jpeg_infifo_th.Init.SourceDataSize = MDMA_SRC_DATASIZE_BYTE;
    hmdma_jpeg_infifo_th.Init.DestDataSize = MDMA_DEST_DATASIZE_WORD;
    hmdma_jpeg_infifo_th.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
    hmdma_jpeg_infifo_th.Init.BufferTransferLength = 32;
    hmdma_jpeg_infifo_th.Init.SourceBurst = MDMA_SOURCE_BURST_32BEATS;
    hmdma_jpeg_infifo_th.Init.DestBurst = MDMA_DEST_BURST_16BEATS;
    hmdma_jpeg_infifo_th.Init.SourceBlockAddressOffset = 0;
    hmdma_jpeg_infifo_th.Init.DestBlockAddressOffset = 0;
    if (HAL_MDMA_Init(&hmdma_jpeg_infifo_th) != HAL_OK)
    {
      Error_Handler();
    }

    if (HAL_MDMA_ConfigPostRequestMask(&hmdma_jpeg_infifo_th, 0, 0) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hjpeg,hdmain,hmdma_jpeg_infifo_th);

    /* JPEG_OUTFIFO_TH Init */
    hmdma_jpeg_outfifo_th.Instance = MDMA_Channel6;
    hmdma_jpeg_outfifo_th.Init.Request = MDMA_REQUEST_JPEG_OUTFIFO_TH;
    hmdma_jpeg_outfifo_th.Init.TransferTriggerMode = MDMA_BUFFER_TRANSFER;
    hmdma_jpeg_outfifo_th.Init.Priority = MDMA_PRIORITY_VERY_HIGH;
    hmdma_jpeg_outfifo_th.Init.Endianness = MDMA_LITTLE_ENDIANNESS_PRESERVE;
    hmdma_jpeg_outfifo_th.Init.SourceInc = MDMA_SRC_INC_DISABLE;
    hmdma_jpeg_outfifo_th.Init.DestinationInc = MDMA_DEST_INC_BYTE;
    hmdma_jpeg_outfifo_th.Init.SourceDataSize = MDMA_SRC_DATASIZE_WORD;
    hmdma_jpeg_outfifo_th.Init.DestDataSize = MDMA_DEST_DATASIZE_BYTE;
    hmdma_jpeg_outfifo_th.Init.DataAlignment = MDMA_DATAALIGN_PACKENABLE;
    hmdma_jpeg_outfifo_th.Init.BufferTransferLength = 32;
    hmdma_jpeg_outfifo_th.Init.SourceBurst = MDMA_SOURCE_BURST_32BEATS;
    hmdma_jpeg_outfifo_th.Init.DestBurst = MDMA_DEST_BURST_32BEATS;
    hmdma_jpeg_outfifo_th.Init.SourceBlockAddressOffset = 0;
    hmdma_jpeg_outfifo_th.Init.DestBlockAddressOffset = 0;
    if (HAL_MDMA_Init(&hmdma_jpeg_outfifo_th) != HAL_OK)
    {
      Error_Handler();
    }

    if (HAL_MDMA_ConfigPostRequestMask(&hmdma_jpeg_outfifo_th, 0, 0) != HAL_OK)
    {
      Error_Handler();
    }

    __HAL_LINKDMA(hjpeg,hdmaout,hmdma_jpeg_outfifo_th);

    /* JPEG interrupt Init */
    HAL_NVIC_SetPriority(JPEG_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(JPEG_IRQn);
  /* USER CODE BEGIN JPEG_MspInit 1 */

  /* USER CODE END JPEG_MspInit 1 */
  }

}

/**
* @brief JPEG MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hjpeg: JPEG handle pointer
* @retval None
*/
void HAL_JPEG_MspDeInit(JPEG_HandleTypeDef* hjpeg)
{
  if(hjpeg->Instance==JPEG)
  {
  /* USER CODE BEGIN JPEG_MspDeInit 0 */

  /* USER CODE END JPEG_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_JPEG_CLK_DISABLE();

    /* JPEG MDMA DeInit */
    HAL_MDMA_DeInit(hjpeg->hdmain);
    HAL_MDMA_DeInit(hjpeg->hdmaout);

    /* JPEG interrupt DeInit */
    HAL_NVIC_DisableIRQ(JPEG_IRQn);
  /* USER CODE BEGIN JPEG_MspDeInit 1 */

  /* USER CODE END JPEG_MspDeInit 1 */
  }

}

/**
* @brief LTDC MSP Initialization
* This function configures the hardware resources used in this example
* @param hltdc: LTDC handle pointer
* @retval None
*/
void HAL_LTDC_MspInit(LTDC_HandleTypeDef* hltdc)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hltdc->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspInit 0 */

  /* USER CODE END LTDC_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_LTDC;
    PeriphClkInitStruct.PLL3.PLL3M = 24;
    PeriphClkInitStruct.PLL3.PLL3N = 201;
    PeriphClkInitStruct.PLL3.PLL3P = 2;
    PeriphClkInitStruct.PLL3.PLL3Q = 2;
    PeriphClkInitStruct.PLL3.PLL3R = 21;
    PeriphClkInitStruct.PLL3.PLL3RGE = RCC_PLL3VCIRANGE_0;
    PeriphClkInitStruct.PLL3.PLL3VCOSEL = RCC_PLL3VCOWIDE;
    PeriphClkInitStruct.PLL3.PLL3FRACN = 0;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_LTDC_CLK_ENABLE();

    __HAL_RCC_GPIOK_CLK_ENABLE();
    __HAL_RCC_GPIOJ_CLK_ENABLE();
    __HAL_RCC_GPIOI_CLK_ENABLE();
    /**LTDC GPIO Configuration
    PK5     ------> LTDC_B6
    PK6     ------> LTDC_B7
    PK3     ------> LTDC_B4
    PJ15     ------> LTDC_B3
    PK4     ------> LTDC_B5
    PJ14     ------> LTDC_B2
    PK7     ------> LTDC_DE
    PJ13     ------> LTDC_B1
    PJ12     ------> LTDC_B0
    PI12     ------> LTDC_HSYNC
    PI14     ------> LTDC_CLK
    PI13     ------> LTDC_VSYNC
    PK2     ------> LTDC_G7
    PK1     ------> LTDC_G6
    PJ11     ------> LTDC_G4
    PK0     ------> LTDC_G5
    PJ10     ------> LTDC_G3
    PJ9     ------> LTDC_G2
    PJ8     ------> LTDC_G1
    PJ6     ------> LTDC_R7
    PJ7     ------> LTDC_G0
    PI15     ------> LTDC_R0
    PJ0     ------> LTDC_R1
    PJ5     ------> LTDC_R6
    PJ1     ------> LTDC_R2
    PJ4     ------> LTDC_R5
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    */
    GPIO_InitStruct.Pin = GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOK, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12
                          |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_0|GPIO_PIN_5
                          |GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_2|GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOJ, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_15;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOI, &GPIO_InitStruct);

    /* LTDC interrupt Init */
    HAL_NVIC_SetPriority(LTDC_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspInit 1 */

  /* USER CODE END LTDC_MspInit 1 */
  }

}

/**
* @brief LTDC MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hltdc: LTDC handle pointer
* @retval None
*/
void HAL_LTDC_MspDeInit(LTDC_HandleTypeDef* hltdc)
{
  if(hltdc->Instance==LTDC)
  {
  /* USER CODE BEGIN LTDC_MspDeInit 0 */

  /* USER CODE END LTDC_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_LTDC_CLK_DISABLE();

    /**LTDC GPIO Configuration
    PK5     ------> LTDC_B6
    PK6     ------> LTDC_B7
    PK3     ------> LTDC_B4
    PJ15     ------> LTDC_B3
    PK4     ------> LTDC_B5
    PJ14     ------> LTDC_B2
    PK7     ------> LTDC_DE
    PJ13     ------> LTDC_B1
    PJ12     ------> LTDC_B0
    PI12     ------> LTDC_HSYNC
    PI14     ------> LTDC_CLK
    PI13     ------> LTDC_VSYNC
    PK2     ------> LTDC_G7
    PK1     ------> LTDC_G6
    PJ11     ------> LTDC_G4
    PK0     ------> LTDC_G5
    PJ10     ------> LTDC_G3
    PJ9     ------> LTDC_G2
    PJ8     ------> LTDC_G1
    PJ6     ------> LTDC_R7
    PJ7     ------> LTDC_G0
    PI15     ------> LTDC_R0
    PJ0     ------> LTDC_R1
    PJ5     ------> LTDC_R6
    PJ1     ------> LTDC_R2
    PJ4     ------> LTDC_R5
    PJ2     ------> LTDC_R3
    PJ3     ------> LTDC_R4
    */
    HAL_GPIO_DeInit(GPIOK, GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_3|GPIO_PIN_4
                          |GPIO_PIN_7|GPIO_PIN_2|GPIO_PIN_1|GPIO_PIN_0);

    HAL_GPIO_DeInit(GPIOJ, GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_12
                          |GPIO_PIN_11|GPIO_PIN_10|GPIO_PIN_9|GPIO_PIN_8
                          |GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_0|GPIO_PIN_5
                          |GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_2|GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOI, GPIO_PIN_12|GPIO_PIN_14|GPIO_PIN_13|GPIO_PIN_15);

    /* LTDC interrupt DeInit */
    HAL_NVIC_DisableIRQ(LTDC_IRQn);
  /* USER CODE BEGIN LTDC_MspDeInit 1 */

  /* USER CODE END LTDC_MspDeInit 1 */
  }

}

/**
* @brief OSPI MSP Initialization
* This function configures the hardware resources used in this example
* @param hospi: OSPI handle pointer
* @retval None
*/
void HAL_OSPI_MspInit(OSPI_HandleTypeDef* hospi)
{
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hospi->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspInit 0 */

  /* USER CODE END OCTOSPI1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_OSPI;
    PeriphClkInitStruct.PLL2.PLL2M = 24;
    PeriphClkInitStruct.PLL2.PLL2N = 266;
    PeriphClkInitStruct.PLL2.PLL2P = 2;
    PeriphClkInitStruct.PLL2.PLL2Q = 2;
    PeriphClkInitStruct.PLL2.PLL2R = 2;
    PeriphClkInitStruct.PLL2.PLL2RGE = RCC_PLL2VCIRANGE_0;
    PeriphClkInitStruct.PLL2.PLL2VCOSEL = RCC_PLL2VCOWIDE;
    PeriphClkInitStruct.PLL2.PLL2FRACN = 0;
    PeriphClkInitStruct.OspiClockSelection = RCC_OSPICLKSOURCE_PLL2;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_OCTOSPIM_CLK_ENABLE();
    __HAL_RCC_OSPI1_CLK_ENABLE();
    /* OCTOSPI1 interrupt Init */
    HAL_NVIC_SetPriority(OCTOSPI1_IRQn, 5, 0);
    HAL_NVIC_EnableIRQ(OCTOSPI1_IRQn);
  /* USER CODE BEGIN OCTOSPI1_MspInit 1 */

  /* USER CODE END OCTOSPI1_MspInit 1 */
  }

}

/**
* @brief OSPI MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hospi: OSPI handle pointer
* @retval None
*/
void HAL_OSPI_MspDeInit(OSPI_HandleTypeDef* hospi)
{
  if(hospi->Instance==OCTOSPI1)
  {
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 0 */

  /* USER CODE END OCTOSPI1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_OCTOSPIM_CLK_DISABLE();
    __HAL_RCC_OSPI1_CLK_DISABLE();

    /* OCTOSPI1 interrupt DeInit */
    HAL_NVIC_DisableIRQ(OCTOSPI1_IRQn);
  /* USER CODE BEGIN OCTOSPI1_MspDeInit 1 */

  /* USER CODE END OCTOSPI1_MspDeInit 1 */
  }

}

/**
* @brief SD MSP Initialization
* This function configures the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspInit(SD_HandleTypeDef* hsd)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};
  if(hsd->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspInit 0 */

  /* USER CODE END SDMMC1_MspInit 0 */

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_SDMMC;
    PeriphClkInitStruct.SdmmcClockSelection = RCC_SDMMCCLKSOURCE_PLL;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

    /* Peripheral clock enable */
    __HAL_RCC_SDMMC1_CLK_ENABLE();

    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**SDMMC1 GPIO Configuration
    PC10     ------> SDMMC1_D2
    PD2     ------> SDMMC1_CMD
    PC12     ------> SDMMC1_CK
    PC11     ------> SDMMC1_D3
    PC9     ------> SDMMC1_D1
    PC8     ------> SDMMC1_D0
    */
    GPIO_InitStruct.Pin = GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_9
                          |GPIO_PIN_8;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF12_SDMMC1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* USER CODE BEGIN SDMMC1_MspInit 1 */

  /* USER CODE END SDMMC1_MspInit 1 */
  }

}

/**
* @brief SD MSP De-Initialization
* This function freeze the hardware resources used in this example
* @param hsd: SD handle pointer
* @retval None
*/
void HAL_SD_MspDeInit(SD_HandleTypeDef* hsd)
{
  if(hsd->Instance==SDMMC1)
  {
  /* USER CODE BEGIN SDMMC1_MspDeInit 0 */

  /* USER CODE END SDMMC1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_SDMMC1_CLK_DISABLE();

    /**SDMMC1 GPIO Configuration
    PC10     ------> SDMMC1_D2
    PD2     ------> SDMMC1_CMD
    PC12     ------> SDMMC1_CK
    PC11     ------> SDMMC1_D3
    PC9     ------> SDMMC1_D1
    PC8     ------> SDMMC1_D0
    */
    HAL_GPIO_DeInit(GPIOC, GPIO_PIN_10|GPIO_PIN_12|GPIO_PIN_11|GPIO_PIN_9
                          |GPIO_PIN_8);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_2);

  /* USER CODE BEGIN SDMMC1_MspDeInit 1 */

  /* USER CODE END SDMMC1_MspDeInit 1 */
  }

}

static uint32_t FMC_Initialized = 0;

static void HAL_FMC_MspInit(void){
  /* USER CODE BEGIN FMC_MspInit 0 */

  /* USER CODE END FMC_MspInit 0 */
  GPIO_InitTypeDef GPIO_InitStruct ={0};
  if (FMC_Initialized) {
    return;
  }
  FMC_Initialized = 1;
  RCC_PeriphCLKInitTypeDef PeriphClkInitStruct = {0};

  /** Initializes the peripherals clock
  */
    PeriphClkInitStruct.PeriphClockSelection = RCC_PERIPHCLK_FMC;
    PeriphClkInitStruct.FmcClockSelection = RCC_FMCCLKSOURCE_D1HCLK;
    if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInitStruct) != HAL_OK)
    {
      Error_Handler();
    }

  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_ENABLE();

  /** FMC GPIO Configuration
  PG15   ------> FMC_SDNCAS
  PD1   ------> FMC_D3
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  PD0   ------> FMC_D2
  PG8   ------> FMC_SDCLK
  PF1   ------> FMC_A1
  PF0   ------> FMC_A0
  PG5   ------> FMC_BA1
  PF2   ------> FMC_A2
  PF4   ------> FMC_A4
  PG4   ------> FMC_BA0
  PF3   ------> FMC_A3
  PF5   ------> FMC_A5
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PE12   ------> FMC_D9
  PD8   ------> FMC_D13
  PD10   ------> FMC_D15
  PF13   ------> FMC_A7
  PE7   ------> FMC_D4
  PE13   ------> FMC_D10
  PH6   ------> FMC_SDNE1
  PF11   ------> FMC_SDNRAS
  PF15   ------> FMC_A9
  PE14   ------> FMC_D11
  PE10   ------> FMC_D7
  PD9   ------> FMC_D14
  PH5   ------> FMC_SDNWE
  PF14   ------> FMC_A8
  PG1   ------> FMC_A11
  PE9   ------> FMC_D6
  PE15   ------> FMC_D12
  PF12   ------> FMC_A6
  PG0   ------> FMC_A10
  PE8   ------> FMC_D5
  PE11   ------> FMC_D8
  PH7   ------> FMC_SDCKE1
  */
  GPIO_InitStruct.Pin = GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_5|GPIO_PIN_4
                          |GPIO_PIN_1|GPIO_PIN_0;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_7
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_11;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_11
                          |GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
  GPIO_InitStruct.Alternate = GPIO_AF12_FMC;
  HAL_GPIO_Init(GPIOH, &GPIO_InitStruct);

  /* USER CODE BEGIN FMC_MspInit 1 */

  /* USER CODE END FMC_MspInit 1 */
}

void HAL_SDRAM_MspInit(SDRAM_HandleTypeDef* hsdram){
  /* USER CODE BEGIN SDRAM_MspInit 0 */

  /* USER CODE END SDRAM_MspInit 0 */
  HAL_FMC_MspInit();
  /* USER CODE BEGIN SDRAM_MspInit 1 */

  /* USER CODE END SDRAM_MspInit 1 */
}

static uint32_t FMC_DeInitialized = 0;

static void HAL_FMC_MspDeInit(void){
  /* USER CODE BEGIN FMC_MspDeInit 0 */

  /* USER CODE END FMC_MspDeInit 0 */
  if (FMC_DeInitialized) {
    return;
  }
  FMC_DeInitialized = 1;
  /* Peripheral clock enable */
  __HAL_RCC_FMC_CLK_DISABLE();

  /** FMC GPIO Configuration
  PG15   ------> FMC_SDNCAS
  PD1   ------> FMC_D3
  PE0   ------> FMC_NBL0
  PE1   ------> FMC_NBL1
  PD0   ------> FMC_D2
  PG8   ------> FMC_SDCLK
  PF1   ------> FMC_A1
  PF0   ------> FMC_A0
  PG5   ------> FMC_BA1
  PF2   ------> FMC_A2
  PF4   ------> FMC_A4
  PG4   ------> FMC_BA0
  PF3   ------> FMC_A3
  PF5   ------> FMC_A5
  PD14   ------> FMC_D0
  PD15   ------> FMC_D1
  PE12   ------> FMC_D9
  PD8   ------> FMC_D13
  PD10   ------> FMC_D15
  PF13   ------> FMC_A7
  PE7   ------> FMC_D4
  PE13   ------> FMC_D10
  PH6   ------> FMC_SDNE1
  PF11   ------> FMC_SDNRAS
  PF15   ------> FMC_A9
  PE14   ------> FMC_D11
  PE10   ------> FMC_D7
  PD9   ------> FMC_D14
  PH5   ------> FMC_SDNWE
  PF14   ------> FMC_A8
  PG1   ------> FMC_A11
  PE9   ------> FMC_D6
  PE15   ------> FMC_D12
  PF12   ------> FMC_A6
  PG0   ------> FMC_A10
  PE8   ------> FMC_D5
  PE11   ------> FMC_D8
  PH7   ------> FMC_SDCKE1
  */
  HAL_GPIO_DeInit(GPIOG, GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_5|GPIO_PIN_4
                          |GPIO_PIN_1|GPIO_PIN_0);

  HAL_GPIO_DeInit(GPIOD, GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_14|GPIO_PIN_15
                          |GPIO_PIN_8|GPIO_PIN_10|GPIO_PIN_9);

  HAL_GPIO_DeInit(GPIOE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_12|GPIO_PIN_7
                          |GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_10|GPIO_PIN_9
                          |GPIO_PIN_15|GPIO_PIN_8|GPIO_PIN_11);

  HAL_GPIO_DeInit(GPIOF, GPIO_PIN_1|GPIO_PIN_0|GPIO_PIN_2|GPIO_PIN_4
                          |GPIO_PIN_3|GPIO_PIN_5|GPIO_PIN_13|GPIO_PIN_11
                          |GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_12);

  HAL_GPIO_DeInit(GPIOH, GPIO_PIN_6|GPIO_PIN_5|GPIO_PIN_7);

  /* USER CODE BEGIN FMC_MspDeInit 1 */

  /* USER CODE END FMC_MspDeInit 1 */
}

void HAL_SDRAM_MspDeInit(SDRAM_HandleTypeDef* hsdram){
  /* USER CODE BEGIN SDRAM_MspDeInit 0 */

  /* USER CODE END SDRAM_MspDeInit 0 */
  HAL_FMC_MspDeInit();
  /* USER CODE BEGIN SDRAM_MspDeInit 1 */

  /* USER CODE END SDRAM_MspDeInit 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
