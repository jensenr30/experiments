#include <stdio.h>
#include "logic_function.h"

// this prints an error to file.
void error(char *errstr){
	FILE *err = fopen("error.txt", "a");
	fprintf(err, errstr);
	fclose(err);
}

// this prints an error to file.
void error_d(char *errstr, int data){
	FILE *err = fopen("error.txt", "a");
	fprintf(err, "%s\t%d",errstr, data);
	fclose(err);
}


/// this will set up a signal to draw its logic value from a certain bit in the variable "vDriver"
// returns 0 on success
// returns 1 on NULL signal
// returns 2 on NULL vDriver
// returns 3 on invalid bit outside range from [0 to LOGIC_VARIABLE_BITS-1]
short logic_signal_point_at_variable(struct logicSignal *signal, uint_fast64_t *vDriver, uint_fast8_t bit){
	
	// check to make sure all input data is valid and within range.
	if(signal == NULL){
		error("logic_signal_point_at_variable() was passed NULL logicSignal.");
		return 1;
	}
	if(vDriver == NULL){
		error("logic_signal_point_at_variable() was passed NULL vDriver.");
		return 2;
	}
	if(bit < 0|| bit >= LOGIC_VARIABLE_BITS){
		error_d("logic_signal_point_at_variable() was passed invalid bit. bit =", bit);
		return 3;
	}
	
	// copy variable adddress into the signal.
	signal->variableDriver = vDriver;
	// record the desired bit of the above data address.
	signal->bit = bit;
	
	// success
	return 0;
}



/// this will set up a signal to draw its logic value from a logic gate, "gDriver"
// returns 0 on success
// returns 1 on NULL signal
// returns 2 on NULL gDriver
short logic_signal_point_at_gate(struct logicSignal *signal, struct logicGate *gDriver){
	
	// check to make sure all input data is valid and within range.
	if(signal == NULL){
		error("logic_signal_point_at_variable() was passed NULL logicSignal.");
		return 1;
	}
	if(gDriver == NULL){
		error("logic_signal_point_at_variable() was passed NULL gDriver.");
		return 2;
	}
	
	// copy the address of the logicGate into the gateDriver pointer in the signal.
	signal->gateDriver = gDriver;
	
	// success
	return 0;
}
