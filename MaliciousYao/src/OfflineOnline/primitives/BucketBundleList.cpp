#include "../../../include/OfflineOnline/primitives/BucketBundleList.hpp"

BucketBundleList::BucketBundleList(shared_ptr<ExecutionParameters> execution, shared_ptr<BucketMapping> bucketMapping)
{
	this->numBuckets = execution->getNumberOfExecutions();
	this->bucketSize = execution->getBucketSize();
	this->bucketMapping = bucketMapping;

	//Create the arrays of the buckets.
	this->buckets = vector<shared_ptr<BucketBundle>>(numBuckets);
	for (int i = 0; i < this->numBuckets; i++) {
		this->buckets[i] = shared_ptr<BucketBundle>(&BucketBundle());
	}
}

void BucketBundleList::add(shared_ptr<Bundle> bundle, int index)
{
	//Get the id of the bucket where the item should be placed.
	int bucketId = bucketMapping->bucketOf(index);

	//Put the item in the right bucket.
	this->buckets[bucketId]->addBundle(bundle);
}

shared_ptr<BucketBundle> BucketBundleList::getBucket(int bucketId)
{
	Preconditions::checkIndexInRange(bucketId, numBuckets);
	return this->buckets[bucketId];
}

shared_ptr<Bundle> BucketBundleList::getBundle(int bucketId, int itemId)
{

	Preconditions::checkIndexInRange(bucketId, numBuckets);
	Preconditions::checkIndexInRange(itemId, bucketSize);
	return this->buckets[bucketId]->getBundleAt(itemId);
}

void BucketBundleList::saveToFiles(string prefix)
{
	//For each bucket, create a file and write the bucket.
	for (int j = 0; j < this->numBuckets; j++) {
		boost::format formatter("%1%.%2%.cbundle");
		formatter % prefix;
		formatter % j;
		string filename = formatter.str();
	}
	//TODO - saveToFiles
}

vector<shared_ptr<BucketBundle>> BucketBundleList::loadBucketFromFile(string filename)
{
	//TOSO - loadBucketFromFile
	return vector<shared_ptr<BucketBundle>>();
}
