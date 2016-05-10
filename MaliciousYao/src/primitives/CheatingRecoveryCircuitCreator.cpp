#include "../../include/primitives/CheatingRecoveryCircuitCreator.hpp"

/**
Constructor that sets the parameters.
input:
circuitFilename Name of cheating recovery circuit.
inputSize Number of inputs.
*/
CheatingRecoveryCircuitCreator::CheatingRecoveryCircuitCreator(string cFilename, int inSize)
{
	this->circuitFilename = cFilename;
	this->inputSize = inSize;
}
/**
Creates the cheating recovery circuit, if it does not exist.
output:
A garble boolean circuit that represents the cheating recovery circuit.
*/
GarbledBooleanCircuit CheatingRecoveryCircuitCreator::create()
{
	//check if the file exists
	//the file doesn't exists - create it
	if (!boost::filesystem::exists(this->circuitFilename)) {

	}
	
	return GarbledBooleanCircuit();
}
