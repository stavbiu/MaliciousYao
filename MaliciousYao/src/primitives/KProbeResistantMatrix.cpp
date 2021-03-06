#include "../../include/primitives/KProbeResistantMatrix.hpp"

void KProbeResistantMatrix::allocateKeys(vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> & probeResistantKeys, block & originalKey0, block & originalKey1, int i, block & newKey)
{
	//Get the delta between the keys.
	block delta = _mm_xor_si128(originalKey0, originalKey1);
	int shares = 0;
	int lastShare = 0;
	//Get the number of shares (the number of times that "1" is shows) of the row i in the matrix.
	// This might fail if the matrix is not probe resistant, with negligible probability.
	int res = getNumberOfShares(i, probeResistantKeys, &shares, &lastShare);
	if (res == 0) {
		cout << "error!!!" << endl;
		return;
	}
	block zero = _mm_setzero_si128();
	block xorOfShares = originalKey0;
	for (int j = 0; j < m; j++) {
		if (((*this->matrix)[i][j] == 0) || (j == lastShare)) {
			// Skip on zeros and skip the last share.
			continue;
		}

		//Check if the keys are not set yet.
		if ((equalBlocks(probeResistantKeys[j * 2], zero) == 0) &&
			(equalBlocks(probeResistantKeys[j * 2 + 1], zero) == 0)) {
			probeResistantKeys[j * 2] = newKey;
			probeResistantKeys[j * 2 + 1] = _mm_xor_si128(newKey, delta);
		}

		block key0 = probeResistantKeys[j * 2];
		xorOfShares = _mm_xor_si128(xorOfShares, key0);

		shares--;
		if (0 == shares) {
			// All but the last share has been allocated
			break;
		}
	}

	//The last pair of keys are the xor of all shares and the xor of it with delta.
	probeResistantKeys[lastShare * 2] = xorOfShares;
	probeResistantKeys[lastShare * 2 + 1] = _mm_xor_si128(xorOfShares, delta);

}

int KProbeResistantMatrix::getNumberOfShares(int i, vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> &probeResistantKeys, int* shares, int* lastShare)
{
	bool allSharesAreAlreadyAssigned = true;
	block zero = _mm_setzero_si128();

	for (int j = 0; j < m; j++) {
		// Count the shares of bit i, and also try to find one that has not been assigned a key yet 
		// (otherwise we cannot complete the xor of all the keys).
		if ((*this->matrix)[i][j] == 1) {
			(*shares)++;

			//Check if the keys are not set yet.
			if ((equalBlocks(probeResistantKeys[j * 2], zero) == 0) &&
				(equalBlocks(probeResistantKeys[j * 2 + 1], zero) == 0)) {
				allSharesAreAlreadyAssigned = false;
				*lastShare = j;
			}
		}
	}

	if (allSharesAreAlreadyAssigned) {
		return 0;
	}
	return 1;
}

KProbeResistantMatrix::KProbeResistantMatrix(shared_ptr<vector<vector<byte>>> newMatrix)
{
	Preconditions::checkNotNull(newMatrix.get());
	Preconditions::checkNotZero(newMatrix.get()->size());

	this->matrix = newMatrix;
	this->n = newMatrix.get()->size();
	this->m = newMatrix.get()->at(0).size();
}

vector<int> KProbeResistantMatrix::getProbeResistantLabels()
{
	vector<int> res;

	boost::push_back(res, boost::irange(0, int(this->m)));

	return res;
}

vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> KProbeResistantMatrix::transformKeys(vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> originalKeys, AES* mes)
{
	int keySize = mes->getBlockSize();
	Preconditions::checkArgument(originalKeys.size()/keySize/2 == this->n);

	//Create vector to hold the new keys. There are two keys for each of the matrix columns.
	vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> probeResistantKeys(m * 2 * keySize);

	//Generate new keys using the encryption scheme.
	auto seedByte = mes->generateKey(KEY_SIZE).getEncoded();
	//vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> seed(&(mes->generateKey(KEY_SIZE).getEncoded()[0]));

	int* seedInt = (int*)&seedByte[0];

	//For each pair of original keys allocate new keys and put them in the probeResistantKeys array.
	for (int i = 0; i < n; i++) {
		//copy to aligned seed
		//TODO - faster? (block*) seed = (block*)&seedByte[0].
		block seed = _mm_set_epi32(seedInt[i*4+3], seedInt[i * 4 + 2], seedInt[i * 4 + 1], seedInt[i * 4]);
		allocateKeys(probeResistantKeys, originalKeys[i * 2], originalKeys[i * 2 + 1], i, seed);
	}

	return probeResistantKeys;
}

CircuitInput* KProbeResistantMatrix::transformInput(const CircuitInput& originalInput, mt19937 * random)
{
	int inputSize = originalInput.size();
	Preconditions::checkArgument(this->n == inputSize);
	
	shared_ptr<vector<byte>> input = originalInput.getInputVectorShared();
	// Init the new vector with -1 values.
	vector<byte>* newInput = new vector<byte>(m, -1);

	// For each input bit of the original input:
	for (int i = 0; i < inputSize; i++) {
		// Go over the line i in the matrix, and also over the new input vector.
		int lastIndexInTheLine = -1;
		int xorOfAllocatedBits = 0;

		for (int j = 0; j < this->m; j++) {
			// We deal with a significant bit.
			// A significant bit is ALWAYS added to the XOR.
			if ((*this->matrix)[i][j] != 0) {
				if (newInput->at(j) == -1) {
					// This bit is not yet allocated.
					lastIndexInTheLine = j; // Use this variable to negate the case where all bits are already allocated.
					(*newInput)[j] = getRandomBit(random);
				}
				xorOfAllocatedBits = xorOfAllocatedBits ^ (*newInput)[j];
			}
			// ELSE:
			// The j^th bit in the new vector is **insignificant** to the i^th bit in the old vector
			// This bit is NOT added to the XOR.
		}
		if (lastIndexInTheLine == -1) {
			// An unallocated bit on the line was not found or have a zeros line in the matrix.
			// In any case this is an illegal state.
			throw new IllegalStateException("this is not a k-probe resistant matrix: could not transform input!");
		}
		// At this point all the bits in the line were allocated, but we may have a mistake with the last bit.
		// In that case we flip it to achieve the correct xor.
		if (xorOfAllocatedBits != input->at(i)) {
			(*newInput)[lastIndexInTheLine] = (byte)(1 - (*newInput)[lastIndexInTheLine]);
		}
	}

	// There may still be un-allocated (but insignificant bits). We must make sure newInput is a binary vector.
	for (int j = 0; j < this->m; j++) {
		if (-1 == (*newInput)[j]) {
			(*newInput)[j] = 0;
		}
	}

	return new CircuitInput(shared_ptr<vector<byte>>(newInput));
}

vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> KProbeResistantMatrix::restoreKeys(vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> &receivedKeys)
{
	Preconditions::checkArgument(receivedKeys.size() / 16 == this->m);

	//Allocate space for the original keys.

	vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> restoredKeysArray(n);

	block xorOfShares;
	for (int i = 0; i < n; i++) {

		xorOfShares = _mm_setzero_si128();

		for (int j = 0; j < m; j++) {

			if (0 == (*this->matrix)[i][j]) {
				continue; // insignificant share
			}

			xorOfShares = _mm_xor_si128(xorOfShares, receivedKeys[j]);
		}

		restoredKeysArray[i] = xorOfShares;
	}


	return restoredKeysArray;
}

void KProbeResistantMatrix::saveToFile(shared_ptr<KProbeResistantMatrix> matrix, string filename)
{
	/*// clean the file
	remove(filename.c_str());
	//open file
	std::ofstream outfile(filename.c_str());
	//write n - number of rows
	outfile << matrix->n << endl;
	//write m - number of column
	outfile << matrix->m << endl;

	//go over the rows and write to file
	for (const auto& a : (*matrix->matrix)) {
		outfile << vectorToString(a, ' ') << endl;
	}

	outfile.close();*/

	//USE CEREAL
	//write to binary file
	std::ofstream os(filename);
	cereal::BinaryOutputArchive  oarchive(os);

	oarchive(matrix);
}

shared_ptr<KProbeResistantMatrix> KProbeResistantMatrix::loadFromFile(string filename)
{
	/*//open file
	ifstream infile(filename.c_str());
	//read n - number of rows
	string line;
	getline(infile, line);
	int n = std::stoi(line);
	//read m - number of column
	getline(infile, line);
	int m = std::stoi(line);

	//read matrix by line
	shared_ptr<vector<vector<byte>>> matrix(new vector<vector<byte>>(n));
	for (int i = 0; i < n; i++) {
		//read line
		getline(infile, line);
		//get vector<byte> out of the line
		auto inputVector = readByteVectorFromString(line, ' ');
		//set in matrix
		(*matrix)[i] = inputVector;
	}
	
	
	return shared_ptr<KProbeResistantMatrix>( new KProbeResistantMatrix(matrix));
	*/

	//USE CEREAL
	//read from file
	std::ifstream is(filename);
	cereal::BinaryInputArchive iarchive(is);

	shared_ptr<KProbeResistantMatrix> matrix;

	iarchive(matrix);

	return matrix;

}
