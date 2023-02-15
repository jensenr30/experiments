#include "neural_network.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand.h"
#include "custom_math.h"

/// this function logs a string to the designated text file
void neural_error_log(char *str)
{
	
	FILE *errorfile = fopen(NEURAL_ERROR_FILE, "a");
	// if the file opened successfully,
	if(errorfile != NULL)
	{
		// write to neural error file
		fprintf(errorfile, "%s\n", str);
		// close the neural error file
		fclose(errorfile);
	}
}
/// this function logs a string to the designated text file with an integer appended
void neural_error_log_d(char *str, int data)
{
	
	FILE *errorfile = fopen(NEURAL_ERROR_FILE, "a");
	// if the file opened successfully,
	if(errorfile != NULL)
	{
		// write to neural error file
		fprintf(errorfile, "%s\t%d\n", str, data);
		// close the neural error file
		fclose(errorfile);
	}
}
/// this function logs a string to the designated text file with an float appended
void neural_error_log_f(char *str, float data)
{
	
	FILE *errorfile = fopen(NEURAL_ERROR_FILE, "a");
	// if the file opened successfully,
	if(errorfile != NULL)
	{
		// write to neural error file
		fprintf(errorfile, "%s\t%f\n", str, data);
		// close the neural error file
		fclose(errorfile);
	}
}
/// this function logs a string to the designated text file with a string appended
void neural_error_log_s(char *str, char *data)
{
	
	FILE *errorfile = fopen(NEURAL_ERROR_FILE, "a");
	// if the file opened successfully,
	if(errorfile != NULL)
	{
		// write to neural error file
		fprintf(errorfile, "%s\t%s\n", str, data);
		// close the neural error file
		fclose(errorfile);
	}
}



/// this function will set the addresses of all neurons (starting at 0 and incrementing from there)
// this function will enumerate all of the neurons and put that enumeration in their addresses.
// returns 0 on success
// returns 1 on invalid net pointer
short nnet_address_neurons(struct neuralNetwork *net)
{
	// if the given network is invalid,
	if(net == NULL)
	{
		// log an error
		neural_error_log("nnet_address_neurons() could not properly count the neurons in the given network as net = NULL");
		// return 1.
		return 1;
	}
	
	
	// enumerate internal (block chain) neurons
	NEURON_COUNT_TYPE i;
	
	struct neuralBlock *currentBlock = net->blockFirst;
	for(i=0; i<net->totalNeurons; i++)
	{
		// if i crosses block boundaries, move to the next block
		if(i%NEURONS_PER_BLOCK == 0 && i != 0)
		{
			currentBlock = currentBlock->blockNext;
		}
		// enumerate the address
		currentBlock->neurons[i%NEURONS_PER_BLOCK].address = i;
	}
	
	// enumerate input neurons
	for(i=0; i<NEURAL_NETWORK_INPUTS; i++)
	{
		// set the address of the input neuron
		net->inputs[i]->address = -1 -i;
	}
	
	// enumerate output neurons
	for(i=0; i<NEURAL_NETWORK_OUTPUTS; i++)
	{
		// set the address of the input neuron
		net->outputs[i]->address = -1 -i -NEURAL_NETWORK_INPUTS;
	}
	
	// success
	return 0;
}


/// this function will allocate space for a new neural network and return a pointer to it.
// if the program fails to allocate a new neural network, it will return NULL.
// by default, this function will allocate the network with 1 neuralBlock.
// this does NOT make connections in the neural network.
// this allocates space for the neurons, it addresses each one, it counts them when it is done.
struct neuralNetwork *nnet_create(NEURON_COUNT_TYPE blocksNumb, NEURON_COUNT_TYPE neuronsPerBlock)
{
	
	// attempt to allocate memory for a neural network
	struct neuralNetwork *newNet =	malloc(sizeof(struct neuralNetwork));
	// check to make sure allocation was successful
	if(newNet == NULL)
	{
		// log an error
		neural_error_log("nnet_create() could not allocate space for a new neural network.");
		return NULL;
	}
	
	// at this point we know that the newNet has been successfully allocated.
	
	// record these variables so that the network knows its own size.
	newNet->blocksNumb = blocksNumb;
	newNet->neuronsPerBlock = neuronsPerBlock;
	//newNet->inputsNumb = inputsNumb;
	//newNet->outputsNumb = outputsNumb;
	
	// used in the for() loops
	NEURON_COUNT_TYPE i,j;
	// used to keep track of which block the program is on
	struct neuralBlock *blockCurrent = NULL;
	
	// initially, set all pointers in the neural network to NULL
	// this step is taken to make sure that when nnet_destroy() is called, everything is either a valid address or NULL. No 0xbaadfood for me!
	newNet->blockFirst = NULL;
	newNet->blockLast = NULL;
	for(i=0; i<NEURAL_NETWORK_INPUTS; i++)
	{
		newNet->inputs[i] = NULL;
	}
	for(i=0; i<NEURAL_NETWORK_OUTPUTS; i++)
	{
		newNet->outputs[i] = NULL;
	}
	
	//------------------------------------------------
	// attempt to allocate memory for the first neuron block in the chain.
	//------------------------------------------------
	newNet->blockFirst = malloc(sizeof(struct neuralBlock));
	// check to make sure allocation was successful
	if(newNet->blockFirst == NULL)
	{
		// log an error
		neural_error_log("nnet_create() could not allocate first block of neurons");
		// delete the new network because we cannot allocate any neuron links (and therefor there are no neurons)
		nnet_destroy(newNet);
		return NULL;
	}
	// set the last link in the list to be the first link in the list (there is only one neuron link so far, as the neural network was just created).
	newNet->blockLast = newNet->blockFirst;
	// set the blockNext and blockPrev to NULL for the first block in the chain (because this is the only link in the list so far)
	(newNet->blockFirst)->blockPrev = NULL;
	(newNet->blockFirst)->blockNext = NULL;
	
	//------------------------------------------------
	// attempt to allocate memory for the reset of the neural blocks
	//------------------------------------------------
	// set the current block to the first block of the neural network.
	blockCurrent = newNet->blockFirst;
	// this keeps track of how many blocks have been allocated.
	NEURON_COUNT_TYPE b;
	for(b = 1; b<blocksNumb; b++)
	{
		if(blockCurrent == NULL)
		{
			neural_error_log_d("nnet_create() had a weird error! blockCurrent = NULL...? b = ",b);
			nnet_destroy(newNet);
			return NULL;
		}
		// try to allocate memory
		blockCurrent->blockNext = malloc(sizeof(struct neuralBlock));
		if(newNet->blockFirst == NULL)
		{
			// log an error
			neural_error_log_d("nnet_create() could not allocate space for any list links inside of the network. b = ",b);
			// delete the new network because we cannot allocate any neuron links (and therefor there are no neurons)
			nnet_destroy(newNet);
			return NULL;
		}
		// make the next pointer look back at this one.
		blockCurrent->blockNext->blockPrev = blockCurrent;
		// the next block has no next block yet. set this to NULL
		blockCurrent->blockNext->blockNext = NULL;
		// move to the next block in the chain
		blockCurrent = blockCurrent->blockNext;
	}
	// the last block that the for loop landed on must be the last block.
	newNet->blockLast = blockCurrent;
	
	if(newNet->blockFirst == NULL)
	{
		neural_error_log("nnet_create() has no first block! Oh shit!");
		nnet_destroy(newNet);
		return NULL;
	}
	if(newNet->blockLast == NULL)
	{
		neural_error_log("nnet_create() has no last  block! Oh well.");
		nnet_destroy(newNet);
		return NULL;
	}
	
	//-----------------------------------------------------------
	// set all internal block-chain neurons to default values
	//-----------------------------------------------------------
	blockCurrent = newNet->blockFirst;
	while(blockCurrent != NULL)
	{
		for(i=0; i<NEURONS_PER_BLOCK; i++)
		{
			// set the value of this neuron to its default value
			blockCurrent->neurons[i].value = NEURON_VALUE_DEFAULT;
			blockCurrent->neurons[i].operation = NEURON_OP_DEFAULT;
			for(j=0; j<NEURON_INPUTS; j++)
			{
				// set all inputs to NULL
				blockCurrent->neurons[i].inputs[j] = NULL;
				// set all weights to 0
				blockCurrent->neurons[i].weights[j] = NEURON_WEIGHT_DEFAULT;
			}
		}
		// default mutation rate for each block
		blockCurrent->mutationRate = NEURON_MUTATION_RATE;
		// switch to the next block in the chain.
		// if the next block is NULL, the while loop will exit
		blockCurrent = blockCurrent->blockNext;
	}
	
	//-----------------------------------------------------------
	// allocate all input neurons
	//-----------------------------------------------------------
	for(i=0; i<NEURAL_NETWORK_INPUTS; i++)
	{
		newNet->inputs[i] = malloc(sizeof(struct neuron));
		if(newNet->inputs[i] == NULL)
		{
			neural_error_log_d("nnet_create() could not allocate space for one of the neural network's input neurons. i =",i);
			nnet_destroy(newNet);
			return NULL;
		}
		// set the value of this input neuron to its default value
		newNet->inputs[i]->value = NEURON_VALUE_DEFAULT;
		// for each input of the input neurons,
		for(j=0; j<NEURON_INPUTS; j++)
		{
			// set that input to null
			newNet->inputs[i]->inputs[j] = NULL;
			// set the weight to default value
			newNet->inputs[i]->weights[j] = NEURON_WEIGHT_DEFAULT;
		}
	}
	//-----------------------------------------------------------
	// allocate all output neurons
	//-----------------------------------------------------------
	for(i=0; i<NEURAL_NETWORK_OUTPUTS; i++)
	{
		newNet->outputs[i] = malloc(sizeof(struct neuron));
		if(newNet->outputs[i] == NULL)
		{
			neural_error_log_d("nnet_create() could not allocate space for one of the neural network's output neurons. i =",i);
			nnet_destroy(newNet);
			return NULL;
		}
		// set the value of this neuron to its default value
		newNet->outputs[i]->value = NEURON_VALUE_DEFAULT;
		// set the operation to its default value
		newNet->outputs[i]->operation = NEURON_OP_DEFAULT;
		// for each input neuron of the output neuron,
		for(j=0; j<NEURON_INPUTS; j++)
		{
			// set that input to NULL
			newNet->outputs[i]->inputs[j] = NULL;
			// set the weight to default value
			newNet->outputs[i]->weights[j] = NEURON_WEIGHT_DEFAULT;
		}
	}
	// set the default mutation rate for output neurons
	newNet->mutationRate = NEURON_MUTATION_RATE;
	
	// count the number of neurons the net has to begin with
	nnet_count_neurons(newNet);
	// enumerate all neurons, thereby giving them proper addresses.
	nnet_address_neurons(newNet);
	
	// if we have allocated everything that we needed to, then we shall return a pointer to the new neural network.
	return newNet;
}


/// this copies the contents of one neuron into another
// this does NOT copy the address of neurons. just the characteristics (operation, value, input connections, etc...)
// returns 0 on success
// returns 1 on invalid source neuron
// returns 2 on invalid destination neuron
short nnet_copy_neuron(struct neuron *source, struct neuron *dest, struct neuralNetwork *destNet)
{
	// if either of the given neuruson are invalid,
	if(source == NULL)
	{
		// log an error
		neural_error_log("nnet_copy_neuron() source = NULL");
		// return 1.
		return 1;
	}
	if(dest == NULL)
	{
		// log an error
		neural_error_log("nnet_copy_neuron() dest = NULL");
		// return 1.
		return 2;
	}
	
	// copy the operation
	dest->operation = source->operation;
	// copy the value
	dest->value = source->value;
	int i;
	// copy all input connections and their associated weights
	for(i=0; i<NEURON_INPUTS; i++)
	{
		// make this input point to the same position in its own network 
		if(source->inputs[i] != NULL)
			dest->inputs[i] = nnet_get_enumerated_neuron(destNet, source->inputs[i]->address);
		else
			dest->inputs[i] = NULL;
		// copy the weight information for this input as well
		dest->weights[i] = source->weights[i];
	}
	
	// success
	return 0;
}


/// this copies a complete neural network into another
// both source and dest must have already been created before copying.
// returns 0 on success
// returns 1 on NULL source
// returns 2 on NULL dest
short nnet_copy(struct neuralNetwork *source, struct neuralNetwork *dest)
{
	// if either of the given networks are invalid,
	if(source == NULL)
	{
		// log an error
		neural_error_log("nnet_copy() source = NULL");
		// return 1.
		return 1;
	}
	if(dest == NULL)
	{
		// log an error
		neural_error_log("nnet_copy() dest = NULL");
		// return 1.
		return 2;
	}
	
	// the number of internal neurons that will be copied is the smallest of the two number of internal neurons
	NEURON_COUNT_TYPE neuronsToCopyInternal = smallest(source->neuronsPerBlock*source->blocksNumb, dest->neuronsPerBlock*dest->blocksNumb);
	// the number of output neurons to copy
	NEURON_COUNT_TYPE neuronsToCopyOutput = NEURAL_NETWORK_OUTPUTS;
	
	//----------------------------------------------
	// copy output neurons
	//----------------------------------------------
	int o;
	for(o=0; o<neuronsToCopyOutput; o++)
	{
		nnet_copy_neuron(source->outputs[o], dest->outputs[o], dest);
	}
	
	//----------------------------------------------
	// copy each internal block of neurons
	//----------------------------------------------
	// these are the current blocks for source and destination
	// i set them to the first block of each network to start.
	struct neuralBlock *currentBlockS = source->blockFirst;
	struct neuralBlock *currentBlockD = dest->blockFirst;
	
	int n, ns = 0, nd = 0;
	for(n=0; n<neuronsToCopyInternal; n++)
	{
		// handle moving to the next blocks for both source and dest. this can even handle source and dests with different neurons per block!
		if(n%source->neuronsPerBlock == 0 && n != 0)
		{
			currentBlockS = currentBlockS->blockNext;
			if(currentBlockS == NULL) break;
			// reset the neuron source counter
			ns = 0;
		}
		if(n%dest->neuronsPerBlock == 0)
		{
			if(n != 0)
			{
				currentBlockD = currentBlockD->blockNext;
				if(currentBlockD == NULL) break;
			}
			// copy the mutation rate from source block to destination block
			currentBlockD->mutationRate = currentBlockS->mutationRate;
			// reset the neuron destination counter
			nd = 0;
		}
		
		// copy the neuron from one block to the next
		nnet_copy_neuron(&(currentBlockS->neurons[ns]), &(currentBlockD->neurons[nd]), dest);
		
		// increment the neuron source counter
		ns++;
		// increment the neuron destination counter
		nd++;
	}
	
	// success
	return 0;
}


/// this function will calculate how many INTERNAL (hidden) neurons there are in a network.
// the input and output neurons are ignored by this function
// this will return the calculated value as well as update the value in the network itself.
// this will also update the "blocks" variable in the network.
NEURON_COUNT_TYPE nnet_count_neurons(struct neuralNetwork *net)
{
	// if the given network is invalid,
	if(net == NULL)
	{
		// log an error
		neural_error_log("nnet_count_neurons() could not properly count the neurons in the given network as net = NULL");
		// return 1.
		return 1;
	}
	
	
	// this is what keeps track of the neural block count. It is set to 1 because the network must have at least one block in it.
	NEURON_COUNT_TYPE neuralBlockCount = 1;
	// this is what keeps track of which block in the network we are looking at.
	struct neuralBlock *blockPointer = net->blockFirst;
	
	// count the number of valid blocks the network has
	while(1)
	{
		// if the current block pointer is valid,
		if(blockPointer->blockNext != NULL)
		{
			// increment the block count
			neuralBlockCount++;
			// advance the blockPointer.
			blockPointer = blockPointer->blockNext;
		}
		// otherwise, if the block pointer IS null, then we have reached the end of the line.
		else
		{
			// stop counting blocks; we are done.
			break;
		}
	}
	
	// update the value in the network
	net->totalNeurons = neuralBlockCount * NEURONS_PER_BLOCK;
	// return the number of neurons the network has been found to have
	return net->totalNeurons;
}


/// this will return a pointer to neuron #X, where X is the "neuronNumber"
struct neuron *nnet_get_enumerated_neuron(struct neuralNetwork *net, NEURON_COUNT_TYPE neuronNumber)
{
	
	// if the given network is invalid,
	if(net == NULL)
	{
		// log an error
		neural_error_log("nnet_get_enumerated_neuron() could not properly find a neuron in the given network as net = NULL");
		// return NULL
		return NULL;
	}
	
	// if the input neuronNumber is too large,
	if(neuronNumber >= net->totalNeurons)
	{
		// log an error
		neural_error_log_d("nnet_get_enumerated_neuron() could not find neuron because neuronNumber was larger than the calculated size of the network:\nneuronNumber =",neuronNumber);
		neural_error_log_d("totalNeurons =",net->totalNeurons);
		// return NULL
		return NULL;
	}
	
	//----------------------------------------------
	// check if the neuron is in the input section
	//----------------------------------------------
	
	if(neuronNumber < 0 && neuronNumber >= -NEURAL_NETWORK_INPUTS)
	{
		return net->inputs[-neuronNumber-1];
	}
	
	//----------------------------------------------
	// check if the neuron is in the output section
	//----------------------------------------------
	
	else if(neuronNumber < -NEURAL_NETWORK_INPUTS && neuronNumber >= -NEURAL_NETWORK_INPUTS - NEURAL_NETWORK_OUTPUTS)
	{
		return net->outputs[-neuronNumber-1-NEURAL_NETWORK_INPUTS];
	}
	
	//----------------------------------------------
	// check if the neuron is in the core of the nn
	//----------------------------------------------
	else if(neuronNumber >= 0 && neuronNumber < net->totalNeurons)
	{
		struct neuralBlock *currentBlock = net->blockFirst;
		// determine the block that the neuron is in.
		NEURON_COUNT_TYPE blockNumber = neuronNumber/NEURONS_PER_BLOCK;
		// the indexNumber is the neuron number INSIDE the block.
		NEURON_COUNT_TYPE indexNumber = neuronNumber%NEURONS_PER_BLOCK;
		
		// advance to the right block in the network
		NEURON_COUNT_TYPE i;
		for(i=0; i<blockNumber; i++)
		{
			// check to make sure the next block pointer is valid
			if(currentBlock->blockNext == NULL)
			{
				// log the error
				neural_error_log("nnet_get_enumerated_neuron() could not make it to the end of the list. block pointers were NULL? The program must not be handling the block pointers right because this should never happen.");
				return NULL;
				break;
			}
			// otherwise, if the next block is indeed valid, advance the block pointer
			currentBlock = currentBlock->blockNext;
		}
		// successfully found the neuron in the list.
		return &(currentBlock->neurons[indexNumber]);
	}
	
	//----------------------------------------------
	// the enumerated neuron must be out of bounds
	//----------------------------------------------
	
	else
	{
		// return NULL pointer (no neuron was found)
		neural_error_log_d("nnet_get_enumerated_neuron() did not find neuron! neuronNumber = ",neuronNumber);
		return NULL;
	}
}


/// this function will return a random neuron in the network.
// this could return an input neuron, an internal neuron, or even an output neuron.
struct neuron *nnet_get_random_neuron(struct neuralNetwork *net)
{
	// get a random number between the inputs and the outputs
	NEURON_COUNT_TYPE neuronNumber = rand_range(-NEURAL_NETWORK_INPUTS-NEURAL_NETWORK_OUTPUTS, net->totalNeurons-1);
	// return that address to that neuron
	return nnet_get_enumerated_neuron( net, neuronNumber );
}

NEURON_TYPE nnet_get_random_weight()
{
	float exponent = rand_range_f(NEURON_WEIGHT_EXPONENT_MIN, NEURON_WEIGHT_EXPONENT_MAX);
	float weight = exp(exponent);
	if(rand_bool()) weight *= -1.0;
	return weight;
}


/// this will randomize the neural network connections between neurons.
// this will also randomize the weights and the operations of each neuron.
// this does NOT randomize the value of neurons
short nnet_jumble(struct neuralNetwork *net)
{
	// if the given network is invalid,
	if(net == NULL)
	{
		// log an error
		neural_error_log("nnet_jumble() could not properly jumble the neurons in the given network as net = NULL");
		// return 1.
		return 1;
	}
	
	NEURON_COUNT_TYPE i;
	int j;
	
	//-----------------------------------------------
	// jumble the output neurons
	//-----------------------------------------------
	for(i=0; i<NEURAL_NETWORK_OUTPUTS; i++)
	{
		net->outputs[i]->operation = nnet_get_random_operation();
		for(j=0; j<NEURON_INPUTS; j++)
		{
			// for each input of every output neuron,
			// get a random input neuron
			net->outputs[i]->inputs[j]  = nnet_get_random_neuron(net);
			// and weight it randomly
			net->outputs[i]->weights[j] = nnet_get_random_weight();
		}
	}
	// get a random mutation rate for the output neurons
	net->mutationRate = nnet_get_random_mutation_rate();
	
	//-----------------------------------------------
	// jumble the internal block-chain neurons
	//-----------------------------------------------
	struct neuralBlock *currentBlock = net->blockFirst;
	
	for(i=0; i<net->totalNeurons; i++)
	{
		// if i crosses block boundaries
		if(i%NEURONS_PER_BLOCK == 0)
		{
			// if this is not the first block,
			if(i != 0)
			{
				// move to the next block
				currentBlock = currentBlock->blockNext;
			}
			// get a random mutation rate for this block of neurons.
			currentBlock->mutationRate = nnet_get_random_mutation_rate();
		}
		
		
		
		// pick a random operation
		currentBlock->neurons[i%NEURONS_PER_BLOCK].operation = nnet_get_random_operation();
		
		
		// loop through all neuron inputs
		for(j=0; j<NEURON_INPUTS; j++)
		{
			// randomly determine if you want to set one input on this neuron to NULL.
			if(rand_ht_eval(NEURON_JUMBLE_NULL_CHANCE))
			{
				// set the neuron to null
				currentBlock->neurons[i%NEURONS_PER_BLOCK].inputs[j] = NULL; // currentBlock->neurons[i].inputs[j]
			}
			else
			{
				// otherwise, pick a random VALID neuron
				currentBlock->neurons[i%NEURONS_PER_BLOCK].inputs[j] = nnet_get_random_neuron(net);
			}
			// pick a weight
			currentBlock->neurons[i%NEURONS_PER_BLOCK].weights[j] = nnet_get_random_weight();
			
		}
	}
	
	// successfully jumbled the neural network
	return 0;
}


/// this will set all the "value" variable to 0 for every neuron (input, output, and internal)
// this should be used before starting any simulation.
// It is necessary to control the initial conditions of the neural network when performing evolution and using the resultant neural networks.
// returns 0 on success
// returns 1 on NULL net pointer
short nnet_set_values_to_0(struct neuralNetwork *net)
{
	// if the given network is invalid,
	if(net == NULL)
	{
		// log an error
		neural_error_log("nnet_set_values_to_0() was sent net = NULL");
		// return 1.
		return 1;
	}
	
	NEURON_COUNT_TYPE i;
	
	// erase the input neurons
	for(i=0; i<NEURAL_NETWORK_INPUTS; i++)
	{
		net->inputs[i]->value = 0;
	}
	// erase the output neurons
	for(i=0; i<NEURAL_NETWORK_OUTPUTS; i++)
	{
		net->outputs[i]->value = 0;
	}
	// erase the internal neurons in the block chain
	struct neuralBlock *bp = net->blockFirst;
	NEURON_COUNT_TYPE b = 0;
	
	while(bp != NULL)
	{
		// erase all the neurons in this block
		for(i=0; i<NEURONS_PER_BLOCK; i++)
		{
			bp->neurons[i].value = 0;
		}
		// increment the number of blocks erased
		b++;
		// move to the next block of neurons
		bp = bp->blockNext;
	}
	
	// success
	return 0;
}


/// this destroys all allocated memory that the neural network has been allocated.
// a neural network need not be fully allocated to call this function.
// this function will determine what memory is valid and what is NULL.
// this function will only destroy (free) valid memory (it won't try to free NULL memory)
// returns 0 on success
// returns 1 on a failure (invalid network pointer)
short nnet_destroy(struct neuralNetwork *trash)
{
	
	// if this function was sent a NULL neuralNetwork pointer, just quit now.
	if(trash == NULL) return 1;
	
	// put the first neuralBlock of the neural network's list into this variable
	struct neuralBlock *currentLink = trash->blockFirst;
	struct neuralBlock *lastLink;
	if(currentLink != NULL)
	{
		// destroy all neuralBlocks in the neural networks network's list
		while(1)
		{
			// if this is the last link in the list
			if(currentLink->blockNext == NULL)
			{
				// destroy the last link
				free(currentLink);
				// and leave
				break;
			}
			else
			{
				// save the current link in the lastLink placeholder
				lastLink = currentLink;
				// advance the current link.
				currentLink = currentLink->blockNext;
				// destroy the link that was just moments ago the current link.
				free(lastLink);
			}
		}
	}
	
	// used for iterating through for() loops
	int i;
	
	// destroy the inputs
	for(i=0; i<NEURAL_NETWORK_INPUTS; i++)
	{
		// if the current input is not NULL,
		if(trash->inputs[i] != NULL)
		{
			// destroy the input
			free(trash->inputs[i]);
		}
	}
	
	// destroy the outputs
	for(i=0; i<NEURAL_NETWORK_OUTPUTS; i++)
	{
		// if the current input is not NULL,
		if(trash->outputs[i] != NULL)
		{
			// destroy the input
			free(trash->outputs[i]);
		}
	}
	
	// we are done destroying all of the elements of the neuralNetwork.
	// finally, we shall destroy the neuralNetwork itself.
	free(trash);
	// success
	return 0;
}


/// this function prints the neural network to file.
// returns 0 on success
// returns 1 on invalid net pointer
// returns 2 on failure to open text file
short nnet_save_txt(struct neuralNetwork *net, char *path)
{
	// if the given network is invalid,
	if(net == NULL)
	{
		// log an error
		neural_error_log("nnet_save_txt() could not properly print network to text file as net = NULL");
		// return error
		return 1;
	}
	
	// attempt to open the destination file
	FILE *fp = fopen(path, "w");
	if(fp == NULL)
	{
		// log error
		neural_error_log_s("nnet_save_txt() could not open file with path =",path);
		// return error
		return 2;
	}
	
	// assuming the file is open and ready to be printed to, START PRINTING!
	
	// print meta information about the neural network
	fprintf(fp, NEURON_PRINT_INPUTS,  (long int)NEURAL_NETWORK_INPUTS);
	fprintf(fp, NEURON_PRINT_OUTPUTS, (long int)NEURAL_NETWORK_OUTPUTS);
	fprintf(fp, NEURON_PRINT_NEURONS, (long int)net->totalNeurons);
	fprintf(fp, NEURON_PRINT_TOTAL,   (long int)(NEURAL_NETWORK_INPUTS+NEURAL_NETWORK_OUTPUTS+net->totalNeurons) );
	// print information about the rows
	fprintf(fp,NEURON_PRINT_COLUMN_HEADERS);
	
	// print the output neuron information
	NEURON_COUNT_TYPE i;
	NEURON_COUNT_TYPE j;
	
	
	//----------------------------------------------
	// print outputs
	//----------------------------------------------
	
	// print output neuron mutation rate information
	fprintf(fp, NEURON_PRINT_OUTPUT_MUTATION_RATE, (float)net->mutationRate);
	for(i=0; i<NEURAL_NETWORK_OUTPUTS; i++)
	{
		// print the address of the output neuron
		fprintf(fp,NEURON_PRINT_FORMAT_ADDR_OP, (long int)net->outputs[i]->address, net->outputs[i]->operation, net->outputs[i]->value);
		// print the addresses of the output neuron's input neurons
		for(j=0; j<NEURON_INPUTS; j++)
		{
			// if the input neuron is valid
			if(net->outputs[i]->inputs[j] != NULL)
			{
				// print the address
				fprintf(fp ,NEURON_PRINT_FORMAT, (long int)net->outputs[i]->inputs[j]->address, net->outputs[i]->weights[j]);
			}
			else
			{
				// otherwise, just print the null neuron code
				fprintf(fp, NEURON_PRINT_FORMAT_NULL, NEURON_PRINT_NULL_STRING, net->outputs[i]->weights[j]);
			}
		}
		//newline
		fprintf(fp,"\n");
	}
	
	
	//----------------------------------------------
	// print inputs (mainly just for debugging)
	//----------------------------------------------
	for(i=0; i<NEURAL_NETWORK_INPUTS; i++)
	{
		// print the address of the output neuron
		fprintf(fp,NEURON_PRINT_FORMAT_ADDR_OP, (long int)net->inputs[i]->address, net->inputs[i]->operation, net->inputs[i]->value);
		// print the addresses of the output neuron's input neurons
		for(j=0; j<NEURON_INPUTS; j++)
		{
			// if the input neuron is valid
			if(net->inputs[i]->inputs[j] != NULL)
			{
				// print the address
				fprintf(fp ,NEURON_PRINT_FORMAT, (long int)net->inputs[i]->inputs[j]->address, net->inputs[i]->weights[j]);
			}
			else
			{
				// otherwise, just print the null neuron code
				fprintf(fp, NEURON_PRINT_FORMAT_NULL, NEURON_PRINT_NULL_STRING, net->inputs[i]->weights[j]);
			}
		}
		//newline
		fprintf(fp,"\n");
	}
	
	//----------------------------------------------
	// print internal neurons
	//----------------------------------------------
	
	// start at the first block of neurons
	struct neuralBlock *currentBlock = net->blockFirst;
	// print the internal neuron information
	for(i=0; i<net->totalNeurons; i++)
	{
		if(i%NEURONS_PER_BLOCK == 0)
		{
			// if this isn't the first neuron, go to the next block
			if(i!=0)
			{
				currentBlock = currentBlock->blockNext;
			}
			// print the mutation rate for the current block
			fprintf(fp,NEURON_PRINT_BLOCK_MUT_RATE, currentBlock->mutationRate);
		}
		
		// print the address of the internal neuron
		fprintf(fp,NEURON_PRINT_FORMAT_ADDR_OP, (long int)currentBlock->neurons[i%NEURONS_PER_BLOCK].address, currentBlock->neurons[i%NEURONS_PER_BLOCK].operation, currentBlock->neurons[i%NEURONS_PER_BLOCK].value);
		for(j=0; j<NEURON_INPUTS; j++)
		{
			// print the addresses and weights of all other neurons 
			if(currentBlock->neurons[i%NEURONS_PER_BLOCK].inputs[j] != NULL)
			{
				fprintf(fp, NEURON_PRINT_FORMAT, (long int)currentBlock->neurons[i%NEURONS_PER_BLOCK].inputs[j]->address, currentBlock->neurons[i%NEURONS_PER_BLOCK].weights[j]);
			}
			else
			{
				// otherwise, just print the null neuron code
				fprintf(fp, NEURON_PRINT_FORMAT_NULL, NEURON_PRINT_NULL_STRING, currentBlock->neurons[i%NEURONS_PER_BLOCK].weights[j]);
			}
		}
		//newline
		fprintf(fp,"\n");
	}
	
	// close the door on your way out
	fclose(fp);
	// success
	return 0;
}




/// this function will evaluate a single neuron 
// returns 0 on success
// returns 1 on a NULL neuron (ron) input
short nnet_evaluate_neuron(struct neuron *ron)
{
	// this is handy for calculating sums
	static NEURON_TYPE sum;
	// this is handy for calculating the product
	static NEURON_TYPE product;
	// this keeps track of which input is being summed/producted/exponentiated/etc...
	static NEURON_COUNT_TYPE i;
	// these two variables are for finding the first and second non-NULL inputs
	static NEURON_COUNT_TYPE iFirst, iSecond;
	
	// if the given neuron is invalid,
	if(ron == NULL)
	{
		// log an error
		neural_error_log("nnet_evaluate_neuron() could not evaluate neuron. ron = NULL");
		// return error
		return 1;
	}
	
	switch(ron->operation)
	{
		// default is addition.
		case nop_addition:
		default:
			// set sum to 0 to start
			sum = 0;
			// for every input
			for(i=0; i<NEURON_INPUTS; i++)
			{
				// if the input neuron is NOT NULL,
				if(ron->inputs[i] != NULL)
				{
					// weight the value of the input-neuron's output and add it to the running total (the sum)
					sum += ron->inputs[i]->value * ron->weights[i];
				}
			}
			// the output of this neuron is equal to the sum of the weighted inputs
			ron->value = sum;
		break;
		
		
		// multiply all input neurons together.
		case nop_multiplication:
			// the product is initially 1
			product = 1;
			// for every input
			for(i=0; i<NEURON_INPUTS; i++)
			{
				// if the input neuron is NOT NULL,
				if(ron->inputs[i] != NULL)
				{
					// the weights, in the case of multiplication, are used as offsets before multiplying
					product *= (ron->inputs[i]->value + ron->weights[i]);
				}
			}
			// the output of this neuron is equal to the product of the offset-inputs
			ron->value = product;
		break;
		
		
		// divide the first input neuron by the second one
		case nop_division:
			// assuming you have at least two inputs per neuron (I think we can assume this is true :P)
			if(NEURON_INPUTS >= 2)
			{
				// set the first and second inputs to -1 to start. By default, it is assumed they are invalid.
				iFirst = iSecond = -1;
				// find the first non-NULL input
				for(i=0; i<NEURON_INPUTS; i++)
				{
					if(ron->inputs[i] != NULL)
					{
						iFirst = i;
						break;
					}
				}
				// find the second non-NULL input
				for(i=iFirst+1; i<NEURON_INPUTS; i++)
				{
					if(ron->inputs[i] != NULL)
					{
						iSecond = i;
						break;
					}
				}
				// if BOTH a first and second VALID input neuron were found,
				if(iFirst != -1 && iSecond != -1)
				{
					// if the neuron's first input is valid,
					if(ron->inputs[iFirst] != NULL)
					{
						// and if the neuron's SECOND input is valid,
						if(ron->inputs[iSecond] != NULL)
						{
							// AND if the divisor is NON-ZERO,
							if(ron->inputs[iSecond]->value + ron->weights[iSecond] != 0.0)
							{
								// finally calculate    (input[0] + weight[0]) / (input[1] + weight[1])
								// in the case of division, the weights act as offsets for each number 
								ron->value = ( ron->inputs[iFirst]->value + ron->weights[iFirst] ) / ( ron->inputs[iSecond]->value + ron->weights[iSecond] );
							}
						}
					}
				}
				// if two valid inputs were not found,
				else
				{
					// output zero
					ron->value = 0;
				}
			}
		break;
		
		
		// exponentiate the sum of all the input neurons
		case nop_exponential:
			// set sum to 0 to start
			sum = 0;
			// for every input
			for(i=0; i<NEURON_INPUTS; i++)
			{
				// if the input neuron is NOT NULL,
				if(ron->inputs[i] != NULL)
				{
					// weight the value of the input-neuron's output and add it to the running total (the sum)
					sum += ron->inputs[i]->value * ron->weights[i];
				}
			}
			// the output of this neuron is equal to the exponential of the sum of the weighted inputs ( e^sum )
			ron->value = exp(sum);
		break;
		
		
		// calculate the sigmoid function of the weighted sum of all non-NULL inputs
		case nop_sigmoid:
			// set sum to 0 to start
			sum = 0;
			// for every input
			for(i=0; i<NEURON_INPUTS; i++)
			{
				// if the input neuron is NOT NULL,
				if(ron->inputs[i] != NULL)
				{
					// weight the value of the input-neuron's output and add it to the running total (the sum)
					sum += ron->inputs[i]->value * ron->weights[i];
				}
			}
			// the output of this neuron is equal to sigmoid function with 
			ron->value = 1.0 / ( 1.0 + exp(-sum) );
		break;
	}
	// if the output value happens to be NaN, just set it to some real value so NaN's don't propagate through the network.
	if(isnan(ron->value)) ron->value = NEURON_NAN_SUBSTITUTE;
	if(isinf(ron->value)) ron->value = NEURON_INFINITY;
	
	
	// success
	return 0;
}




/// this function will evaluate a neural network.
// this function will calculate the neural network moving from the first neuron to the last neuron sequentially.
// this function will create no "propagation delay" in the network.
// It evaluates linearly through the neurons, and then linearly through the outputs.
// NOTE: THIS FUNCTION DOES NOT SET THE INPUT NEURONS. A different function will need to do that.
// returns 0 on success
// returns 1 on a NULL net
// returns 2 if the neuralNetwork has no blockFirst
// returns 3 if the current neuron being evaluated is found to be NULL. Also prints a verbose error to the error log. Bonus!
short nnet_evaluate(struct neuralNetwork *net)
{
	// if the given network is invalid,
	if(net == NULL)
	{
		// log an error
		neural_error_log("nnet_evaluate() could not evaluate neuralNetwork. net = NULL");
		// return error
		return 1;
	}
	// this keeps track of the number of neurons
	NEURON_COUNT_TYPE n;
	// this keeps track of which neural block we are currently evaluating
	struct neuralBlock *blockCurrent;
	// this is a pointer to the current neuron being evaluated
	struct neuron *nc;
	// set b to the first block in the neuralNetwork
	blockCurrent = net->blockFirst;
	if(blockCurrent == NULL)
	{
		// log an error
		neural_error_log("nnet_evaluate() could not evaluate neuralNetwork. net has no blockFirst. blockFirst = NULL");
		// return error
		return 2;
	}
	
	//----------------------------------------------
	// evaluate the internal neurons from first to last (linearly)
	//----------------------------------------------
	
	while(blockCurrent != NULL)
	{
		
		for(n=0; n<NEURONS_PER_BLOCK; n++)
		{
			// save a pointer to the current neuron being evaluated
			nc = &(blockCurrent->neurons[n]);
			// if the current neuron is NULL,
			if(nc == NULL)
			{
				neural_error_log("nnet_evaluate() ran into a NULL nc (current neuron). I don't really think this function should exit this way. The function SHOULD exit when it finds the last neuronBlock. That said, if an neural network has a number of neurons that is not evenly divisible by the neuronBlock size (for whatever fucked up reason that would ever make that necessary) this function could exit this way and it might look like there was a problem when there really wasn't. Whelp, that's all I've got.");
				return 3;
			}
			// evaluate the current neuron
			nnet_evaluate_neuron(nc);
		}
		
		// move to the pointer to point at the next block in the list.
		// if this is null, the while loop will catch it.
		blockCurrent = blockCurrent->blockNext;
	}
	
	for(n=0; n<NEURAL_NETWORK_OUTPUTS; n++)
	{
		nnet_evaluate_neuron(net->outputs[n]);
	}
	
	// success! everything went well apparently. imagine that.
	return 0;
}


/// this will mutate a single neuron from some network
// returns 0 on success
// return 1 on invalid ron
// returns 2 on invalid net
short nnet_mutate_neuron(struct neuron *ron, struct neuralNetwork *net)
{
	if(ron == NULL)
	{
		neural_error_log("nnet_mutate_neuron() failed! ron = NULL!");
		return 1;
	}
	if(net == NULL)
	{
		neural_error_log("nnet_mutate_neuron() failed! net = NULL!");
		return 2;
	}
	
	// this describes the amount of the neuron gets mutated (degree of mutation)
	// this could be very little or a lot
	// this value is from 0 to 100000
	int DOM = rand_ht();
	
	// randomly get a new operation
	if(rand_ht_eval(DOM)) ron->operation = nnet_get_random_operation();
	
	int i;
	// for all inputs
	for(i=0; i<NEURON_INPUTS; i++)
	{
		// randomly,
		if(rand_ht_eval(DOM))
		{
			// change the weight of an input neuron
			ron->weights[i] = nnet_get_random_weight();
			// also randomly change where an input is connected.
			if(rand_ht_eval(DOM))
			{
				if(rand_ht_eval(NEURON_JUMBLE_NULL_CHANCE))
					ron->inputs[i] = NULL;
				else
					ron->inputs[i] = nnet_get_random_neuron(net);
			}
		}
	}
	
	// success
	return 0;
}

/// this will mutate a neural network.
// the mutation rate depends on the neural network itself.
// returns 0 for successful mutation
// return 1 for NULL net
short nnet_mutate(struct neuralNetwork *net)
{
	if(net == NULL)
	{
		neural_error_log("nnet_mutate() failed! net = NULL!");
		return 1;
	}
	
	// randomly change the mutation rate of output neurons
	if(rand_percent(NEURON_MUTATION_RATE_META))
	{
		net->mutationRate = nnet_get_random_mutation_rate();
	}
	
	
	
	/// TODO: write code to mutate a neural network
	
	//----------------------------------------------
	// mutate output neurons 
	//----------------------------------------------
	
	int o;
	// for every output neuron,
	for(o=0; o<NEURAL_NETWORK_OUTPUTS; o++)
	{
		// randomly determin if,
		if(rand_percent(net->mutationRate))
		{
			// this output neuron should be randomized.
			nnet_mutate_neuron(net->outputs[o],net);
		}
	}
	
	//----------------------------------------------
	// mutate internal "hidden" neurons 
	//----------------------------------------------
	struct neuralBlock *cBlock = net->blockFirst;
	
	while(cBlock != NULL)
	{
		// randomly change the mutation rate of this block
		if(rand_percent(NEURON_MUTATION_RATE_META))
		{
			cBlock->mutationRate = nnet_get_random_mutation_rate();
		}
		
		int n;
		// for every neuron in this block,
		for(n=0; n<net->neuronsPerBlock; n++)
		{
			// based on the mutationRate of the block,
			if(rand_percent(cBlock->mutationRate))
			{
				// mutate this neuron
				nnet_mutate_neuron(&(cBlock->neurons[n]),net);
			}
		}
		// move on to the next block
		cBlock = cBlock->blockNext;
	}
	
	//success
	return 0;
}


/// this is a simple function to train neural networks to generate data similarly to how the testData and the testGoal correlate.
// testIn is an array of values to be fed to the input(s) of the neural network
// testOut is an array of values that SHOULD be obtained at the outputs(s) of the neural network for their respective testData inputs.
// testPoints is how many input and output value pairs there are that the function can use to test with
// blocksPerNet is how many neuralBlocks each neuralNetwork will have
// netsPerGen is how many neural networks will be tested side-by-side in the same generation. Current limitation is 1000. I would have to do a decent amount of work to remove get around this limitation.
// trainLinearly: 
	// if this is 0, the neural network will randomly test pairs of input and output data. This forces the neural network not to rely on memory for the next answer.
	// if non-zero, it will test points starting with the first point and ending with the last point. It will test linearly through the testData and the network can learn to rely on its internal memory.
// errorTol is the acceptable amount of error between the perfect output (testOut) and the output that the neuralNetworks generate.
	// this tells us how close the neuralNetwork's results have to be to the desired results.
	// 0.01 is 1%
	// this is an average of all the error for each test point
struct neuralNetwork *nnet_quick_train(NEURON_TYPE *testIn, NEURON_TYPE *testOut, unsigned int testPoints, unsigned int blocksPerNet, unsigned int netsPerGen, char trainLinearly, float errorTol)
{
	
	//----------------------------------------------
	// variable definitions
	//----------------------------------------------
	// maximum possible neuralNetworks per generation
	const int netsPerGenMax = 1000;
	// indexes / for() loop variables
	int i,n,t,o;
	// this keeps track of the minimum average error for neuralNetworks in a generation
	// default to 100% (this makes sure the function enters the while() loop
	float minAverageError = 1;
	
	
	//----------------------------------------------
	// check for errors in input data
	//----------------------------------------------
	if(testIn == NULL)
	{
		neural_error_log("nnet_quick_train() failed! testIn = NULL!");
		return NULL;
	}
	if(testOut == NULL)
	{
		neural_error_log("nnet_quick_train() failed! testOut = NULL!");
		return NULL;
	}
	if(testPoints < 1)
	{
		neural_error_log_d("nnet_quick_train() failed! testPoints less than 1. testPoints = ", testPoints);
		return NULL;
	}
	if(blocksPerNet < 1)
	{
		neural_error_log_d("nnet_quick_train() failed! blocksPerNet less than 1. blocksPerNet = ", blocksPerNet);
		return NULL;
	}
	
	if(netsPerGen < 2 || netsPerGen > netsPerGenMax)
	{
		neural_error_log_d("nnet_quick_train() failed! netsPerGen invalid. netsPerGen = ", netsPerGen);
		return NULL;
	}
	if(errorTol < 0)
	{
		neural_error_log_f("nnet_quick_train() warning: errorTol is negative. This is meant to specify the amount of acceptable error (try positive nubmers). errorTol = ", errorTol);
	}
	
	
	
	//----------------------------------------------
	// create the necessary neural networks (allocate memory for them)
	//----------------------------------------------
	
	// create a structure with pointers to possibly netsPerGenMax neuralNetworks
	struct neuralNetwork *nets[netsPerGenMax];
	// this holds the amount of error each neural network has from the target data for the generation currently being evaluated
	float errors[netsPerGenMax];
	// this tell us which neural networks were the best
	unsigned int order[netsPerGenMax];
	// this keeps track of what the target was supposed to be for an individual network for a single data point
	NEURON_TYPE target, output;
	unsigned int gen = 0;
	
	// set all to NULL for now.
	for(n=0; n<netsPerGenMax; n++)
	{
		nets[n]= NULL;
	}
	
	// attempt to create netsPerGen neuralNetworks.
	for(n=0; n<netsPerGen; n++)
	{
		// attempt to allocate a new neuralNetwork
		nets[n] = nnet_create(blocksPerNet, NEURONS_PER_BLOCK);
		// if a new neuralNetwork could not be created,
		if(nets[n] == NULL)
		{
			// report error
			neural_error_log_d("nnet_quick_train() could not create net! n = ",n);
			neural_error_log("deleting all previous nets and aborting quick_train!");
			// delete all neuralNetworks previously created
			for(n--; n>=0; n--) nnet_destroy(nets[n]);
			// abort quick_train
			return NULL;
		}
	}
	// at this point, we have (netsPerGen number of) neuralNetworks successfully created.
	printf("%d neuralNetworks successfully generated\n",netsPerGen);
	
	
	//----------------------------------------------
	// initially randomize neural networks
	//----------------------------------------------
	
	// for all nets
	for(n=0; n<netsPerGen; n++)
	{
		// jumble the connections, weights, and operations
		nnet_jumble(nets[n]);
	}
	printf("jumbled neuralNetworks\n");
	
	// open a file to print the signals to
	unsigned int printPeriod = 10; // this describes how many generations it takes to print the output data from the network
	FILE *sigOut = fopen("sigOut.txt", "w");
	
	// as long as the minimum average error is less than the specified tolerance, keep evolving those neural networks.
	while(minAverageError > errorTol)
	{
		//----------------------------------------------
		// evaluate each neural network given testIn and testOut
		//----------------------------------------------
		
		// for each neural network
		for(n=0; n<netsPerGen; n++)
		{
			// set all values in the neural network to 0
			nnet_set_values_to_0(nets[n]);
			// set the error to 0
			errors[n] = 0;
			// for each test point
			for(t=0; t<testPoints; t++)
			{
				// for each input of the neuralNetwork
				for(i=0; i<NEURAL_NETWORK_INPUTS; i++)
				{
					// set the input to the value from testIn
					nets[n]->inputs[i]->value = testIn[t*NEURAL_NETWORK_INPUTS+i];
				}
				//nets[n]->outputs[0]->value = 0.5;
				// evaluate the neuralNetwork
				nnet_evaluate(nets[n]);
				
				// for each output of the neuralNetwork
				for(o=0; o<NEURAL_NETWORK_OUTPUTS; o++)
				{
					target = testOut[t*NEURAL_NETWORK_OUTPUTS+o];
					output = nets[n]->outputs[o]->value;
					// calculate output
					errors[n] += square((target - output));
				}
				if(gen%printPeriod == 0 && n==0)  fprintf(sigOut, "%e,",output);
			}
			// calculate the average error per test point
			errors[n] = errors[n] / (testPoints*NEURAL_NETWORK_OUTPUTS);
			
		}
		
		//----------------------------------------------
		// copy and mutate the top performing neuralNetworks
		//----------------------------------------------
		
		printf("Generation %u\n",gen);
		for(n=0; n<netsPerGen; n++)
		{
			printf("errors[%d] = %e\n",n,errors[n]);
		}
		
		// find the nets with the least amount of error
		bubble_sort_f(errors, netsPerGen, order);
		
		// if the average error from the best network is below the threshold
		if(errors[0] < errorTol)
		{
			// we can exit the while() loop
			break;
		}
		
		unsigned int goodNet, badNet;
		//struct neuralBlock *b1, *b2;
		// copy the best half of the neural networks into the worst half's position
		for(n=0; n<netsPerGen/2; n++)
		{
			goodNet = order[n];
			badNet  = order[n+netsPerGen/2];
			//b1 = nets[order[n]]->blockFirst;
			//b2 = nets[order[n+netsPerGen/2]]->blockFirst;
			// copy the good nets into the lesser nets
			nnet_copy(nets[goodNet], nets[badNet]);
			printf("copying %u -> %u\n",goodNet, badNet);
			
			if(gen == 14 && n == 0)
			{
				nnet_save_txt(nets[goodNet], "goodNet2.txt");
				printf("goodNet = %u\nbadNet  = %u\n", goodNet, badNet);
				nnet_save_txt(nets[badNet],  "badNet.txt");
			}
			
			// mutate the copied net
			//nnet_mutate(nets[order[n]]);
			nnet_mutate(nets[order[n+netsPerGen/2]]);
			
			if(gen == 14 && n == 0)
			{
				nnet_save_txt(nets[badNet],  "badNetMut.txt");
			}
		}
		
		if(gen%printPeriod == 0)
		{
			fprintf(sigOut, "\n");
			char myStr[50] = "D:/gen-";
			char numbStr[20];
			itoa(gen,numbStr,10);
			strcat(myStr, numbStr);
			strcat(myStr, ".txt");
			nnet_save_txt(nets[0], myStr);
		}
		
		if(gen%13 == 0 && gen != 0)
		{
			nets[0]->outputs[0]->inputs[0] = nnet_get_enumerated_neuron(nets[0], -1);
			nets[0]->outputs[0]->inputs[1] = NULL;
			nets[0]->outputs[0]->inputs[2] = NULL;
			nets[0]->outputs[0]->inputs[3] = NULL;
			nets[0]->outputs[0]->inputs[4] = NULL;
			nets[0]->outputs[0]->inputs[5] = NULL;
			nets[0]->outputs[0]->inputs[6] = NULL;
			nets[0]->outputs[0]->inputs[7] = NULL;
			nets[0]->outputs[0]->inputs[8] = NULL;
			nets[0]->outputs[0]->inputs[9] = NULL;
			nets[0]->outputs[0]->inputs[10] = NULL;
			nets[0]->outputs[0]->inputs[11] = NULL;
			nets[0]->outputs[0]->inputs[12] = NULL;
			nets[0]->outputs[0]->inputs[13] = NULL;
			nets[0]->outputs[0]->inputs[14] = NULL;
			nets[0]->outputs[0]->inputs[15] = NULL;
			nets[0]->outputs[0]->inputs[16] = NULL;
			nets[0]->outputs[0]->inputs[17] = NULL;
			nets[0]->outputs[0]->inputs[18] = NULL;
			nets[0]->outputs[0]->inputs[19] = NULL;
			nets[0]->outputs[0]->inputs[20] = NULL;
			nets[0]->outputs[0]->inputs[21] = NULL;
			nets[0]->outputs[0]->inputs[22] = NULL;
			nets[0]->outputs[0]->inputs[23] = NULL;
			nets[0]->outputs[0]->inputs[24] = NULL;
			nets[0]->outputs[0]->inputs[25] = NULL;
			nets[0]->outputs[0]->inputs[26] = NULL;
			nets[0]->outputs[0]->inputs[27] = NULL;
			nets[0]->outputs[0]->inputs[28] = NULL;
			nets[0]->outputs[0]->inputs[29] = NULL;
			nets[0]->outputs[0]->weights[0] = 1.3;
			nets[0]->outputs[0]->operation = nop_addition;
			nnet_save_txt(nets[0], "goodNet1.txt");
			
		}
		
		// increment the generation
		gen++;
		
	}// while error is too large
	
	fclose(sigOut);
	
	// return the most fit neural network
	return nets[order[0]];
}




