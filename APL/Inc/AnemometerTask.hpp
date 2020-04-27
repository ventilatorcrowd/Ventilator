/*******************************************************************************
* File          : AnemometerTask.hpp
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
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ANEMOMETERTASK_HPP
#define ANEMOMETERTASK_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "TaskBase.hpp"
#include "stm32f7xx_hal.h"

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
NAMESPACE
*******************************************************************************/

class CAnemometerTask
    : public threadCore::CTaskBase
{
public:
    CAnemometerTask(char const * const pName
                  , const float freq
                  , uint32_t priority
                  , void * const pStack
                  , const size_t stackSize
                  , TIM_HandleTypeDef * phtim
                  , CWatchdogBase * pWatchdog = nullptr);
    ~CAnemometerTask(void) = default;
    void funcBegin(void) override;
    void funcMain(void) override;

private:

private:
    TIM_HandleTypeDef * m_pTimer;
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* ANEMOMETERTASK_HPP */
