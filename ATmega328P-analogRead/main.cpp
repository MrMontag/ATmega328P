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
#include <stdio.h>
#include <avr/io.h>

// Oscillator frequency of micro controller
// run on Arduino board is 16 MHz
#define F_CPU   16000000UL
#include <util/delay.h>

#define BAUD    250000
// USART Baud Rate Register
#define MYUBRR  F_CPU/16/BAUD-1

void USART_init(unsigned int ubrr)
{
	/*Set baud rate */
	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;
	/* Enable receiver and transmitter */
	UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	/* Set frame format: 8data, 2stop bit */
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);
}

void USART_transmit(unsigned char data)
{
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

int main(void)
{
	USART_init(MYUBRR);
    ADMUX |= (1 << REFS0) | MUX0;
	ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS2) | (1 << ADPS0);
	
	int value;
	uint8_t low, high;
	
    while (1) 
    {
		low = ADCL;
		high = ADCH;
		value = (high << 8) | low;
		char buffer[5];
		sprintf(buffer, "%d", value);
		for (int i=0; i<5; ++i)
		{
			if (!buffer[i]) break;
			USART_transmit(buffer[i]);
		}
		USART_transmit('\n');
		_delay_ms(1);
    }
}

