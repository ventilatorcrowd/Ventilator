/*******************************************************************************
* File          : ILI9340.cpp
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

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "ILI9340.hpp"
#include "string.h"

/*******************************************************************************
NAMESPACE
*******************************************************************************/


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
 * \param   pSPI        - pointer to the spi peripheral
 * \param   pCS_Port    - SPI chip select port
 * \param   CS_Pin      - SPI chip select ping
 * \param   pDC_Port    - LCD data/command port
 * \param   DC_Pin      - LCD data/command pin
 * \param   pReset_Port - LCD reset port
 * \param   Reset_Pin   - LCD reset pin
 *
 * \return  None
 */
CILI9340::CILI9340(SPI_HandleTypeDef * pSPI
                         , GPIO_TypeDef * pCS_Port
                         , uint16_t CS_Pin
                         , GPIO_TypeDef * pDC_Port
                         , uint16_t DC_Pin
                         , GPIO_TypeDef * pReset_Port
                         , uint16_t Reset_Pin)
    : m_pSPI(pSPI)
    , m_pCS_Port(pCS_Port)
    , m_CS_Pin(CS_Pin)
    , m_pDC_Port(pDC_Port)
    , m_DC_Pin(DC_Pin)
    , m_pReset_Port(pReset_Port)
    , m_Reset_Pin(Reset_Pin)
    , m_height(TFT_HEIGHT)
    , m_width(TFT_WIDTH)
    , char_xStart(0)
    , char_yStart(0)
    , char_x(0)
    , char_y(0)
    , m_pFont(nullptr)
    , m_fontColour(BLACK)
{}

/**\brief   Init function to set the screen up, must be called before use.
 *
 * \param   None
 *
 * \return  None
 */
void CILI9340::init(void)
{
    HWReset();
    chipInit();
    setRotation(0);
    fillScreen(WHITE);
}

/**\brief   Sets the area of screen to be written to.
 *
 * \param   x0  - Horizontal start position
 * \param   y0  - Vertical start position
 * \param   x1  - Horizontal end position
 * \param   y1  - Vertical end position
 *
 * \return  None
 */
void CILI9340::setScreenLocation(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1)
{
    uint8_t horizontal[] = {(uint8_t)(x0 >> 8), (uint8_t)x0, (uint8_t)(x1 >> 8), (uint8_t)x1};
    writeRegister(_CMD_CASET, horizontal, sizeof(horizontal));

    uint8_t vertical[] = {(uint8_t)(y0 >> 8), (uint8_t)y0, (uint8_t)(y1 >> 8), (uint8_t)y1};
    writeRegister(_CMD_PASET, vertical, sizeof(vertical));

    writeRegister(_CMD_RAMWR);
}

/**\brief   Triggers a hardware reset and brings the LCD back up with the
 *          correct delays. When this function exits, the LCD should be back up
 *          and running.
 *
 * \param   None
 *
 * \return  None
 */
void CILI9340::HWReset(void)
{
    HAL_GPIO_WritePin(m_pReset_Port, m_Reset_Pin, GPIO_PIN_SET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(m_pReset_Port, m_Reset_Pin, GPIO_PIN_RESET);
    HAL_Delay(500);
    HAL_GPIO_WritePin(m_pReset_Port, m_Reset_Pin, GPIO_PIN_SET);
    HAL_Delay(500);
}

/**\brief   Brings the LCD up with the registers all configured for use.
 *
 * \param   None
 *
 * \return  None
 */
void CILI9340::chipInit(void)
{
    uint8_t tempVal[] = {0x03, 0x80, 0x02};
    writeRegister(0xEF, tempVal, sizeof(tempVal));

    uint8_t tempVal1[] = {0x00, 0xC1, 0x30};
    writeRegister(0xCF, tempVal1, sizeof(tempVal1));

    uint8_t tempVal2[] = {0x64, 0x03, 0x12, 0x81};
    writeRegister(0xED, tempVal2, sizeof(tempVal2));

    uint8_t tempVal3[] = {0x85, 0x00, 0x78};
    writeRegister(0xE8, tempVal3, sizeof(tempVal3));

    uint8_t tempVal4[] = {0x39, 0x2C, 0x00, 0x34, 0x02};
    writeRegister(0xCB, tempVal4, sizeof(tempVal4));

    uint8_t tempVal5[] = {0x20};
    writeRegister(0xf7, tempVal5, sizeof(tempVal5));

    uint8_t tempVal6[] = {0x00, 0x00};
    writeRegister(0xEA, tempVal6, sizeof(tempVal6));

    uint8_t pwrCTRL1[] = {0x23};
    writeRegister(_CMD_PWCTR1, pwrCTRL1, sizeof(pwrCTRL1));

    uint8_t pwrCTRL2[] = {0x10};
    writeRegister(_CMD_PWCTR2, pwrCTRL2, sizeof(pwrCTRL2));

    uint8_t vmcCTRL1[] = {0x3e, 0x28};
    writeRegister(_CMD_VMCTR1, vmcCTRL1, sizeof(vmcCTRL1));

    uint8_t vmcCTRL2[] = {0x86};
    writeRegister(_CMD_VMCTR2, vmcCTRL2, sizeof(vmcCTRL2));

    uint8_t madCTRL[] = {BIT_MADCTL_MX | BIT_MADCTL_BGR};
    writeRegister(_CMD_MADCTL, madCTRL, sizeof(madCTRL));

    uint8_t picFMT[] = {0x55};
    writeRegister(_CMD_PIXFMT, picFMT, sizeof(picFMT));

    uint8_t frmCTRL[] = {0x00, 0x18};
    writeRegister(_CMD_FRMCTR1, frmCTRL, sizeof(frmCTRL));

    uint8_t dfuCTRL[] = {0x08, 0x82, 0x27};
    writeRegister(_CMD_DFUNCTR, dfuCTRL, sizeof(dfuCTRL));

    uint8_t g3CTRL[] = {0x00};
    writeRegister(_CMD_G3CTRL, g3CTRL, sizeof(g3CTRL));

    uint8_t gSET[] = {0x01};
    writeRegister(_CMD_GAMMASET, gSET, sizeof(gSET));

    uint8_t gammaCTRL_P[] = {0x0f, 0x31, 0x2B, 0x0C, 0x0E, 0x08, 0x4E, 0xF1
                            , 0x37, 0x07, 0x10, 0x03, 0x0E, 0x09, 0x00};
    writeRegister(_CMD_GMCTRP1, gammaCTRL_P, sizeof(gammaCTRL_P));

    uint8_t gammaCTRL_N[] = {0x00, 0x0E, 0x14, 0x03, 0x11, 0x07, 0x31, 0xC1
                            , 0x48, 0x08, 0x0F, 0x0C, 0x31, 0x36, 0x0F};
    writeRegister(_CMD_GMCTRN1, gammaCTRL_N, sizeof(gammaCTRL_N));

    writeRegister(_CMD_SLPOUT);
    HAL_Delay(120);
    writeRegister(_CMD_DISPON);
}

/**\brief   Write data to register. Can be used to write 0 data to register for
 *          soft resets and display on/off commands
 *
 * \param   regAddr - register to write data to
 * \param   pData   - pointer to array of data to send. Default nullptr
 * \param   length  - length of data to be written. Default 0
 *
 * \return  None
 */
void CILI9340::writeRegister(uint8_t regAddr, uint8_t * pData, size_t length)
{
    HAL_GPIO_WritePin(m_pDC_Port, m_DC_Pin, GPIO_PIN_RESET);

    HAL_GPIO_WritePin(m_pCS_Port, m_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(m_pSPI, &regAddr, 1, 1);

    HAL_GPIO_WritePin(m_pDC_Port, m_DC_Pin, GPIO_PIN_SET);

    if(0 < length)
    {
        HAL_SPI_Transmit(m_pSPI, pData, length, 1);
    }

    HAL_GPIO_WritePin(m_pCS_Port, m_CS_Pin, GPIO_PIN_SET);
}

/**\brief   Send data over SPI. Used to send data after the registers have been
 *          prepared to receive data.
 *
 * \param   pData   - pointer to array of data to send
 * \param   length  - length of data to be written
 *
 * \return  None
 */
void CILI9340::writeData(uint8_t * pData, size_t length)
{
    HAL_GPIO_WritePin(m_pDC_Port, m_DC_Pin, GPIO_PIN_SET);

    HAL_GPIO_WritePin(m_pCS_Port, m_CS_Pin, GPIO_PIN_RESET);

//    if(65535 < length)
    HAL_SPI_Transmit(m_pSPI, pData, length, 1);

    HAL_GPIO_WritePin(m_pCS_Port, m_CS_Pin, GPIO_PIN_SET);
}

/**\brief   Checks if the x and y coordinates exceed the boundary of the LCD.
 *
 * \param   x   - Horizontal component
 * \param   y   - Vertical component
 *
 * \return  true if exceeds boundary or false if not
 */
bool CILI9340::boundaryCheck(int16_t x, int16_t y)
{
  if ((x < 0) || (y < 0)) return true;  // todo - single return only needed here
  if ((x >= m_width) || (y >= m_height)) return true;
    return false;
}

/**\brief   Draws a single pixel at the desired coordinates
 *
 * \param   x       - Horizontal component
 * \param   y       - Vertical component
 * \param   colour  - colour to draw the pixel
 *
 * \return  true if exceeds boundary or false if not
 */
void CILI9340::drawPixel(int16_t x, int16_t y, uint16_t colour)
{
    fillRect(x, y, x + 1u, y + 1u, colour);
}

/**\brief   Draws a vertical single pixel width line at the desired coordinates.
 *
 * \param   x       - Horizontal component
 * \param   y       - Vertical component
 * \param   h       - line height
 * \param   colour  - colour to draw the pixel
 *
 * \return  true if exceeds boundary or false if not
 */
void CILI9340::drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t colour)
{
    fillRect(x, y, x, (y + h) - 1, colour);
}

/**\brief   Draws a horizontal single pixel width line at the desired
 *          coordinates.
 *
 * \param   x       - Horizontal component
 * \param   y       - Vertical component
 * \param   h       - line width
 * \param   colour  - colour to draw the pixel
 *
 * \return  true if exceeds boundary or false if not
 */
void CILI9340::drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t colour)
{
    fillRect(x, y, (x + w) - 1, y, colour);
}

/**\brief   Fills the screen with a single colour
 *
 * \param   colour  - colour to draw the pixel
 *
 * \return  true if exceeds boundary or false if not
 */
void CILI9340::fillScreen(uint16_t colour)
{
    fillRect(0, 0, m_width, m_height, colour);
}

/**\brief   Draws a rectangle at the desired coordinates.
 *
 * \param   x       - Horizontal component
 * \param   y       - Vertical component
 * \param   w       - rectangle width
 * \param   h       - rectangle height
 * \param   colour  - colour to draw the pixel
 *
 * \return  true if exceeds boundary or false if not
 */
void CILI9340::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t colour)
{
    if (boundaryCheck(x,y)) return;
    if (((x + w) - 1) >= m_width)  w = m_width - x;
    if (((y + h) - 1) >= m_height) h = m_height - y;
    setScreenLocation(x, y, (x + w) -1, (y + h) - 1);

    for (y = h; y > 0; y--)
    {
        for (x = w; x > 0; x--)
        {
            uint16_t pixel = __builtin_bswap16(colour);
            writeData((uint8_t *)&pixel, 2);
        }
    }
}

/**\brief   Draws a rectangular image at the desired coordinates.
 *
 * \param   x       - Horizontal component
 * \param   y       - Vertical component
 * \param   w       - rectangle width
 * \param   h       - rectangle height
 * \param   pColour - pointer to colour array
 *
 * \return  true if exceeds boundary or false if not
 */
void CILI9340::drawImage(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t * pColour, size_t length)
{
    if (boundaryCheck(x,y)) return;
    if (((x + w) - 1) >= m_width)  w = m_width - x;
    if (((y + h) - 1) >= m_height) h = m_height - y;
    setScreenLocation(x, y, (x + w) -1, (y + h) - 1);

    uint32_t pixelIndex = 0;
    for (y = h; y > 0; y--)
    {
        for (x = w; x > 0; x--)
        {
            uint16_t pixel = __builtin_bswap16(pColour[pixelIndex]);
            writeData((uint8_t *)&pixel, 2);
            ++pixelIndex;
        }
    }
}

/**\brief   Put single character out on the display.
 *
 * \param   value   - Character to write
 *
 * \return  character written
 */
int CILI9340::putc(char value)
{
    if (value == '\n')
    {    // new line
        char_x = char_xStart;
        char_y = char_y + m_pFont[2];
        if (char_y >= m_height - m_pFont[2])
        {
            char_y = char_yStart;
        }
    }
    else
    {
        drawCharacter(char_x, char_y, value);
    }

    return value;
}

/**\brief   Put null terminated string out on the display.
 *
 * \param   pString - Pointer to the string to write
 *
 * \return  number of characters written
 */
int CILI9340::puts(char const * const pString)
{
    auto charIndex = 0;

    while(charIndex < strlen(pString))
    {
        if(pString[charIndex] == '\0')
        {
            break;
        }
        if (pString[charIndex] == '\n')
        {    // new line
            char_x = char_xStart;
            char_y = char_y + m_pFont[2];
            if (char_y >= m_height - m_pFont[2])
            {
                char_y = char_yStart;
            }
        }
        else
        {
            drawCharacter(char_x, char_y, pString[charIndex]);
        }
        ++charIndex;
    }

    return charIndex;
}

/**\brief   Put null terminated string of defined length out on the display.
 *
 * \param   pString - Pointer to the string to write
 * \param   length  - length of string to write
 *
 * \return  number of characters written
 */
int CILI9340::putsN(uint8_t const * const pString, size_t length)
{
    auto charIndex = 0;

    while(charIndex < length)
    {
        if(pString[charIndex] == '\0')
        {
            break;
        }
        if (pString[charIndex] == '\n')
        {    // new line
            char_x = char_xStart;
            char_y = char_y + m_pFont[2];
            if (char_y >= m_height - m_pFont[2])
            {
                char_y = char_yStart;
            }
        }
        else
        {
            drawCharacter(char_x, char_y, pString[charIndex]);
        }
        ++charIndex;
    }

    return charIndex;
}

/**\brief   Sets text start location.
 *
 * \param   x   - horizontal component
 * \param   y   - vertical component
 *
 * \return  None
 */
void CILI9340::setTextLocation(uint32_t x, uint32_t y)
{
    char_x = char_xStart = x;
    char_y = char_yStart = y;
}

/**\brief   Sets text font.
 *
 * \param   pFont   - pointer to text array
 *
 * \return  None
 */
void CILI9340::setFont(unsigned char const * pFont)
{
    m_pFont = pFont;
    m_fontData.byteCount = m_pFont[0];                    // bytes / char
    m_fontData.horizontal = m_pFont[1];                       // get horizontal size of font
    m_fontData.vertical = m_pFont[2];                      // get vertical size of font
    m_fontData.pCharTable = &m_pFont[4];                       // start of bitmap table
}

/**\brief   Sets text font colour.
 *
 * \param   colour  - text colour
 *
 * \return  None
 */
void CILI9340::setTextColour(uint32_t colour)
{
    m_fontColour = colour;
}

/**\brief   Sets text background colour.
 *
 * \param   colour  - text colour
 *
 * \return  None
 */
void CILI9340::setBackgroundColour(uint32_t colour)
{
    m_backgroundColour = colour;
}

/**\brief   Creates the bit pattern for the desired character and sends it out
 *          on the comms bus.
 *
 * \param   x   - horizontal component
 * \param   y   - vertical component
 * \param   c   - character
 *
 * \return  None
 */
void CILI9340::drawCharacter(uint32_t x, uint32_t y, int c)
{
    unsigned int hor,
    vert,
    offset,
    bpl,
    j,
    i,
    b;
    unsigned char const * character;
    unsigned char z,w;

    #ifdef use_ram
    unsigned int pixel;
    unsigned int p;
    unsigned int dma_count,dma_off;
    uint16_t *buffer;
    #endif

    if ((c < 31) || (c > 127)) return;   // test char range

    // read m_pFont parameter from start of array
    offset = m_pFont[0];                    // bytes / char
    hor = m_pFont[1];                       // get horizontal size of font
    vert = m_pFont[2];                      // get vertical size of font
    bpl = m_pFont[3];                       // bytes per line

    if (char_x + hor > m_width)
    {
        char_x = char_xStart;
        char_y = char_y + vert;
        if (char_y >= m_height - m_pFont[2])
        {
            char_y = char_yStart;
        }
    }

    setScreenLocation(char_x, char_y, char_x + hor - 1, char_y + vert - 1);           // setup char box

    #ifdef use_ram
    pixel = hor * vert;                        // calculate buffer size
    buffer = (uint16_t *) malloc (2*pixel);    // we need a buffer for the font
    if(buffer != NULL) {                       // there is memory space -> use dma
        character = &m_pFont[((c -32) * offset) + 4]; // start of char bitmap
        w = character[0];                          // width of actual char
        p = 0;
        // construct the m_pFont into the buffer
        for (j=0; j<vert; j++) {            //  vert line
            for (i=0; i<hor; i++) {         //  horz line
                z =  character[bpl * i + ((j & 0xF8) >> 3)+1];
                b = 1 << (j & 0x07);
                if (( z & b ) == 0x00) {
                    buffer[p] = _background;
                } else {
                    buffer[p] = _foreground;
                }
                p++;
            }
        }
        // copy the buffer with DMA SPI to display
        dma_off = 0;  // offset for DMA transfer
        DMA_InitStructure.DMA_MemoryBaseAddr  = (uint32_t)  (buffer + dma_off);
        DMA_InitStructure.DMA_MemoryInc  = DMA_MemoryInc_Enable;

        switch(spi_num){        // decide which SPI is to use
        case (1):
        DMA_Init(DMA1_Channel3, &DMA_InitStructure);  // init the DMA
        // start DMA
         do {
            if (pixel > 0X10000) {         // this is a giant m_pFont !
                dma_count = 0Xffff;
                pixel = pixel - 0Xffff;
            } else {
                dma_count = pixel;
                pixel = 0;
            }
            DMA_SetCurrDataCounter(DMA1_Channel3, dma_count);
            SPI_I2S_DMACmd(SPI1, SPI_I2S_DMAReq_Tx,ENABLE);
            DMA_Cmd(DMA1_Channel3, ENABLE);
            while(DMA_GetCurrDataCounter(DMA1_Channel3) != 0);     // wait for end of transfer
            DMA_Cmd(DMA1_Channel3, DISABLE);
        }while(pixel > 0);
        break;

        case (2):
        DMA_Init(DMA1_Channel5, &DMA_InitStructure);  // init the DMA
        // start DMA
         do {
            if (pixel > 0X10000) {         // this is a giant m_pFont !
                dma_count = 0Xffff;
                pixel = pixel - 0Xffff;
            } else {
                dma_count = pixel;
                pixel = 0;
            }
            DMA_SetCurrDataCounter(DMA1_Channel5, dma_count);
            SPI_I2S_DMACmd(SPI2, SPI_I2S_DMAReq_Tx,ENABLE);
            DMA_Cmd(DMA1_Channel5, ENABLE);
            while(DMA_GetCurrDataCounter(DMA1_Channel5) != 0);     // wait for end of transfer
            DMA_Cmd(DMA1_Channel5, DISABLE);
        }while(pixel > 0);
        break;

        case (3):
        DMA_Init(DMA2_Channel2, &DMA_InitStructure);  // init the DMA
        // start DMA
         do {
            if (pixel > 0X10000) {         // this is a giant m_pFont !
                dma_count = 0Xffff;
                pixel = pixel - 0Xffff;
            } else {
                dma_count = pixel;
                pixel = 0;
            }
            DMA_SetCurrDataCounter(DMA2_Channel2, dma_count);
            SPI_I2S_DMACmd(SPI3, SPI_I2S_DMAReq_Tx,ENABLE);
            DMA_Cmd(DMA2_Channel2, ENABLE);
            while(DMA_GetCurrDataCounter(DMA2_Channel2) != 0);     // wait for end of transfer
            DMA_Cmd(DMA2_Channel2, DISABLE);
        }while(pixel > 0);
        break;

        }
        spi_bsy();
        free ((uint16_t *) buffer);
        spi_16(0);
    }

    else{
        #endif

        character = &m_pFont[(((uint32_t)c -32u) * offset) + 4u]; // start of char bitmap
        w = character[0];                          // width of actual char
        for (j = 0; j < vert; j++)
        {  //  vertical line
            for (i = 0; i < hor; i++)
            {   //  horizontal line
                z =  character[bpl * i + ((j & 0xF8) >> 3) + 1];
                b = 1u << (j & 0x07);

                uint16_t pixel = __builtin_bswap16((( z & b ) == 0x00) ? m_backgroundColour : m_fontColour);
                writeData((uint8_t *)&pixel, 2);
            }
        }

    #ifdef use_ram
    }
    #endif
//    setScreenLocation(0, 0, m_width,  m_height);
    if ((w + 2u) < hor)
    {                   // x offset to next char
        char_x += w + 2u;
    }
    else
    {
        char_x += hor;
    }
}

/**\brief   Converts independent red/green/blue values to a single colour value.
 *
 * \param   red     - red value
 * \param   green   - green value
 * \param   blue    - blue value
 *
 * \return  565 compatible value
 */
uint16_t CILI9340::colour565(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((red & 0xF8) << 8) | ((green & 0xFC) << 3) | (blue >> 3);
}

/**\brief   Sets the screen rotation.
 *
 * \param   rotation    - rotation value (0 - 4)
 *
 * \return  None
 */
void CILI9340::setRotation(uint8_t rotation)
{
    uint8_t _dta = BIT_MADCTL_BGR;

    switch (rotation % 4)// can't be higher than 3
    {
        case 0:
            _dta |= BIT_MADCTL_MX;
          m_width  = TFT_WIDTH;
          m_height = TFT_HEIGHT;
            break;

        case 1:
            _dta |= BIT_MADCTL_MV;
          m_width  = TFT_HEIGHT;
          m_height = TFT_WIDTH;
        break;

        case 2:
            _dta |= BIT_MADCTL_MY;
          m_width  = TFT_WIDTH;
          m_height = TFT_HEIGHT;
        break;

        case 3:
            _dta |= BIT_MADCTL_MV | BIT_MADCTL_MY | BIT_MADCTL_MX;
          m_width  = TFT_WIDTH;
          m_height = TFT_HEIGHT;
        break;

        default:
            // default case
            break;
    }

    writeRegister(_CMD_MADCTL, &_dta, sizeof(_dta));
}

/**\brief   Colour palette inversion.
 *
 * \param   invert  - true to invert image colours
 *
 * \return  None
 */
void CILI9340::invertDisplay(bool invert)
{
    writeRegister((invert) ? _CMD_INVON : _CMD_INVOFF);
}

extern "C" void CILI9340_init(CILI9340 * p) { p->init(); }
extern "C" void CILI9340_drawPixel(CILI9340 * p, int16_t x, int16_t y, uint16_t colour) { p->drawPixel(x, y, colour); }
