/*
	Generate sin wave.

	Microcontroller: ATmega32
	Clock: 8 MHz
	External hardware: RC filter on PB3
	Compiler: AVR GCC

	http://aquaticus.info/pwm-sine-wave

	$Revision: 128 $
*/

#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <math.h>
#include <stdio.h>

/// Number of probes for one period of sine wave
#define SAMPLE_RES 252
#define PRESCALAR 1

/* InitSinTable() used to initiate the table */
uint8_t  wave[SAMPLE_RES];

/// Current wave sample number
static uint8_t sample = 0;

float sineWaveSample(int sampleNumber, int sampleFreq) {
    return sin(sampleNumber / (sampleFreq / (M_PI * 2)));
}

/**
	Generate sin table in range 0-359 deg.

	In fact only values 0-89 could be computed, but to make things
	simpler entire range is calculated.
*/
void InitSinTable()
{
	//sin period is 2*PI
	// const float step = (2*M_PI)/(float)SAMPLE_RES;
    float zero = 128.0;

	float s;

    uint16_t sampleRate = F_CPU/PRESCALAR;
    int sampleFreq = sampleRate/440;

	//in radians
	for(int sampleNumber = 0; sampleNumber < SAMPLE_RES; sampleNumber++)
	{
		// s = sin( sampleNumber * step );
        //calculate OCR value (in range 0-255, timer0 is 8 bit)
        // wave[sampleNumber] = (uint8_t) round(zero + (s*127.0));
		s = sineWaveSample(sampleNumber, sampleFreq);
        wave[sampleNumber] = (uint8_t) round(zero + (s*127.0));
	}
}

/**
 Initializes timer0 for PWM generation
*/
void InitPWM()
{
	DDRB |= _BV(PB3); //OC0 pin as output

	TCCR0 |= _BV(WGM01) | _BV(WGM00); //mode 1, Fast PWM

	TCCR0 |= _BV(COM01); //Clear OC0 on compare match, set OC0 at BOTTOM

	TCCR0 |= _BV(CS00); //prescaler divider 1

	TIMSK |= _BV(TOIE0); //Timer/Counter0 Overflow Interrupt Enable
}

int main()
{
	InitPWM();

	InitSinTable();


	sei(); //enable global interruprts

	//go to sleep mode
	while(1)
	{
		sleep_mode();
	}
}

/**
	Interrupt routine. Needed to synchronize change of OCR0 with the end of period.
*/

ISR(TIMER0_OVF_vect)
{
	OCR0 = wave[sample];

	sample++;

	if( sample >= SAMPLE_RES-1 )
		sample = 0;
}

