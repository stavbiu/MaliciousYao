#include "../../include/primitives/CommitmentBundle.hpp"

CommitmentBundle::CommitmentBundle(shared_ptr<vector<byte>> commitmentsVec, shared_ptr<vector<long>> commitmentsIdsVec, shared_ptr<vector<byte>> decommitmentsVec, shared_ptr<vector<byte>> decommitmentRandomsVec)
{
	this->commitments = shared_ptr<vector<byte>>(commitmentsVec);
	this->commitmentIds = shared_ptr<vector<long>>(commitmentsIdsVec);
	this->decommitments = shared_ptr<vector<byte>>(decommitmentsVec);
	this->decommitmentRandoms = shared_ptr<vector<byte>>(decommitmentRandomsVec);
}

CmtCCommitmentMsg * CommitmentBundle::getCommitment(int wireIndex, int sigma) const
{
	//Check that the sigma is 0 or 1.
	Preconditions::checkBinary(sigma);

	//Return the commitment that matches the given sigma of the given wire index.

	//TODO -CmtSimpleHashCommitmentMessage
	//Return the commitment that matches the given sigma of the given wire index.
	/*byte[] commitment = new byte[commitmentSize];
	System.arraycopy(commitments, wireIndex * 2 * commitmentSize + sigma*commitmentSize, commitment, 0, commitmentSize);
	return new CmtSimpleHashCommitmentMessage(commitment, commitmentIds[wireIndex * 2 + sigma]);
	*/

	return nullptr;
}

CmtCDecommitmentMessage * CommitmentBundle::getDecommitment(int wireIndex, int sigma)
{
	//Check that the sigma is 0 or 1.
	Preconditions::checkBinary(sigma);

	//TODO - CmtSimpleHashDecommitmentMessage
	//Return the decommitment that matches the given sigma of the given wire index.
	/*byte[] r = new byte[commitmentSize];
	byte[] x = new byte[keySize];
	System.arraycopy(decommitmentRandoms, wireIndex * 2 * commitmentSize + sigma*commitmentSize, r, 0, commitmentSize);
	System.arraycopy(decommitments, wireIndex * 2 * keySize + sigma*keySize, x, 0, keySize);

	//Create and return a CmtCDecommitmentMessage from the copied x, r.
	return new CmtSimpleHashDecommitmentMessage(new ByteArrayRandomValue(r), x);
	*/

	return nullptr;
}

bool CommitmentBundle::operator==(const CommitmentBundle & b)
{
	int size = commitmentIds->size() / 2;
	//For each wire's index in the labels array:
	for (int i = 0; i < size; i++) {
		//Get the index and the matching commitments.
		//Check that both commitments are equal.
		for (int k = 0; k < 2; k++) {
			auto m1 = this->getCommitment(i, k);
			string c1 = m1->toString();
			auto m2 = b.getCommitment(i, k);
			string c2 = m2->toString();
			if (c1.compare(c2) != 0) {
				boost::format formatter("commitments differ for index=%1% and sigma=%2%: c1 = %3%, c2 = %4%");
				formatter % i;
				formatter % k;
				formatter % c1;
				formatter % c2;
				throw CheatAttemptException(formatter.str());
				return false;
			}
		}
	}
	return true;
}
