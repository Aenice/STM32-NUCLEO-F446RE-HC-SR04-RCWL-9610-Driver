extern "C"
{
#include "main.h"
#include "tim.h"
#include "gpio.h"
#include "usart.h"
}

#include "HCSR04.hpp"
#include "Utils.hpp"

void SystemClock_Config(void);
//GPIO_PIN_4 = trigger
HCSR04 hcsr04(GPIOA, GPIO_PIN_4);

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_TIM2_Init();
    MX_USART2_UART_Init();
    // Start ECHO input capture interrupts
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
    HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_2);

    char buffer[100];
    constexpr float MAX_DISTANCE_CM = 50.0f;
    float distance = 0;

    while (true)
    {
        hcsr04.trigger();

        HAL_Delay(100);

        if (hcsr04.isReady())
        {
            distance = hcsr04.getDistanceCm();

            if (distance <= MAX_DISTANCE_CM)
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
            }
            else
            {
                HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
            }

            if (HCSR04::SENSOR_MAX_DISTANCE_CM < distance)
            {
                snprintf(buffer, sizeof(buffer), "Out of SENSOR_MAX_DISTANCE_CM Distance = %.2f cm\r\n", distance);
            }
            else
            {
                snprintf(buffer, sizeof(buffer), "Distance = %.2f cm\r\n", distance);
            }

            HAL_UART_Transmit(&huart2, (uint8_t*)buffer, strlen(buffer), 100);
        }
    }
}

extern "C" void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    hcsr04.onCapture(htim);
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 4;
    RCC_OscInitStruct.PLL.PLLN = 180;
    RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
    RCC_OscInitStruct.PLL.PLLQ = 2;
    RCC_OscInitStruct.PLL.PLLR = 2;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }

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

/**
* @brief  This function is executed in case of error occurrence.
* @retval None
*/

void Error_Handler(void)
{
    __disable_irq();
    while (1)
    {
    }
}
#ifdef USE_FULL_ASSERT
/**
* @brief  Reports the name of the source file and the source line number
*         where the assert_param error has occurred.
* @param  file: pointer to the source file name
* @param  line: assert_param error line source number
* @retval None
*/
void assert_failed(uint8_t *file, uint32_t line)
{
}
#endif /* USE_FULL_ASSERT */
