#pragma once

#include "../../include/common/CommonMaliciousYao.hpp"
#include <libscapi/include/interactive_mid_protocols/CommitmentScheme.hpp>
#include <libscapi/include/infra/Common.hpp>
#include <cereal/archives/xml.hpp>	// for variable name
#include <cereal/types/vector.hpp>	// vector recognition
#include <cereal/types/memory.hpp>  // for smart pointers

/**
 A CommitmentBundle is a struct that holds the parameters pf the commitments on the keys. 

 These parameters are the commitements of all keys, decommitments and the wires indices. 

 The bundle is used during the offline and the online phases of the protocol.
*/
class CommitmentBundle {
private:
	shared_ptr<vector<byte>> commitments;
	shared_ptr<vector<long>> commitmentIds;
	shared_ptr<vector<byte>> decommitments;
	shared_ptr<vector<byte>> decommitmentRandoms;

	int commitmentSize = 20;
	int keySize = 16;

public:

	CommitmentBundle(){}

	/**
	 A constructor that sets the given arguments.
	 Inputs:
		 labels The wires' indices.
		 commitments Commitments on all wires' keys.
		 decommitments Decommitments on all wires' keys.
	*/
	 CommitmentBundle(shared_ptr<vector<byte>> commitmentsVec, shared_ptr<vector<long>> commitmentsIdsVec, shared_ptr<vector<byte>> decommitmentsVec, shared_ptr<vector<byte>> decommitmentRandomsVec);

	 /**
	  A constructor that sets the given arguments.
	  Inputs:
		 labels The wires' indices.
		 commitments Commitments on all wires' keys.
	 */
	 CommitmentBundle(shared_ptr<vector<byte>> commitments, shared_ptr<vector<long>> commitmentIds) {
		 CommitmentBundle(commitments, commitmentIds, NULL, NULL);
	 }

	 /**
	  Returns the commitment that matches the given sigma of the given wire index.
	  Inputs:
		 wireIndex The index of the wire to get the commitment on.
		 sigma A boolean that indicates which commitment to return.
	 */
	CmtCCommitmentMsg* getCommitment(int wireIndex, int sigma) const;

	 /**
	  Returns the decommitment that matches the given sigma of the given wire index.
	  Inputs:
		 wireIndex The index of the wire to get the decommitment on.
		 sigma A boolean that indicates which decommitment to return.
	 */
	 CmtCDecommitmentMessage* getDecommitment(int wireIndex, int sigma);

	
	 shared_ptr<vector<byte>> getCommitments() { return this->commitments; }
	 shared_ptr<vector<long>> getCommitmentsIds() { return this->commitmentIds; }

	 /**
	  Set the commitments of the given wires' indices.
	  Inputs:
		 commitmentsArr two- dimensions array that holds each commitment of each wire's key.
		 labels Indices of the wires.
	 Output:
		 A new created commitment bundle.
	 */
	 static CommitmentBundle setCommitments(shared_ptr<vector<byte>> commitmentsArr, shared_ptr<vector<long>> commitmentIds) {
		 return CommitmentBundle(commitmentsArr, commitmentIds);
	 }

	 /**
	  Verifies that this commitment bundle and the given one are equal.
	  Input:
		 other Another CommitmentBundle to check equality.
	  @throws CheatAttemptException in case the given bundle is different than this one.
	 */
	 bool operator==(const CommitmentBundle& b);

	 // This method lets cereal know which data members to serialize
	 template<class Archive>
	 void serialize(Archive & archive)
	 {
		 // serialize things by passing them to the archive
		 archive(CEREAL_NVP(commitments), CEREAL_NVP(commitmentIds), CEREAL_NVP(decommitments), 
			 CEREAL_NVP(decommitmentRandoms), CEREAL_NVP(commitmentSize), CEREAL_NVP(keySize));
	 }
};