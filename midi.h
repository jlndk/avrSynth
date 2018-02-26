#include "declarations.h"

// Presets for MIDI
// Don't change unless you know what you're doing
#define MIDI_NOTE_OFFSET	36		// semitones
#define MIDI_CMD_BUFFER		8		// cmds
#define MIDI_INPUT_BUFFER	256		// bytes

// Binary status codes
// Written in HEX for legibility
#define MIDI_NOTE_OFF		8
#define MIDI_NOTE_ON		9
#define MIDI_PRESSURE		0xA
#define MIDI_CONTROL		0xB
#define MIDI_PATCH			0xC
#define MIDI_C_PRESSURE		0xD
#define MIDI_PITCH_BEND		0xE
#define MIDI_STATUS			0xF


// Struct for MIDI cmds
// Used in cmd buffer
typedef struct
{
	uint8_t status;
	uint8_t byte1;
	uint8_t byte2;
} midi_cmd;

midi_cmd cmds[MIDI_CMD_BUFFER];			// MIDI cmd buffer

uint8_t wr_cmd = 0;						// Index # of cmd write
uint8_t rd_cmd = 0;						// Index # of cmd read
uint8_t midi_input[MIDI_INPUT_BUFFER];	// MIDI input buffer