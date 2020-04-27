/*******************************************************************************
* File          : SubscribeDebounce.hpp
*
* Description   : 
*
* Project       :
*
* Author        : s.gilbert
*
* Created on    : 2 Mar 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SUBSCRIBEDEBOUNCE_HPP
#define SUBSCRIBEDEBOUNCE_HPP

/******************************************************************************
INCLUDES
*******************************************************************************/

#include "SubscribeBase.hpp"

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
CONSTANTS
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

class CSubscribeDebounce
    : public CSubscribeBase
{
public:
    CSubscribeDebounce(void * pTable, size_t size);
    ~CSubscribeDebounce() = default;

private:
    void configureGPIO(subscription_t * pSubscription) override;
    void unconfigureGPIO(subscription_t * pSubscription) override;
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/


#endif /* SUBSCRIBEDEBOUNCE_HPP */
