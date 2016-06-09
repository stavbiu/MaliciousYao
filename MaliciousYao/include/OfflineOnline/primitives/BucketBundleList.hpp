#pragma once

#include <fstream>
#include <cereal/archives/binary.hpp>
#include <cereal/types/vector.hpp>	// vector recognition
#include <cereal/types/memory.hpp>  // for smart pointers
#include <cereal/types/polymorphic.hpp>

#include "../../../include/common/CommonMaliciousYao.hpp"
#include "../../../include/OfflineOnline/primitives/BucketBundle.hpp"
#include "../../../include/OfflineOnline/primitives/BucketMapping.hpp"
#include "../../../include/primitives/ExecutionParameters.hpp"
#include "../../../include/OfflineOnline/primitives/Bundle.hpp"

/*
 Class BucketBundleList holds vector of buckets each consists of Bundle.
*/
class BucketBundleList {
private:
	int numBuckets;					// The number of buckets (arrays)) in the list.
	int bucketSize;					// The number of bundles in each bucket.
	shared_ptr<BucketMapping> bucketMapping;	// An object that maps a bundle into the right bucket.
	vector<shared_ptr<BucketBundle>> buckets;		// Arrays that stores all bundles.

public:

	BucketBundleList(){}

	/**
	* A constructor that initializes the list using the given execution parameters and bucketMapping.
	* @param execution contains the number of buckets and bucket size.
	* @param bucketMapping An object that maps a bundle into the right bucket.
	*/
	BucketBundleList(shared_ptr<ExecutionParameters> execution, shared_ptr<BucketMapping> bucketMapping);

	/**
	* Adds the given item to the list.
	* @param item To add to the list.
	* @param index The index that the item should be placed at.
	*/
	void add(shared_ptr<Bundle> bundle, int index);

	/**
	* Returns the number of buckets in the list.
	*/
	int size() { return this->numBuckets; }

	/**
	* Returns the bucket according to the given id.
	* @param bucketId The id of the requested bucket.
	*/
	shared_ptr<BucketBundle> getBucket(int bucketId);

	/**
	* Returns the bundle according to the given item and bucket ids.
	* @param bucketId The id of the bucket where the item is placed.
	* @param itemId The id of the requested item.
	*/
	shared_ptr<Bundle> getBundle(int bucketId, int itemId);

	/**
	* Prints the buckets to files. Each bucket is printed to a different file.
	* @param prefix The prefix of the files names.
	* @throws FileNotFoundException
	* @throws IOException
	*/
	void saveToFiles(string prefix);

	/**
	* Loads a bucket of Bundles from a file. (This actually reads one bucket in each function call).
	* @param filename The name of the file to read from.
	* @return The created array filled with items.
	* @throws FileNotFoundException
	* @throws IOException
	*/
	static shared_ptr<BucketBundle> loadBucketFromFile(string filename);

};