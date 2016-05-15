#include "../../include/primitives/CircuitInput.hpp"

/**
A constructor that sets the given input for the given wires.
input:
inputBits The input for each wire.
wireLabels The indices of the wires.
*/
CircuitInput::CircuitInput(shared_ptr<vector<byte>> inputBits, shared_ptr<vector<int>> wireLabels)
{
	// check input is correct
	Preconditions::checkNotZero(inputBits->size());
	Preconditions::checkArgument(inputBits->size() == wireLabels->size());

	this->input = inputBits;
	// check that all the bits are 0 or 1
	for (const auto& b : *inputBits) {
		Preconditions::checkBinary(b);
	}
	this->labels = wireLabels;
}

CircuitInput* CircuitInput::fromByteArray(shared_ptr<vector<byte>> inputArray)
{
	shared_ptr<vector<int>> wireLabels(new vector<int>);

	//Crate an indices array from 0 to inputArray size
	boost::push_back(*wireLabels, boost::irange(0, int(inputArray->size())));

	//Create a new CircuitInput object and return it.
	return new CircuitInput(inputArray, wireLabels);
}

/**
 Alternative constructor.
 It creates new CircuitInput object and read the input from the given file.
 input:
		filename The name of the file to read the inputs from.
		bc The circuit to get the inputs for.
		party the party number which the inputs belongs.
 return:
		the created CircuitInput object.
*/
CircuitInput* CircuitInput::fromFile(string filename, GarbledBooleanCircuit* gbc, int party)
{
	return new CircuitInput(shared_ptr<vector<byte>> (readInputAsVector(filename)), copyVectorToSharedPtr(circuitGetLabels(gbc, party)));
}

/**
 Alternative constructor.
 It creates new CircuitInput object and sets random inputs.
 Inputs:
		labels The indices of the wires.
		 random maker.
 Return:
		the created CircuitInput object.
*/
CircuitInput * CircuitInput::randomInput(shared_ptr<vector<int>> labels, mt19937* mt)
{
	return new CircuitInput(shared_ptr<vector<byte>>(makeRandomBitByteVector(mt, labels->size())), labels);
}

/*
Inherited via NetworkSerialized
*/
string CircuitInput::toString()
{

	//TODO - toString of CircuitInput
	return string();
}

/*
Inherited via NetworkSerialized
*/
void CircuitInput::initFromString(const string & raw)
{
	//TODO - initFromString of CircuitInput
}
