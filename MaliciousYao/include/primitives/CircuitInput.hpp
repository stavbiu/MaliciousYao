#pragma once

#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <libscapi/include/infra/Common.hpp>
#include <libscapi/include/circuits/GarbledCircuitFactory.hpp>
#include <vector>
#include "../../include/common/Preconditions.hpp"
#include "../../include/common/CommonMaliciousYao.hpp"


using namespace std;

/**
 This class Manages the input of the circuit.

 It contains the wires' indices the input bytes for each wire index.
*/
class CircuitInput : public NetworkSerialized {
private:
	shared_ptr<vector<byte>> input;
	shared_ptr<vector<int>> labels;

public:
	/**
	 A constructor that sets the given input for the given wires.
	 input:
	 inputBits The input for each wire.
	 wireLabels The indices of the wires.
	*/
	CircuitInput(shared_ptr<vector<byte>> inputBits, shared_ptr<vector<int>> wireLabels);

	/**
	 Alternative constructor.
	 It creates new CircuitInput object with the given input and a new wire indices array such as the indices are [0, ..., input.length].
	 input:
		 inputArray  The input for each wire.
		 the created CircuitInput object.
	*/
	static CircuitInput* fromByteArray(shared_ptr<vector<byte>> inputArray);

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
	static CircuitInput* fromFile(string filename, GarbledBooleanCircuit* gbc, int party);

	/**
	 Alternative constructor.
	 It creates new CircuitInput object and sets random inputs.
	  Inputs:
		 labels The indices of the wires.
		 the created CircuitInput object.
	*/
	static CircuitInput* randomInput(shared_ptr<vector<int>> labels);


	// Inherited via NetworkSerialized
	virtual string toString() override;
	virtual void initFromString(const string & raw) override;
};