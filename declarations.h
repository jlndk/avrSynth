#include <stdint.h>

// Synth
#define	WAVET_SIZE			64		// byte
#define SAMPLE_RATE			44100	// Hz
#define	CONTROL_RATE		100		// Hz
#define MIDI_HIGHEST_NOTE	105

// Note Values
#define C2		1000/65.41
#define Cs2		1000/69.30
#define D2		1000/73.41
#define Ds2		1000/77.78
#define E2		1000/82.41
#define F2		1000/87.31
#define Fs2		1000/92.50
#define G2		1000/98.00
#define Gs2		1000/103.83
#define A2		1000/110.00
#define As2		1000/116.54
#define B2		1000/123.47

#define C3		1000/130.81
#define Cs3		1000/138.59
#define D3		1000/146.83
#define Ds3		1000/155.56
#define E3		1000/164.81
#define F3		1000/174.61
#define Fs3		1000/185.00
#define G3		1000/196.00
#define Gs3		1000/207.65
#define A3		1000/220.00
#define As3		1000/233.08
#define B3		1000/246.94

#define C4		1000/261.63
#define Cs4		1000/277.18
#define D4		1000/293.67
#define Ds4		1000/311.13
#define E4		1000/329.63
#define F4		1000/349.23
#define Fs4		1000/369.99
#define G4		1000/392.00
#define Gs4		1000/415.30
#define A4		1000/440.00
#define As4		1000/466.16
#define B4		1000/493.88

#define C5		1000/523.25
#define Cs5		1000/554.37
#define D5		1000/587.33
#define Ds5		1000/622.25
#define E5		1000/659.26
#define F5		1000/698.46
#define Fs5		1000/739.99
#define G5		1000/783.99
#define Gs5		1000/830.61
#define A5		1000/880.00
#define As5		1000/932.33
#define B5		1000/987.77

// Notes 36 - 83 (from C0)

const float notelib[48] =
{
	C2, Cs2, D2, Ds2, E2, F2, Fs2, G2, Gs2, A2, As2, B2,
	C3, Cs3, D3, Ds3, E3, F3, Fs3, G3, Gs3, A3, As3, B3,
	C4, Cs4, D4, Ds4, E4, F4, Fs4, G4, Gs4, A4, As4, B4,
	C5, Cs5, D5, Ds5, E5, F5, Fs5, G5, Gs5, A5, As5, B5
};