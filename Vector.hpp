#pragma once

template<class T, unsigned int n>
class Vector
{
	T x[n];
public:
	Vector(void);
	Vector(T*, unsigned int);
	~Vector(void);

	// Accessors
	T coeff(unsigned int);
	void coeff(T, unsigned int);

	// Operators


	// Class technical information
	unsigned int size();
};

////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////

template<class T, unsigned int n>
Vector<T,n>::Vector(void)
{
	for(unsigned int i=0; i<n; i++)
		x[i] = 0;
}

template<class T, unsigned int n>
Vector<T,n>::Vector(T* _data, unsigned int _n)
{
	// Check for size match
	if(_n > n)
		_n = n;

	for(unsigned int i=0; i<_n; i++)
		x[i] = _data[i];
}

template<class T, unsigned int n>
Vector<T,n>::~Vector(void)
{
}

//////////////////////////////////////////////////////////
// Accessors
//////////////////////////////////////////////////////////

template<class T, unsigned int n>
T Vector<T, n>::coeff(unsigned int i)
{
	return x[i];
}

template<class T, unsigned int n>
void Vector<T, n>::coeff(T t, unsigned int i)
{
	if(i>=n)
		return;

	x[i] = t;
}

//////////////////////////////////////////////////////////
// Operators
//////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////
// Technical Information
//////////////////////////////////////////////////////////

template<class T, unsigned int n>
unsigned int Vector<T,n>::size()
{
	return n;
}
