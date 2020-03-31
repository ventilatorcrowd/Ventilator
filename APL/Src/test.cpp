/*******************************************************************************
* File          : test.cpp
*
* Description   :
*
* Project       :
*
* Author        : s.gilbert
*
* Created on    : 3 Jan 2020
*
*******************************************************************************/

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "test.hpp"
#include "CircularBuffer.hpp"
#include "stm32f7xx_hal.h"
#include "main.h"

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

/**\brief   Constructor
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

/**\brief   Main routine, toggles a GPIO a number of times and then falls in to
 *          a while loop.
 *
 * \param   None
 *
 * \return  None
 */
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

/**\brief   Watchdog timeout routine, sets a different GPIO high then exits.
 *          a while loop.
 *
 * \param   pMsg    - message from watchdog task
 *
 * \return  returns false which starves the watchdog
 */
bool CTestTask::funcTimeout(void * pMsg)
{
    (void)pMsg;
    HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);

    return false;
}
