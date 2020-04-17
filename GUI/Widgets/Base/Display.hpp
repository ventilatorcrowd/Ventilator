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
    virtual int putc(char value) = 0;
    virtual int puts(char const * const pString) = 0;
    virtual int putsN(uint8_t const * const pString, size_t length) = 0;
    virtual void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t colour) = 0;

};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* DISPLAY_HPP */
