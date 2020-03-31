/*******************************************************************************
* File          : PneumaticActuator.hpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 30 Mar 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef PNEUMATICACTUATOR_HPP
#define PNEUMATICACTUATOR_HPP

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

class CPneumaticActuator
    : public threadCore::CTaskBase
{
public:
    CPneumaticActuator(char const * const pName,
              const float freq = 100.0
              , uint32_t priority = 1
              , void * const pStack = nullptr
              , const size_t stackSize = 0
              , TIM_HandleTypeDef * phtim = nullptr
              , CWatchdogBase * pWatchdog = nullptr);
    ~CPneumaticActuator() = default;
    void funcBegin() override;
    void funcMain() override;
    void setSpeed(uint32_t speed);
    void setAmplitude(uint32_t amplitude);
//    bool funcTimeout(void * pMsg) override;

//private:
protected:
    TIM_HandleTypeDef * m_pTimer;
    uint32_t m_sineIndex;
    uint32_t m_speed;
    uint32_t m_amplitude;
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* PNEUMATICACTUATOR_HPP */
