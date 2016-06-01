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
	vector<vector<int>> buckets;
	map<int,int>  mapping;

public:
	/**
	* A constructor that does the mapping of circuits numbers into buckets.
	* @param circuits the ids of the circuits.
	* @param seed A random byte array to use in order to shuffle the circuits.
	* @param numBuckets The number of required buckets.
	* @param bucketSize The number of circuit in each bucket.
	*/
	BucketMapping(vector<int> &circuits, vector<byte> &seed, int numBuckets, int bucketSize);
};
