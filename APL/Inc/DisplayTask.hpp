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
#include "DisplayOutput.hpp"
#include "ActuatorDisplay.hpp"

#include "controlWidget.hpp"
#include "GraphWidget.hpp"
#include "IndicatorWidget.hpp"

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
    , public CDisplayOutput
    , public CActuatorDisplay
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
    void setRespRateValue(uint32_t value) override;
    void setPhaseValue(bool phase) override;

private:
    void showSplashScreen(void);

private:
    CDisplay * m_pDisplay;
    uint32_t m_height;
    uint32_t m_width;
    CControlWidget ControlWidget;
    CGraphWidget GraphWidget;
    CIndicatorWidget IndicatorWidget;
    uint32_t m_respiritoryValue;
    bool m_newRespValue;
    uint32_t m_phaseValue;
    bool m_newPhaseValue;
    bool m_init;
};


/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* DISPLAYTASK_HPP */
