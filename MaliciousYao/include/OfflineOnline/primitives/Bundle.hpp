#pragma once

#include "../../../include/common/CommonMaliciousYao.hpp"
#include "../../../include/primitives/CommitmentBundle.hpp"
#include "../../../include/CommitmentWithZkProofOfDifference/DifferenceCommitmentCommitterBundle.hpp"
#include "../../../include/OfflineOnline/primitives/CommitmentsPackage.hpp"
#include "../../../include/common/aligned_allocator_no_destructor.hpp"
#include <libscapi/include/circuits/GarbledBooleanCircuit.h>
#include <libscapi/include/CryptoInfra/Key.hpp>
#include <cereal/archives/xml.hpp>	// for variable name
#include <cereal/types/vector.hpp>	// vector recognition
#include <cereal/types/memory.hpp>  // for smart pointers

/**
 A bundle is a struct that holds a garbled circuit along with all of the circuit's parameters. 

 These parameters are the input and output keys, translation table, masks, extended keys, commitments on the keys and more. 

 The bundle is used during the offline and the online phases of the protocol.
*/
class Bundle : public NetworkSerialized {
private:
	shared_ptr<vector<byte>> seed;
	block* garbledTables;  	// The underlying garbled circuit.
	shared_ptr<vector<byte>> translationTable;			// Output from the garble function.

	//Masks that are used in the protocol.
	shared_ptr<vector<byte>> placementMask;
	shared_ptr<vector<byte>>commitmentMask;

	//Indices of x, y1 extended, y2 and output wires.
	shared_ptr<vector<int>> inputLabelsX;
	shared_ptr<vector<int>> inputLabelsY1Extended;
	shared_ptr<vector<int>> inputLabelsY2;
	shared_ptr<vector<int>> outputLabels;

	//Additional keys besides the above wires' indices.
	shared_ptr<vector<byte>> inputWiresX;
	shared_ptr<vector<byte>> inputWiresY1Extended;
	shared_ptr<vector<byte>> inputWiresY2;
	int numberOfOutputs;
	//unique_ptr<block, aligned_free> outputWires;
	block* outputWires;

	//Commitments on the keys.
	shared_ptr<CommitmentBundle> commitmentsX;
	shared_ptr<CommitmentBundle> commitmentsY1Extended;
	shared_ptr<CommitmentBundle> commitmentsY2;

	shared_ptr<SecretKey> secret;

	shared_ptr<DifferenceCommitmentCommitterBundle> diffCommitments;

	int keySize;	//Size of each key, in bytes.

	shared_ptr<CmtCCommitmentMsg> commitment;
	shared_ptr<CmtCDecommitmentMessage> decommit;


public:
	//Bundle():outputWires(nullptr){}
	Bundle(){}

	/**
	* A constructor.
	*/
	Bundle(shared_ptr<vector<byte>> seed, GarbledBooleanCircuit * garbledCircuit, block * wireValues, int numberOfOutputs,
		shared_ptr<vector<byte>> placementMask, shared_ptr<vector<byte>> commitmentMask, shared_ptr<vector<int>> inputLabelsX,
		shared_ptr<vector<int>> inputLabelsY1Extended, shared_ptr<vector<int>> inputLabelsY2, shared_ptr<vector<int>> outputLabels,
		shared_ptr<vector<byte>> inputWiresX, shared_ptr<vector<byte>> inputWiresY1Extended, shared_ptr<vector<byte>> inputWiresY2,
		shared_ptr<CommitmentBundle> commitmentsX, shared_ptr<CommitmentBundle> commitmentsY1Extended,
		shared_ptr<CommitmentBundle> commitmentsY2, shared_ptr<CmtCCommitmentMsg> commitment, shared_ptr< CmtCDecommitmentMessage> decommit,
		shared_ptr<SecretKey> secret, int keySize);

	/*
	* A distructor.
	*/
	~Bundle() {
		_aligned_free(this->outputWires);
	}

	shared_ptr<vector<byte>> getSeed() { return this->seed; }
	shared_ptr<vector<byte>> getTranslationTable() { return this->translationTable;	}
	shared_ptr<vector<byte>> getPlacementMask() { return this->placementMask; }
	shared_ptr<vector<byte>> getCommitmentMask() {	return this->commitmentMask; }
	shared_ptr<vector<int>> getInputLabelsX() {	return this->inputLabelsX; }
	shared_ptr<vector<int>> getInputLabelsY1Extended() { return this->inputLabelsY1Extended; }
	shared_ptr<vector<int>>getInputLabelsY2() { return this->inputLabelsY2; }
	shared_ptr<vector<int>> getOutputLabels() { return this->outputLabels; }
	shared_ptr<vector<byte>> getInputWiresX() { return this->inputWiresX; }
	shared_ptr<vector<byte>> getInputWiresY1Extended() { return this->inputWiresY1Extended; }
	shared_ptr<vector<byte>> getInputWiresY2() { return this->inputWiresY2; }
	//unique_ptr<block> getOutputWires() { return this->outputWires; }
	block getOutputWiresAt(int index) { return this->outputWires[index]; }
	shared_ptr<CommitmentBundle> getCommitmentsX() { return this->commitmentsX; }
	shared_ptr<CommitmentBundle> getCommitmentsY1Extended() { return this->commitmentsY1Extended; }
	shared_ptr<CommitmentBundle> getCommitmentsY2() { return commitmentsY2; }
	shared_ptr<CmtCCommitmentMsg> getCommitmentsOutputKeys() { return this->commitment; }
	shared_ptr<CmtCDecommitmentMessage> getDecommitmentsOutputKeys() { return this->decommit; }

	block* getGarbledTables() {
		//TODO - check delete
		/*block* temp = this->garbledTables;
		this->garbledTables = NULL;
		return temp;*/
		return this->garbledTables;
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
	void getCommitments(shared_ptr<CommitmentsPackage> pack);

	void setDifferenceCommitmentBundle(shared_ptr<DifferenceCommitmentCommitterBundle> bundle) { this->diffCommitments = bundle; }

	shared_ptr<DifferenceCommitmentCommitterBundle> getDifferenceCommitmentBundle() { return this->diffCommitments; }

	shared_ptr<SecretKey> getSecret() { return this->secret; }


	// Inherited via NetworkSerialized
	virtual string toString() override;

	virtual void initFromString(const string & raw) override;

	// This method lets cereal know which data members to save to file
	template<class Archive>
	void save(Archive & archive) const;

	// This method lets cereal know which data members to load to file
	template<class Archive>
	void load(Archive & archive);
};

template<class Archive>
inline void Bundle::save(Archive & archive) const
{
	//in order to send ouptutWires - block*, we need to make vector byte and send it.
	int byteNum = SIZE_OF_BLOCK * 2 * this->numberOfOutputs;
	byte* temp = (byte*)outputWires;
	//make byte vector of block*
	vector<byte> outputWiresToSend(temp, temp + byteNum);

	// serialize things by passing them to the archive
	archive(CEREAL_NVP(seed), CEREAL_NVP(placementMask), CEREAL_NVP(commitmentMask),
		CEREAL_NVP(inputLabelsX), CEREAL_NVP(inputLabelsY1Extended), CEREAL_NVP(inputLabelsY2),
		CEREAL_NVP(outputLabels), CEREAL_NVP(commitmentsX), CEREAL_NVP(commitmentsY1Extended),
		CEREAL_NVP(commitmentsY2), CEREAL_NVP(diffCommitments), CEREAL_NVP(keySize), CEREAL_NVP(numberOfOutputs)
		, CEREAL_NVP(outputWiresToSend));

	//TODO - add , CEREAL_NVP(secret) when SecretKey will have serialize
	//TODO - add serialize when CmtCCommitmentMsg and CmtCDecommitmentMessage will have it.
	// CEREAL_NVP(commitment), CEREAL_NVP(decommit),
}

template<class Archive>
inline void Bundle::load(Archive & archive)
{
	//read outputWires to vector<byte> align to 16 with no destractor
	vector<byte, aligned_allocator_no_destructor<byte, SIZE_OF_BLOCK>> readOutputWires;

	// serialize things by passing them to the archive
	archive(CEREAL_NVP(seed), CEREAL_NVP(placementMask), CEREAL_NVP(commitmentMask),
		CEREAL_NVP(inputLabelsX), CEREAL_NVP(inputLabelsY1Extended), CEREAL_NVP(inputLabelsY2),
		CEREAL_NVP(outputLabels), CEREAL_NVP(commitmentsX), CEREAL_NVP(commitmentsY1Extended),
		CEREAL_NVP(commitmentsY2), CEREAL_NVP(diffCommitments), CEREAL_NVP(keySize), CEREAL_NVP(numberOfOutputs)
		, CEREAL_NVP(readOutputWires));

	//convert from vector<byte> to block*
	block* readTest = (block*)&readOutputWires[0];

	//TODO - add , CEREAL_NVP(secret) when SecretKey will have serialize
	//TODO - add serialize when CmtCCommitmentMsg and CmtCDecommitmentMessage will have it.
	// CEREAL_NVP(commitment), CEREAL_NVP(decommit),

}
