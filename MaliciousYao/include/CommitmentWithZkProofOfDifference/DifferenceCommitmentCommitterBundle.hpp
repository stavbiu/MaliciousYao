#pragma once

#include "../../include/common/CommonMaliciousYao.hpp"
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
	vector<byte> x;							//The committed value.
	CmtCCommitmentMsg* wCommitment;			//Sigma array.
	//TODO - SC c;								//The pairs of commitments on the committed value.

public:

};