/*******************************************************************************
* File          : DebounceTask.cpp
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

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "DebounceTask.hpp"
#include "stm32f7xx_hal.h"
//#include "stm32f405xx.h"
#include "stdint.h"
#include "TaskConfigs.hpp"

/*******************************************************************************
NAMESPACE
*******************************************************************************/

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define DEBOUNCE_TIME_MS (10)

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
CONSTANTS
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

//const osThreadDef_t os_thread_def_debounce = {
//        DebounceTask.pThreadName,
//        nullptr,    // this gets populated in the task.start routine
//        DebounceTask.priority,
//        0,
//        DebounceTask.stackSize
//};

/*******************************************************************************
MODULE VARIABLES
*******************************************************************************/

uint8_t subscriptionTable[(sizeof(CNode<CSubscribeDebounce::subscription_t>) + sizeof(bool))]; // memory space for subscription table, effective number of active GPIO subscriptions at a given time.
uint32_t debounceTable[DEBOUNCE_TIME_MS * DBTASKFREQUENCY_MS];                  //  debounce stabilisiation period x task frequency

/*******************************************************************************
MODULE FUNCTION DECLARATIONS
*******************************************************************************/

/*******************************************************************************
FUNCTION DEFINITIONS
*******************************************************************************/

/**\brief   Constructor.
 *
 * \param   pName       - pointer to the task name
 * \param   freq        - task update frequency
 * \param   priority    - task priority
 * \param   pStack      - pointer to stack space
 * \param   stackSize   - stack size in bytes
 * \param   pWatchdog   - pointer to the watchdog hardware
 *
 * \return  None
 */
CDebounceTask::CDebounceTask(char const * const pName
                             , const float freq
                             , uint32_t priority
                             , void * const pStack
                             , const size_t stackSize
                             , CWatchdogBase * pWatchdog)
    : threadCore::CTaskBase(pName, freq, priority, pStack, stackSize, pWatchdog)
//    , m_OSThreadDef(OSThreadDef)
    , m_subscribedGPIOs(subscriptionTable, sizeof(subscriptionTable))
    , GPIOData(debounceTable, sizeof(debounceTable))
{}

/**\brief   Registers a callback to the specified port and pin combination.
 *
 * \param   GPIO_port           - pointer to the port struct
 * \param   GPIO_pin            - pin ID
 * \param   pull_up_down        - one of GPIO_NOPULL, GPIO_PULLUP or GPIO_PULLDOWN
 * \param   assertCallback      - pointer to function to use for callback
 * \param   assertArg           - pointer to callback argument
 * \param   deassertCallback    - pointer to function to use for callback
 * \param   deassertArg         - pointer to callback argument
 *
 * \return  returns true if successful otherwise returns false
 */
bool CDebounceTask::subscribe(GPIO_TypeDef * GPIO_port
                              , uint16_t GPIO_pin
                              , uint32_t pull_up_down
                              , callbackFuncPtr_t assertCallback, void * assertArg
                              , callbackFuncPtr_t deassertCallback, void * deassertArg)
{
    return m_subscribedGPIOs.subscribe(GPIO_port
                                , GPIO_pin
                                , pull_up_down
                                , assertCallback, assertArg
                                , deassertCallback, deassertArg);
}

/**\brief   Unregisters the callback of the specified port and pin combination
 *
 * \param   GPIO_port   - pointer to the port struct
 * \param   GPIO_pin    - pin ID
 *
 * \return  None
 */
void CDebounceTask::unsubscribe(GPIO_TypeDef * GPIO_port, uint16_t GPIO_pin)
{
    m_subscribedGPIOs.unsubscribe(GPIO_port , GPIO_pin);
}

/**\brief   main thread function.
 *
 * \param   None
 *
 * \return  None
 */
void CDebounceTask::funcMain(void)
{
    auto subscribeCount = m_subscribedGPIOs.getSubscriptionCount();

    updateIOs(subscribeCount);
    checkDebouncedIOs(subscribeCount);
}

/**\brief   Gets the current IO states of all registered IOs and pushes values
 *          to the debounce arrays. Then updates debounce states.
 *
 * \param   subscribeCount  - number of entries in list
 *
 * \return  None
 */
void CDebounceTask::updateIOs(uint32_t subscribeCount)
{
    GPIO_TypeDef * GPIO_port = nullptr;
    uint16_t pGPIO_pin = 0;
    uint32_t pinList = 0;

    for(auto i = 0u; i < subscribeCount; ++i)
    {
        m_subscribedGPIOs.getSubscriptionList(i, &GPIO_port, &pGPIO_pin);
        pinList |= ((HAL_GPIO_ReadPin(GPIO_port, pGPIO_pin) == GPIO_PIN_SET ? 1u : 0u) << i);
    }

    GPIOData.update(pinList);
}

/**\brief   Checks the debounced IOs for an assert and calls the associated
 *          callback.
 *
 * \param   subscribeCount  - number of entries in list
 *
 * \return  None
 */
void CDebounceTask::checkDebouncedIOs(uint32_t subscribeCount)
{
    for(auto i = 0u; i < subscribeCount; ++i)
    {
        /* isAsserted() is true only when the IO (after debouncing) initially
         * changes state. Will not be true again until the IO is first
         * de-asserted.
         */
        if(GPIOData.isAsserted((i + 1)))
        {
            callbackFuncPtr_t callback = m_subscribedGPIOs.getAssertCallback(i);
            if(callback)
            {
                callback(m_subscribedGPIOs.getAssertCallbackMsg(i));
            }
        }
        if(GPIOData.isDeasserted((i + 1)))
        {
            callbackFuncPtr_t callback = m_subscribedGPIOs.getDeassertCallback(i);
            if(callback)
            {
                callback(m_subscribedGPIOs.getDeassertCallbackMsg(i));
            }
        }
    }
}

/**\brief   Has selected GPIO been asserted.
 *
 * \param   GPIOID  - GPIO to be checked
 *
 * \return  returns true if the selected GPIO has been pressed
 */
bool CDebounceTask::isAsserted(uint32_t GPIOID)
{
    return GPIOData.isAsserted(GPIOID);
}


/**\brief   Has selected GPIO been de-asserted.
 *
 * \param   GPIOID  - GPIO to be checked
 *
 * \return  returns true if the selected GPIO has been released
 */
bool CDebounceTask::isDeasserted(uint32_t GPIOID)
{
    return GPIOData.isDeasserted(GPIOID);
}

/**\brief   Has any GPIO changed state
 *
 * \param   None
 *
 * \return  returns 1 in the bit field if any GPIO that has changed state
 */
uint32_t CDebounceTask::anyChangedState(void)
{
    return GPIOData.anyChangedState();
}
