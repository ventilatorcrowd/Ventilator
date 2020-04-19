/*******************************************************************************
* File          : widgetBase.hpp
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
#ifndef WIDGETBASE_HPP
#define WIDGETBASE_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "Display.hpp"
#include "stdint.h"
#include "stdio.h"
#include "string.h"

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

class CPixel
{
public:
    CPixel(int16_t x0 = 0, int16_t y0 = 0, uint16_t colour = 0)
    : m_x0(x0)
    , m_y0(y0)
    , m_colour(colour)
{

}

public:
    uint32_t m_x0;
    uint32_t m_y0;
    uint32_t m_colour;
};

class CPosition
{
public:
    CPosition(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1)
        : m_x0(x0)
        , m_x1(x1)
        , m_y0(y0)
        , m_y1(y1)
{}

public:
    uint32_t m_x0;
    uint32_t m_x1;
    uint32_t m_y0;
    uint32_t m_y1;
};

class CLine
    : public CPosition
{
public:
    CLine(uint32_t x0, uint32_t x1, uint32_t y0, uint32_t y1, uint32_t colour)
        : CPosition(x0, x1, y0, y1)
        , m_colour(colour)
        , m_width(1)
    {}

public:
    uint32_t m_colour;
    uint32_t m_width;
};

class CWidgetBase
{
public:
    CWidgetBase(CDisplay * pDisplay, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t backgroundColour)
    : m_pDisplay(pDisplay)
    , m_position(x0, x1, y0, y1)
    , m_backgroundColour(backgroundColour)
{}
    void init(void)
    {
        m_pDisplay->fillRect(this->m_position.m_x0
                             , this->m_position.m_y0
                             , this->m_position.m_x1 - this->m_position.m_x0
                             , this->m_position.m_y1 - this->m_position.m_y0
                             , this->m_backgroundColour);
    }

public:
    CDisplay * m_pDisplay;
    CPosition m_position;
    uint32_t m_backgroundColour;
};


class CText
        : public CWidgetBase
{
public:

    CText(CDisplay * pDisplay
          , uint32_t x0
          , uint32_t y0
          , uint32_t x1
          , uint32_t y1
          , unsigned char const * pFont
          , uint32_t fontColour
          , uint32_t backgroundColour)
        : CWidgetBase(pDisplay, x0, y0, x1, y1, backgroundColour)
        , m_text{0}
        , m_textLength(0)
        , m_xStart(x0 + ((x1 - x0) / 2))
        , m_yStart(y0 + ((y1 - y0) / 2))
        , m_xCurrent(m_xStart)
        , m_yCurrent(m_yStart)
        , m_pFont(nullptr)
        , m_fontColour(fontColour)
        , m_backgroundColour(backgroundColour)
    {}

    void setFont(unsigned char const * pFont)
    {
        m_pFont = pFont;
    }

    void setTextColour(uint32_t fontColour)
    {
        m_fontColour = fontColour;
    }

    void setText(char const * string)
    {
        m_pDisplay->setFont(m_pFont);
        m_pDisplay->setTextLocation(m_xCurrent, m_yCurrent);
        m_pDisplay->setBackgroundColour(m_backgroundColour);

        if(findStringWidth((char const *)m_text) != findStringWidth(string))
        {
            // write text in background colour in case new text is smaller
            m_pDisplay->setTextColour(m_backgroundColour);
            m_pDisplay->putsN((uint8_t const *)m_text, m_textLength);
        }

        m_textLength = strlen(strncpy(m_text, string, sizeof(m_text)));
        m_xCurrent = m_xStart - (findStringWidth(m_text) / 2);
        m_pDisplay->setTextLocation(m_xCurrent, m_yCurrent);
        m_pDisplay->setTextColour(m_fontColour);
        m_pDisplay->putsN((uint8_t const *)m_text, m_textLength);
    }

    /**\brief   Finds character width.
     *
     * \param   c   - character
     *
     * \return  None
     */
    size_t findCharacterWidth(int c)
    {
        uint32_t hor = m_pFont[1];                       // get horizontal size of font
        uint32_t offset = m_pFont[0];                    // bytes / char;

        if ((c < 31) || (c > 127)) return 0;   // test char range
        unsigned char const * character = &m_pFont[(((uint32_t)c -32u) * offset) + 4u];
        unsigned char w = character[0];                          // width of actual char

        return ((w + 2u) < hor) ? (w + 2u) : hor;
    }

    /**\brief   Finds string width.
     *
     * \param   pStr    - pointer to the string
     *
     * \return  None
     */
    size_t findStringWidth(char const * const pStr)
    {
        size_t length = 0;

        for (auto i = 0u; i < strlen(pStr); ++i)
        {
            length += findCharacterWidth(pStr[i]);
        }

        return length;
    }

public:
    char m_text[100];
    size_t m_textLength;
    uint32_t m_xStart;
    uint32_t m_yStart;
    uint32_t m_xCurrent;
    uint32_t m_yCurrent;
    unsigned char const * m_pFont;
    uint32_t m_fontColour;
    uint32_t m_backgroundColour;
};

class CTextbox
    : public CWidgetBase
{

public:
    CTextbox(CDisplay * pDisplay, uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1, uint32_t backgroundColour)
    : CWidgetBase(pDisplay, x0, y0, x1, y1, backgroundColour)
    , m_header(pDisplay
                , (x0 + ((x1 - x0) / 2))
                , (y0 + ((y1 - y0) / 2)) - 15
                , (x0 + ((x1 - x0) / 2))
                , (y0 + ((y1 - y0) / 2)) - 15
                , nullptr
                , WHITE
                , backgroundColour)
    , m_body(pDisplay
             , (x0 + ((x1 - x0) / 2))
             , (y0 + ((y1 - y0) / 2))
             , (x0 + ((x1 - x0) / 2))
             , (y0 + ((y1 - y0) / 2))
             , nullptr
             , WHITE
             , backgroundColour)    {}

public:
    CText m_header;
    CText m_body;

};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* WIDGETBASE_HPP */
