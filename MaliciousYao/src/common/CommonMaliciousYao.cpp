#include "../../include/common/CommonMaliciousYao.hpp"


vector<int> circuitGetLabels(GarbledBooleanCircuit* gbc, int party)
{
	Preconditions::checkIntegerInRange(party, 1, 2);
	return gbc->getInputWireIndices(party);
}

vector<byte>* makeRandomBitByteVector(mt19937 * mt, int size)
{
	uniform_int_distribution<> dis(0, 1);

	auto vec = new vector<byte>(size);

	for (int i = 0; i < size; i++) {
		vec->at(i) = byte(dis(*mt));
	}

	return vec;
}

byte getRandomBit(mt19937 * mt)
{
	uniform_int_distribution<> dis(0, 1);

	return byte(dis(*mt));
}

vector<byte>* getBinaryByteArray(vector<byte> bytes)
{
	int numBits = sizeof(byte)*bytes.size();
	vector<byte>* binary = new vector<byte>(numBits);
	// Mask the entire value up to this bit.
	int mask = 0x80;

	for (int i = 0; i < numBits; i++)
	{
		// Take the byte the current bit belongs to.
		byte currentByte = bytes[i / sizeof(byte)];
		// Shift by the current bit's index within the byte.
		int shiftBy = i % sizeof(byte);
		// If the bit is zero the entire value will be zero.
		// Cast the result back to byte (numbers are int by default).
		(*binary)[i] = (byte)((currentByte << shiftBy & mask) == 0 ? 0 : 1);
	}

	return binary;
}

vector<byte>* readFromString(string str)
{
	auto fromStr = explode(str, ' ');
	int numBytes = fromStr.size();
	auto resVec = new vector<byte>(numBytes);

	//go over fromStr and set the first char in to resVec as byte
	for (int i = 0; i < numBytes; i++) {
		(*resVec)[i] = fromStr[i][0];
	}

	return resVec;
}
