#pragma once
#include <stdexcept>

using namespace std;

/**
 This class provides some pre-checks that can be used in the protocol.
*/
class Preconditions {
public:
	/**
	 Checks if the given expression is true.
	 If not, the function throws an exception.
	 input:
		Expression To check.
	*/
	static void checkArgument(bool expression) {
		//assert
		if (!expression) {
			throw invalid_argument("Illegal Argument Exception");
		}
	}

	/**
	 Checks if the given expression is not zero.
	 If the expression is zero, the function throws an exception.
	 input:
		Expression To check.
	*/
	static void checkNotZero(int expression) {
		checkArgument(0 != expression);
	}

	/**
	 Checks if the given pointer is not null.
	 If the pointer is null, the function throws an exception.
	 input:
		Pointer To check.
	*/
	static void checkNotNull(void* ptr) {
		checkArgument(NULL != ptr);
	}

	/**
	 Checks if the given index is between the given min and max values.
	 If not, the function throws an exception.
	 input:
		i The index to check.
		min The minimum value that the index can be.
		max The maximum value that the index can be.
	*/
	static void checkIntegerInRange(int i, int min, int max) {
		checkArgument((min <= i) && (i <= max));
	}

	/**
	 Checks if the given index is below the given upper bound.
	 If not, the function throws an exception.
	 input:
		i The index to check.
		upperBound The maximum value that the index can be.
	*/
	static void checkIndexInRange(int i, int upperBound) {
		checkIntegerInRange(i, 0, upperBound - 1);
	}

	/**
	 Checks if the given value is a binary value (e.g. 0/1).
	 If not, the function throws an exception.
	 input:
		i The value to check.
	*/
	static void checkBinary(int i) {
		checkIntegerInRange(i, 0, 1);
	}
};
