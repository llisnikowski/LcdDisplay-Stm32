/*
 * pin.hpp
 *
 *  Created on: Sep 30, 2022
 *      Author: Łukasz
 */

#ifndef PERIPHERY_PORTANDPIN_HPP_
#define PERIPHERY_PORTANDPIN_HPP_

#include <stdint.h>
#include "gpio.h"
#include "port.hpp"

/*!
 * \brief The PortAndPin class store a port and pin for a given gpio.
 */
class PortAndPin
{
public:
	constexpr PortAndPin(Port port, uint8_t pin);

	constexpr uint8_t getPin() const;
	constexpr uint16_t getPinMask() const;
	constexpr Port getPort() const;
	constexpr GPIO_TypeDef * getGPIO() const;
	constexpr GPIO_TypeDef * operator->() const;

private:
	/*!
	 * \brief Stored port.
	 * \see Port
	 */
	Port port_;
	/*!
	 * \brief Stored pin.
	 */
	uint8_t pin_;
};


/*!
 * \brief Constructor for pair a port and a pin.
 * \param port - Stored port.
 * \param pin - Stored pin. Pin must be less than 16.
 * \see Port
 */
constexpr PortAndPin::PortAndPin(Port port, uint8_t pin)
	:port_(port), pin_(pin & 0x0f)
{
}

/*!
 * \brief Return pin.
 * \return Stored pin.
 */
constexpr uint8_t PortAndPin::getPin() const
{
	return pin_;
}

/*!
 * \brief Return pin mask.
 * \return The mask to stored pin, e.g. for 5: 0x4 (0b0010'0000 or otherwise (1 << 5)).
 */
constexpr uint16_t PortAndPin::getPinMask() const
{
	return 1 << pin_;
}

/*!
 * \brief Return port.
 * \return Stored port.
 * \see Port
 */
constexpr Port PortAndPin::getPort() const
{
	return port_;
}

/*!
 * \brief Return GPIO_TypeDef * for stored port.
 * \return GPIO_TypeDef * for stored port.
 */
constexpr GPIO_TypeDef * PortAndPin::getGPIO() const
{
	return &port_;
}

/*!
 * \brief The equivalent to getGPIO()
 * \return GPIO_TypeDef * for stored port.
 * \see getGPIO()
 */
constexpr GPIO_TypeDef * PortAndPin::operator->() const
{
	return &port_;
}

#endif /* PERIPHERY_PORTANDPIN_HPP_ */
