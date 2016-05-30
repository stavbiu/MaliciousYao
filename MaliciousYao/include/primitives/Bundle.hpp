#pragma once

#include "../../include/common/CommonMaliciousYao.hpp"
#include "../../include/primitives/CommitmentBundle.hpp"
#include <libscapi/include/circuits/GarbledBooleanCircuit.h>
#include <libscapi/include/CryptoInfra/Key.hpp>

/**
 A bundle is a struct that holds a garbled circuit along with all of the circuit's parameters. 

 These parameters are the input and output keys, translation table, masks, extended keys, commitments on the keys and more. 

 The bundle is used during the offline and the online phases of the protocol.
*/
class Bundle{
private:
	vector<byte> seed;
	block* garbledTables;  	// The underlying garbled circuit.
	vector<byte> translationTable;			// Output from the garble function.

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
	vector<byte> outputWires;

	//Commitments on the keys.
	CommitmentBundle* commitmentsX;
	CommitmentBundle* commitmentsY1Extended;
	CommitmentBundle* commitmentsY2;

	SecretKey* secret;

	//TODO - DifferenceCommitmentCommitterBundle diffCommitments;

	int keySize;	//Size of each key, in bytes.

	CmtCCommitmentMsg* commitment;
	CmtCDecommitmentMessage* decommit;

public:
	
};