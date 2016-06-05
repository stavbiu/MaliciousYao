#pragma once

#include "../../../include/common/CommonMaliciousYao.hpp"
#include "../../../include/OfflineOnline/primitives/Bundle.hpp"

/*
 Class BucketBundle save all the bundle the belongs in one bucket
*/
class BucketBundle {
private:
	int numBundle;										//save the number of current bundle in bucket
	vector<shared_ptr<Bundle>> bucket;		//save all the bundles

public:
	/*
	 Init Bucket
	*/
	BucketBundle() {
		this->numBundle = 0;
	}

	vector<shared_ptr<Bundle>> getAllBundles() { return this->bucket; }
	int size() { return this->numBundle; }

	shared_ptr<Bundle> getBundleAt(int index) { return this->bucket[index]; }

	void addBundle(shared_ptr<Bundle> b) { 
		this->bucket.push_back(b);
		this->numBundle++;
	}

};
