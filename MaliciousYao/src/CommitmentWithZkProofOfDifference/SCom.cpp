#include "../../include/CommitmentWithZkProofOfDifference/SCom.hpp"

SCom::SCom(CmtCommitter * committer, vector<byte>& x, vector<byte>& r, long id)
{
	//Check that the length of the given arrays are equal.
	Preconditions::checkArgument(x.size() == r.size());

	int size = x.size();
	//Xor x and r.
	vector<byte> xXorR(size);
	for (int i = 0; i < size; i++) {
		xXorR[i] = (byte)(x[i] ^ r[i]);
	}

	//Convert the byte[] into a commit value.
	shared_ptr<CmtCommitValue> v0(committer->generateCommitValue(xXorR));
	shared_ptr<CmtCommitValue> v1(committer->generateCommitValue(r));

	//Get the commitment messages of r and x^r.
	this->c0 = committer->generateCommitmentMsg(v0, id);
	this->c1 = committer->generateCommitmentMsg(v1, id + 1);

	//Get the decommitment messages of r and x^r.
	this->d0 = committer->generateDecommitmentMsg(c0->getId());
	this->d1 = committer->generateDecommitmentMsg(c1->getId());
}
