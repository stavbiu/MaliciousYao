#pragma once

#include <boost/algorithm/string.hpp>
#include <libscapi/include/primitives/DlogOpenSSL.hpp>
#include <libscapi/include/primitives/HashOpenSSL.hpp>
#include <libscapi/include/primitives/PrfOpenSSL.hpp>
#include <libscapi/include/primitives/Kdf.hpp>

using namespace std;


/**
* This class defines some primitives objects to use in the protocol.
*/
class CryptoPrimitives {
private:
	mt19937 random = get_seeded_random();

	OpenSSLDlogECF2m* dlog;

	OpenSSLSHA256 hash;

	HKDF kdf;

	OpenSSLAES aes;

public:
	//constructor
	CryptoPrimitives(string dlogfile) : kdf(&OpenSSLHMAC()) {
		dlog = new OpenSSLDlogECF2m(dlogfile, string("K-233"),this->random);
	};	

	//distructor
	~CryptoPrimitives() {
		delete this->dlog;
	}

	//get primitives
	mt19937* getRandom() { return &(this->random); }
	OpenSSLDlogECF2m* getDlog() { return this->dlog; }
	OpenSSLSHA256* getHash() { return &(this->hash); }
	HKDF* getHKDF() { return &(this->kdf); }
	OpenSSLAES* getAES(){ return &(this->aes); }


};