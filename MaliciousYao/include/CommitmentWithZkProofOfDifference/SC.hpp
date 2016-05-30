#pragma once

#include "../../include/common/CommonMaliciousYao.hpp"
#include "../../include/CommitmentWithZkProofOfDifference/SCom.hpp"

/**
* This class holds the special commitment objects of the difference protocol. 
* This protocol is used in the input consistency check, and reveals the xor of both committed values
* without revealing the committed values themselves.
*
* Each commitment object contains a pair of commitments and pair of related decommitments.
*
* The protocol has multiple commitments according to the security parameter.This class holds all paires of commitments.
*
* @author Cryptography and Computer Security Research Group Department of Computer Science Bar - Ilan University
*
*/
class SC {
private:
	int n;						//Size of the committed value, in bytes.
	int s;						//Security parameter.
	long commitmentId;			//The id of the commitment object. This is given in the constructor and increased 
								//during the creation of the commitments.
								//After creating all commitment objects, it will contain the next available id for the next commitments.
	vector<vector<byte>> r;		//Random values used in the commitment.
	vector<SCom> commitments;			//List of commitment pairs.

public:

	/**
	* A constructor that sets the given parameters.
	* @param committer The commitment protocol to use.
	* @param x The actual committed value.
	* @param id The id of the commitment object. Will be increased during the creation of the commitments.
	* After creating all commitment objects, it will contain the next available id for the next commitments.
	* @param s Security parameter. The number of commitment pairs to create.
	* @param random Source of randomnes to use.
	*/
	SC(CmtCommitter* committer, vector<byte> &x, long id, int s, mt19937* random= &get_seeded_random());

	/**
	* Returns an array of commitment that contains all commitments objects from all pairs.
	*/
	vector<shared_ptr<CmtCCommitmentMsg>> getCommitments();

	/**
	* Returns an array of decommitment that contains all decommitments objects from all pairs.
	*/
	vector<shared_ptr<CmtCDecommitmentMessage>> getDecommitments();

	/**
	* returns the sigma decommitment from pair number i.
	* @param i The index of the commitment pair to get the decommitment from.
	* @param sigma Indicates which decommitment to return. The first of the second.
	*/
	shared_ptr<CmtCDecommitmentMessage> getDecom(int i, int sigma) { return this->commitments[i].getDecom(sigma); }

	/**
	* Returns the random value that placed in index i.
	* @param i The index of the random value to return.
	*/
	vector<byte> getR(int i) { return this->r[i]; }

	/**
	* Return a big array that contain all random values.
	*/
	vector<byte> getR();

	/**
	* Returns the id after creation of all commitments. <p>
	* The id now contain the next available id that can be used for the next commitment.
	*/
	long getNextAvailableCommitmentId() { return this->commitmentId; }
};