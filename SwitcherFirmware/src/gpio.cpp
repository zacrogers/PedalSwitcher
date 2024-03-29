/*
 * gpio.cpp
 *
 * Created: 15-Jan-20 4:07:46 PM
 *  Author: Zac
 */ 

#include "gpio.hh"
namespace z_lib
{	
	Gpio::Gpio(volatile uint8_t *port, uint8_t pin, Mode mode)
	{
		this->port = port;
		this->pin  = pin;
		this->mode = mode;
		
		switch(mode)
		{
			case Mode::IN:
				DDR(*port) &= ~(1 << this->pin);
				break;
				
			case Mode::OUT:
				DDR(*port) |= (1 << this->pin);
				break;
				
			case Mode::PULLUP:
				DDR(*port) &= ~(1 << this->pin);
				*port |= (1 << this->pin);
				break;
		}
	}
	
	void Gpio::set(void)
	{
		*this->port |= (1 << this->pin);
	}
	
	void Gpio::clear(void)
	{
		*this->port &= ~(1 << this->pin);		
	}
	
	void Gpio::toggle(void)
	{
		*this->port ^= (1 << this->pin);		
	}
	
	uint8_t Gpio::read(void)
	{
		return (PIN(*this->port) & (1U << this->pin));
	}

	void Gpio::set_pullup(void)
	{
		if(Mode::IN == this->mode)
		{
			this->set();
		}
	}
}