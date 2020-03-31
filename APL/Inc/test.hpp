/*
 * test.hpp
 *
 *  Created on: 4 Jan 2020
 *      Author: s.gilbert
 */

#ifndef TEST_HPP
#define TEST_HPP

#include "TaskBase.hpp"


class CTestTask
    : public threadCore::CTaskBase
{
public:
    CTestTask(char const * const pName,
              const float freq = 100.0
              , uint32_t priority = 1
              , void * const pStack = nullptr
              , const size_t stackSize = 0
              , CWatchdogBase * pWatchdog = nullptr);
    ~CTestTask() = default;
    void funcMain() override;
    bool funcTimeout(void * pMsg) override;

//private:
    char const * const m_pTaskName;
    float m_freq;
    uint32_t m_taskCount;
protected:
};



#endif /* APL_INC_TEST_HPP_ */
