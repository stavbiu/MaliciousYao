#include "../../include/primitives/KProbeResistantMatrix.hpp"

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

vector<byte> KProbeResistantMatrix::transformKeys(const vector<byte>& originalKeys, AES* mes)
{
	int keySize = mes->getBlockSize();
	Preconditions::checkArgument(originalKeys.size()/keySize/2 == this->n);

	//Create vector to hold the new keys. There are two keys for each of the matrix columns.
	vector<byte> probeResistantKeys(m * 2 * keySize);

	//Generate new keys using the encryption scheme.
	vector<byte> seed = mes->generateKey(KEY_SIZE).getEncoded();

	//Call the native function that transform the keys.
	//TODO - fix call when transformKeys will be ready
	//TODO - transformKeys from JNI
	//void transformKeys(const vector<byte>& originalKeys, vector<byte>& probeResistantKeys, vector<byte>& seed, int n, int m, shared_ptr<vector<vector<byte>>> matrix);
	//transformKeys(originalKeys, probeResistantKeys, seed, n, m, matrix);

	return probeResistantKeys;
}

CircuitInput* KProbeResistantMatrix::transformInput(CircuitInput& originalInput, mt19937 * random)
{
	int inputSize = originalInput.size();
	Preconditions::checkArgument(this->n == inputSize);
	
	vector<byte>* input = originalInput.getInputVector();
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
		if (xorOfAllocatedBits != (*input)[i]) {
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

VecBlock KProbeResistantMatrix::restoreKeys(VecBlock receivedKeys)
{
	Preconditions::checkArgument(receivedKeys.getSize() / 16 == this->m);

	//Allocate space for the original keys.

	VecBlock restoredKeysArray(n);

	block xorOfShares;
	for (int i = 0; i < n; i++) {

		xorOfShares = _mm_setzero_si128();

		for (int j = 0; j < m; j++) {

			if (0 == (*this->matrix)[i][j]) {
				continue; // insignificant share
			}

			xorOfShares = _mm_xor_si128(xorOfShares, receivedKeys.getBlock().get()[j]);
		}

		restoredKeysArray.getBlock().get()[i] = xorOfShares;
	}


	return restoredKeysArray;
}

void KProbeResistantMatrix::saveToFile(KProbeResistantMatrix matrix, string filename)
{
	// clean the file
	remove(filename.c_str());
	//open file
	std::ofstream outfile(filename.c_str());
	//write n - number of rows
	outfile << matrix.n << endl;
	//write m - number of column
	outfile << matrix.m << endl;

	//go over the rows and write to file
	for (const auto& a : (*matrix.matrix)) {
		outfile << vectorToString(a) << endl;
	}

	outfile.close();
}

KProbeResistantMatrix KProbeResistantMatrix::loadFromFile(string filename)
{
	//open file
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
		auto inputVector = readFromString(line);
		//set in matrix
		(*matrix)[i] = *inputVector;
	}

	return KProbeResistantMatrix(matrix);
}
