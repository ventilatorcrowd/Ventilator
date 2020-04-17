/*******************************************************************************
* File          : DisplayTask.hpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 17 Apr 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef DISPLAYTASK_HPP
#define DISPLAYTASK_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "TaskBase.hpp"
#include "Display.hpp"

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


class CDisplayTask
    : public threadCore::CTaskBase
{
public:
    CDisplayTask(char const * const pName
                  , const float freq
                  , uint32_t priority
                  , void * const pStack
                  , const size_t stackSize
                  , CDisplay * pDisplay
                  , CWatchdogBase * pWatchdog = nullptr);
    ~CDisplayTask(void) = default;
    void funcBegin(void) override;
    void funcMain(void) override;

private:

private:
    CDisplay * m_pDisplay;
};


/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* DISPLAYTASK_HPP */
