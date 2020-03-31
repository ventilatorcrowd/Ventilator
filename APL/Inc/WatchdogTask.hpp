/*******************************************************************************
* File          : WatchdogTask.hpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 3 Mar 2020
*
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APL_INC_WATCHDOGTASK_HPP
#define APL_INC_WATCHDOGTASK_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "stdint.h"
#include "TaskBase.hpp"
#include "WatchdogThread.hpp"
#include "LinkedList.hpp"
#include "cmsis_os2.h"
#include "stm32f7xx_hal.h"
#include "stm32f7xx_hal_iwdg.h"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define WD_SUCCESS (0)
#define WD_FAIL (-1)
constexpr uint32_t MAX_TRACKERS = 15;

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

typedef struct
{
    void const *    taskHandle;
    uint32_t        taskID;
    bool            sleep;
    uint32_t        periodMS;
    uint32_t        maxCounter;
    timeoutFunc     callback;
    void *          pInstance;
    void *          pMsg;
}activity_t;

typedef int32_t watchdogHandle_t;

class CWatchdogTask
        : public threadCore::CTaskBase
        , public CWatchdogBase
{
public:
    CWatchdogTask(char const * const pName = "WatchdogTask"
                  , const float freq = 100
                  , const uint32_t priority = osPriorityRealtime7
                  , void * const pStack = nullptr
                  , const size_t stackSize = 0
                  , IWDG_HandleTypeDef * pWatchdog = nullptr);
    ~CWatchdogTask() = default;
    void funcBegin(void) override;
    void funcMain(void) override;
    int32_t registerTask(void * pHandle
                         , uint32_t periodMS
                         , timeoutFunc callback = nullptr
                         , void * pInstance = nullptr
                         , void * pMsg = nullptr) override;
    int32_t deregisterTask(void * pHandlepHandle) override;
    int32_t feed(void * pHandle) override;
    int32_t sleep(void * pHandle) override;

private:
    IWDG_HandleTypeDef * m_pWatchdog;
    float m_freq;
    CLinkedList<activity_t> m_activityTracker;
    bool m_watchdogFeed;
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/

#endif /* APL_INC_WATCHDOGTASK_HPP */
