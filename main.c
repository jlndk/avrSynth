#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "sin.h"

int sampleRate;

/**
 * Function To Initialize TIMER0 In Fast
 * PWWM Mode.
 */
void InitPWM()
{
   /*
   TCCR0 - Timer Counter Control Register (TIMER0)
   -----------------------------------------------

   BITS DESCRIPTION

   NO:   NAME   DESCRIPTION
   --------------------------
   BIT 7 : FOC0   Force Output Compare [Not used in this example]
   BIT 6 : WGM00  Wave form generartion mode [SET to 1]

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


   TCCR0|=(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<CS00);

   //Set OC0 PIN as output. It is  PB3 on ATmega16 ATmega32
   DDRB|=(1<<PB3);
}

float sineWaveSample(int sampleNumber, int sampleFreq) {
    return sin(sampleNumber / (sampleFreq / (M_PI * 2)));
}

void playSineWave(int frequency, int duration, float volume) {
    //Find the number of samples required
    int sampleCount = sampleRate * duration;

    //Create an array with that length
    float buffer[sampleCount];

    //Find the duration of a single wave
    int sampleFreq = sampleRate / frequency;

    //Generate all samples
    for (int i = 0; i < sampleCount; i++) {
        buffer[i] = sineWaveSample(i, sampleFreq) * volume;
    }

    //Output to PWM
}

void main()
{
   uint8_t i;

   InitPWM();

   int frequency = 440;
   sampleRate = 44100;
   int duration = 1000;
   int sampleFreq = frequency/sampleRate;

   while(1)
   {


        uint8_t delay,n;

        // for(delay=1;delay<=50;delay++)
        // {
        //  for(n=0;n<(51-delay);n++)
        //  {
        //     for(i=0;i<=254;i++)
        //     {
        //        OCR0 = sine + i;
        //        _delay_loop_2(delay);
        //
        //     }
        //  }
        // }
        for(delay=50;delay>=2;delay--)
        {
         for(n=0;n<(51-delay);n++)
         {
            for(i=0;i<=254;i++)
            {
               OCR0= sine + i;
               // OCR0= sineWaveSample(i, ) * 128;
               _delay_loop_2(delay);
            }
         }
        }


   }
}
