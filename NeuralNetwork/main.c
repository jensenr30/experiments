#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "neural_network.h"
#include "custom_math.h"
#include "rand.h"


int main()
{
	// seed the random number generator
	sgenrand(time(NULL));
	
	//-----------------------------------------------
	// test neural network functions and stuff
	//-----------------------------------------------
	
	unsigned int blocks = 1;
	
	// create a neural network
	struct neuralNetwork *myNet = nnet_create(blocks, NEURONS_PER_BLOCK);
	
	
	// count the neurons
	printf("Counting Neurons... total neurons = %lu\n\n", (long unsigned)nnet_count_neurons(myNet));
	
	
	// test getting a neuron
	printf("Getting enumerated neuron... ");
	struct neuron *myNeuron = nnet_get_enumerated_neuron(myNet, 40);
	if(myNeuron != NULL)
	{
		printf("Got neuron.\n");
	}
	else
	{
		printf("Did not gen neuron!\n");
	}
	
	// attempt to jumble the network
	//nnet_jumble(myNet);
	/*
	// test getting all neurons
	int i,j;
	for(i=0; i<NEURONS_PER_BLOCK; i++)
	{
		// get neuron
		myNeuron = nnet_get_enumerated_neuron(myNet, i);
		if(myNeuron == &(myNet->blockFirst->neurons[i]))
		{
			printf("Got neuron %3d get_addr %3ld | ", i, (long int)myNeuron->address);
			// print each of the neuron's inputs' addresses.
			for(j=0; j<NEURON_INPUTS; j++)
			{
				if(myNeuron->inputs[j] != NULL)
					printf("%3ld ", (long int)myNeuron->inputs[j]->address);
				else
					printf("  ~ ");
				
			}
			printf("\n");
		}
		else
		{
			printf("DID NOT GET NEURON %d!\n", i);
		}
	}
	
	printf("\nNEURON_INFINITY = %e\n",NEURON_INFINITY);
	printf("NEGATIVE_NEURON_INFINITY = %e\n",-NEURON_INFINITY);
	*/
	
	/*
	
	//-----------------------------------------------
	// test the neural network operations
	//-----------------------------------------------
	
	// get a neuron in myNet
	myNeuron = nnet_get_enumerated_neuron(myNet, 0);
	
	if(myNeuron != &myNet->blockFirst->neurons[0])
	{
		printf("could not get enumerated neuron");
		return 56;
	}
	// set neuron 1 to have 
	myNeuron->inputs[0] = nnet_get_enumerated_neuron(myNet, 1);
	myNeuron->inputs[1] = nnet_get_enumerated_neuron(myNet, 2);
	myNeuron->inputs[2] = nnet_get_enumerated_neuron(myNet, 3);
	myNeuron->inputs[3] = nnet_get_enumerated_neuron(myNet, 4);
	myNeuron->inputs[4] = nnet_get_enumerated_neuron(myNet, 5);
	myNeuron->inputs[5] = nnet_get_enumerated_neuron(myNet, 6);
	myNeuron->inputs[6] = nnet_get_enumerated_neuron(myNet, 7);
	myNeuron->inputs[7] = nnet_get_enumerated_neuron(myNet, 8);
	
	myNeuron->inputs[0]->value = 1;
	myNeuron->inputs[1]->value = 2;
	myNeuron->inputs[2]->value = 3;
	myNeuron->inputs[3]->value = 4;
	myNeuron->inputs[4]->value = 5;
	myNeuron->inputs[5]->value = 6;
	myNeuron->inputs[6]->value = 7;
	myNeuron->inputs[7]->value = 8;
	
	myNeuron->weights[0] = 1;
	myNeuron->weights[1] = 1;
	myNeuron->weights[2] = 1;
	myNeuron->weights[3] = 1;
	myNeuron->weights[4] = 1;
	myNeuron->weights[5] = 1;
	myNeuron->weights[6] = 1;
	myNeuron->weights[7] = 1;
	
	myNeuron->operation = nop_exponential;
	
	int retVal = nnet_evaluate(myNet);
	
	printf("\nnnet_evaluate() returned %d.\nCalculated output value is %f\n", retVal, myNeuron->value);
	
	
	*/
	/*
	//-----------------------------------------------
	// the following block of code tests iterative evaluation of the network
	//-----------------------------------------------
	int n;
	FILE *testData = fopen("testData.txt", "w");
	if(testData != NULL)
	{
		// print the initial value of this single neuron
		fprintf(testData, "%14e,", myNet->blockFirst->neurons[8].value);
		// do a bunch of iterations of evaluating the network
		for(i=0; i<1000; i++)
		{
			// evaluate the network
			nnet_evaluate(myNet);
			// loop through the first 32 neurons
			for(n=0; n<32; n++)
			{
				// print the value of the neuron
				fprintf(testData, "%14e,", myNet->blockFirst->neurons[n].value);
				//if(isnan(myNet->blockFirst->neurons[n].value)) fprintf(testData, "    wasnan    ,");
			}
			fprintf(testData, "\n");
		}
		fclose(testData);
	}
	*/
	
	//----------------------------------------------
	// test bubble sort
	//----------------------------------------------
	/*
	int N = 500;
	float ran[N], ranOrig[N];
	unsigned int ord[N];
	int j;
	for(j=0; j<N; j++)
	{
		ran[j] = (rand()%100) / (float)(rand()%100 + 1);
		ranOrig[j] = ran[j];
		printf("%f\t%d\n",ran[j],j);
	}
	
	printf("\n\n");
	
	// sort the data
	if(!bubble_sort_f(ran, N, ord))	{ printf("sorted correctly!\n\n\n"); }
	else 						{ printf("sort failed!\n\n\n"); }
	
	for(j=0; j<N; j++)
	{
		printf("%f\t%2u\t",ran[j],ord[j]);
		if(ran[j] == ranOrig[ord[j]])	printf(".\n");
		else 						printf("X\n");
	}
	
	
	return 0;
	*/
	
	/*
	//----------------------------------------------
	// test get_rand_mutation_rate
	//----------------------------------------------
	int j;
	for(j=0; j<100; j++)
		printf("%e\n",nnet_get_random_mutation_rate());
	*/
	
	/*
	//----------------------------------------------
	// test nnet_copy
	//----------------------------------------------
	
	struct neuralNetwork *myCopy = nnet_create(4, NEURONS_PER_BLOCK);
	
	nnet_copy(myNet, myCopy);
	
	nnet_save_txt(myNet, "myNet.txt");
	nnet_save_txt(myCopy, "myCopy.txt");
	
	nnet_destroy(myNet);
	nnet_destroy(myCopy);
	return 0;
	*/
	
	/*
	// test random percentage
	int j; for(j=0;j<100;j++) printf("%c\n",46 + rand_percent(0.1)*(88-46));
	*/
	
	/*
	// test mutation
	nnet_save_txt(myNet, "myNet.txt");
	nnet_mutate(myNet);
	nnet_save_txt(myNet, "myNetMut.txt");
	*/
	
	//----------------------------------------------
	// attempt to train a neural network to approximate the sin() function
	//----------------------------------------------
	
	// set up test data
	int trainingPoints = 500;
	NEURON_TYPE trainIn[trainingPoints];
	NEURON_TYPE trainOut[trainingPoints];
	int i;
	NEURON_TYPE pi = 3.1415926;
	
	FILE *sigOrig = fopen("sigOrig.txt", "w");
	
	// set up the training points
	for(i=0; i<trainingPoints; i++)
	{
		// input range is from -2pi to +2pi
		trainIn[i] = -2*pi + 4*pi*(i/(float)(trainingPoints-1));
		// target output function is sin(x)
		//trainOut[i] = sin(trainIn[i]);
		// target function is just x
		trainOut[i] = trainIn[i];
		fprintf(sigOrig, "%e,", trainOut[i]);
	}
	
	fclose(sigOrig);
	
	//test to make sure the input neuron can be read by the output neuron directly
	myNet->inputs[0]->value = 333.0;
	myNet->outputs[0]->inputs[0] = nnet_get_enumerated_neuron(myNet, -1);
	myNet->outputs[0]->inputs[1] = NULL;
	myNet->outputs[0]->inputs[2] = NULL;
	myNet->outputs[0]->inputs[3] = NULL;
	myNet->outputs[0]->inputs[4] = NULL;
	myNet->outputs[0]->inputs[5] = NULL;
	myNet->outputs[0]->inputs[6] = NULL;
	myNet->outputs[0]->inputs[7] = NULL;
	myNet->outputs[0]->weights[0] = 1.5;
	myNet->outputs[0]->operation = nop_addition;
	nnet_evaluate(myNet);
	printf("output = %e\n", myNet->outputs[0]->value);
	nnet_save_txt(myNet, "myNet.txt");
	
	
	
	// attempt to create a network that approximates the sin() function
	struct neuralNetwork *sinNet = nnet_quick_train(trainIn, trainOut, trainingPoints, 1, 20, 0, 0.001);
	
	// print neural network to file
	nnet_save_txt(sinNet, "sinNet.txt");
	
	
	
	// destroy the neural network(s)
	nnet_destroy(myNet);
	nnet_destroy(sinNet);
	
	return 0;
}
