#pragma once

#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <libscapi/include/infra/Common.hpp>
#include <libscapi/include/circuits/GarbledCircuitFactory.hpp>
#include <libscapi/include/CryptoInfra/Key.hpp>
#include <vector>
#include "../../include/common/Preconditions.hpp"
#include "../../include/common/CommonMaliciousYao.hpp"


using namespace std;

/**
 This class Manages the input of the circuit.

 It contains the wires' indices the input bytes for each wire index.
*/
class CircuitInput {
private:
	shared_ptr<vector<byte>> input;
	int sizeCircuit;

public:
	/**
	 A constructor that sets the given input for the given wires.
	 input:
	 inputBits The input for each wire.
	 wireLabels The indices of the wires.
	*/
	CircuitInput(shared_ptr<vector<byte>> inputBits);


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
	static CircuitInput* fromFile(string filename);

	/**
	 Alternative constructor.
	 It creates new CircuitInput object and sets random inputs.
	 Inputs:
		 labels The indices of the wires.
		 random maker.
	 Return:
		 the created CircuitInput object.
	*/
	static CircuitInput* randomInput(int sizeCircuit, mt19937* mt);

	/**
	 Alternative constructor. 
	 It creates new CircuitInput object and sets the inputs from the given key.
	 Inputs:
		inputKey The key that used to get the inputs.
	 Return:
		the created CircuitInput object.
	*/
	static CircuitInput* fromSecretKey(SecretKey inputKey);

	/**
	 Returns the size of the inputs.
	*/
	int size() const { return this->sizeCircuit; }

	/**
	 Returns the N'th input bit.
	 Input:
		 n the index of the wire to get the input of.
	*/
	byte getNthBit(int n) { return (*this->input)[n]; }

	/**
	 Return pointer for vector inputs for wires.
	*/
	//vector<byte>* getInputVector() { return this->input.get(); }

	/*
	 Return shared pointer for vector inputs for wires.
	*/
	shared_ptr<vector<byte>> getInputVectorShared() const { return this->input; }

	/**
	 Returns the xor of the inputs in the two given CircuitInputs objects.
	 Inputs:
		 x1 The first input to xor with the other.
		 x2 The second input to xor with the other.
	 Return:
		 the xor result.
	*/
	static vector<byte> xor (const CircuitInput* x1, const CircuitInput* x2);

};