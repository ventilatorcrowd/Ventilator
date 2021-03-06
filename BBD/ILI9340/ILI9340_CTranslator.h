/*******************************************************************************
* File          : ILI9340.h
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 14 Apr 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef ILI9340_H
#define ILI9340_H

#ifdef __cplusplus
extern "C" {
#endif

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
INLINE FUNCTION DEFINITIONS
*******************************************************************************/

void ILI9340_init(void);

void ILI9340_drawPixel(int16_t x, int16_t y, uint16_t colour);


#ifdef __cplusplus
}
#endif

#endif /* ILI9340_H */
