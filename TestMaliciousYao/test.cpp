#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "catch.hpp"
#include <vector>
#include <boost/range/irange.hpp>
#include <boost/range/algorithm_ext/push_back.hpp>

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
}