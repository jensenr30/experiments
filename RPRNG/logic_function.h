#include <stdint.h>
// there are three inputs to every logic function
//#define LOGICF_INPUT_BITS 6
// there are eight possible outputs for every logic function (2^3)
//#define LOGICF_OUTPUT_BITS 64

// this is the type of number that will be used to store function data
//typedef int_fast64_t logicf_f_type;
//typedef int_fast8_t logicf_o_type;

//#define LOGICF_1	((int_fast64_t)0x00000000)
//#define LOGICF_0	((int_fast64_t)0xffffffff)

// this stores information about a logic function

/* how to get an output from a logic function
	int index = 
	for(bit=1; b<LOGICF_INPUT_BITS; b*=2) index|evaluate

*/

/*
struct logicFunctionData{
	
	
	logicf_type f;
	
	// these are pointers to the three inputs, x[0], x[1], and x[2]
	struct logicFunctionData *x[LOGICF_INPUT_BITS];
	
	// this holds the current value of the output
	// output = f&(1<<(logic_evaluate(x[0]) + logic_evaluate(x[1])<<1 + logic_evaluate(x[2])<<2)) ONLY WHEN THE LOGIC UPDATE OCCURS! (on a clock cycle event)
	unsigned char output;
	
	// this is what the output will be when the next update, or "clock cycle" occurs.
	// this is used as temporary storage for 
	unsigned char outputBuffer;
	
	
};
*/

#define LOGIC_VARIABLE_BITS 64

// this is a logic signal. This is responsible for routing information between logic gates (and from certain bits in variables to logic gate inputs)
struct logicSignal {
	
	// this is a pointer to a gate that is acting as an output.
	// this points to the output of a logic gate.
	// if this is valid, that means this signal is being "gate driven."
	// if this is NULL, then the interpreter will check the variableDriven pointer.
	struct logicGate *gateDriver;
	
	// if this is valid (and gateDriven is NULL) then this signal is referred to as being "variable driven"
	// a certain bit will be picked from this variable and used as the signals logic level.
	// for example: logicSignal's output = (*variableDriver)&(1<<bit);
	uint_fast64_t *variableDriver;
	// this tells us what bit we want to look for in the 64 bit integer that the above pointer points to.
	uint_fast8_t bit;
	
};


/// lo stands for "logic operation"
#define lo_OR		0
#define lo_AND		1
#define lo_NOR		2
#define lo_NAND		3
#define lo_NOT		4
#define lo_XOR		5
#define lo_XNOR		6

#define LOGIC_GATE_OPERANDS 2
/// this is a logic gate. 
struct logicGate {

	// this is the operation that will be carried out on the two operands
	uint_fast8_t op;
	
	// this is a pointer to a logicSignal.
	// A logic Signal can either be the output of another logicGate or a bit from a variable
	struct logicSignal inputSignal[LOGIC_GATE_OPERANDS];
	
};




short logic_signal_point_at_variable(struct logicSignal *signal, uint_fast64_t *vDriver, uint_fast8_t bit);
short logic_signal_point_at_gate(struct logicSignal *signal, struct logicGate *gDriver);
