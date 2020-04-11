/*******************************************************************************
* File          : DebounceTask.hpp
*
* Description   : 
*
* Project       :
*
* Author        : s.gilbert
*
* Created on    : 20 Feb 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DEBOUNCETASK_HPP
#define DEBOUNCETASK_HPP

/******************************************************************************
INCLUDES
*******************************************************************************/

#include "TaskBase.hpp"
#include "GPIODebounceTools.hpp"
#include "SubscribeDebounce.hpp"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define DBTASKFREQUENCY_MS    (1)

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

//const extern osThreadDef_t os_thread_def_debounce;

/*******************************************************************************
CONSTANTS
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

class CDebounceTask
        : public threadCore::CTaskBase
{
public:
    CDebounceTask(char const * const pName
                  , const float freq
                  , uint32_t priority
                  , void * const pStack
                  , const size_t stackSize
                  , CWatchdogBase * pWatchdog);
    ~CDebounceTask(void) = default;
    void funcMain(void) override;
    bool subscribe(GPIO_TypeDef * GPIO_port
                  , uint16_t GPIO_pin
                  , uint32_t pull_up_down
                  , callbackFuncPtr_t assertCallback, void * assertArg
                  , callbackFuncPtr_t deassertCallback, void * deassertArg);
    void unsubscribe(GPIO_TypeDef* GPIO_port, uint16_t GPIO_pin);
    bool isAsserted(uint32_t GPIOID);
    bool isDeasserted(uint32_t GPIOID);
    uint32_t anyChangedState(void);

protected:
    void updateIOs(uint32_t subscribeCount);
    void checkDebouncedIOs(uint32_t subscribeCount);


private:

protected:
    CSubscribeDebounce m_subscribedGPIOs;
    CGPIOData GPIOData;

private:

};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/

#endif /* DEBOUNCETASK_HPP */
