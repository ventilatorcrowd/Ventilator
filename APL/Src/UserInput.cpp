/*******************************************************************************
* File          : UserInput.cpp
*
* Description   : 
*
* Project       : 
*
* Author        : s.gilbert
*
* Created on    : 30 Mar 2020
*
*******************************************************************************/

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "UserInput.hpp"

/*******************************************************************************
NAMESPACE
*******************************************************************************/


/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define ADC_MAX_VOLTAGE (3.3f)
#define ADC_BIT_COUNT (4096.0f)
#define ADC_BIT_WEIGHT (ADC_MAX_VOLTAGE / ADC_BIT_COUNT)

/*******************************************************************************
TYPES
*******************************************************************************/

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
MODULE VARIABLES
*******************************************************************************/

/*******************************************************************************
MODULE FUNCTION DECLARATIONS
*******************************************************************************/

/*******************************************************************************
FUNCTION DEFINITIONS
*******************************************************************************/
/**\brief   Constructor
 *
 * \param   pName       - pointer to the task name
 * \param   freq        - task update frequency
 * \param   priority    - task priority
 * \param   pStack      - pointer to stack space
 * \param   stackSize   - stack size in bytes
 * \param   pADC        - pointer to the adc handle
 * \param   m_pActuator - pointer to the actuator class
 * \param   pWatchdog   - pointer to the watchdog hardware
 *
 * \return  None
 */
CUserInput::CUserInput(char const * const pName
                     , const float freq
                     , uint32_t priority
                     , void * const pStack
                     , const size_t stackSize
                     , ADC_HandleTypeDef * pADC
                     , CControlWidget * pOutputDisplay
                     , CPneumaticActuator * pActuator
                     , CWatchdogBase * pWatchdog)
    : threadCore::CTaskBase(pName, freq, priority, pStack, stackSize, pWatchdog)
    , m_pADC(pADC)
    , m_pOutputDisplay(pOutputDisplay)
    , m_pActuator(pActuator)
//    , m_channel({0})
//    , m_ADCData({0})
{}

/**\brief   Main routine, averages the ADC readings. called every 10mS
 *
 * \param   None
 *
 * \return  None
 */
void CUserInput::funcMain(void)
{
    uint16_t channel[CHANNEL_COUNT][BUFFER_DEPTH] = {0};

    /* deinterleave data into 3 channels to allow buffers to be processed as
     * independant arrays.
     */
    auto arrayIndex = 0;
    for (auto channelArrayIndex = 0u; channelArrayIndex < BUFFER_DEPTH; ++channelArrayIndex)
    {
        channel[0][channelArrayIndex] = m_ADCData[arrayIndex];
        ++arrayIndex;
        channel[1][channelArrayIndex] = m_ADCData[arrayIndex];
        ++arrayIndex;
        channel[2][channelArrayIndex] = m_ADCData[arrayIndex];
        ++arrayIndex;
    }

    m_channel[0] = calcBufferAvg(&channel[0][0], ARRAY_LEN(channel[0])) / ADC_BIT_COUNT * 100;
    m_channel[1] = calcBufferAvg(&channel[1][0], ARRAY_LEN(channel[0])) / ADC_BIT_COUNT * 100;
    m_channel[2] = calcBufferAvg(&channel[2][0], ARRAY_LEN(channel[0])) / ADC_BIT_COUNT * 100;

    m_pActuator->setSpeed((uint32_t)m_channel[0]);
    m_pActuator->setAmplitude((uint32_t)m_channel[1]);

    static uint32_t taskCount = 0;

    if(10 < taskCount)
    {
        char respRate[10] = {0};
        snprintf(respRate, sizeof(respRate), "%d bpm", (uint32_t)m_channel[0]);
//        m_pOutputDisplay->respRate.m_body.setText(respRate);
        taskCount = 0;
    }
    ++taskCount;


    HAL_ADC_Start_DMA(m_pADC, (uint32_t *)m_ADCData, ARRAY_LEN(m_ADCData));
}

/**\brief   Simple routine to calculate the average value of a buffer
 *
 * \param   pADCbuffer  - pointer to buffer
 * \param   length      - number of items in the buffer
 *
 * \return  Average reading of the buffer
 */
float CUserInput::calcBufferAvg(uint16_t * pADCbuffer, size_t length)
{
    float returnVal = 0;

    for (auto arrayIndex = 0u; arrayIndex < length; ++arrayIndex)
    {
        returnVal += pADCbuffer[arrayIndex];
    }

    return returnVal / length;
}
