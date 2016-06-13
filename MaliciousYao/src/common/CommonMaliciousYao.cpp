#include "../../include/common/CommonMaliciousYao.hpp"


vector<int> circuitGetLabels(GarbledBooleanCircuit* gbc, int party)
{
	Preconditions::checkIntegerInRange(party, 1, 2);
	return gbc->getInputWireIndices(party);
}

vector<byte> makeRandomBitByteVector(mt19937 * mt, int size)
{
	uniform_int_distribution<> dis(0, 1);

	vector<byte> vec(size);

	for (int i = 0; i < size; i++) {
		vec[i] = byte(dis(*mt));
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

vector<byte> readByteVectorFromString(string str, const char separator)
{
	auto fromStr = explode(str, separator);
	int numBytes = fromStr.size();
	vector<byte> resVec(numBytes);

	//go over fromStr and set the first char in to resVec as byte
	for (int i = 0; i < numBytes; i++) {
		resVec[i] = fromStr[i][0];
	}

	return resVec;
}

vector<long> readLongVectorFromString(string str, const char separator)
{
	auto fromStr = explode(str, separator);
	int num = fromStr.size();
	vector<long> resVec(num);

	//go over fromStr and set the first char in to resVec as byte
	for (int i = 0; i < num; i++) {
		resVec[i] = std::stol(fromStr[i]);
	}

	return resVec;
}

vector<int> readIntVectorFromString(string str, const char separator)
{
	auto fromStr = explode(str, separator);
	int num = fromStr.size();
	vector<int> resVec(num);

	//go over fromStr and set the first char in to resVec as byte
	for (int i = 0; i < num; i++) {
		resVec[i] = std::stoi(fromStr[i]);
	}

	return resVec;
}

vector<string> readStringVectorFromString(string str, const char separator)
{
	auto fromStr = explode(str, separator);
	return fromStr;
}

bool equalBlocks(block & a, block & b)
{
	long *ap = (long*)&a;
	long *bp = (long*)&b;
	if ((ap[0] == bp[0]) && (ap[1] == bp[1])) {
		return false;
	}
	else {
		return true;
	}
}

