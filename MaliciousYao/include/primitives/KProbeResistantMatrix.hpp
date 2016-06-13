#pragma once

#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>
#include <libscapi/include/primitives/Prf.hpp>
#include <libscapi/include/CryptoInfra/Key.hpp>
#include "../../include/common/Preconditions.hpp"
#include "../../include/common/CommonMaliciousYao.hpp"
#include "../../include/primitives/CircuitInput.hpp"
#include "../../include/common/CommonMaliciousYao.hpp"
#include <cereal/archives/xml.hpp>	// for variable name
#include <cereal/archives/binary.hpp> // binary file save
#include <cereal/types/vector.hpp>	// vector recognition
#include <cereal/types/memory.hpp>  // for smart pointers

using namespace std;

class KProbeResistantMatrix
{
private:
	const int KEY_SIZE = 128;

	shared_ptr<vector<vector<byte>>> matrix;	//The K probe-resistant matrix.
	int n;							//Number of matrix's rows.
	int m;							//Number of matrix's columns.

	void allocateKeys(vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> & probeResistantKeys, block &originalKey0, block &originalKey1, int i, block &newKey);

	int getNumberOfShares(int i, vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> &probeResistantKeys, int* shares, int* lastShare);

public:
	KProbeResistantMatrix(){}

	/**
	 A constructor that sets the given matrix.
	*/
	KProbeResistantMatrix(shared_ptr<vector<vector<byte>>> newMatrix);

	/**
	 Returns the probe resistant input size (the matrix columns).
	*/
	int getProbeResistantInputSize() {	return m; }

	/**
	 Returns vector of size m, when each cell i contains "i".
	*/
	vector<int> getProbeResistantLabels();

	/**
	 Gets a original keys and transform them into keys that corresponds to the matrix.
	 Inputs:
		 originalKeys The keys that matched the rows of the matrix.
		 mes used to generate new keys.
	 Return
		 the transformed keys, that matched the columns of the matrix.
	*/
	vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> transformKeys(vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> originalKeys, AES* mes);

	/**
	 Gets a original inputs and transform them into inputs that corresponds to the matrix columns.
	 Inputs:
		 originalInput The inputs that matched the rows of the matrix.
		 random used to generate new inputs.
	 Returns:
		 the transformed inputs, that matched the columns of the matrix.
	*/
	CircuitInput* transformInput(const CircuitInput& originalInput, mt19937* random);

	/**
	 Restores the original keys using the matrix from the transformed keys.
	 Input:
		 receivedKeys the transformed keys.
	 Return:
		 the original restored keys.
	*/
	vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> restoreKeys(vector<block, aligned_allocator<block, SIZE_OF_BLOCK>> &receivedKeys);

	/**
	 Saves the matrix to a file.
	 Inputs:
		 matrix The matrix to write to the file.
		 filename The name of the file to write the matrix to.
	*/
	static void saveToFile(shared_ptr<KProbeResistantMatrix> matrix, string filename);

	/**
	 Loads the matrix from a file.
	 Input:
		 filename The name of the file to read the matrix from.
	 Return:
		 The read matrix.
	*/
	static shared_ptr<KProbeResistantMatrix> loadFromFile(string filename);


	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		// serialize things by passing them to the archive
		archive(CEREAL_NVP(n), CEREAL_NVP(m), CEREAL_NVP(matrix));
	}
};
