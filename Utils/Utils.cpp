#include "Utils.hpp"

void Utils::delayUs(uint16_t us)
{
    uint16_t start = __HAL_TIM_GET_COUNTER(&htim2);

    while ((__HAL_TIM_GET_COUNTER(&htim2) - start) < us)
    {
    }
}