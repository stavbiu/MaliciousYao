#include "../../../include/OfflineOnline/subroutines/OfflineOtSenderRoutine.hpp"

vector<byte> OfflineOtSenderRoutine::buildInput(int bucketId, int b)
{
	Preconditions::checkBinary(b);

	//Allocate space for the input array.
	vector<byte> inputArr (this->m * this->bucketSize * (this->keySize + this->hashSize));
	int pos = 0;

	// For each wire the keys and decommitments for all circuits are grouped together.
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < bucketSize; j++) {
			shared_ptr<Bundle> bundle = buckets->getBundle(bucketId, j);

			//Get the xor of the key and commitment mask.
			SecretKey xorKeyWithCmtMask;

			//TODO - KeyUtils

		}
	}


	return inputArr;
}

void OfflineOtSenderRoutine::runOtExtensionTransfer(int bucketId)
{
	//TODO - OfflineOtSenderRoutine::runOtExtensionTransfer
}

OfflineOtSenderRoutine::OfflineOtSenderRoutine(ExecutionParameters execution, CryptoPrimitives primitives, KProbeResistantMatrix matrix, shared_ptr<BucketBundleList> buckets)
{
	//Sets the parameters.
	//this->maliciousOtSender = maliciousOtSender;
	this->buckets = buckets;
	this->numBuckets = execution.getNumberOfExecutions();
	this->bucketSize = execution.getBucketSize();
	this->hashSize = primitives.getHash()->getHashedMsgSize();
	this->keySize = primitives.getAES()->getBlockSize();
	this->m = matrix.getProbeResistantInputSize();
}

void OfflineOtSenderRoutine::run()
{
	for (int bucketId = 0; bucketId < numBuckets; bucketId++) {
		runOtExtensionTransfer(bucketId);
	}
}
