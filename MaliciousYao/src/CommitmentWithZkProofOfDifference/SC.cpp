#include "../../include/CommitmentWithZkProofOfDifference/SC.hpp"

SC::SC(CmtCommitter* committer, vector<byte>& x, long id, int s, mt19937* random)
{
	//Set the parameters.
	this->n = x.size();
	this->s = s;
	this->commitmentId = id;

	//Allocate space for the random values and commitments.
	r = vector<vector<byte>>(s);
	this->commitments = vector<SCom>(s);

	//Create each commitment pair, s times.
	for (int i = 0; i < s; i++) {
		//generate random string.
		this->r[i] = makeRandomBitByteVector(random, n);
		//Create pair of commitments.
		this->commitments[i] = SCom(committer, x, r[i], this->commitmentId);
		//Increase the id by 2, since two commitments were already created.
		this->commitmentId += 2;
	}

}

vector<shared_ptr<CmtCCommitmentMsg>> SC::getCommitments()
{
	//Create a long array of commitments.
	vector<shared_ptr<CmtCCommitmentMsg>> messages(s * 2);

	//Get each pair of commitments and put the commitments in the big array.
	for (int i = 0; i < s; i++) {
		messages[2 * i] = this->commitments[i].getC0();
		messages[2 * i + 1] = this->commitments[i].getC1();
	}

	return messages;
}

vector<shared_ptr<CmtCDecommitmentMessage>> SC::getDecommitments()
{
	//Create a long array of decommitments.
	vector<shared_ptr<CmtCDecommitmentMessage>> messages(this->s * 2);

	//Get each pair of decommitments and put the decommitments in the big array.
	for (int i = 0; i < s; i++) {
		messages[2 * i] = this->commitments[i].getDecom(0);
		messages[2 * i + 1] = this->commitments[i].getDecom(1);
	}

	return messages;
}

vector<byte> SC::getR()
{
	//Allocate enough space for all random values.
	int size = r[0].size();
	vector<byte> allR(r.size()*size);

	//Copy each random value to the big array.
	int row = r.size();
	int countNum = 0;
	for (int i = 0; i < row; i++) {
		std::copy_n(this->r[i].begin(), size, &allR[countNum]);
		countNum += size;
	}

	return allR;
}

