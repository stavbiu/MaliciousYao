#pragma once

#include <libscapi/include/circuits/GarbledBooleanCircuit.h>
#include <math.h>

using namespace std;

/**
 This class manages the parameters needed by the execution.

 These parameters contain the garbled circuit and boolean circuit used in the protocol, as well as
 protocol parameters described in "Blazing Fast 2PC in the "Offline/Online Setting with Security for
 Malicious Adversaries" paper by Yehuda Lindell and Ben Riva, section 2.4 [Cut-and-Choose Parameters].

 This class contains also the number of evaluated and checked circuits and more.
*/
class ExecutionParameters
{
private:
	GarbledBooleanCircuit* bc;		// The boolean circuit to evaluate in the protocol.
	GarbledBooleanCircuit* gbc;		// Array of garbled circuit from the above boolean circuit.
									// We hold an array of the same circuit because when we use 
									// thread, each one works on a different circuit.
	int numExecutions;				// N
	int statisticalParameter;		// s
	int bucketSize;					// B
	double evaluationProbability;	// p

	int numCircuits;				// N * B
	int evalCircuits;				// N * B / p
	int checkCircuits;				// N * B / p -  N * B

public:
	/*
	 Constructor that sets the parameters.
	*/
	ExecutionParameters(GarbledBooleanCircuit* bc, GarbledBooleanCircuit* mainGbc, 
		int numExecutions, int statisticalParameter, int bucketSize, double evaluationProbability);

	/*
	 Getters
	*/
	GarbledBooleanCircuit* getCircuit() { return this->gbc; }
	int numberOfExecutions() { return this->numExecutions; }
	int bucketSize() { return this->bucketSize; }
	double evaluationProbability() { return this->evaluationProbability; }
	int numCircuits() { return this->numCircuits; }
	int evalCircuits() { return this->evalCircuits; }
	int checkCircuits() { return this->checkCircuits; }
	GarbledBooleanCircuit* getBooleanCircuit() { return this->bc; }
	
};
