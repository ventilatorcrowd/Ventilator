/*******************************************************************************
* File          : Display.hpp
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
#ifndef DISPLAY_HPP
#define DISPLAY_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "stdint.h"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define BLACK       0x0000
#define NAVY        0x000F
#define DARKGREEN   0x03E0
#define DARKCYAN    0x03EF
#define MAROON      0x7800
#define PURPLE      0x780F
#define OLIVE       0x7BE0
#define LIGHTGREY   0xC618
#define DARKGREY    0x7BEF
#define BLUE        0x001F
#define GREEN       0x07E0
#define CYAN        0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define YELLOW      0xFFE0
#define WHITE       0xFFFF
#define ORANGE      0xFD20
#define GREENYELLOW 0xAFE5
#define PINK        0xF81F

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

class CDisplay
{
public:
    CDisplay() = default;
    virtual ~CDisplay() = default;
    virtual void setTextLocation(uint32_t x, uint32_t y) = 0;
    virtual void setFont(unsigned char const * font) = 0;
    virtual void setTextColour(uint32_t colour) = 0;
    virtual void setBackgroundColour(uint32_t colour) = 0;
    virtual void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t colour) = 0;
    virtual void drawPixel(int16_t x0, int16_t y0, uint16_t colour) = 0;
    virtual int putc(char value) = 0;
    virtual int puts(char const * const pString) = 0;
    virtual int putsN(uint8_t const * const pString, size_t length) = 0;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t colour) = 0;

};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* DISPLAY_HPP */
