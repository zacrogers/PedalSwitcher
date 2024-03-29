/*
 * gpio.h
 *
 * Created: 15-Jan-20 3:39:04 PM
 *  Author: Zac
 */ 
#pragma once

#include <avr/io.h>
#include <stdint.h>

/* Macros to get data direction, and input register from port definition */
#define DDR(x)  (*(&x - 1))
#define PIN(x)  (*(&x - 2))
#define PORT(x) (x)

namespace z_lib
{	
	class Gpio
	{
		public:
			enum class Mode
			{
				IN = 0,
				OUT,
				PULLUP,
				ANALOG	
			};

			Gpio(volatile uint8_t *port, uint8_t pin, Mode mode);
			
			void    set         (void);
			void    clear       (void);
			void    toggle      (void);
			uint8_t read        (void);
			uint8_t analog_read (void);
			void    set_pullup  (void);
		
		private:
			volatile uint8_t *port;
			uint8_t pin;
			Mode mode;
	};
}

