/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
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
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "DAQ.h"
#include "OsConfig.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for DAQ */
osThreadId_t DAQHandle;
const osThreadAttr_t DAQ_attributes = {
  .name = "DAQ",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for OsConfigTask */
osThreadId_t OsConfigTaskHandle;
const osThreadAttr_t OsConfigTask_attributes = {
  .name = "OsConfigTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDAQTask(void *argument);
void OsConfig(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

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
  /* creation of DAQ */
  DAQHandle = osThreadNew(StartDAQTask, NULL, &DAQ_attributes);

  /* creation of OsConfigTask */
  OsConfigTaskHandle = osThreadNew(OsConfig, NULL, &OsConfigTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDAQTask */
/**
  * @brief  Function implementing the DAQ thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDAQTask */
void StartDAQTask(void *argument)
{
  /* USER CODE BEGIN StartDAQTask */
  DAQ_Init();

  /* Infinite loop */
  for(;;)
  {
	DAQ();

    osDelay(1000);
  }
  /* USER CODE END StartDAQTask */
}

/* USER CODE BEGIN Header_OsConfig */
/**
* @brief Function implementing the OsConfigTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_OsConfig */
void OsConfig(void *argument)
{
  /* USER CODE BEGIN OsConfig */

  OS_Config_Init();

  /* Infinite loop */
  for(;;)
  {
	OS_Config();
    osDelay(500);
  }
  /* USER CODE END OsConfig */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
