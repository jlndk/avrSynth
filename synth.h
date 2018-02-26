#include "midi.h"

typedef enum {
	SQUARE,
	SAWTOOTH,
	SINE,
	NOISE
} osc_type;

typedef enum {
	PLAYING,
	DECAYING,
	OFF
} note_state;

// Flag for output to stop/start playing
uint8_t PLAYING = 0;