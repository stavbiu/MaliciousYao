#include "../../../include/OfflineOnline/primitives/Bundle.hpp"

Bundle::Bundle(shared_ptr<vector<byte>> seed, GarbledBooleanCircuit * garbledCircuit, block * wireValues, int numberOfOutputs,
	shared_ptr<vector<byte>> placementMask, shared_ptr<vector<byte>> commitmentMask, shared_ptr<vector<int>> inputLabelsX,
	shared_ptr<vector<int>> inputLabelsY1Extended, shared_ptr<vector<int>> inputLabelsY2, shared_ptr<vector<int>> outputLabels,
	shared_ptr<vector<byte>> inputWiresX, shared_ptr<vector<byte>> inputWiresY1Extended, shared_ptr<vector<byte>> inputWiresY2,
	shared_ptr<CommitmentBundle> commitmentsX, shared_ptr<CommitmentBundle> commitmentsY1Extended,
	shared_ptr<CommitmentBundle> commitmentsY2, shared_ptr<CmtCCommitmentMsg> commitment, shared_ptr< CmtCDecommitmentMessage> decommit,
	shared_ptr<SecretKey> secret, int keySize)
{
	this->seed = seed;

	this->garbledTables = garbledCircuit->getGarbledTables();
	this->translationTable = shared_ptr<vector<byte>>(&garbledCircuit->getTranslationTable());

	this->placementMask = placementMask;
	this->commitmentMask = commitmentMask;

	this->inputLabelsX = inputLabelsX;
	this->inputLabelsY1Extended = inputLabelsY1Extended;
	this->inputLabelsY2 = inputLabelsY2;
	this->outputLabels = outputLabels;

	this->inputWiresX = inputWiresX;
	this->inputWiresY1Extended = inputWiresY1Extended;
	this->inputWiresY2 = inputWiresY2;
	this->numberOfOutputs = numberOfOutputs;
	this->outputWires = unique_ptr<block, aligned_free>(wireValues);

	this->commitmentsX = commitmentsX;
	this->commitmentsY1Extended = commitmentsY1Extended;
	this->commitmentsY2 = commitmentsY2;
	this->commitment = commitment;
	this->decommit = decommit;

	this->secret = secret;

	this->keySize = keySize;
}

void Bundle::getCommitments(shared_ptr<CommitmentsPackage> pack)
{
	pack->setCommitmentsX(this->commitmentsX->getCommitments(), this->commitmentsX->getCommitmentsIds());
	pack->setCommitmentsY1Extended(this->commitmentsY1Extended->getCommitments(), this->commitmentsY1Extended->getCommitmentsIds());
	pack->setCommitmentsY2(this->commitmentsY2->getCommitments(), this->commitmentsY2->getCommitmentsIds());
	pack->setCommitmentsOutputKeys(this->commitment.get());
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
