#include "../../include/primitives/ExecutionParameters.hpp"

/*
Constructor that sets the parameters.
*/
ExecutionParameters::ExecutionParameters(GarbledBooleanCircuit * bc, GarbledBooleanCircuit * mainGbc, int numExecutions, int statisticalParameter, int bucketSize, double evaluationProbability)
{
	this->bc = bc;
	this->gbc = mainGbc;
	this->numExecutions = numExecutions;	//N
	this->statisticalParameter = statisticalParameter;	//s
	this->bucketSize = bucketSize;	//B
	this->evaluationProbability = evaluationProbability; //P

	this->evalCircuits = numExecutions * bucketSize;
	this->numCircuits = ceil(evalCircuits / evaluationProbability);
	this->checkCircuits = numCircuits - evalCircuits;
}
