#pragma once

#include "../../../include/common/CommonMaliciousYao.hpp"

/**
* This class manage the mapping of bundles into buckets.
*
* Meaning, given an item, this class returns the id of the bucket where the item should be placed.
*
* @author Cryptography and Computer Security Research Group Department of Computer Science Bar-Ilan University
*
*/
class BucketMapping {
private:
	vector<int> shuffledCircuits;
	vector<shared_ptr<vector<int>>> buckets;
	map<int,int>  mapping;

public:
	/**
	* A constructor that does the mapping of circuits numbers into buckets.
	* @param circuits the ids of the circuits.
	* @param seed A random byte array to use in order to shuffle the circuits.
	* @param numBuckets The number of required buckets.
	* @param bucketSize The number of circuit in each bucket.
	*/
	BucketMapping(vector<int> &circuits, int numBuckets, int bucketSize, mt19937* random = &get_seeded_random());

	/**
	* Returns the bucket id of the given circuit.
	* @param circuitId The id of the circuit that its bucket should returned.
	*/
	int bucketOf(int circuitId) {
		//check that circuitId exist
		Preconditions::checkArgument(std::find(shuffledCircuits.begin(), shuffledCircuits.end(),circuitId) != shuffledCircuits.end());
		return mapping[circuitId];
	}

	/**
	* Returns the array represents this bucket.
	* @param bucketIndex The id of the bucket that should be returned.
	*/
	shared_ptr<vector<int>> getBucket(int bucketIndex) { return this->buckets[bucketIndex]; }
};
