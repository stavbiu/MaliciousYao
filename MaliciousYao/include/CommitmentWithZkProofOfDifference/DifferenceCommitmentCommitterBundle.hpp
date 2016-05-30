#pragma once

#include "../../include/common/CommonMaliciousYao.hpp"
#include "../../include/CommitmentWithZkProofOfDifference/SC.hpp"
#include <libscapi/include/interactive_mid_protocols/CommitmentScheme.hpp>

using namespace std;

/**
* This class used to hold some data of the committer in the difference protocol. <p>
* It is written to a file in the end of the offline phase and read again in the beginning of the online phase. <p>
*
* This bundle holds a value to commit on, the related pair of commitments and the wCommitment which is the
* sigma array generated by the receiver of the protocol.
*
* @author Cryptography and Computer Security Research Group Department of Computer Science Bar-Ilan University (Asaf COhen)
*
*/
class DifferenceCommitmentCommitterBundle {
private:
	shared_ptr<vector<byte>> x;							//The committed value.
	shared_ptr<CmtCCommitmentMsg> wCommitment;			//Sigma array.
	shared_ptr<SC> c;								//The pairs of commitments on the committed value.

public:

	/**
	* A constructor that sets the parameters.
	* @param x The committed value.
	* @param c The pairs of commitments on the committed value.
	* @param wCommitment The sigma array.
	*/
	DifferenceCommitmentCommitterBundle(shared_ptr<vector<byte>> x, shared_ptr<SC> c, shared_ptr<CmtCCommitmentMsg> wCommitment);

	/*
	* Get function for each class member.
	*/
	shared_ptr<vector<byte>> getX() { return this->x; }

	shared_ptr<CmtCCommitmentMsg> getCommitmentToW() {	return this->wCommitment;	}

	shared_ptr<SC> getC() { return this->c; }

};