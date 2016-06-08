#pragma once

#include "../../../include/common/CommonMaliciousYao.hpp"
#include "../../../include/OfflineOnline/primitives/Bundle.hpp"
#include <cereal/archives/xml.hpp>	// for variable name
#include <cereal/types/vector.hpp>	// vector recognition
#include <cereal/types/memory.hpp>  // for smart pointers

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

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		// serialize things by passing them to the archive
		archive(CEREAL_NVP(numBundle), CEREAL_NVP(bucket));
	}
};
