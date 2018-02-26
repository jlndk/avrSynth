// Aske Emil Ofir and Jonas Lindenskov Nielsen 2018
// See midi.h for information regarding MIDI words
#include "synth.h"

// Writes input buffer to cmd buffer
void midi_write() 
{
	// Fetch first element from input buffer
	uint8_t cur_byte = midi_input[MIDI_INPUT_BUFFER] & MIDI_INPUT_BUFFER - 1;

	// MSB = 1 meaning a status byte
	if (cur_byte >> 7) 
	{
		// Cycle to next element to avoid overwriting
		if (cmds[wr_cmd].status != 0)
		{
			wr_cmd = wr_cmd + 1;
		}
		cmds[wr_cmd].status = cur_byte;
		return;
	}

	// Assume data byte if not status byte
	if (cmds[wr_cmd].byte1 = 0)
	{
		cmds[wr_cmd].byte1 = cur_byte;
		return;
	}

	// Since data bytes never appear more than 2 in a row, we can always assume that byte 2 is last
	cmds[wr_cmd].byte2 = cur_byte;
	return;
}

// Reads commands from buffer
void midi_read() 
{
	// Easy syntax
	uint8_t status		= cmds[rd_cmd].status;
	uint8_t byte1		= cmds[rd_cmd].byte1;
	uint8_t byte2		= cmds[rd_cmd].byte2;

	// Take first command from buffer to read
	rd_cmd				= rd_cmd + 1 & MIDI_CMD_BUFFER - 1;

	switch (status >> 4)
	{
		case MIDI_NOTE_OFF:
		{
			PLAYING = 0;
			break;
		}

		case MIDI_NOTE_ON:
		{
			// NOTE_ON command with velocity 0 will be interpreted as NOTE_OFF
			if (byte2 == 0)
			{
				PLAYING = 0;
				break;
			}

			uint8_t note = byte1 - MIDI_NOTE_OFFSET;
			computeCycles(note);
			PLAYING = 1;
			break;
		}

		default:
		{
			break;
		}
	}
}

// Calls read/write commands
void midi_update()
{
	// Only read if processed input is available
	if (wr_cmd >= rd_cmd)
	{
		midi_read();
	}

	// Write as long as there is input to process
	midi_write();
}