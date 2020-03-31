/*******************************************************************************
* File          : AdMutex.cpp
*
* Description   : Implementation file for mutex tools
*
* Project       :
*
* Author        : R.Dixon
*
* Created on    : 01 Apr 2019
*
* This document is protected by copyright, and contains information proprietary
* to Animal Dynamics.
*
* $Id: AdMutex.cpp 12 2019-04-15 20:07:02Z sgilbert $
*******************************************************************************/

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "AdMutex.hpp"
#include "ch.h"

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

using namespace adCore;

/*******************************************************************************
INLINE FUNCTIONS
*******************************************************************************/

CMutex::CMutex()
    : m_pMtx(reinterpret_cast<mutex_t*>(m_mtxBuf))
{
    SIZE_OF_CHIBIOS_MUTEX::Check<sizeof(mutex_t)>();
    chMtxObjectInit(m_pMtx);
}

/**\brief   Maps the AD mutex lock request on to the ChibiOS mutex lock
 *
 * \param   None
 *
 * \return  None
 */
void CMutex::Lock(void)
{
  chMtxLock(m_pMtx);
}

/**\brief   Maps the AD mutex unlock request on to the ChibiOS mutex unlock
 *
 * \param   None
 *
 * \return  None
 */
void CMutex::Unlock(void)
{
  chMtxUnlock(m_pMtx);
}

/**\brief   Constructor. Triggers the mutex lock
 *
 * \param   mtx -   Reference to the mutex
 *
 * \return  None
 */
CMutexLock::CMutexLock(CMutex& mtx)
        : m_rMtx(mtx)
{
    m_rMtx.Lock();
}

/**\brief   Destructor. Clears the mutex lock
 *
 * \param   None
 *
 * \return  None
 */
CMutexLock::~CMutexLock()
{
    m_rMtx.Unlock();
}
