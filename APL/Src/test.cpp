/*
 * test.cpp
 *
 *  Created on: 3 Jan 2020
 *      Author: s.gilbert
 */

#include "test.hpp"
#include "CircularBuffer.hpp"
#include "stm32f7xx_hal.h"
#include "main.h"


CTestTask::CTestTask(char const * const pName
                     , const float freq
                     , uint32_t priority
                     , void * const pStack
                     , const size_t stackSize
                     , CWatchdogBase * pWatchdog)
    : threadCore::CTaskBase(pName, freq, priority, pStack, stackSize, pWatchdog)
    , m_pTaskName(pName)
    , m_freq(freq)
    , m_taskCount(0)
{}

void CTestTask::funcMain(void)
{
    HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

//    ++m_taskCount;
//    if(5 < m_taskCount)
//    {
//        while(1)
//        {}
//    }
}

bool CTestTask::funcTimeout(void * pMsg)
{
    (void)pMsg;
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

    return false;
}


