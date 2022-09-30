/*
 * pin.hpp
 *
 *  Created on: Sep 30, 2022
 *      Author: Łukasz
 */

#ifndef PERIPHERY_PORTANDPIN_HPP_
#define PERIPHERY_PORTANDPIN_HPP_

#include "gpio.h"
#include "port.hpp"

/*!
 * \brief The PortAndPin class store a port and pin for a given gpio.
 */
class PortAndPin
{
public:
	constexpr PortAndPin(Port port, uint8_t pin);

	constexpr Port getPort() const;
	constexpr Port getPin() const;
	constexpr GPIO_TypeDef * getGPIO() const;

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
	:port(port), pin(pin)
{
	static_assert(pin < 16, "Pin must be less than 16.");
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
 * \brief Return pin.
 * \return Stored pin.
 */
constexpr Port getPin() const
{
	return pin_;
}

/*!
 * \brief Return GPIO_TypeDef * for stored port.
 * \return GPIO_TypeDef * for stored port.
 */
constexpr GPIO_TypeDef * getGPIO() const
{
	return &port_;
}

#endif /* PERIPHERY_PORTANDPIN_HPP_ */
