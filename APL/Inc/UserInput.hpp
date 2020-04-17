/*******************************************************************************
* File          : UserInput.hpp
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
#ifndef USERINPUT_HPP
#define USERINPUT_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "TaskBase.hpp"
#include "stm32f7xx_hal.h"
#include "PneumaticActuator.hpp"
#include "controlWidget.hpp"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define CHANNEL_COUNT (3)
#define BUFFER_DEPTH (10)

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/


class CUserInput
    : public threadCore::CTaskBase
{
public:
    CUserInput(char const * const pName,
              const float freq = 100.0
              , uint32_t priority = 1
              , void * const pStack = nullptr
              , const size_t stackSize = 0
              , ADC_HandleTypeDef * pADC = nullptr
              , CControlWidget * pOutputDisplay = nullptr
              , CPneumaticActuator * pActuator = nullptr
              , CWatchdogBase * pWatchdog = nullptr);
    ~CUserInput() = default;
    void funcMain() override;
//    bool funcTimeout(void * pMsg) override;

private:
    float calcBufferAvg(uint16_t * pADCbuffer, size_t length);

//private:
protected:
    ADC_HandleTypeDef * m_pADC;
    CControlWidget * m_pOutputDisplay;
    CPneumaticActuator * m_pActuator;
    float m_channel[CHANNEL_COUNT];
    uint16_t m_ADCData[BUFFER_DEPTH * CHANNEL_COUNT] __attribute__ ((aligned));

};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* USERINPUT_HPP */
