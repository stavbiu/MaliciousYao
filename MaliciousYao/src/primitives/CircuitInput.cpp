#include "../../include/primitives/CircuitInput.hpp"

/**
A constructor that sets the given input for the given wires.
input:
inputBits The input for each wire.
wireLabels The indices of the wires.
*/
CircuitInput::CircuitInput(shared_ptr<vector<byte>> inputBits)
{
	// check input is correct
	Preconditions::checkNotZero(inputBits->size());

	this->input = inputBits;
	// check that all the bits are 0 or 1
	for (const auto& b : *inputBits) {
		Preconditions::checkBinary(b);
	}

	this->sizeCircuit = inputBits->size();
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
CircuitInput* CircuitInput::fromFile(string filename)
{
	return new CircuitInput(shared_ptr<vector<byte>> (readInputAsVector(filename)));
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
CircuitInput * CircuitInput::randomInput(int sizeCircuit, mt19937* mt)
{
	return new CircuitInput(shared_ptr<vector<byte>>(makeRandomBitByteVector(mt, sizeCircuit)));
}

/**
Alternative constructor.
It creates new CircuitInput object and sets the inputs from the given key.
Inputs:
inputKey The key that used to get the inputs.
Return:
the created CircuitInput object.
*/
CircuitInput * CircuitInput::fromSecretKey(SecretKey inputKey)
{
	shared_ptr<vector<byte>> inputBinaryArray(getBinaryByteArray(inputKey.getEncoded()));

	//Create a new CircuitInput object from the inputs and indices arrays and return it.
	return new CircuitInput(inputBinaryArray);
}


/**
Returns the xor of the inputs in the two given CircuitInputs objects.
Inputs:
	x1 The first input to xor with the other.
	x2 The second input to xor with the other.
Return:
	the xor result.
*/
vector<byte> CircuitInput:: xor (CircuitInput* x1, CircuitInput* x2)
{
	//Check if the sizes of inputs are equal.
	Preconditions::checkArgument(x1->size() == x2->size());

	int sizeCir = x1->size();
	shared_ptr<vector<byte>> vec1 = x1->getInputVectorShared();
	shared_ptr<vector<byte>> vec2 = x2->getInputVectorShared();
	vector<byte> res(sizeCir);

	// Xor the inputs arrays.
	for (int i = 0 ; i < sizeCir ; i++) {
		res[i] = byte(vec1->at(i) ^ vec2->at(i));
	}

	return res;
}
