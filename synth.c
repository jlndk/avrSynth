#include <avr/pgmspace.h>

#include "synth.h"
#include "sin.h"

rd_idx = 0;

float computeCycles(uint8_t note)
{
	return notelib[note] / ((1 / SAMPLE_RATE) * TCCR0);
}

float sineWaveSample(int sampleNumber, int sampleFreq) {
    return sin(sampleNumber / (sampleFreq / (M_PI * 2)));
}

void playSineWave(int frequency, int duration, float volume) {
    //Find the number of samples required
    int sampleCount = SAMPLE_RATE * duration;

    //Create an array with that length
    float buffer[sampleCount];

    //Find the duration of a single wave
    int sampleFreq = sampleRate / frequency;

    //Generate all samples
    for (int i = 0; i < sampleCount; i++) {
        buffer[i] = sineWaveSample(i, sampleFreq) * volume;
    }
}

void play()
{
	if (TCNT0 <= computeCycles && PLAYING = 1)
	{
		PORTC = 0xFF;
		break;
	}
	TCNT0 = 0;
	PORTC = 0x00;
}
