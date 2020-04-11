/*******************************************************************************
* File          : ButtonHandler.hpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 4 Apr 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BUTTONHANDLER_HPP
#define BUTTONHANDLER_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "TaskBase.hpp"
#include "DebounceTask.hpp"
#include "LinkedList.hpp"
#include "DebounceTask.hpp"
#include "PneumaticActuator.hpp"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

typedef void (* GPIOcallbackFuncPtr_t)(void *);

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

class CbuttonHandler
        : public threadCore::CTaskBase
{
public:
    class CGPIOCallback
    {
    public:
        uint32_t counter;
        GPIOcallbackFuncPtr_t shortPressCallback;
        GPIOcallbackFuncPtr_t longPressCallback;
        void * pInstance;
    };

    CbuttonHandler(char const * const pName
                  , const float freq
                  , uint32_t priority
                  , void * const pStack
                  , const size_t stackSize
                  , CDebounceTask * pDebounceTask
                  , CPneumaticActuator * pActuator = nullptr
                  , CWatchdogBase * pWatchdog = nullptr);
    ~CbuttonHandler(void) = default;
    void funcBegin(void) override;
    void funcMain(void) override;

private:
    void subscribe(GPIO_TypeDef * GPIO_port
                   , uint16_t GPIO_pin
                   , uint32_t pull_up_down
                   , GPIOcallbackFuncPtr_t shortPressCallback
                   , GPIOcallbackFuncPtr_t longPressCallback
                   , void * pInstance);
    static void _press(void * pInstance);
    static void _release(void * pInstance);
    static void _shortButtonPress(void * pInstance);
    static void _longButtonPress(void * pInstance);
    void pressed();
    void released();

private:
    uint32_t m_changed;
    uint32_t m_buttonState;
    uint32_t m_previousButtonState;
    size_t m_buttonCount;
    CLinkedList<CGPIOCallback> m_buttonCounter;
    CDebounceTask * m_pDebounceTask;
    CPneumaticActuator * m_pActuator;

};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* BUTTONHANDLER_HPP */
