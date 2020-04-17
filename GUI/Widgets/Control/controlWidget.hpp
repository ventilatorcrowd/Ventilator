/*******************************************************************************
* File          : controlWidget.hpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 16 Apr 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef CONTROLWIDGET_HPP
#define CONTROLWIDGET_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "widgetBase.hpp"

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

class CControlWidget
    : public CWidgetBase
{
public:
    CControlWidget(CDisplay * pDisplay, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t backgroundColour)
        : CWidgetBase(pDisplay, x0, y0, x1, y1, backgroundColour)
        , respRate(pDisplay,    x0,                     y0,                     ((x1 - x0) / 2) - 1,    ((y1 - y0) / 2) - 1,  backgroundColour)
        , inspRate(pDisplay,    ((x1 - x0) / 2) + 1,    y0,                     x1,                     ((y1 - y0) / 2) - 1,  backgroundColour)
        , IERatio(pDisplay,     x0,                     ((y1 - y0) / 2) + 1,    ((x1 - x0) / 2) - 1,     y1,             backgroundColour)
        , TidalVolume(pDisplay, ((x1 - x0) / 2) + 1,    ((y1 - y0) / 2) + 1,    x1,                      y1,             backgroundColour)
    {

    }

    void init()
    {
        respRate.init();
        respRate.m_header.setFont(Arial12x12);
        respRate.m_header.setTextColour(WHITE);
        respRate.m_header.setText("Respiritory Rate");
        respRate.m_body.setFont(Arial12x12);
        respRate.m_body.setTextColour(WHITE);
        respRate.m_body.setText("0 bpm");

        inspRate.init();
        inspRate.m_header.setFont(Arial12x12);
        inspRate.m_header.setTextColour(WHITE);
        inspRate.m_header.setText("Inspiritory Rate");
        inspRate.m_body.setFont(Arial12x12);
        inspRate.m_body.setTextColour(WHITE);
        inspRate.m_body.setText("---");

        IERatio.init();
        IERatio.m_header.setFont(Arial12x12);
        IERatio.m_header.setTextColour(WHITE);
        IERatio.m_header.setText("I:E Rate");
        IERatio.m_body.setFont(Arial12x12);
        IERatio.m_body.setTextColour(WHITE);
        IERatio.m_body.setText("1:1");

        TidalVolume.init();
        TidalVolume.m_header.setFont(Arial12x12);
        TidalVolume.m_header.setTextColour(WHITE);
        TidalVolume.m_header.setText("Tidal Volume");
        TidalVolume.m_body.setFont(Arial12x12);
        TidalVolume.m_body.setTextColour(WHITE);
        TidalVolume.m_body.setText("0 ml");
    }

    ~CControlWidget() = default;
public:
    CTextbox respRate;
    CTextbox inspRate;
    CTextbox IERatio;
    CTextbox TidalVolume;
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* CONTROLWIDGET_HPP */
