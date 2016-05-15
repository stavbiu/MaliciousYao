#pragma once

#include <libscapi/include/infra/Common.hpp>
#include <vector>

typedef unsigned char byte;

using namespace std;

/**
 This class Manages the input of the circuit.

 It contains the wires' indices the input bytes for each wire index.
*/
class CircuitInput : public NetworkSerialized {
private:
	shared_ptr<byte> input;
	shared_ptr<int> labels;

public:
	/**
	 A constructor that sets the given input for the given wires.
	 inputBits The input for each wire.
	 wireLabels The indices of the wires.
	*/
	CircuitInput(shared_ptr<byte> inputBits, shared_ptr<int> wireLabels);

	// Inherited via NetworkSerialized
	virtual string toString() override;
	virtual void initFromString(const string & raw) override;
};