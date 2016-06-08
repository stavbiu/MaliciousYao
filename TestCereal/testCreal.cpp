#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include "classes.h"
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <cereal/archives/binary.hpp>
//#include <cereal/archives/portable_binary.hpp>
#include <cereal/archives/xml.hpp>
#include <cereal/archives/json.hpp>

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

}