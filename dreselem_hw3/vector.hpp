//Ford Tang
//46564602

#pragma once

#include <iostream>
#include <stdlib.h>
#include <string.h>

template
<typename T>
class MathVector
{
private:
	int size; // the number of elements in this Vector
	T * buf; // the base of the array of Ts, you must allocate it
public:
	MathVector( int n ) {
		// Vector v1(10); -- create a 10 element Vector
		size = n;
        	buf = new T[size];
	}

	~MathVector() {
		// destructor called automatically when a Vector dies
		//delete buf;
	}

	MathVector( const MathVector & v ) {
		// copy constructor
		size = v.size;
		buf = new T[size];
		for (int i = 0; i < size; i++)
			buf[i] = v.buf[i];
	}

	T & operator [] ( const int i ) {
		// return V[i];
		return buf[i];
	}

	const T & operator [] ( const int i ) const {
		// return V[i];
		return buf[i];
	}

	T operator * ( const MathVector & v ) const {
		// return this * v (dot product) - should throw exception if sizes don't match
		if(size != v.size)
			throw "Sizes do not match!";
		T total = 0;
		for (int i = 0; i < size; i++)
			total += buf[i] * v[i];
		return total;
	}

	MathVector operator + ( const MathVector & v ) const {
		// return this + v - should throw exception if sizes don't match
		if(size != v.size)
			throw "Sizes do not match!";
		MathVector result = MathVector(size);
		for (int i = 0; i < size; i++)
			result[i] = buf[i] + v[i];
		return result;
	}

	const MathVector & operator = ( const MathVector & v ) {
		// return (this = v);
		size = v.size;
		buf = v.buf;
		return *this;
	}

	bool operator == ( const MathVector & v ) const {
		// return this == v
		if (size != v.size)
			return false;
		for (int i = 0; i < size; i++)
			if (buf[i] != v[i])
				return false;
		return true;
	}

	bool operator != ( const MathVector & v ) const {
		// return this != v
		if (size != v.size)
			return true;
		for (int i = 0; i < size; i++)
			if (buf[i] != v[i])
				return true;
		return false;
	}

	MathVector operator * ( const int n ) const {
		// return this * n (scalar multiplication)
		for (int i = 0; i <  size; i++)
			buf[i] *= n;
		return *this;
	}

	friend std::ostream& operator << ( std::ostream & o, const MathVector & v ) {
		// cout << V2; -- prints the vector in format (v0, v1, v2,...,vn)
		o << "(";
		for (int i = 0; i < v.size - 1; i++)
			o << v[i] << ",";
		o << v[v.size - 1] << ")";
	}
};
