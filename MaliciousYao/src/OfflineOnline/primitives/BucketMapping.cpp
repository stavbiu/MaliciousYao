#include "../../../include/OfflineOnline/primitives/BucketMapping.hpp"

BucketMapping::BucketMapping(vector<int>& circuits, int numBuckets, int bucketSize, mt19937* random)
{
	//Check that the number of circuit equals to numBuckets * bucketSize.
	Preconditions::checkArgument(circuits.size() == numBuckets * bucketSize);

	//Create a new array that contains the circuits, then shuffle it.
	//TODO - check if random can replace vector<byte> seed
	this->shuffledCircuits = circuits;
	std::shuffle(this->shuffledCircuits.begin(), this->shuffledCircuits.end(), *random);
	
	//TODO - create seeded random
	/*
	mt19937 random1 = get_seeded_random();
	 int seed = random1();
	 mt19937 newRandom;
	 newRandom.seed(seed);
	 */

	//init buckets
	this->buckets = vector<shared_ptr<vector<int>>>(numBuckets);
	this->mapping = map<int, int>();
	//Put in the buckets arrays and the mapping map the indices of the shuffled circuits.
	//The indices are taken from the shufflesCircuits array.
	for (int bucketIndex = 0; bucketIndex < numBuckets; bucketIndex++) {
		this->buckets[bucketIndex] = shared_ptr<vector<int>>(&vector<int>(bucketSize));
		for (int i = 0; i < bucketSize; i++) {
			int circuit = shuffledCircuits[bucketIndex * bucketSize + i];
			this->buckets[bucketIndex]->at(i) = circuit;
			this->mapping[circuit] = bucketIndex;
		}
	}
}
