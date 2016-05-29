#include "../../include/primitives/CommitmentBundle.hpp"

CommitmentBundle::CommitmentBundle(vector<byte>* commitmentsVec, vector<long>* commitmentsIdsVec, vector<byte>* decommitmentsVec, vector<byte>* decommitmentRandomsVec)
{
	this->commitments = shared_ptr<vector<byte>>(commitmentsVec);
	this->commitmentIds = shared_ptr<vector<long>>(commitmentsIdsVec);
	this->decommitments = shared_ptr<vector<byte>>(decommitmentsVec);
	this->decommitmentRandoms = shared_ptr<vector<byte>>(decommitmentRandomsVec);
}
