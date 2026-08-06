#ifndef HC_SR04_RCWL_9610_Utils_HPP_
#define HC_SR04_RCWL_9610_Utils_HPP_

#include <cstdio>

extern "C"
{
#include "tim.h"
}

class Utils
{
public:
    Utils() = default;
    ~Utils() = default;

    static void delayUs(uint16_t us);
};

#endif
