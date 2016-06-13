#pragma once

#include <libscapi/include/infra/File.hpp>
#include <libscapi/include/infra/Scanner.hpp>
#include <libscapi/include/circuits/GarbledBooleanCircuit.h>

#include "../../include/common/Preconditions.hpp"
#include "../../include/common/aligned_allocator.hpp"
#include "../../include/common/aligned_allocator_no_destructor.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

typedef unsigned char byte;

typedef __m128i block;


typedef pair<byte*, int> vec_byte;

#define SIZE_OF_BLOCK 16//size in bytes

#ifdef _WIN32
#else
#include <libscapi/include/circuits/Compat.h>
#endif

using namespace std;

/*
* For deleting block* in unique_ptr
*/
struct aligned_free {
	void operator()(void* p) {
		_aligned_free(p);
	}
};


/********************************************
 Common functions for MaliciousYao protocol
*********************************************/

/*
 Basic function that take vector and make it in to a string with separator char between every element.
*/
//TODO - vectorToString ****DOES NOT WORK****
template <typename T>
string vectorToString(const vector<T>& vec, const char* separator) 
{
	std::ostringstream oss;

	if (!vec.empty()) {
		// Convert all but the last element to avoid a trailing separator
		std::copy(vec.begin(), vec.end() - 1,
			std::ostream_iterator<T>(oss, separator));

		// Now add the last element with no delimiter
		oss << vec.back();
	}
	else {
		oss << "";
	}

	return oss.str();
}

template <typename T>
string vectorToString(const vector<T>* vec, const char separator)
{
	std::ostringstream oss;

	if (!vec->empty()) {
		// Convert all but the last element to avoid a trailing " "
		std::copy(vec->begin(), vec->end() - 1,
			std::ostream_iterator<T>(oss, &separator));

		// Now add the last element with no delimiter
		oss << vec->back();
	}
	else {
		oss << "";
	}

	return oss.str();
}

/**
 Returns the input indices of the given party in the given circuit.
 Inputs:
	 bc The boolean circuit to get the input indices of.
	 party The number of the party we want his input indices.
*/
vector<int> circuitGetLabels(GarbledBooleanCircuit* gbc, int party);

/*
 Get vector on stack and copy to new vector on heap.
 Return shared_ptr to the new vector
*/
template <typename T>
shared_ptr<vector<T>> copyVectorToSharedPtr(vector<T> vec)
{
	shared_ptr<vector<T>> arr(new vector<T>(vec.size()));

	copy(vec.begin(), vec.end(), inserter(*arr.get(), arr->begin()));

	return arr;
}

/*
 Make vector of random bits, save as bytes.
 inputs:
	random generator
	vector size
*/
vector<byte> makeRandomBitByteVector(mt19937* mt, int size);

/*
Make random bit, as byte.
inputs:
random generator
*/
byte getRandomBit(mt19937 * mt);

/*
 Returns a byte array that is the binary representation of the given byte[].
*/
vector<byte>* getBinaryByteArray(vector<byte> bytes);

/*
 Read string that was made with vectorToString() to vector<byte>
*/
vector<byte> readByteVectorFromString(string str, const char separator);

/*
Read string that was made with vectorToString() to vector<long>
*/
vector<long> readLongVectorFromString(string str, const char separator);

/*
Read string that was made with vectorToString() to vector<int>
*/
vector<int> readIntVectorFromString(string str, const char separator);

/*
Read string that was made with vectorToString() to vector<string>
*/
vector<string> readStringVectorFromString(string str, const char separator);


/*
	Class VecBlock save block* align and size
*/
class VecBlock {
	block* blockArray = NULL;
	int size;

public:
	/*
	 Create block* aligned to block size (16) in given size.
	*/
	VecBlock(int num) {
		this->size = num;
		this->blockArray =(block *)_mm_malloc(sizeof(block) * num, SIZE_OF_BLOCK);
	}

	~VecBlock() {
		//_aligned_free(this->blockArray);
		_mm_free(this->blockArray);
	}
	/*
	 Create block* from vector of bytes
	*/
	VecBlock(vector<byte>& vec) {
		this->size = vec.size();
		this->blockArray = (block *)_mm_malloc(sizeof(block) * this->size, SIZE_OF_BLOCK);
		//copy bytes to block
		memcpy(this->blockArray, &vec[0], sizeof(block) * this->size);
	}

	block* getBlock() { return this->blockArray; }
	int getSize() { return this->size; }

	void setBlock(block* newBlock, int newSize) {
		if (blockArray != NULL) {
			_aligned_free(this->blockArray);
		}

		this->blockArray = newBlock;
		this->size = newSize;
	}
	
	block& operator[](std::size_t idx) { return this->blockArray[idx]; }
};

//A function that checks if two blocks are equal by casting to double size long array and check each half of a block
bool equalBlocks(block &a, block &b);
