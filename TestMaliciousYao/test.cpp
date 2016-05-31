#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <vector>
#include <string>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

#include <MaliciousYao/include/common/CommonMaliciousYao.hpp>

using namespace std;

TEST_CASE("Common methods", "[]") {

	SECTION("range_int_vector") {
		vector<int> v;

		//Crate an indices array from 0 to inputArray size
		boost::push_back(v, boost::irange(0, 5));

		REQUIRE(v[4] == 4);
		REQUIRE(v[3] == 3);
		REQUIRE(v[2] == 2);
		REQUIRE(v[1] == 1);
		REQUIRE(v[0] == 0);
		REQUIRE(v.size() == 5);
	}

	SECTION("copy_vector_to_shared_ptr_vector") {
		vector<int> indices = {1,2,3,4,5};
		shared_ptr<vector<int>> intArr(new vector<int>(indices.size()));
		copy(indices.begin(), indices.end(), inserter(*intArr.get(), intArr->begin()));

		for (int i = 0; i < indices.size(); i++) {
			REQUIRE(indices[i] == (*intArr)[i]);
		}
	}

	SECTION("write byte string to file and read") {
		// clean and create the test file
		remove("byte_string_test.txt");
		std::ofstream outfile("byte_string_test.txt");
		vector<byte> vec = { (byte)0, (byte)1, (byte)0, (byte)0, (byte)1 };
		string toSend = vectorToString(vec);
		outfile << toSend << std::endl;
		outfile.close();

		// read the file as config file
		std::ifstream infile("byte_string_test.txt");
		string line;
		getline(infile, line);

		/*vector<byte>* inputVector = new vector<byte>(5);
		auto fromLine = explode(line, ' ');
		for (int i = 0; i < 5; i++)
			(*inputVector)[i] = fromLine[i][0];
		*/
		auto inputVector = readByteVectorFromString(line);

		for (int i = 0; i < 5; i++) {
			REQUIRE(vec[i] == inputVector[i]);
		}
		infile.close();

	}

	SECTION("write long string to file and read") {
		// clean and create the test file
		remove("long_string_test.txt");
		std::ofstream outfile("long_string_test.txt");
		vector<long> vec = { 1, 222, 5, 3, 99959 };
		string toSend = vectorToString(vec);
		outfile << toSend << std::endl;
		outfile.close();

		// read the file as config file
		std::ifstream infile("long_string_test.txt");
		string line;
		getline(infile, line);

		/*vector<byte>* inputVector = new vector<byte>(5);
		auto fromLine = explode(line, ' ');
		for (int i = 0; i < 5; i++)
		(*inputVector)[i] = fromLine[i][0];
		*/
		auto inputVector = readLongVectorFromString(line);

		for (int i = 0; i < 5; i++) {
			REQUIRE(vec[i] == inputVector[i]);
		}
		infile.close();

	}

	SECTION("print dynamic format") {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 2; j++) {
				boost::format fmter("i: %1%, j: %2%\n");
				fmter % i;
				fmter % j;
				cout << fmter.str();
			}
		}
	}

	SECTION("copy vector") {
		//make matrix a
		vector<vector<int>> a(3);
		int num = 0;
		int size = 2;
		for (int i = 0; i < 3; i++) {
			a[i] = vector<int>(size);
			for (int j = 0; j < size; j++) {
				a[i][j] = num;
				num++;
			}
		}

		//copy to one vector test
		vector<int> test(3*size);
		int t = 0;
		for (int i = 0; i < 3; i++) {
			std::copy_n(a[i].begin(), size, &test[t]);
			t += size;
		}
		//test
		for (int i = 0; i < 3 * size; i++) {
			REQUIRE(test[i] == i);
		}
	}

}