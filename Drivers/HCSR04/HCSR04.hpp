#ifndef HC_SR04_RCWL_9610_HCSR04_HPP_
#define HC_SR04_RCWL_9610_HCSR04_HPP_

#include <cstdio>
#include <cstring>

#include "Utils.hpp"

extern "C" 
{
#include "stm32f4xx_hal.h"
#include <string.h>
#include "usart.h"
}

class HCSR04
{
public:
    HCSR04(GPIO_TypeDef* GPIOx, uint16_t PinTrigger);
    ~HCSR04() = default;

public:
    void trigger() const;
    void onCapture(TIM_HandleTypeDef *htim);

    bool isReady();
    float getDistanceCm() const;

private:
    void setEchoStartCapture(uint32_t value);
    void setEchoEndCapture(uint32_t value);

    void calcDistanceCm();

public:
    static constexpr float SENSOR_MAX_DISTANCE_CM = 400.0f;
    static constexpr float SOUND_SPEED_CM_PER_US = 0.0343f;

private:
    uint16_t m_pinTrigger;
    GPIO_TypeDef* m_GPIOx;

    uint32_t m_echoStartCapture = 0;
    uint32_t m_echoEndCapture = 0;

    volatile bool m_ready = false;
    volatile float m_distanceCm = 0;
};

#endif
