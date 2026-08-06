#include "HCSR04.hpp"

HCSR04::HCSR04(GPIO_TypeDef* GPIOx, uint16_t PinTrigger) :
	m_GPIOx(GPIOx),
	m_pinTrigger(PinTrigger)
{
}

void HCSR04::trigger() const
{
    HAL_GPIO_WritePin(m_GPIOx, m_pinTrigger, GPIO_PIN_SET);
    Utils::delayUs(10);
    HAL_GPIO_WritePin(m_GPIOx, m_pinTrigger, GPIO_PIN_RESET);
}

void HCSR04::onCapture(TIM_HandleTypeDef *htim)
{
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
    {
        setEchoStartCapture(HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1));
    }
    else if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
    {
        setEchoEndCapture(
            HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2)
        );

        calcDistanceCm();

        m_ready = true;
    }
}

bool HCSR04::isReady()
{
	if (m_ready)
	{
		m_ready = false;

		return true;
	}
	return false;
}

void HCSR04::setEchoStartCapture(uint32_t value)
{
    m_echoStartCapture = value;
}

void HCSR04::setEchoEndCapture(uint32_t value)
{
    m_echoEndCapture = value;
}

void HCSR04::calcDistanceCm()
{
	m_distanceCm = (m_echoEndCapture - m_echoStartCapture) * SOUND_SPEED_CM_PER_US / 2.0f;
}

float HCSR04::getDistanceCm() const
{
    return m_distanceCm;
}
