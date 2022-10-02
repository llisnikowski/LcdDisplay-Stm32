/*
 * lcdDisplay.cpp
 *
 *  Created on: Sep 30, 2022
 *      Author: Łukasz
 */

#include "lcdDisplay.hpp"
#include "gpio.h"
#include "delay/delay.hpp"

LcdDisplay::LcdDisplay(PortAndPin rs, PortAndPin e, PortAndPin dataFirstPin)
	:rs_(rs), e_(e), dataFirstPin_(dataFirstPin)
{
}

LcdDisplay::~LcdDisplay()
{
}

void LcdDisplay::init()
{
	rs_->BRR = rs_.getPinMask();
	resetE();

	HAL_Delay(15);

	setHalfByte(0x03);
	delay_us(4100);
	setHalfByte(0x03);
	delay_us(100);

	setHalfByte(0x03);
	delay_us(100);
	sendCmd(LCD_FUNCTIONSET|LCD_4BITMODE|LCD_2LINE|LCD_5x8DOTS); // 4-bit, 2 lanes, 5x7 chars


	sendCmd(LCD_DISPLAYCONTROL | LCD_CURSOROFF); // Cursor off
	sendCmd(LCD_DISPLAYCONTROL | LCD_DISPLAYON); // LCD on
	sendCmd(LCD_ENTRYMODESET | LCD_ENTRYLEFT); // Data entry right

	//LCD_Cls(); // Clear display

}

void LcdDisplay::sendByte(uint8_t byte)
{
	setE();
	setHalfByte(byte >> 4);
	resetE();

	setE();
	setHalfByte(byte);
	resetE();

	delay_us(120);
}


void LcdDisplay::setHalfByte(uint8_t byte)
{
	uint16_t portData = (byte & 0x0f) << dataFirstPin_.getPin();
	uint32_t bsrr = portData | (~portData << 16);
	dataFirstPin_->BSRR = bsrr;
}

void LcdDisplay::sendCmd(uint8_t cmd)
{
	rs_->BRR = rs_.getPinMask();
	sendByte(cmd);
	delay_us(2000);
}

void LcdDisplay::sendData(uint8_t data)
{
	rs_->BSRR = rs_.getPinMask();
	sendByte(data);
	delay_us(1000);
}


void LcdDisplay::clear()
{
	sendCmd(LCD_CLEARDISPLAY);
}

void LcdDisplay::setCursor(uint8_t x, uint8_t y)
{
	if(!(y & 0x01)){
		y = LCD_LINE1;
	}
	else{
		y = LCD_LINE2;
	}
	x = x & 0x0f;

	sendCmd(LCD_SETDDRAMADDR | y | x);
}


void LcdDisplay::print(const char c)
{
	sendData(c);
}

void LcdDisplay::print(const char* str)
{
	char c;
	while((c = *(str++)))
		print(c);
}

void LcdDisplay::printInt(const int value)
{
	if(value>10) printInt(value/10);
	print(value % 10 + '0');
}

