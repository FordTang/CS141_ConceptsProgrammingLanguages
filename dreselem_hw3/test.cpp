#include "vector_key.hpp"

#include <sstream>
#include <assert.h>

int main(int argc, char **argv) {
	MathVector<int> v1(3);
	v1[0] = 2;
	v1[1] = 4;
	v1[2] = 3;

	{
		MathVector<int> v2 = v1;
		std::stringstream ss;
		ss << v2;
		assert(v1 == v2);
		assert(ss.str() == "(2,4,3)");
	}

	{
		std::stringstream ss;
		assert(v1 * v1 == 29);
	}

	{
		MathVector<int> v2(3);
		v2[0] = 4;
		v2[1] = 0;
		v2[2] = 1;
		std::stringstream ss;
		ss << (v1 + v2);
		assert(v1 != v2);
		assert(ss.str() == "(6,4,4)");
	}

	{
		MathVector<int> v2(3);
		v2[0] = 4;
		v2[1] = 0;
		v2[2] = 1;
		v2 = v1;
		std::stringstream ss;
		ss << v2;
		assert(v1 == v2);
		assert(ss.str() == "(2,4,3)");
	}

	{
		MathVector<int> v2 = v1*2;
		std::stringstream ss;
		ss << v2;
		assert(ss.str() == "(4,8,6)");
	}

	std::cout << "tests passed" << std::endl;
}