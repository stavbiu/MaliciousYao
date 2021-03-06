#include "../../../include/OfflineOnline/primitives/CommitmentsPackage.hpp"

CommitmentsPackage::CommitmentsPackage(int cmtSize, int s)
{
	this->cmtSize = cmtSize;
	this->s = s;
}

void CommitmentsPackage::setSeedCmt(CmtCCommitmentMsg * seedCommitment)
{
	this->seedCmt = std::static_pointer_cast<vector<byte>>(seedCommitment->getCommitment());
	this->seedIds = seedCommitment->getId();
}

void CommitmentsPackage::setMaskCmt(CmtCCommitmentMsg* maskCommitment)
{
	this->maskCmt = std::static_pointer_cast<vector<byte>>( maskCommitment->getCommitment());
	this->maskIds = maskCommitment->getId();
}

void CommitmentsPackage::setCommitmentsX(shared_ptr<vector<byte>> commitmentsX, shared_ptr<vector<long>> commitmentsXIds)
{
	this->commitmentsX = commitmentsX;
	this->commitmentsXIds = commitmentsXIds;
}

void CommitmentsPackage::setCommitmentsY1Extended(shared_ptr<vector<byte>> commitmentsY1Extended, shared_ptr<vector<long>> commitmentsY1ExtendedIds)
{
	this->commitmentsY1Extended = commitmentsY1Extended;
	this->commitmentsY1ExtendedIds = commitmentsY1ExtendedIds;
}

void CommitmentsPackage::setCommitmentsY2(shared_ptr<vector<byte>> commitmentsY2, shared_ptr<vector<long>> commitmentsY2Ids)
{
	this->commitmentsY2 = commitmentsY2;
	this->commitmentsY2Ids = commitmentsY2Ids;
}


vector<vector<CmtCCommitmentMsg*>> CommitmentsPackage::getDiffCommitments()
{
	int size = diffCommitments->size() / (2 * s) / this->cmtSize;
	vector<vector<CmtCCommitmentMsg*>> commitments (size);
	for (int k = 0; k < size; k++) {
		vector<CmtCCommitmentMsg*> innerComs(2 * s);
		for (int i = 0; i < 2 * s; i++) {
			shared_ptr<vector<byte>> commitment(new vector<byte>(this->cmtSize));
			memcpy(&commitment->at(0), &diffCommitments->at(k*s * 2 * cmtSize + i*cmtSize), cmtSize);
			innerComs[i] = new CmtSimpleHashCommitmentMessage(commitment, diffCommitmentsIds->at(k * 2 * s + i));
		}
		commitments[k] = innerComs;
	}

	return commitments;
}

void CommitmentsPackage::setDiffCommitments(vector<vector<CmtCCommitmentMsg*>> diffCommitments)
{
	int size = diffCommitments.size();
	this->diffCommitments = shared_ptr<vector<byte>>(new vector<byte>(size * 2 * this->s*this->cmtSize));
	this->diffCommitmentsIds = shared_ptr<vector<long>>(new vector<long>(size * 2 * this->s));

	for (int i = 0; i < size; i++) {
		vector<CmtCCommitmentMsg*> com = diffCommitments[i];
		int cSize = com.size();
		for (int k = 0; k < cSize; k++) {
			memcpy(&(this->diffCommitments->at(i*s * 2 * cmtSize + k*cmtSize)), 
				&(static_pointer_cast<vector<byte>>(com[k]->getCommitment())->at(0)), cmtSize);
			this->diffCommitmentsIds->at(i * 2 * s + k) = com[k]->getId();
		}
	}
}

/*
string CommitmentsPackage::toString()
{
	//save evrey data as string in a vector
	vector<string> vecS(14);
	vecS[0] = vectorToString(this->seedCmt.get(), ' ');
	vecS[1] = std::to_string(this->seedIds);
	vecS[2] = vectorToString(this->maskCmt.get(), ' ');
	vecS[3] = std::to_string(this->maskIds);
	vecS[4] = vectorToString(this->commitmentsX.get(), ' ');
	vecS[5] = vectorToString(this->commitmentsXIds.get(), ' ');
	vecS[6] = vectorToString(this->commitmentsY1Extended.get(), ' ');
	vecS[7] = vectorToString(this->commitmentsY1ExtendedIds.get(), ' ');
	vecS[8] = vectorToString(this->commitmentsY2.get(), ' ');
	vecS[9] = vectorToString(this->commitmentsY2Ids.get(), ' ');
	vecS[10] = vectorToString(this->commitmentsOutputKeys.get(), ' ');
	vecS[11] = vectorToString(this->diffCommitments.get(), ' ');
	vecS[12] = vectorToString(this->diffCommitmentsIds.get(), ' ');
	vecS[13] = std::to_string(this->cmtSize);
	vecS[14] = std::to_string(this->s);

	string res;
	//make one vector separated by ";"
	/*for (int i = 0; i < 12; i++) {
		res += vecS[i] + ';';
	}
	//last elemant
	res += vecS[12];*//*
	char temp = ';';
	res = vectorToString(vecS, &temp);

	return res;
}
*//*
void CommitmentsPackage::initFromString(const string & raw)
{
	//separate string by ";"
	auto fromStr = readStringVectorFromString(raw, ';');
	//get every data
	this->seedCmt = shared_ptr<vector<byte>>(&readByteVectorFromString(fromStr[0], ' '));
	this->seedIds = std::stol(fromStr[1]);
	this->maskCmt = shared_ptr<vector<byte>>(&readByteVectorFromString(fromStr[2], ' '));
	this->maskIds = std::stol(fromStr[3]);
	this->commitmentsX = shared_ptr<vector<byte>>(&readByteVectorFromString(fromStr[4], ' '));
	this->commitmentsXIds = shared_ptr<vector<long>>(&readLongVectorFromString(fromStr[5], ' '));
	this->commitmentsY1Extended = shared_ptr<vector<byte>>(&readByteVectorFromString(fromStr[6], ' '));
	this->commitmentsY1ExtendedIds = shared_ptr<vector<long>>(&readLongVectorFromString(fromStr[7], ' '));
	this->commitmentsY2 = shared_ptr<vector<byte>>(&readByteVectorFromString(fromStr[8], ' '));
	this->commitmentsY2Ids = shared_ptr<vector<long>>(&readLongVectorFromString(fromStr[9], ' '));
	this->commitmentsOutputKeys = shared_ptr<vector<byte>>(&readByteVectorFromString(fromStr[10], ' '));
	this->diffCommitments = shared_ptr<vector<byte>>(&readByteVectorFromString(fromStr[11], ' '));
	this->diffCommitmentsIds = shared_ptr<vector<long>>(&readLongVectorFromString(fromStr[12], ' '));
	this->cmtSize = std::stoi(fromStr[13]);
	this->s = std::stoi(fromStr[14]);

}*/
