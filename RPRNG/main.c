/**
This program was written and designed by Ryan Jensen
RPRNG stands for "Ryans Pseudo-Random Number Generator (whew! that was a mouth full).
This program is intended to generate a state machine that outputs "noisy" data.
That is, data that is weighted fairly (each bit waveform has a 50% duty cycle)
The sequence that is produced should have a flat frequency spectrum.
The state machine should be optimized to have a very long cycle time while still producing a noisy output.

This will be achieved through a genetic algorithm that optimizes for:
- high noisiness
- ease of calculation
- the even weighting for bits
- a long repeat cycle

*/
#include <stdio.h>
#include "logic_function.h"
#include "RPRNG.h"


int main( int argc, char *argv[] ){
	
	
	return 0;
}
