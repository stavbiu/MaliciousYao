#pragma once

#include <libscapi/include/infra/File.hpp>
#include <libscapi/include/infra/Scanner.hpp>
#include <libscapi/include/circuits/GarbledBooleanCircuit.h>

#include "../../include/common/Preconditions.hpp"

#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <iostream>

typedef unsigned char byte;

using namespace std;

/********************************************
 Common functions for MaliciousYao protocol
*********************************************/

/*
 Basic function that take vector and make it in to a string with "," between evry element.
*/
template <typename T>
string vectorToString(const vector<T>& vec);

/*
 Read from file vector of bytes.
 The first number is the number of inputs.
*/
vector<byte>* readInputAsVector(string input_file);

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
shared_ptr<vector<T>> copyVectorToSharedPtr(vector<T> vec);

/*
 Make vector of random bits, save as bytes.
 inputs:
	random generator
	vector size
*/
vector<byte>* makeRandomBitByteVector(mt19937* mt, int size);