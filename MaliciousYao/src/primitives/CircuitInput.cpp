#include "../../include/primitives/CircuitInput.hpp"

/**
A constructor that sets the given input for the given wires.
inputBits The input for each wire.
wireLabels The indices of the wires.
*/
CircuitInput::CircuitInput(shared_ptr<byte> inputBits, shared_ptr<int> wireLabels)
{
	
}

string CircuitInput::toString()
{
	return string();
}

void CircuitInput::initFromString(const string & raw)
{
}
