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

#include "controlWidget.hpp"
#include "GraphWidget.hpp"

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
                  , uint32_t height
                  , uint32_t width
                  , CWatchdogBase * pWatchdog = nullptr);
    ~CDisplayTask(void) = default;
    void funcBegin(void) override;
    void funcMain(void) override;

private:
    void showSpashScreen(void);

private:
    CDisplay * m_pDisplay;
    uint32_t m_height;
    uint32_t m_width;
    CControlWidget ControlWidget;
    CGraphWidget GraphWidget;
};


/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* DISPLAYTASK_HPP */
