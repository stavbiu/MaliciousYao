#include "../../include/common/CommonMaliciousYao.hpp"

/*
 Basic function that take vector and make it in to a string with "," between evry element.
*/
template <typename T>
string vectorToString(const vector<T>& vec) {
	std::ostringstream oss;

	if (!vec.empty()) {
		// Convert all but the last element to avoid a trailing ","
		std::copy(vec.begin(), vec.end() - 1,
			std::ostream_iterator<T>(oss, ","));

		// Now add the last element with no delimiter
		oss << vec.back();
	}
	else {
		oss << "";
	}

	return oss.str();
}

/*
Get vector on stack and copy to new vector on heap.
Return shared_ptr to the new vector
*/
template<typename T>
shared_ptr<vector<T>> copyVectorToSharedPtr(vector<T> vec)
{
	shared_ptr<vector<T>> arr(new vector<T>(vec.size()));

	copy(vec.begin(), vec.end(), inserter(*arr.get(), arr->begin()));

	return arr;
}


/*
 Read from file vector of bytes.
 The first number is the number of inputs.
*/
vector<byte>* readInputAsVector(string input_file) {
	cout << "reading from file " << input_file << endl;;
	auto sc = scannerpp::Scanner(new scannerpp::File(input_file));
	int inputsNumber = sc.nextInt();
	vector<byte>* inputVector = new vector<byte>(inputsNumber);
	for (int i = 0; i < inputsNumber; i++)
		(*inputVector)[i] = (byte)sc.nextInt();
	return inputVector;
}

/**
Returns the input indices of the given party in the given circuit.
Inputs:
bc The boolean circuit to get the input indices of.
party The number of the party we want his input indices.
*/
vector<int> circuitGetLabels(GarbledBooleanCircuit* gbc, int party)
{
	Preconditions::checkIntegerInRange(party, 1, 2);
	return gbc->getInputWireIndices(party);
}

/*
Make vector of random bits, save as bytes.
inputs:
	random generator
	vector size
*/
vector<byte>* makeRandomBitByteVector(mt19937 * mt, int size)
{
	uniform_int_distribution<> dis(0, 1);

	auto vec = new vector<byte>(size);

	for (int i = 0; i < size; i++) {
		(*vec)[i] = byte(dis(mt));
	}

	return vec;
}
