#pragma once


#include <libscapi/include/circuits/GarbledBooleanCircuit.h>

/**
 A bundle is a struct that holds a garbled circuit along with all of the circuit's parameters. 

 These parameters are the input and output keys, translation table, masks, extended keys, commitments on the keys and more. 

 The bundle is used during the offline and the online phases of the protocol.
*/
class Bundle{

public:
	/**
	 This is an inner class that builds the Bundle.
	*/
	static class Builder {
	private:
		vector<byte> seed;

		GarbledBooleanCircuit* garbledCircuit;	// The underlying garbled circuit.
		//****************************************
		//TODO - FastCircuitCreationValues wireValues;		// Output from the garble function.

		//Masks that are used in the protocol.
		vector<byte> placementMask;
		vector<byte> commitmentMask;

		//Indices of x, y1 extended, y2 and output wires.
		vector<int> inputLabelsX;
		vector<int> inputLabelsY1Extended;
		vector<int> inputLabelsY2;
		vector<int> outputLabels;

		//Additional keys besides the above wires' indices.
		vector<byte> inputWiresX;
		vector<byte> inputWiresY1Extended;
		vector<byte> inputWiresY2;
	};
};