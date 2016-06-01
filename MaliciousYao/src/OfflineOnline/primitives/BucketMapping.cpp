#include "../../../include/OfflineOnline/primitives/BucketMapping.hpp"

BucketMapping::BucketMapping(vector<int>& circuits, vector<byte>& seed, int numBuckets, int bucketSize)
{
	//Check that the number of circuit equals to numBuckets * bucketSize.
	Preconditions::checkArgument(circuits.size() == numBuckets * bucketSize);

	//Create a new array that contains the circuits, then shuffle it.
	this->shuffledCircuits = circuits;
}
