#include "../../../include/OfflineOnline/primitives/CommitmentsPackage.hpp"

CommitmentsPackage::CommitmentsPackage(int cmtSize, int s)
{
	this->cmtSize = cmtSize;
	this->s = s;
}

void CommitmentsPackage::setSeedCmt(CmtCCommitmentMsg * seedCommitment)
{
	//TODO - seedCommitment->getCommitment() return shared_ptr<void> need casting to CmtSimpleHashCommitmentMessage
	//this->seedCmt = seedCommitment->getCommitment();
	this->seedIds = seedCommitment->getId();
}

void CommitmentsPackage::setMaskCmt(CmtCCommitmentMsg* maskCommitment)
{
	//TODO - seedCommitment->getCommitment() return shared_ptr<void> need casting to CmtSimpleHashCommitmentMessage
	//this->maskCmt = maskCommitment->getCommitment();
	this->maskIds = maskCommitment->getId();
}

void CommitmentsPackage::setCommitmentsX(vector<byte> commitmentsX, vector<long> commitmentsXIds)
{
	this->commitmentsX = commitmentsX;
	this->commitmentsXIds = commitmentsXIds;
}

void CommitmentsPackage::setCommitmentsY1Extended(vector<byte> commitmentsY1Extended, vector<long> commitmentsY1ExtendedIds)
{
	this->commitmentsY1Extended = commitmentsY1Extended;
	this->commitmentsY1ExtendedIds = commitmentsY1ExtendedIds;
}

void CommitmentsPackage::setCommitmentsY2(vector<byte> commitmentsY2, vector<long> commitmentsY2Ids)
{
	this->commitmentsY2 = commitmentsY2;
	this->commitmentsY2Ids = commitmentsY2Ids;
}


vector<vector<CmtCCommitmentMsg>>* CommitmentsPackage::getDiffCommitments()
{
	int size = diffCommitments.size() / (2 * s) / this->cmtSize;
	auto commitments = new vector<vector<CmtCCommitmentMsg>>(size);
	for (int k = 0; k < size; k++) {
		//TODO - CmtSimpleHashCommitmentMessage[] innerComs = new CmtSimpleHashCommitmentMessage[2*s];
		for (int i = 0; i < 2 * s; i++) {
			vector<byte> commitment(this->cmtSize);
			//** System.arraycopy(diffCommitments, k*s * 2 * cmtSize + i*cmtSize, commitment, 0, cmtSize);
			//** innerComs[i] = new CmtSimpleHashCommitmentMessage(commitment, diffCommitmentsIds[k * 2 * s + i]);
		}
		//** commitments[k] = innerComs;
	}

	return commitments;
}

void CommitmentsPackage::setDiffCommitments(vector<vector<CmtCCommitmentMsg>>* diffCommitments)
{
	int size = diffCommitments->size();
	this->diffCommitments = vector<byte>(size * 2 * this->s*this->cmtSize);
	this->diffCommitmentsIds = vector<long>(size * 2 * this->s);

	for (int i = 0; i < size; i++) {
		vector<CmtCCommitmentMsg> com = diffCommitments->at(i);
		int cSize = com.size();
		for (int k = 0; k < cSize; k++) {
			//TODO - System.arraycopy(((CmtSimpleHashCommitmentMessage)com[k]).getCommitment(), 0, this.diffCommitments, i*s * 2 * cmtSize + k*cmtSize, cmtSize);
			this->diffCommitmentsIds[i * 2 * s + k] = com[k].getId();
		}
	}
}

string CommitmentsPackage::toString()
{
	//TODO - toString()
	return string();
}

void CommitmentsPackage::initFromString(const string & raw)
{
	//TODO - initFromString(string raw)
}
