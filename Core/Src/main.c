/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "string.h"
#include "stdio.h"
#include "mpu6050.h"
#include <math.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MIN_CCR 0
#define MAX_CCR 499
#define BASE_CCR 299

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t rxBuffer[1];  // Single character buffer
uint8_t messageBuffer[MAX_MESSAGE_SIZE];  // Complete message buffer
uint16_t messageIndex = 0;  // Current position in message
uint8_t messageComplete = 0;  // Flag indicating complete message
MPU6050_t MPU6050;
double current_xvalue = 0;
double current_yvalue = 0;
int intitial_check = 0;
float Kp_roll  = 2.0f;

uint16_t final_m1_ccr;
uint16_t final_m2_ccr;
uint16_t final_m3_ccr;
uint16_t final_m4_ccr;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void update_motor_pwm(uint16_t m1_ccr, uint16_t m2_ccr, uint16_t m3_ccr, uint16_t m4_ccr) {
    // 타이머의 CCR 레지스터에 직접 값을 써서 PWM 듀티 사이클을 변경
    // HAL 함수를 사용해도 되지만, 레지스터 직접 접근이 더 빠릅니다.
    TIM1->CCR1 = m1_ccr;
    TIM1->CCR2 = m2_ccr;
    TIM1->CCR3 = m3_ccr;
    TIM1->CCR4 = m4_ccr;
}
float constrain(float value, float min, float max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_I2C2_Init();
  MX_TIM1_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_3);
  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);

  // Start UART reception in interrupt mode (single character)
  HAL_UART_Receive_IT(&huart2, rxBuffer, 1);
  char initMsg[] = "HAL_UART_Receive_IT success\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)initMsg, strlen(initMsg), HAL_MAX_DELAY);

  while (MPU6050_Init(&hi2c2) == 1);
  char mpuMsg[] = "MPU6050_Init success\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)mpuMsg, strlen(mpuMsg), HAL_MAX_DELAY);
  HAL_Delay(1000);

  char welcomeMsg[] = "UART2 Interrupt Ready!\r\n";
  HAL_UART_Transmit(&huart2, (uint8_t*)welcomeMsg, strlen(welcomeMsg), HAL_MAX_DELAY);

  if (intitial_check == 1) {
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 200);
  HAL_Delay(2000);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 200);
  HAL_Delay(2000);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 200);
  HAL_Delay(2000);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_3, 0);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 200);
  HAL_Delay(2000);
  __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_4, 0);
  }

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    MPU6050_Read_All(&hi2c2, &MPU6050);
    current_xvalue = MPU6050.KalmanAngleX; // MPU6050.KalmanAngleX는 -90에서 +90 사이의 값
    current_yvalue = MPU6050.KalmanAngleY + 90;

    char xvalueStr[64];
    int current_xvalInt = (int)current_xvalue;
    int current_yvalInt = (int)current_yvalue;
    int current_xvalFrac = (int)(fabs(current_xvalue - current_xvalInt) * 100);
    int current_yvalFrac = (int)(fabs(current_yvalue - current_yvalInt) * 100);

    snprintf(xvalueStr, sizeof(xvalueStr), "X: %d.%02d, Y: %d.%02d \r\n", current_xvalInt, current_xvalFrac, current_yvalInt, current_yvalFrac);
    HAL_UART_Transmit(&huart2, (uint8_t*)xvalueStr, strlen(xvalueStr), HAL_MAX_DELAY);

    float roll_control_output  = 4.5f * current_xvalue; // Roll 제어 출력
    
    // 3. 모터 믹싱 (Mixing) - Pitch 항 제거로 공식이 단순화됨
    // float형으로 먼저 계산하여 정밀도 유지
    // 왼쪽 모터 (1, 2)는 속도 감소
    float motor1_pwm = BASE_CCR - roll_control_output;
    float motor2_pwm = BASE_CCR - roll_control_output;
    // 오른쪽 모터 (3, 4)는 속도 증가
    float motor3_pwm = BASE_CCR + roll_control_output;
    float motor4_pwm = BASE_CCR + roll_control_output;
    
    // 4. PWM 값 범위 제한 (Saturation/Clamping)
    // 계산된 PWM 값이 설정한 범위를 벗어나지 않도록 함 (매우 중요!)
    final_m1_ccr = (uint16_t)constrain(motor1_pwm, MIN_CCR, MAX_CCR);
    final_m2_ccr = (uint16_t)constrain(motor2_pwm, MIN_CCR, MAX_CCR);
    final_m3_ccr = (uint16_t)constrain(motor3_pwm, MIN_CCR, MAX_CCR);
    final_m4_ccr = (uint16_t)constrain(motor4_pwm, MIN_CCR, MAX_CCR);

    // 5. 최종 계산된 CCR 값을 모터에 적용
    TIM1->CCR1 = final_m1_ccr;
    TIM1->CCR2 = final_m2_ccr;
    TIM1->CCR3 = final_m3_ccr;
    TIM1->CCR4 = final_m4_ccr;

    HAL_Delay(10);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
