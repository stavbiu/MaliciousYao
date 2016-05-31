#pragma once

#include "../../include/common/CommonMaliciousYao.hpp"
#include "../../include/primitives/CommitmentBundle.hpp"
#include "../../include/CommitmentWithZkProofOfDifference/DifferenceCommitmentCommitterBundle.hpp"
#include "../../include/OfflineOnline/primitives/CommitmentsPackage.hpp"
#include <libscapi/include/circuits/GarbledBooleanCircuit.h>
#include <libscapi/include/CryptoInfra/Key.hpp>

/**
 A bundle is a struct that holds a garbled circuit along with all of the circuit's parameters. 

 These parameters are the input and output keys, translation table, masks, extended keys, commitments on the keys and more. 

 The bundle is used during the offline and the online phases of the protocol.
*/
class Bundle : public NetworkSerialized {
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
	block* outputWires;

	//Commitments on the keys.
	CommitmentBundle* commitmentsX;
	CommitmentBundle* commitmentsY1Extended;
	CommitmentBundle* commitmentsY2;

	SecretKey* secret;

	DifferenceCommitmentCommitterBundle diffCommitments;

	int keySize;	//Size of each key, in bytes.

	CmtCCommitmentMsg* commitment;
	CmtCDecommitmentMessage* decommit;


public:
	/**
	* A constructor.
	*/
	Bundle(vector<byte>& seed, GarbledBooleanCircuit * garbledCircuit, block * wireValues, 
		vector<byte>& placementMask, vector<byte>& commitmentMask, vector<int>& inputLabelsX, 
		vector<int>& inputLabelsY1Extended, vector<int>& inputLabelsY2, vector<int>& outputLabels, 
		vector<byte>& inputWiresX, vector<byte>& inputWiresY1Extended, vector<byte>& inputWiresY2, 
		CommitmentBundle * commitmentsX, CommitmentBundle * commitmentsY1Extended, 
		CommitmentBundle * commitmentsY2, CmtCCommitmentMsg * commitment, CmtCDecommitmentMessage * decommit, 
		SecretKey * secret, int keySize);


	vector<byte> getSeed() { return this->seed; }
		vector<byte> getTranslationTable() { return this->translationTable;	}
	vector<byte> getPlacementMask() { return this->placementMask; }
	vector<byte> getCommitmentMask() {	return this->commitmentMask; }
	vector<int> getInputLabelsX() {	return this->inputLabelsX; }
	vector<int> getInputLabelsY1Extended() { return this->inputLabelsY1Extended; }
	vector<int>getInputLabelsY2() { return this->inputLabelsY2; }
	vector<int> getOutputLabels() { return this->outputLabels; }
	vector<byte> getInputWiresX() { return this->inputWiresX; }
	vector<byte> getInputWiresY1Extended() { return this->inputWiresY1Extended; }
	vector<byte> getInputWiresY2() { return this->inputWiresY2; }
	block* getOutputWires() { return this->outputWires; }
	CommitmentBundle* getCommitmentsX() { return this->commitmentsX; }
	CommitmentBundle* getCommitmentsY1Extended() { return this->commitmentsY1Extended; }
	CommitmentBundle* getCommitmentsY2() { return commitmentsY2; }
	CmtCCommitmentMsg* getCommitmentsOutputKeys() { return this->commitment; }
	CmtCDecommitmentMessage* getDecommitmentsOutputKeys() { return this->decommit; }

	block* getGarbledTables() {
		block* temp = this->garbledTables;
		this->garbledTables = NULL;
		return temp;
	}

	//TODO - getProbeResistantWire() , SecretKeySpec ?
	/*SecretKey* getProbeResistantWire(int wireIndex, int sigma) {
		Preconditions::checkBinary(sigma);
		return new SecretKeySpec(inputWiresY1Extended, (wireIndex * 2 + sigma)*keySize, keySize, "");
	}*/

	/**
	* Put in the commitment package the commitments on X, Y1Extended, Y2 and ouptut keys.
	* @param pack CommitmentsPackage that should be filled with the commitments.
	*/
	void getCommitments(CommitmentsPackage* pack);

	DifferenceCommitmentCommitterBundle getDifferenceCommitmentBundle() { return this->diffCommitments; }

	SecretKey* getSecret() { return this->secret; }


	// Inherited via NetworkSerialized
	virtual string toString() override;

	virtual void initFromString(const string & raw) override;

};