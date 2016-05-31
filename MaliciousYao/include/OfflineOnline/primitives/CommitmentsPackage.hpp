#pragma once

#include "../../../include/common/CommonMaliciousYao.hpp"
#include <libscapi/include/interactive_mid_protocols/CommitmentScheme.hpp>

/**
* This package gathering together some objects that should be sent over the offline protocol.
*
* In order to be as fast as we can, we send a group of thing instead of every one of them alone.
*
* @author Cryptography and Computer Security Research Group Department of Computer Science Bar-Ilan University 
*
*/
class CommitmentsPackage: public NetworkSerialized {
	int cmtSize = 20;				//Size of every commitment, in bytes.
	int s;							//Security parameter.

	/**
	* The following arguments related to the commitments: masks, commitments on different wires, ids, etc.
	*/
	shared_ptr<vector<byte>> seedCmt;
	long seedIds;
	shared_ptr<vector<byte>> maskCmt;
	long maskIds;
	shared_ptr<vector<byte>> commitmentsX;
	shared_ptr<vector<long>> commitmentsXIds;
	shared_ptr<vector<byte>> commitmentsY1Extended;
	shared_ptr<vector<long>> commitmentsY1ExtendedIds;
	shared_ptr<vector<byte>> commitmentsY2;
	shared_ptr<vector<long>> commitmentsY2Ids;
	shared_ptr<vector<byte>> commitmentsOutputKeys;
	shared_ptr<vector<byte>> diffCommitments;
	shared_ptr<vector<long>> diffCommitmentsIds;

public:
	/**
	* A constructor that sets the given parameters.
	* @param cmtSize Size of every commitment, in bytes.
	* @param s Security parameter.
	*/
	CommitmentsPackage(int cmtSize, int s);

	
	// Setters and getters for each class member.
	
	void setSeedCmt(CmtCCommitmentMsg* seedCommitment);

	/*
	 Create new CmtCCommitmentMsg.
	*** Caller needs to Delete. ***
	*/
	CmtCCommitmentMsg* getSeedCmt() { //TODO - return new CmtSimpleHashCommitmentMessage(seedCmt, seedIds); 
	}

	void setMaskCmt(CmtCCommitmentMsg* maskCommitment);

	/*
	Create new CmtCCommitmentMsg.
	*** Caller needs to Delete. ***
	*/
	CmtCCommitmentMsg* getMaskCmt() { //TODO - return new CmtSimpleHashCommitmentMessage(maskCmt, maskIds);
	}

	shared_ptr<vector<byte>> getCommitmentsX() { return this->commitmentsX; }

	shared_ptr<vector<long>> getCommitmentXIds() { return this->commitmentsXIds; }

	void setCommitmentsX(shared_ptr<vector<byte>> commitmentsX, shared_ptr<vector<long>> commitmentsXIds);

	shared_ptr<vector<byte>> getCommitmentsY1Extended() { return this->commitmentsY1Extended; }

	shared_ptr<vector<long>> getCommitmentY1ExtendedIds() { return this->commitmentsY1ExtendedIds; }

	void setCommitmentsY1Extended(shared_ptr<vector<byte>> commitmentsY1Extended, shared_ptr<vector<long>> commitmentsY1ExtendedIds);

	shared_ptr<vector<byte>> getCommitmentsY2() { return this->commitmentsY2; }

	shared_ptr<vector<long>> getCommitmentY2Ids() { return this->commitmentsY2Ids; }

	void setCommitmentsY2(shared_ptr<vector<byte>> commitmentsY2, shared_ptr<vector<long>> commitmentsY2Ids);

	/*
	Create and return a CmtCCommitmentMsg from the commitmentsOutputKeys.
	*** Caller needs to Delete. ***
	*/
	CmtCCommitmentMsg* getCommitmentsOutputKeys() {//TODO - return new CmtSimpleHashCommitmentMessage(commitmentsOutputKeys, 0);
	}

	/*
	 Set the given commitmentsX in the commitmentsOutputKeys and commitmentsOutputKeysIds members.
	*/
	void setCommitmentsOutputKeys(CmtCCommitmentMsg* output) {
		//TODO - getCommitment() return shared_ptr<void> need casting to CmtSimpleHashCommitmentMessage
		//this->commitmentsOutputKeys = output->getCommitment();
	}

	/*
	 Create and return a CmtCCommitmentMsg[][] from the diffCommitments and diffCommitmentsIds members.
	 *** Caller needs to Delete. ***
	*/
	vector<vector<CmtCCommitmentMsg*>> getDiffCommitments();

	/*
	 Set the given commitmentsX in the diffCommitments and diffCommitmentsIds members.
	*/
	void setDiffCommitments(vector<vector<CmtCCommitmentMsg*>> diffCommitments);

	// Inherited via NetworkSerialized
	virtual string toString() override;

	virtual void initFromString(const string & raw) override;

};
