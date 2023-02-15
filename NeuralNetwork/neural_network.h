#include <inttypes.h>
#include <float.h>
#include <math.h>

//---------------------------------------------
// neuron definitions
//---------------------------------------------

// this is how many inputs a neuron has
#define NEURON_INPUTS 30
// this is the value that a neuron will start off with when it is created
#define NEURON_VALUE_DEFAULT 0
// this is the value that a neuron's input weights will start with when that neuron is created
#define NEURON_WEIGHT_DEFAULT 0
// this is the maximum exponent that can be fed into the exp() function to give the weight magnitude
#define NEURON_WEIGHT_EXPONENT_MAX 10
// this is the minimum exponent that can be fed into the exp() function to give the weight magnitude
#define NEURON_WEIGHT_EXPONENT_MIN -10
// this is the chance (out of 100,000) that a neuron will be NULL
#define NEURON_JUMBLE_NULL_CHANCE 10000
// this is the default rate at which mutation occurs (the default value for all of the mutation rates in a neural network
#define NEURON_MUTATION_RATE 0.1
// this is the rate at which the mutation rates are, themselves, mutated. This is a meta mutation rate.
#define NEURON_MUTATION_RATE_META 0.9

// this is the data type that the neurons operate with (see struct neuron)
#define NEURON_TYPE float
// this is the data types that is used to hold a count of how many neurons there are in a network.
#define NEURON_COUNT_TYPE int_fast64_t
// this is the value that a neuron's value will be set to instead of NaN
#define NEURON_NAN_SUBSTITUTE 0.123456

// this is the placeholder for infinity that neurons use
#define NEURON_INFINITY 1000000//__FLT_MAX__
// this is how many neurons are in a single link in a linked neuron list
#define NEURONS_PER_BLOCK 256

// this defines how many inputs each neural network has
#define NEURAL_NETWORK_INPUTS 1
// this defines how many outputs each neural network has
#define NEURAL_NETWORK_OUTPUTS 1

//---------------------------------------------
// neuron printing standards definitions
//---------------------------------------------
// here are definitions that describe how neural networks are to be printed to file.
// this is the line that indicates how many INPUTS a neural network has
#define NEURON_PRINT_INPUTS					"INPUT(s)      =%10ld\n"
// this is the line that indicates how many OUTPUT a neural network has
#define NEURON_PRINT_OUTPUTS				"OUTPUT(s)     =%10ld\n"
// this is the line that indicates how many total neurons a network has
#define NEURON_PRINT_NEURONS				"INTERNAL(s)   =%10ld\n"
// this is the line that indicates how many total neurons the network has (inputs + outputs + block-chain)
#define NEURON_PRINT_TOTAL					"TOTAL         =%10ld\n"
// this is the line that indicates what the mutation rate is for output neurons
#define NEURON_PRINT_OUTPUT_MUTATION_RATE	"OUT_MUT_RATE  =%10e\n"
// this is the line that describes what the mutation rate is for a specific block
#define NEURON_PRINT_BLOCK_MUT_RATE	"BLOCK_MUT_RATE = %10e\n"
// this is the column header that gives names to each column
#define NEURON_PRINT_COLUMN_HEADERS "      Addr | nop |          value    ###\n"
// this is the string that will be printed when a neuron input is NULL
#define NEURON_PRINT_NULL_STRING "          ~"
// this is how each neuron is started. The neuron address, the neuron operation, then the neuron value
#define NEURON_PRINT_FORMAT_ADDR_OP	"%10ld | %3d | %14e    ###"
// this is the output format when printing neurons to text files
#define NEURON_PRINT_FORMAT			"%11ld: %14e | "
// this is the output format when printing NULL neurons to text files
#define NEURON_PRINT_FORMAT_NULL	"%s: %14e | "

//---------------------------------------------
// neuron operation definitions
//---------------------------------------------

// this is the number of valid operations there are for neurons.
#define NEURON_OPS_VALID 5
// this is the maximum number of operations that the datatype for operations can handle. 
#define NEURON_OPS_MAX 256
// this is the data type that neurons' operations are stored in (see struct neuron)
#define NEURON_OP_TYPE uint_fast8_t
// this is the default operation that a neuron has when it is created
#define NEURON_OP_DEFAULT 0


/// these are all of the neuron operations that instruct the program how to calculate a neuron's value
// in a neural network, the first neuron in the list is evaluated first. [0] is evaluated first. [1] is evaluated second. And so on...
// the last neurons evaluated are the outputs. They are enumerated and evaluated in the order of (-NEURAL_NETWORK_INPUTS-1) to (-NEURAL_NETWORK_INPUTS-1-NEURAL_NETWORK_OUTPUTS)
// "nop" roughly stands for "neural operation"
// subtraction is pointless. It should be done by using the addition operator with negative weights.
// this list should always have numbers from 0 to NEURON_OPS_VALID-1
// if there are any gaps in the definitions here, the program will interpret them as addition operations. And you are going to have to live with that.
#define nop_addition			0	// adds			all non-NULL inputs[] neurons' values using "weights" as multipliers for each sum term before summing
#define nop_multiplication		1	// multiplies 	all non-NULL inputs[] neurons' values using "weights" as offsets for each product term before multiplying
#define nop_division			2	// divides the first non-NULL input by the second non-NULL input. "weights" are used as offsets for the first and second non-NULL input before dividing.
#define nop_exponential			3	// takes the exponential of all the non-NULL weighted inputs: e^(weighted_input1 + weighted_input2 + weighted_input3 + ...)
#define nop_sigmoid				4	// calculates sigmoid function to the weighted sum of the non-NULL inputs
// bitwise operations have yet to be written at this point.
#define nop_bwAND				5	// bitwise AND  of all non-NULL inputs.
#define nop_bwOR				6	// bitwise OR   of all non-NULL inputs.
#define nop_bwNAND				7	// bitwise NAND of all non-NULL inputs.
#define nop_bwNOR				8	// bitwise NOR  of all non-NULL inputs.
#define nop_bwXOR				9	// bitwise XOR  of all non-NULL inputs.
#define nop_bwXNOR				10	// bitwise XNOR of all non-NULL inputs.
#define nop_bwNOT				11	// bitwise NOT  of the first non-NULL input
 


//---------------------------------------------
// structure definitions
//---------------------------------------------

// this is a neuron.
// this simple little machine does all of the work.
struct neuron
{
	// this is the numerical address of the neuron inside the network.
	// the numerical address corresponds to the number of the neuron in the block chain.
	// this is very helpful when printing data to a file and then reading it back into memory.
	// neurons in the network are from 0 to infinity (or as big as the data types will allow)
	// input neurons are from -1 to -NEURAL_NETWORK_INPUTS.
	// output neurons are from -NEURAL_NETWORK_INPUTS-1 to -NEURAL_NETWORK_INPUTS-1 -NEURAL_NETWORK_OUTPUTS
	NEURON_COUNT_TYPE address;
	
	// this is the value that the neuron is currently at.
	// Think of this as the neuron's "output" value
	NEURON_TYPE value;
	
	// these are the neurons that are inputs (if they are unconnected, they should be set to NULL)
	// they point to the neurons that are used as the inputs
	struct neuron *inputs[NEURON_INPUTS];
	// these are the weights for each input. These are always applied to the neuron.
	// these are always strictly weights.
	// for some operations - like multiplication and division - these "weights" are used more as offsets applied to inputs BEFORE the operation
	NEURON_TYPE weights[NEURON_INPUTS];
	
	
	// this defines what operation will be carried out to calculate the current value of the neuron.
	NEURON_OP_TYPE operation;
	
};

// this is a block in a block chain (linked list) of neurons
// each block in the chain contains a number of neurons (or a "block" or a "chunk" of neurons, if you prefer)
// neurons in one block can have their inputs point at neurons in other blocks.
struct neuralBlock
{
	// this is the previous block in the chain.
	// if this is NULL, this is the first block in the chain.
	struct neuralBlock *blockPrev;
	// this is the next block in the chain.
	// if this is NULL, this is the last block in the chain.
	struct neuralBlock *blockNext;
	
	// these are the neurons in the chain
	struct neuron neurons[NEURONS_PER_BLOCK];
	
	// this specifies the probability of a neuron mutating in this specific block
	float mutationRate;
	
};

// a neural network is organized in the below structure.
struct neuralNetwork
{
	// this is the first block in the chain
	struct neuralBlock *blockFirst;
	// this is the last block in the chain
	struct neuralBlock *blockLast;
	
	
	// these are the neural network input neurons
	struct neuron *inputs[NEURAL_NETWORK_INPUTS];
	// these are the neural network output neurons
	struct neuron *outputs[NEURAL_NETWORK_OUTPUTS];
	
	// this specifies how likely it is that an output neuron will mutate
	float mutationRate;
		
	// this is the total number of neurons that the network contains
	NEURON_COUNT_TYPE totalNeurons;
	// this tells us how many blocks there are in the network
	NEURON_COUNT_TYPE blocksNumb;
	// this tells us how many neurons there are per block
	NEURON_COUNT_TYPE neuronsPerBlock;
	// this tells us how many inputs there are in this network
	//NEURON_COUNT_TYPE inputsNumb;
	// this tells us how many output there are in this network
	//NEURON_COUNT_TYPE outputsNumb;
};



// this is the default file location for error logging
#define NEURAL_ERROR_FILE "neural_error.txt"


//---------------------------------------------
// function prototypes and function definitions
//---------------------------------------------
void neural_error_log  (char *str);
void neural_error_log_d(char *str, int   data);
void neural_error_log_f(char *str, float data);
void neural_error_log_s(char *str, char *data);


struct neuralNetwork *nnet_create(NEURON_COUNT_TYPE blocksNumb, NEURON_COUNT_TYPE neuronsPerBlock);
short nnet_set_values_to_0(struct neuralNetwork *net);
short nnet_copy(struct neuralNetwork *source, struct neuralNetwork *dest);
short nnet_destroy(struct neuralNetwork *trash);

NEURON_COUNT_TYPE nnet_count_neurons(struct neuralNetwork *net);
struct neuron *nnet_get_enumerated_neuron(struct neuralNetwork *net, NEURON_COUNT_TYPE neuronNumber);
short nnet_address_neurons(struct neuralNetwork *net);

short nnet_save_txt(struct neuralNetwork *net, char *path);


short nnet_jumble(struct neuralNetwork *net);
short nnet_mutate(struct neuralNetwork *net);
#define nnet_get_random_operation() (rand_range(0,NEURON_OPS_VALID-1))
#define nnet_get_random_mutation_rate() pow( 10, rand_range_f(-10,0) )

short nnet_evaluate(struct neuralNetwork *net);
struct neuralNetwork *nnet_quick_train(NEURON_TYPE *testIn, NEURON_TYPE *testOut, unsigned int testPoints, unsigned int blocksPerNet, unsigned int netsPerGen, char trainLinearly, float errorTol);

