#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "classes.h"
#include "aligned_allocator.hpp"
#include "aligned_allocator_no_destructor.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/types/memory.hpp>

#include <algorithm>

#define SIZE_OF_BLOCK 16//size in bytes

using namespace std;

TEST_CASE("Common methods", "[]") {

	SECTION("int"){
		int j = 5;
		{
			//writh to file
			std::ofstream os("dataInt.xml");
			cereal::XMLOutputArchive archive(os);

			archive(j);
		}
		//read from file
		std::ifstream is("dataInt.xml");
		cereal::XMLInputArchive archive(is);

		int r;
		archive(r);

		REQUIRE(r == j);
	}

	SECTION("vector int") {
		vector<int> j = {1,2,3,4,5};
		{
			//writh to file
			std::ofstream os("dataVecInt.xml");
			cereal::XMLOutputArchive archive(os);

			archive(j);
		}
		//read from file
		std::ifstream is("dataVecInt.xml");
		cereal::XMLInputArchive archive(is);

		vector<int> r;
		archive(r);

		REQUIRE(r == j);
	}

	SECTION("vector int - Binary") {
		vector<int> j = { 1,2,3,4,5 };
		//std::stringstream ss("dataVecIntBinary.bin");
		{
			//writh to file
			std::ofstream os("dataVecIntBinary");
			std::ios::binary;
			cereal::BinaryOutputArchive oarchive(os);

			oarchive(j);
		}
		//read from file
		std::ifstream is("dataVecIntBinary");
		std::ios::binary;
		cereal::BinaryInputArchive iarchive(is);

		vector<int> r;
		iarchive(r);

		REQUIRE(r == j);
	}



	SECTION("XML file test") {
		level2 myLevel2;
		myLevel2.initVectors(4, 2);

		{
			//writh to file
			std::ofstream os("data.xml");
			cereal::XMLOutputArchive archive(os);

			archive(myLevel2);
		}
		//read from file
		std::ifstream is("data.xml");
		cereal::XMLInputArchive archive(is);

		level2 inputLevel2;

		archive(inputLevel2);

		REQUIRE(inputLevel2 == myLevel2);
	}

	SECTION("JSON file test") {
		level2 myLevel2;
		myLevel2.initVectors(4, 2);

		{
			//writh to file
			std::ofstream os("dataJSON.json");
			cereal::JSONOutputArchive  oarchive(os);

			oarchive(myLevel2);
		}
		//read from file
		std::ifstream is("dataJSON.json");
		cereal::JSONInputArchive iarchive(is);

		level2 inputLevel2;

		iarchive(inputLevel2);

		REQUIRE(inputLevel2 == myLevel2);
	}

	SECTION("binary file test") {
		level2 myLevel2;
		myLevel2.initVectors(4, 2);

		{
			//writh to file
			std::ofstream os("dataBinary");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(myLevel2);
		}
		//read from file
		std::ifstream is("dataBinary");
		cereal::BinaryInputArchive iarchive(is);

		level2 inputLevel2;

		iarchive(inputLevel2);

		REQUIRE(inputLevel2 == myLevel2);
	}

	SECTION("smart pointer test") {

		uniqueLevel2 myUniqueLevel2;

		{
			//writh to file
			std::ofstream os("smart_pointer_test");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(myUniqueLevel2);
		}

		REQUIRE(!myUniqueLevel2.checkNull());

		//read from file
		std::ifstream is("smart_pointer_test");
		cereal::BinaryInputArchive iarchive(is);

		uniqueLevel2 inputUniqueLevel2;

		iarchive(inputUniqueLevel2);

		REQUIRE(!inputUniqueLevel2.checkNull());

		REQUIRE(inputUniqueLevel2 == myUniqueLevel2);
	}

	SECTION("test block") {
		/*int16_t num = 12;
		__m128i test= _mm_set1_epi16(num);
		unique_ptr<byte> testByte((byte*)&test);
		{
			//writh to file
			std::ofstream os("blockTest");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(testByte);
		}
		//read from file
		std::ifstream is("blockTest");
		cereal::BinaryInputArchive iarchive(is);

		__m128i readTest;
		unique_ptr<byte> readTestByte;

		iarchive(readTestByte);

		REQUIRE(*readTestByte == *testByte);

		readTest = *(__m128i*)readTestByte.get();

		__m128i neq = _mm_xor_si128(readTest, test);
		REQUIRE(_mm_test_all_zeros(neq, neq));*/

		blockU test;
		test.mm = _mm_set1_epi16(12);

		{
			//writh to file
			std::ofstream os("blockTest");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(test.bytes);
		}

		//read from file
		std::ifstream is("blockTest");
		cereal::BinaryInputArchive iarchive(is);

		blockU readTest;

		iarchive(readTest.bytes);

		__m128i neq = _mm_xor_si128(readTest.mm, test.mm);
		REQUIRE(_mm_test_all_zeros(neq, neq));
	}

	SECTION("test unique_ptr<block>") {
		/*unique_ptr<block[]> test((block *)_mm_malloc(sizeof(block) * 2, SIZE_OF_BLOCK));

		test[0].mm = _mm_set1_epi16(12);
		test[0].mm = _mm_set1_epi16(10);
		*/

		/*block_ptr test;
	    test.mm = (__m128i *)_mm_malloc(sizeof(block) * 2, SIZE_OF_BLOCK);

		test.mm[0] = _mm_set1_epi16(12);
		test.mm[1] = _mm_set1_epi16(10);

		unique_ptr<byte> temp(test.bytes);

		{
			//writh to file
			std::ofstream os("blockTestUnique");
			cereal::BinaryOutputArchive  oarchive(os);

			

			oarchive(temp);
		}

		//read from file
		std::ifstream is("blockTestUnique");
		cereal::BinaryInputArchive iarchive(is);

		block_ptr readTest;

		iarchive(temp);

		readTest.bytes = temp.release();

		__m128i neq = _mm_xor_si128(readTest.mm[0], test.mm[0]);
		REQUIRE(_mm_test_all_zeros(neq, neq));

		neq = _mm_xor_si128(readTest.mm[1], test.mm[1]);
		REQUIRE(_mm_test_all_zeros(neq, neq));
		*/
	}

	SECTION("test block to vector") {
		block* test = (block *)_mm_malloc(sizeof(block) * 2, SIZE_OF_BLOCK);
		test[0] = _mm_set1_epi16(12);
		test[1] = _mm_set1_epi16(10);


		int byteNum = 2 * SIZE_OF_BLOCK;
		byte* temp = (byte*)test;
		//make byte vector of block*
		vector<byte> toSend(temp, temp + byteNum);
		
		{

			//writh to file
			std::ofstream os("blockTestToByte");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(toSend);
		}

		//read from file
		std::ifstream is("blockTestToByte");
		cereal::BinaryInputArchive iarchive(is);

		//vector<byte, aligned_allocator<byte, SIZE_OF_BLOCK>> readFile;
		vector<byte, aligned_allocator_no_destructor<byte, SIZE_OF_BLOCK>> readFile;

		iarchive(readFile);

		//from vector to block*
		block* readTest = (block*)&readFile[0];

		__m128i neq = _mm_xor_si128(readTest[0], test[0]);
		REQUIRE(_mm_test_all_zeros(neq, neq));

		neq = _mm_xor_si128(readTest[1], test[1]);
		REQUIRE(_mm_test_all_zeros(neq, neq));

		_aligned_free(test);
		_aligned_free(readTest);

	}

	SECTION("inheritance") {
		level2Son test;

		{
			//writh to file
			std::ofstream os("inheritance");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(test);
		}

		//read from file
		std::ifstream is("inheritance");
		cereal::BinaryInputArchive iarchive(is);

		level2 readFile;

		iarchive(readFile);

		level2* temp = &test;
		REQUIRE(*temp == readFile);
	}

	SECTION("shared_ptr") {
		shared_ptr<level2> test(new level2());

		{
			//writh to file
			std::ofstream os("shared_ptr");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(test);
		}

		//read from file
		std::ifstream is("shared_ptr");
		cereal::BinaryInputArchive iarchive(is);

		shared_ptr<level2> readFile;

		iarchive(readFile);

		REQUIRE(test->operator==(*readFile.get()));
	}

	SECTION("object with smart_ptr") {
		vector<shared_ptr<level3>> test(2);
		test[0] = shared_ptr<level3>(new level3());
		test[1] = shared_ptr<level3>(new level3());

		{
			//writh to file
			std::ofstream os("shared_ptr");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(test);
		}

		//read from file
		std::ifstream is("shared_ptr");
		cereal::BinaryInputArchive iarchive(is);

		vector<shared_ptr<level3>> readFile;

		iarchive(readFile);

		REQUIRE(test[0]->operator==(*readFile[0].get()));
		REQUIRE(test[1]->operator==(*readFile[1].get()));
	}

	SECTION("2 hierarchy smart_ptr ") {
		level4 test;

		{
			//writh to file
			std::ofstream os("shared_ptr");
			cereal::BinaryOutputArchive  oarchive(os);

			oarchive(test);
		}

		//read from file
		std::ifstream is("shared_ptr");
		cereal::BinaryInputArchive iarchive(is);

		level4 readFile;

		iarchive(readFile);

		REQUIRE(test == readFile);
	}


}