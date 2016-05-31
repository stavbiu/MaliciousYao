#include "../../include/primitives/Bundle.hpp"

Bundle::Bundle(vector<byte>& seed, GarbledBooleanCircuit * garbledCircuit, block * wireValues, vector<byte>& placementMask, vector<byte>& commitmentMask, vector<int>& inputLabelsX, vector<int>& inputLabelsY1Extended, vector<int>& inputLabelsY2, vector<int>& outputLabels, vector<byte>& inputWiresX, vector<byte>& inputWiresY1Extended, vector<byte>& inputWiresY2, CommitmentBundle * commitmentsX, CommitmentBundle * commitmentsY1Extended, CommitmentBundle * commitmentsY2, CmtCCommitmentMsg * commitment, CmtCDecommitmentMessage * decommit, SecretKey * secret, int keySize)
{
	this->seed = seed;

	this->garbledTables = garbledCircuit->getGarbledTables();
	this->translationTable = garbledCircuit->getTranslationTable();

	this->placementMask = placementMask;
	this->commitmentMask = commitmentMask;

	this->inputLabelsX = inputLabelsX;
	this->inputLabelsY1Extended = inputLabelsY1Extended;
	this->inputLabelsY2 = inputLabelsY2;
	this->outputLabels = outputLabels;

	this->inputWiresX = inputWiresX;
	this->inputWiresY1Extended = inputWiresY1Extended;
	this->inputWiresY2 = inputWiresY2;
	this->outputWires = wireValues;

	this->commitmentsX = commitmentsX;
	this->commitmentsY1Extended = commitmentsY1Extended;
	this->commitmentsY2 = commitmentsY2;
	this->commitment = commitment;
	this->decommit = decommit;

	this->secret = secret;

	this->keySize = keySize;
}

void Bundle::getCommitments(CommitmentsPackage* pack)
{
	pack->setCommitmentsX(this->commitmentsX->getCommitments(), this->commitmentsX->getCommitmentsIds());
	pack->setCommitmentsY1Extended(this->commitmentsY1Extended->getCommitments(), this->commitmentsY1Extended->getCommitmentsIds());
	pack->setCommitmentsY2(this->commitmentsY2->getCommitments(), this->commitmentsY2->getCommitmentsIds());
	pack->setCommitmentsOutputKeys(this->commitment);
}

string Bundle::toString()
{
	//TODO - toString in Bundle
	return string();
}

void Bundle::initFromString(const string & raw)
{
	//TODO - initFromString in Bundle
}
