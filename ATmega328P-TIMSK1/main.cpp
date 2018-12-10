/*
 * ATmega328P test projects
 * 
 * Copyright (c) 2018 Alexander Fust
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * This program is free software: you can redistribute it and/or modify
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */
#include <avr/io.h>
#include <avr/interrupt.h>

// Oscillator frequency of micro controller
// run on Arduino board is 16 MHz
#define F_CPU  16000000UL
#include <util/delay.h>

#define TCNT1_START 31250

ISR(TIMER1_OVF_vect)
{
	TCNT1 = TCNT1_START;
	PORTB ^= (1 << PORTB5);
}

int main(void)
{
	DDRB |= (1 << DDB5);
	
	TCCR1A = 0;
	TCCR1B = 0;

	TCNT1 = TCNT1_START;	
	TCCR1B |= (1 << CS12);
	TIMSK1 |= (1 << TOIE1);
	
	sei();
	
    while (1) 
    {
    }
}

