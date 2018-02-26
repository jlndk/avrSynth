#include <avr/io.h>
#include <avr/delay.h>
#include <avr/pgmspace.h>
#include <math.h>
#include "midi.h"

// Interrupt function
// Adds input to buffer
ISR(USART_RXC_vect)
{
	uint8_t input = UDR0;		// Where input is taken from
	midi_input[MIDI_INPUT_BUFFER] = input & MIDI_INPUT_BUFFER + 1;
}

// Init settings
void portInit()
{
	DDRA = 0xFF; // All GPIO on port D set to output
	DDRC = 0xFF;
	PORTA = 0xFF;
	DDRD = 0x00;
}

void midiInit()
{
	UBRRH = 00;
	UBRRL = 31;
	UCSRB = (1 << RXCIE) | (1 << RXEN);
	UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0); //8 bit, 1 stop, no parity
}

// Clock Cycles before turning off/on = Delay / Clock * Prescaler

/**
 * Function To Initialize TIMER0 In Fast
 * PWWM Mode.
 */
void initPWM()
{
	/*
	TCCR0 - Timer Counter Control Register (TIMER0)
	-----------------------------------------------

	BITS DESCRIPTION

	NO:   NAME   DESCRIPTION
	--------------------------
	BIT 7 : FOC0   Force Output Compare [Not used in this example]
	BIT 6 : WGM00  Wave form generation mode [SET to 1]

	BIT 5 : COM01  Compare Output Mode        [SET to 1]
	BIT 4 : COM00  Compare Output Mode        [SET to 0]
	BIT 3 : WGM01  Wave form generartion mode [SET to 1]
	BIT 2 : CS02   Clock Select               [SET to 0]
	BIT 1 : CS01   Clock Select               [SET to 0]
	BIT 0 : CS00   Clock Select               [SET to 1]

	The above settings are for
	--------------------------
	Timer Clock = CPU Clock (No Prescalling)
	Mode        = Fast PWM
	PWM Output  = Non Inverted

	*/

	TIMSK = (1 << TOIE0);	// Timer Interrupt Mask Register
	TCNT0 = 254;			// Prescaler
	TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00)|(1<<CS01);

	//Set OC0 PIN as output. It is PB3 on ATmega16
	DDRB|=(1<<PB3);
}

void main()
{
	portInit();
	midiInit();
	initPWM();

	while(1)
	{
		midi_update();
		play();
	}
}
