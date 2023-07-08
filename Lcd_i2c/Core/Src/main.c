#include "main.h"
#include "i2c.h"
#include "gpio.h"
#include "lcd_i2c.h"

#include <stdio.h>

void SystemClock_Config(void);

uint8_t contador = 0;
char buf_lcd[18];

const char fig_1[8] = { 0x0A, 0x0A, 0x0A, 0x00, 0x11, 0x11, 0x0E, 0x00 };
const char fig_2[8] = { 0x04, 0x11, 0x0E, 0x04, 0x04, 0x0A, 0x11, 0x00 };
const char fig_3[8] = { 0x00, 0x0A, 0x1F, 0x1F, 0x1F, 0x0E, 0x04, 0x00 };
const char fig_4[8] = { 0x0E, 0x1F, 0x1F, 0x0E, 0x0A, 0x11, 0x11, 0x00 };
const char fig_5[8] = { 0x04, 0x0E, 0x1F, 0x04, 0x04, 0x04, 0x04, 0x00 };
const char fig_6[8] = { 0x0E, 0x0A, 0x11, 0x11, 0x11, 0x1F, 0x1F, 0x00 };
const char fig_7[8] = { 0x04, 0x0E, 0x04, 0x04, 0x15, 0x15, 0x0E, 0x00 };
const char fig_8[8] = { 0x1F, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x1F, 0x00 };

int main(void) {

	HAL_Init();

	SystemClock_Config();

	MX_GPIO_Init();
	MX_I2C1_Init();

	Lcd_Init();

	Lcd_Clear();
	Lcd_CGRAM_CreateChar(0, fig_1);
	Lcd_CGRAM_CreateChar(1, fig_2);
	Lcd_CGRAM_CreateChar(2, fig_3);
	Lcd_CGRAM_CreateChar(3, fig_4);
	Lcd_CGRAM_CreateChar(4, fig_5);
	Lcd_CGRAM_CreateChar(5, fig_6);
	Lcd_CGRAM_CreateChar(6, fig_7);
	Lcd_CGRAM_CreateChar(7, fig_8);

	while (1) {

		Lcd_Set_Cursor(1, 1);
		Lcd_Send_String("Test LCD 16x2");
		Lcd_Set_Cursor(2, 1);
		Lcd_Send_String("STM32F103C8T6");
		Lcd_Set_Cursor(2, 15);
		Lcd_Blink();
		HAL_Delay(2500);
		Lcd_NoBlink();
		Lcd_Clear();
		HAL_Delay(400);
	}


}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL12;
  RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_I2C1;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
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
