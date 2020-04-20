/*******************************************************************************
* File          : GraphWidget.hpp
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
#ifndef GRAPHWIDGET_HPP
#define GRAPHWIDGET_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "widgetBase.hpp"
#include "LinkedList.hpp"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define MAX_LINES (10)

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

class CGraphWidget
    : public CWidgetBase
{

public:
    CGraphWidget(CDisplay * pDisplay, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t backgroundColour)
        : CWidgetBase(pDisplay, x0, y0, x1, y1, backgroundColour)
        , m_title(pDisplay
            , (x0 + ((x1 - x0) / 2))
            , y0 + 1
            , (x0 + ((x1 - x0) / 2))
            , y0 + 1
            , nullptr
            , BLACK
            , backgroundColour)
        , m_xLegend(x0, x1, y1 - 10, y1 - 10, DARKGREY)
        , m_yLegend(x0 + 10, x0 + 10, y0, y1, DARKGREY)
    {
        for (int i = 0; i < MAX_LINES; ++i)
        {
            m_line[i].init(&m_dataTable[i][0], sizeof(m_dataTable[i]));
        }

    }

    ~CGraphWidget() = default;

    void init()
    {
        CWidgetBase::init();
        m_title.init();
        m_title.setFont(Arial12x12);
        m_title.setText("Pressure");
        m_pDisplay->drawLine(m_xLegend.m_x0
                             , m_xLegend.m_y0
                             , m_xLegend.m_x1
                             , m_xLegend.m_y1
                             , m_xLegend.m_colour);

        m_pDisplay->drawLine(m_yLegend.m_x0
                             , m_yLegend.m_y0
                             , m_yLegend.m_x1
                             , m_yLegend.m_y1
                             , m_yLegend.m_colour);
    }

    void addPoint(uint32_t lineID, float y0, uint16_t colour)
    {
        if (m_init)
        {
            uint32_t x = m_yLegend.m_x0;
            uint32_t y = m_xLegend.m_y0 - (((m_position.m_y0 - 10) / 100) * y0);
            CPixel lastPoint;

            uint32_t activeNodeCount = m_line[lineID].countNodes();
            m_line[lineID].peakFromNode(activeNodeCount, &lastPoint);

            if(0 != activeNodeCount)
            {
                x = lastPoint.m_x0 + 1;
            }
            CPixel point(x, y, colour);
            m_line[lineID].pushToBack(&point);
            m_pDisplay->drawPixel(point.m_x0, point.m_y0, point.m_colour);
        }
    }

    void setLineColour(uint32_t lineID, uint16_t colour)
    {
        for (uint32_t nodeList = 0; nodeList < m_line[lineID].countNodes(); ++nodeList)
        {
            CPixel point;
            m_line[lineID].peakFromNode(nodeList, &point);
            point.m_colour = colour;
            m_line[lineID].updateNode(nodeList, &point);
            m_pDisplay->drawPixel(point.m_x0, point.m_y0, point.m_colour);
        }
    }

    void deleteLine(uint32_t lineID)
    {
        setLineColour(lineID, m_backgroundColour);
        m_line[lineID].deleteList();
    }

public:
    CText m_title;
    CLine m_xLegend;
    CLine m_yLegend;

    uint8_t m_dataTable[MAX_LINES][320 * sizeof(CNode<CPixel>)];
    CLinkedList<CPixel> m_line[MAX_LINES];
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* GRAPHWIDGET_HPP */
