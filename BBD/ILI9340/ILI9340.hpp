/*******************************************************************************
* File          : ILI9340.hpp
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
#ifndef ILI9340_HPP
#define ILI9340_HPP

/*******************************************************************************
INCLUDES
*******************************************************************************/

#include "stdint.h"
#include "stm32f7xx_hal.h"

/*******************************************************************************
DEFINITIONS
*******************************************************************************/

#define TFT_WIDTH               (240)
#define TFT_HEIGHT              (320)
#define TFT_MW                  (TFT_WIDTH - 1)
#define TFT_MH                  (TFT_HEIGHT - 1)

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

#define _CMD_NOP                0x00//No Operation
#define _CMD_SWRESET            0x01//Software Reset
#define _CMD_SLPIN              0x10//Enter Sleep Mode
#define _CMD_SLPOUT             0x11//*Sleep OUT
#define _CMD_PTLON              0x12//Partial Mode ON
#define _CMD_NORON              0x13//Normal Display Mode ON
#define _CMD_INVOFF             0x20//Display Inversion OFF
#define _CMD_INVON              0x21//Display Inversion ON
#define _CMD_GAMMASET           0x26//*Gamma Set
#define _CMD_DISPOFF            0x28//Display OFF
#define _CMD_DISPON             0x29//*Display ON
#define _CMD_CASET              0x2A//*Column Address Set
#define _CMD_PASET              0x2B//*Page Address Set
#define _CMD_RAMWR              0x2C//*Memory Write
#define _CMD_PTLAR              0x30//Partial Area
#define _CMD_VSCRLLD            0x33//Vertical Scrolling Definition
#define _CMD_TEFXOFF            0x34//Tearing Effect Line OFF
#define _CMD_TEFXON             0x35//Tearing Effect Line ON
#define _CMD_MADCTL             0x36//*Memory Access Control
#define _CMD_VSCLLSA            0x37//Vertical Scrolling Start Address
#define _CMD_IDLEOFF            0x38//Idle Mode OFF
#define _CMD_IDLEON             0x39//Idle Mode ON
#define _CMD_PIXFMT             0x3A//*Pixel Format Set
#define _CMD_WRMEMCON           0x3C//Write Memory Continue
#define _CMD_TEARSCN            0x44//Set Tear Scanline
#define _CMD_WDBRIGHT           0x51//Write Display Brightness
#define _CMD_WCTRLDIS           0x53//Write CTRL Display
#define _CMD_WCABRGCTRL         0x55//Write Content Adaptive Brightness Control
#define _CMD_WCABCMBRG          0x5E//Write CABC Minimum Brightness
#define _CMD_RGBINTSC           0xB0//RGB Interface Signal Control
#define _CMD_FRMCTR1            0xB1//*Frame Control (In Normal Mode)
#define _CMD_FRMCTR2            0xB2//Frame Control (In Idle Mode)
#define _CMD_FRMCTR3            0xB3//Frame Control (In Partial Mode)
#define _CMD_INVCTR             0xB4//Display Inversion Control
#define _CMD_BLKPC              0xB5//Blanking Porch Control
#define _CMD_DFUNCTR            0xB6//*Display Function Control
#define _CMD_ENTMSET            0xB7//Entry Mode Set
#define _CMD_BKLGCTRL1          0xB8//Backlight Control 1
#define _CMD_BKLGCTRL2          0xB9//Backlight Control 2
#define _CMD_BKLGCTRL3          0xBA//Backlight Control 3
#define _CMD_BKLGCTRL4          0xBB//Backlight Control 4
#define _CMD_BKLGCTRL5          0xBC//Backlight Control 5
#define _CMD_BKLGCTRL6          0xBD//Backlight Control 6
#define _CMD_BKLGCTRL7          0xBE//Backlight Control 7
#define _CMD_BKLGCTRL8          0xBF//Backlight Control 8
#define _CMD_PWCTR1             0xC0//*Power Control 1
#define _CMD_PWCTR2             0xC1//*Power Control 2
#define _CMD_PWCTR3             0xC2//Power Control 3 (normal)
#define _CMD_PWCTR4             0xC3//Power Control 4 (idle)
#define _CMD_PWCTR5             0xC4//Power Control 5 (partial)
#define _CMD_VMCTR1             0xC5//VCOM Control 1
#define _CMD_VMCTR2             0xC7//VCOM Control 2
#define _CMD_MVMEMWR            0xD0//NV Memory Write
#define _CMD_MVMEMPK            0xD0//NV Memory Protection Key
#define _CMD_POSGAMUT           0xE0//Positive Gamma Correction
#define _CMD_NEGGAMUT           0xE1//Negative Gamma Correction
#define _CMD_DGAMMCTRL1         0xE2//Digital Gamma Control 1
#define _CMD_DGAMMCTRL2         0xE3//Digital Gamma Control 2
#define _CMD_G3CTRL             0xF2//3 gamma control enable
#define _CMD_INTFCTRL           0xF6//Interface Control


#define BIT_MADCTL_MY           0x80//*
#define BIT_MADCTL_MX           0x40//*
#define BIT_MADCTL_MV           0x20//*
#define BIT_MADCTL_ML           0x10
#define BIT_MADCTL_RGB          0x00
#define BIT_MADCTL_BGR          0x08//*
#define BIT_MADCTL_MH           0x04


#define _CMD_RDID1              0xDA
#define _CMD_RDID2              0xDB
#define _CMD_RDID3              0xDC
#define _CMD_RDID4              0xDD

#define _CMD_GMCTRP1            0xE0
#define _CMD_GMCTRN1            0xE1

/*******************************************************************************
TYPES
*******************************************************************************/

struct charStruct_t
{
    uint32_t byteCount;
    uint32_t horizontal;
    uint32_t vertical;
    uint8_t const * pCharTable;
};

/*******************************************************************************
GLOBAL VARIABLES
*******************************************************************************/

/*******************************************************************************
NAMESPACE
*******************************************************************************/

class CILI9340
{

 public:
    CILI9340(SPI_HandleTypeDef * pSPI
              , GPIO_TypeDef * pCS_Port
              , uint16_t CS_Pin
              , GPIO_TypeDef * pDC_Port
              , uint16_t DC_Pin
              , GPIO_TypeDef * pReset_Port
              , uint16_t Reset_Pin);
    ~CILI9340() = default;

  void init(void);
  void setScreenLocation(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
  void fillScreen(uint16_t colour);
  void drawPixel(int16_t x, int16_t y, uint16_t colour);
  void drawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t colour);
  void drawFastHLine(int16_t x, int16_t y, int16_t w, uint16_t colour);
  void fillRect(int16_t x, int16_t y, int16_t w, int16_t h,uint16_t colour);
  void drawImage(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t * pColour, size_t length);
  int putc(char value);
  int puts(char const * const pString);
  int putsN(uint8_t const * const pString, int length);
  void setTextLocation(uint32_t x, uint32_t y);
  void setFont(unsigned char const * font);
  void setTextColour(uint32_t colour);
  void drawCharacter(uint32_t x, uint32_t y, int c);
  void setRotation(uint8_t rotation);
  void invertDisplay(bool invert);
  void clearScreen(int16_t colour = 0x0000);
  uint16_t colour565(uint8_t red, uint8_t green, uint8_t blue);
//void          setBrightness(uint8_t val);

 private:
    void HWReset(void);
    void chipInit(void);
    void writeRegister(uint8_t regAddr, uint8_t * pData = nullptr, size_t length = 0);
    void writeData(uint8_t * pData, size_t length);
//    void writeCommand(uint8_t c);
//    void writeCommands(uint8_t *cmd, uint8_t length);
    bool boundaryCheck(int16_t x,int16_t y);


private:
    SPI_HandleTypeDef * m_pSPI;
    GPIO_TypeDef * m_pCS_Port;
    uint16_t m_CS_Pin;
    GPIO_TypeDef * m_pDC_Port;
    uint16_t m_DC_Pin;
    GPIO_TypeDef * m_pReset_Port;
    uint16_t m_Reset_Pin;
    uint32_t m_height;
    uint32_t m_width;
    unsigned int char_xStart;
    unsigned int char_yStart;
    unsigned int char_x;
    unsigned int char_y;
    unsigned char const * m_pFont;
    uint32_t m_fontColour;
    charStruct_t m_fontData;
};

/*******************************************************************************
INLINE FUNCTION DEFINITIONS
*******************************************************************************/

extern "C" void CILI9340_init(CILI9340 * p);
extern "C" void CILI9340_drawPixel(CILI9340 * p, int16_t x, int16_t y, uint16_t colour);

#endif /* ILI9340_HPP */
