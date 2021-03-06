#pragma once
#include <vector>
#include <string>
#include <cereal/archives/xml.hpp>	// for variable name
#include <cereal/types/vector.hpp>	// vector recognition
#include <cereal/types/string.hpp>  // string recognition

#include <cereal/types/base_class.hpp> // for inheritance

typedef unsigned char byte;
typedef __m128i block;

using namespace std;

class basic1{
	std::vector<int> vec;
	std::string str;
	unsigned int val;

public:
	basic1() {
		str = "Hello";
		val = 10;
		initVec();
	}

	void setVec(vector<int> newVec) { this->vec = newVec; }
	void setStr(string newStr) { this->str = newStr; }
	void setVal(int newVal) { this->val = newVal; }

	vector<int> getVec() { return this->vec; }
	string getString() { return this->str; }
	int getVal() { return this->val; }

	void initVec() {
		this->vec = vector<int>(this->val);
		for (unsigned int i = 0; i < val; i++) {
			vec[i] = i;
		}
	}

	bool operator==(const basic1& b) {
		if (!std::equal(this->vec.begin(), this->vec.end(), b.vec.begin()))
			return false;
		else if (this->str.compare(b.str) != 0)
			return false;
		else if (this->val != b.val)
			return false;
		else
			return true;		
	}

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(CEREAL_NVP(vec), CEREAL_NVP(str), CEREAL_NVP(val)); // serialize things by passing them to the archive
	}

};

class basic2 {
	vector<int> vecInt;
	vector<long> vecLong;
	vector<byte> vecByte;

public:
	basic2() { initVecs(5, 5, 5); }

	void setIntVec(vector<int> newVec) { this->vecInt = newVec; }
	void setLongVec(vector<long> newVec) { this->vecLong = newVec; }
	void setByteVec(vector<byte> newVec) { this->vecByte = newVec; }

	vector<int> getIntVec() { return this->vecInt; }
	vector<long> getLongVec() { return this->vecLong; }
	vector<byte> getByteVec() { return this->vecByte; }

	void initVecs(unsigned int vecIntNum, unsigned int vecLongNum, unsigned int vecByteNum) {
		this->vecInt = vector<int>(vecIntNum);
		for (unsigned int i = 0; i < vecIntNum; i++) {
			vecInt[i] = i;
		}

		this->vecLong = vector<long>(vecLongNum);
		for (unsigned int i = 0; i < vecIntNum; i++) {
			vecLong[i] = i;
		}

		this->vecByte = vector<byte>(vecByteNum);
		for (unsigned int i = 0; i < vecIntNum; i++) {
			vecByte[i] = (byte)i;
		}
	}

	bool operator==(const basic2& b) {
		if (!std::equal(this->vecInt.begin(), this->vecInt.end(), b.vecInt.begin()))
			return false;
		else if (!std::equal(this->vecLong.begin(), this->vecLong.end(), b.vecLong.begin()))
			return false;
		else if (!std::equal(this->vecByte.begin(), this->vecByte.end(), b.vecByte.begin()))
			return false;
		else
			return true;
	}

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(CEREAL_NVP(vecInt), CEREAL_NVP(vecLong), CEREAL_NVP(vecByte)); // serialize things by passing them to the archive
	}
};

class level1 {
	vector<basic1> vecBas1;
	basic2 bas2;
	double val;

public:
	level1(){
		vecBas1 = vector<basic1>(3);
		for (int i = 0; i < 3; i++) {
			vecBas1[i].setVal(i + 3);
			vecBas1[i].initVec();
		}
		bas2 = basic2();
		val = 0.9;
	}

	void addBas1(basic1 newBas) { vecBas1.push_back(newBas); }
	void setVal(float t) { this->val = t; }
	void setBas2(basic2 newBas) { this->bas2 = newBas; }

	vector<basic1> getVecBas1() { return this->vecBas1; }
	basic2 getBas2() { return this->bas2; }
	double getVal() { return this->val; }

	bool operator==(const level1& b) {
		if (!std::equal(this->vecBas1.begin(), this->vecBas1.end(), b.vecBas1.begin()))
			return false;
		else if (!(this->bas2 == b.bas2))
			return false;
		else if (this->val != b.val)
			return false;
		else
			return true;

	}

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(CEREAL_NVP(vecBas1), CEREAL_NVP(bas2), CEREAL_NVP(val)); // serialize things by passing them to the archive
	}
};

class level2 {

	vector<level1> vecLevel1;
	vector<basic2> vecBas2;

public:
	level2() { initVectors(4, 2); }

	vector<level1> getLevel1Vec() { return this->vecLevel1; }
	vector<basic2> getBasic2Vec() { return this->vecBas2; }

	void initVectors(unsigned int level1Num, unsigned int basic2Num) {
		this->vecLevel1 = vector<level1>(level1Num);
		this->vecLevel1[level1Num - 1].addBas1(basic1());
		this->vecLevel1[level1Num - 1].getVecBas1()[0].setVal(2);
		this->vecLevel1[level1Num - 1].getVecBas1()[0].initVec();

		this->vecBas2 = vector<basic2>(basic2Num);
		this->vecBas2[basic2Num - 1].initVecs(2, 2, 2);
	}

	bool operator==(const level2& b) {
		if (!std::equal(this->vecLevel1.begin(), this->vecLevel1.end(), b.vecLevel1.begin()))
			return false;
		else if (!std::equal(this->vecBas2.begin(), this->vecBas2.end(), b.vecBas2.begin()))
			return false;
		else
			return true;
	}

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(CEREAL_NVP(vecLevel1), CEREAL_NVP(vecBas2)); // serialize things by passing them to the archive
	}

};

class uniqueLevel2 {
	unique_ptr<level2> myLevel2;

public:
	uniqueLevel2() {
		myLevel2 = make_unique<level2>(level2());
	}

	bool operator==(const uniqueLevel2& b) {
		return (*this->myLevel2.get() == *b.myLevel2.get());
	}

	bool checkNull() { return myLevel2 == NULL; }

	template<class Archive>
	void save(Archive & archive) const {
		archive(myLevel2);
	}

	template<class Archive>
	void load(Archive & archive) {
		archive(myLevel2);
	}


	// This method lets cereal know which data members to serialize
	/*template<class Archive>
	void serialize(Archive & archive)
	{
		archive(CEREAL_NVP(myLevel2)); // serialize things by passing them to the archive
	}*/
};

union blockU {
	__m128i mm;
	byte bytes[16];
};

union block_ptr {
	__m128i* mm = nullptr;
	byte* bytes;
};

class level2Son : public level2 {
private:
	basic1 sonBasic1;

public:
	level2Son() :level2(){
		this->sonBasic1.setStr("In son!!");
	}

	bool operator==(const level2Son& b) {
		if (!(this->sonBasic1 == b.sonBasic1))
			return false;
		else
			return level2::operator==(b);

	}

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(cereal::base_class<level2>(this),CEREAL_NVP(sonBasic1)); // serialize things by passing them to the archive
	}

};

class level3 {
	shared_ptr<vector<level1>> vecLevel1;
	vector<shared_ptr<basic2>> vecBas2;

public:
	level3() { initVectors(4, 2); }

	//vector<level1> getLevel1Vec() { return this->vecLevel1; }
	//vector<basic2> getBasic2Vec() { return this->vecBas2; }

	void initVectors(unsigned int level1Num, unsigned int basic2Num) {
		this->vecLevel1 = shared_ptr<vector<level1>>(new vector<level1>(level1Num));
		this->vecLevel1->at(level1Num - 1).addBas1(basic1());
		this->vecLevel1->at(level1Num - 1).getVecBas1()[0].setVal(2);
		this->vecLevel1->at(level1Num - 1).getVecBas1()[0].initVec();

		this->vecBas2 = vector<shared_ptr<basic2>>(basic2Num);
		for (int i = 0; i < basic2Num; i++) {
			this->vecBas2[i] = shared_ptr<basic2>(new basic2());
		}
		this->vecBas2[basic2Num - 1]->initVecs(2, 2, 2);
	}

	bool operator==(const level3& b) {
		if (!std::equal(this->vecLevel1->begin(), this->vecLevel1->end(), b.vecLevel1->begin()))
			return false;
		else if (b.vecBas2.size() != this->vecBas2.size())
			return false;
		else 
			for (int i = 0; i < this->vecBas2.size(); i++) {
				if (!this->vecBas2[i]->operator==(*b.vecBas2[i]))
					return false;
			}
		return true;
	}

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(CEREAL_NVP(vecLevel1), CEREAL_NVP(vecBas2)); // serialize things by passing them to the archive
	}

};

class level4 {
	shared_ptr<vector<shared_ptr<level3>>> p;

public:

	level4() {
		p = shared_ptr<vector<shared_ptr<level3>>>(new vector<shared_ptr<level3>>(3));
		p->at(0) = shared_ptr<level3>(new level3());
		p->at(1) = shared_ptr<level3>(new level3());
		p->at(2) = shared_ptr<level3>(new level3());

		p->at(1)->initVectors(1, 1);
		p->at(2)->initVectors(3, 3);
	}

	bool operator==(const level4& b) {
		for (int i = 0; i < 3; i++) {
			if (!p->at(i)->operator==(*b.p->at(i)))
				return false;
		}
		return true;
	}

	// This method lets cereal know which data members to serialize
	template<class Archive>
	void serialize(Archive & archive)
	{
		archive(CEREAL_NVP(p)); // serialize things by passing them to the archive
	}
};
