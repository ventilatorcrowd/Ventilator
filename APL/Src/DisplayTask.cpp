/*******************************************************************************
* File          : DisplayTask.cpp
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

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "DisplayTask.hpp"

#include "Arial12x12.h"
#include "Arial24x23.h"
#include "Arial28x28.h"

#include "GUI.h"

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

extern GUI_CONST_STORAGE GUI_BITMAP bmVentilatorCrowdLogo0201;

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
 * \param   pDisplay    - pointer to display handle
 * \param   height      - display height in pixels
 * \param   width       - display width in pixels
 *
 * \return  None
 */
CDisplayTask::CDisplayTask(char const * const pName
                     , const float freq
                     , uint32_t priority
                     , void * const pStack
                     , const size_t stackSize
                     , CDisplay * pDisplay
                     , uint32_t height
                     , uint32_t width
                     , CWatchdogBase * pWatchdog)
    : threadCore::CTaskBase(pName, freq, priority, pStack, stackSize, pWatchdog)
    , m_pDisplay(pDisplay)
    , m_height(height)
    , m_width(width)
    , ControlWidget(m_pDisplay, 0, 0, m_width, (m_height / 2) - 1, BLUE)
    , GraphWidget(m_pDisplay, 0, (m_height / 2) + 1, m_width, m_height, LIGHTGREY)
    , IndicatorWidget(m_pDisplay
                      , m_width - 10
                      , (m_height / 2) + 1
                      , m_width
                      , (m_height / 2) + 1 + 10
                      , RED)
{}

/**\brief   Starts display
 *
 * \param   None
 *
 * \return  None
 */
void CDisplayTask::funcBegin(void)
{
    showSplashScreen();
    sleepMilliseconds(2000);
    m_pDisplay->fillScreen(WHITE);

    ControlWidget.init();
    GraphWidget.init();
    IndicatorWidget.init();
    this->m_init = true;
}

/**\brief   Main routine, controls the images being generated on the display.
 *
 * \param   None
 *
 * \return  None
 */
void CDisplayTask::funcMain(void)
{

    uint32_t testData[] = {0x8000,0x8283,0x8506,0x8789,0x8a0a,0x8c8b,0x8f0b,0x9189,
            0x9405,0x9680,0x98f8,0x9b6e,0x9de1,0xa051,0xa2be,0xa527,
            0xa78d,0xa9ef,0xac4d,0xaea6,0xb0fb,0xb34b,0xb596,0xb7dc,
            0xba1c,0xbc56,0xbe8a,0xc0b9,0xc2e0,0xc502,0xc71c,0xc930,
            0xcb3c,0xcd41,0xcf3e,0xd133,0xd320,0xd505,0xd6e2,0xd8b6,
            0xda82,0xdc44,0xddfd,0xdfad,0xe154,0xe2f1,0xe484,0xe60e,
            0xe78d,0xe902,0xea6d,0xebcd,0xed22,0xee6d,0xefad,0xf0e2,
            0xf20c,0xf32a,0xf43d,0xf545,0xf641,0xf731,0xf816,0xf8ee,
            0xf9bb,0xfa7c,0xfb31,0xfbd9,0xfc76,0xfd06,0xfd89,0xfe01,
            0xfe6c,0xfeca,0xff1c,0xff61,0xff9a,0xffc6,0xffe6,0xfff9,
            0xffff,0xfff9,0xffe6,0xffc6,0xff9a,0xff61,0xff1c,0xfeca,
            0xfe6c,0xfe01,0xfd89,0xfd06,0xfc76,0xfbd9,0xfb31,0xfa7c,
            0xf9bb,0xf8ee,0xf816,0xf731,0xf641,0xf545,0xf43d,0xf32a,
            0xf20c,0xf0e2,0xefad,0xee6d,0xed22,0xebcd,0xea6d,0xe902,
            0xe78d,0xe60e,0xe484,0xe2f1,0xe154,0xdfad,0xddfd,0xdc44,
            0xda82,0xd8b6,0xd6e2,0xd505,0xd320,0xd133,0xcf3e,0xcd41,
            0xcb3c,0xc930,0xc71c,0xc502,0xc2e0,0xc0b9,0xbe8a,0xbc56,
            0xba1c,0xb7dc,0xb596,0xb34b,0xb0fb,0xaea6,0xac4d,0xa9ef,
            0xa78d,0xa527,0xa2be,0xa051,0x9de1,0x9b6e,0x98f8,0x9680,
            0x9405,0x9189,0x8f0b,0x8c8b,0x8a0a,0x8789,0x8506,0x8283,
            0x8000,0x7d7c,0x7af9,0x7876,0x75f5,0x7374,0x70f4,0x6e76,
            0x6bfa,0x697f,0x6707,0x6491,0x621e,0x5fae,0x5d41,0x5ad8,
            0x5872,0x5610,0x53b2,0x5159,0x4f04,0x4cb4,0x4a69,0x4823,
            0x45e3,0x43a9,0x4175,0x3f46,0x3d1f,0x3afd,0x38e3,0x36cf,
            0x34c3,0x32be,0x30c1,0x2ecc,0x2cdf,0x2afa,0x291d,0x2749,
            0x257d,0x23bb,0x2202,0x2052,0x1eab,0x1d0e,0x1b7b,0x19f1,
            0x1872,0x16fd,0x1592,0x1432,0x12dd,0x1192,0x1052,0xf1d,
            0xdf3,0xcd5,0xbc2,0xaba,0x9be,0x8ce,0x7e9,0x711,
            0x644,0x583,0x4ce,0x426,0x389,0x2f9,0x276,0x1fe,
            0x193,0x135,0xe3,0x9e,0x65,0x39,0x19,0x6,
            0x0,0x6,0x19,0x39,0x65,0x9e,0xe3,0x135,
            0x193,0x1fe,0x276,0x2f9,0x389,0x426,0x4ce,0x583,
            0x644,0x711,0x7e9,0x8ce,0x9be,0xaba,0xbc2,0xcd5,
            0xdf3,0xf1d,0x1052,0x1192,0x12dd,0x1432,0x1592,0x16fd,
            0x1872,0x19f1,0x1b7b,0x1d0e,0x1eab,0x2052,0x2202,0x23bb,
            0x257d,0x2749,0x291d,0x2afa,0x2cdf,0x2ecc,0x30c1,0x32be,
            0x34c3,0x36cf,0x38e3,0x3afd,0x3d1f,0x3f46,0x4175,0x43a9,
            0x45e3,0x4823,0x4a69,0x4cb4,0x4f04,0x5159,0x53b2,0x5610,
            0x5872,0x5ad8,0x5d41,0x5fae,0x621e,0x6491,0x6707,0x697f,
            0x6bfa,0x6e76,0x70f4,0x7374,0x75f5,0x7876,0x7af9,0x7d7c};

    static uint32_t i = 0;
    static uint32_t lineID = 0;

    GraphWidget.addPoint(lineID, (((float)testData[i]) /65535.0f) * (100.0 / (lineID + 1)), RED);
    if(i > ARRAY_LEN(testData))
    {
        i = 0;
        GraphWidget.setLineColour(lineID, DARKGREY);
        lineID = (++lineID) % MAX_LINES;

        GraphWidget.deleteLine(lineID);
    }
    else
    {
        ++i;
    }

    if(m_newRespValue)
    {
        char respRate[10] = {0};
        snprintf(respRate, sizeof(respRate), "%d bpm", m_respiritoryValue);
        ControlWidget.respRate.m_body.setText(respRate);
        m_newRespValue = false;
    }

    if(m_newPhaseValue)
    {
        IndicatorWidget.setColour(m_phaseValue ? GREEN : BLUE);
        m_newPhaseValue = false;
    }

}

/**\brief   Shows the start spash screen
 *
 * \param   None
 *
 * \return  None
 */
void CDisplayTask::showSplashScreen(void)
{
    m_pDisplay->drawImage(0, 55, 320, 129, (uint16_t *)bmVentilatorCrowdLogo0201.pData, 412800u);

    m_pDisplay->setBackgroundColour(WHITE);
    m_pDisplay->setFont(Arial28x28);
    m_pDisplay->setTextLocation(50, 0);
    m_pDisplay->puts("DEVELOPMENT");

    m_pDisplay->setFont(Arial12x12);
    m_pDisplay->setTextLocation(240 - 60, 240 - 12);
    m_pDisplay->puts("Version: Dev 1.0.0");
}

void CDisplayTask::setRespRateValue(uint32_t value)
{
    if(this->m_init)
    {
        if(value != m_respiritoryValue)
        {
            m_respiritoryValue = value;
            m_newRespValue = true;
        }
    }
}

void CDisplayTask::setPhaseValue(bool phase)
{
    if(this->m_init)
    {
        if(phase != m_phaseValue)
        {
            m_phaseValue = phase;
            m_newPhaseValue = true;
        }
    }
}


