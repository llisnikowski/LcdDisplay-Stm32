/*
 * lcdDisplay.hpp
 *
 *  Created on: Sep 30, 2022
 *      Author: Łukasz
 */

#ifndef LCDDISPLAY_LCDDISPLAY_HPP_
#define LCDDISPLAY_LCDDISPLAY_HPP_

#include "periphery/portAndPin.hpp"


// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02

#define LCD_ENTRYMODESET 0x04
	// flags for display entry mode
	#define LCD_ENTRYRIGHT 0x00
	#define LCD_ENTRYLEFT 0x02
	#define LCD_ENTRYSHIFTINCREMENT 0x01
	#define LCD_ENTRYSHIFTDECREMENT 0x00

#define LCD_DISPLAYCONTROL 0x08
	// flags for display on/off control
	#define LCD_DISPLAYON 0x04
	#define LCD_DISPLAYOFF 0x00
	#define LCD_CURSORON 0x02
	#define LCD_CURSOROFF 0x00
	#define LCD_BLINKON 0x01
	#define LCD_BLINKOFF 0x00

#define LCD_CURSORSHIFT 0x10
	// flags for display/cursor shift
	#define LCD_DISPLAYMOVE 0x08
	#define LCD_CURSORMOVE 0x00
	#define LCD_MOVERIGHT 0x04
	#define LCD_MOVELEFT 0x00

#define LCD_FUNCTIONSET 0x20
	// flags for function set
	#define LCD_8BITMODE 0x10
	#define LCD_4BITMODE 0x00
	#define LCD_2LINE 0x08
	#define LCD_1LINE 0x00
	#define LCD_5x10DOTS 0x04
	#define LCD_5x8DOTS 0x00

#define LCD_SETCGRAMADDR 0x40	//own character
#define LCD_SETDDRAMADDR 0x80	//cursor


#define LCD_LINE1 0x00
#define LCD_LINE2 0x40


/*
 * \brief The LcdDisplay class provides support for Lcd Display with HF44780 driver
 */
class LcdDisplay
{
public:
	LcdDisplay(PortAndPin rs, PortAndPin e, PortAndPin dataFirstPin);
	~LcdDisplay();
	void init();

	void clear();
	void setCursor(uint8_t x, uint8_t y);

	void print(const char c);
	void print(const char* str);
	void printInt(const int value);

private:
	void sendCmd(uint8_t cmd);
	void sendData(uint8_t data);
	void sendByte(uint8_t byte);
	void setHalfByte(uint8_t byte);
	void setE(){e_->BSRR = e_.getPinMask();}
	void resetE(){e_->BRR = e_.getPinMask();}

	PortAndPin rs_;
	PortAndPin e_;
	PortAndPin dataFirstPin_;
};

#endif /* LCDDISPLAY_LCDDISPLAY_HPP_ */
