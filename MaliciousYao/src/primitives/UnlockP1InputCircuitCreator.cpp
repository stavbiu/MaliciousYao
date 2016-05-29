#include "../../include/primitives/UnlockP1InputCircuitCreator.hpp"

/**
Puts the indices of the input wires in the array.
input:
currentLabel first index.
return:
the last index.
*/
int UnlockP1InputCircuitCreator::calculateInputLabels(int currentLabel)
{
	for (int i = 0; i < this->numberOfParties; i++) {
		vector<int>* partyLabels = new vector<int>(numberOfInputWires[i]);
		for (int j = 0; j < this->numberOfInputWires[i]; j++) {
			(*partyLabels)[j] = currentLabel;
			currentLabel++;
		}
		this->inputLabels.push_back(*partyLabels);
	}
	return currentLabel;
}

/**
Puts the indices of the output wires in the array.
input:
currentLabel first index.
return:
the last index.
*/
int UnlockP1InputCircuitCreator::calculateOutputLabels(int currentLabel)
{
	for (int i = 0; i < this->numberOfOutputWires; i++) {
		this->outputLabels.push_back(currentLabel);
		currentLabel++;
	}
	return currentLabel;
}


/**
Constructor that sets the parameters and fill internal members.
input:
	filename The name of the file to create.
	numInputWiresP1 The number of inputs of P1.
*/
UnlockP1InputCircuitCreator::UnlockP1InputCircuitCreator(string setfilename, int numInputWiresP1)
{
	this->filename = setfilename;
	this->numberOfParties = 2;
	this->numberOfInputWires = new int[this->numberOfParties];
	this->numberOfInputWires[0] = numInputWiresP1;	// One wire per one input bit of P1
	this->numberOfInputWires[1] = 1;	// This is the "master" wire that may or may not unlock P1's input.
	this->numberOfGates = numInputWiresP1;	// One AND gate for each input wire of P1.
	this->numberOfOutputWires = numInputWiresP1; // One output wire for each input wire of P1.
	this->masterKeyLabel = numInputWiresP1 + 1;
}

/**
Creates the circuit recovery file.
*/
void UnlockP1InputCircuitCreator::create()
{
	int currentLabel = 1;
	//Sets the input and output wires indices.
	currentLabel = calculateInputLabels(currentLabel);
	currentLabel = calculateOutputLabels(currentLabel);

	//open file
	ofstream outfile(this->filename);

	//Write the number of gates and parties.
	outfile << this->numberOfGates << endl << this->numberOfParties << endl;

	// Input wires section.
	for (int i = 0; i < this->numberOfParties; i++) {
		// The labeling of parties starts from "1".
		int partyLabel = i + 1;

		// The party's label, followed by how much input wires it has, followed by the indices of the input wires.
		outfile << partyLabel << " " << this->numberOfInputWires[i] << endl;

		// The party's input wires' labels.
		auto inputLabelsForThisParty = this->inputLabels[i];
		for (const auto& j : inputLabelsForThisParty) {
			outfile << j << endl;
		}
		outfile << endl;

		// Output wires section.
		// The number of output wires, followed by the indices of the output wires.
		outfile << this->numberOfOutputWires << endl;
		for (const auto& j : this->outputLabels) {
			outfile << j << endl;
		}
		outfile << endl;
	}

	// Gates section.
	int numInputsWiresForGate = 2;
	int numOutputsWiresForGate = 1;
	string truthTableANDGate("0001");
	auto inputLabelsP1 = this->inputLabels[0];

	//For each gate, print the number of inputs of this gate, number of outputs of this gate, 
	//indices of input wires, indices of output wires and the gate truth table. 
	int sizeNum = inputLabelsP1.size();

	for (int i = 0; i < sizeNum; i++) { // inputLabelsP1.size() == outputLabels.size() == numberOfGates
		outfile << numInputsWiresForGate << " " << numOutputsWiresForGate << " " << inputLabelsP1[i] <<
			" " << this->masterKeyLabel << " " << this->outputLabels[i] << " " << truthTableANDGate << endl;
	}

	//close file
	outfile.close();
}
