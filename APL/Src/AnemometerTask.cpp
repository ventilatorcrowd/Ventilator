/*******************************************************************************
* File          : AnemometerTask.cpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 10 Apr 2020
*
*******************************************************************************/

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "AnemometerTask.hpp"
//#include "main.h"

/*******************************************************************************
NAMESPACE
*******************************************************************************/


/*******************************************************************************
DEFINITIONS
*******************************************************************************/

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
MODULE VARIABLES
*******************************************************************************/

/*******************************************************************************
MODULE FUNCTION DECLARATIONS
*******************************************************************************/

/*******************************************************************************
FUNCTION DEFINITIONS
*******************************************************************************/

CAnemometerTask::CAnemometerTask(char const * const pName
                                 , const float freq
                                 , uint32_t priority
                                 , void * const pStack
                                 , const size_t stackSize
                                 , TIM_HandleTypeDef * phtim
                                 , CWatchdogBase * pWatchdog)
    : threadCore::CTaskBase(pName, freq, priority, pStack, stackSize, pWatchdog)
    , m_pTimer(phtim)
{

}

void CAnemometerTask::funcBegin(void)
{
    HAL_TIM_PWM_Start(m_pTimer, TIM_CHANNEL_2);
//    HAL_GPIO_WritePin(US_Trigger_GPIO_Port, US_Trigger_Pin, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(US_Trigger_GPIO_Port, US_Trigger_Pin, GPIO_PIN_RESET);
}

void CAnemometerTask::funcMain(void)
{
    HAL_TIM_PWM_Start(m_pTimer, TIM_CHANNEL_2);
//    HAL_GPIO_WritePin(US_Trigger_GPIO_Port, US_Trigger_Pin, GPIO_PIN_SET);
//    HAL_GPIO_WritePin(US_Trigger_GPIO_Port, US_Trigger_Pin, GPIO_PIN_RESET);
}
