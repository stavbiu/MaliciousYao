#pragma once

#include "../../include/common/CommonMaliciousYao.hpp"
#include <libscapi/include/interactive_mid_protocols/CommitmentScheme.hpp>

/**
* This class represents one commitment in the difference protocol. 
* Each commitment contains commitment message on the random value r and the xor of r and the message x. 
* It also contain the decommitments of the above commitments.
*
* @author Cryptography and Computer Security Research Group Department of Computer Science Bar-Ilan University 
*
*/
class SCom {
private:
	shared_ptr<CmtCCommitmentMsg> c0;				//commitment on x xor r.
	shared_ptr<CmtCCommitmentMsg> c1;				//commitment on  r.		
	shared_ptr<CmtCDecommitmentMessage> d0;			//decommitment on x xor r.
	shared_ptr<CmtCDecommitmentMessage> d1;			//decommitment on r.

public:
	/**
	* A constructor that computes the commitment and decommitment messages of x xor r and r.
	* @param committer Used to commit and decommit the values.
	* @param x The actual value to commit on.
	* @param r The random value used to commit.
	* @param id The first id to use in the commitment.
	* @throws CommitValueException if the given committer cannot commit on a byte[].
	*/
	SCom(CmtCommitter* committer, vector<byte> &x, vector<byte> &r, long id);

	/**
	* Returns the commitment message of x^r.
	*/
	shared_ptr<CmtCCommitmentMsg> getC0() { return this->c0; }

	/**
	* Returns the commitment message of r.
	*/
	shared_ptr<CmtCCommitmentMsg> getC1() { return this->c1; }

	/**
	* Returns the decommitment message of r or x^r according to the given index.
	* @param i Indicates which decommitment to return.
			If i==0, return the decommitment on x^r.
			Else, return the decommitment on r.
	*/
	shared_ptr<CmtCDecommitmentMessage> getDecom(int i) { return (i == 0) ? this->d0 : this->d1; }
};