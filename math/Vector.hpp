#pragma once
#include <stdarg.h>
#include <iostream>
#include <math.h>

using namespace std;

template<class T, unsigned int n>
class Vector
{
	T x[n];
public:
	//Constructors
	Vector();
	Vector(T X, ...);
	Vector(T*, unsigned int);
	Vector(T);
	~Vector(void);

	// Accessors
	T coeff(unsigned int) const;
	void coeff(T, unsigned int);

	// Friend Operators
	template<class t, unsigned int N> friend ostream& operator << (ostream&, const Vector<T,n>&);

	// Accessor Operators
	T operator[](unsigned int);
	T operator()(unsigned int);
	
	// Compound Assignment Operators
	Vector& operator=(const Vector &);
	Vector& operator+=(const Vector &);
	Vector& operator-=(const Vector &);
	Vector& operator*=(const T);
	Vector& operator/=(const T);
	
	// Binary Arithmetic Operators
	const Vector operator + (const Vector &) const;
	const Vector operator - (const Vector &) const;
	const Vector operator * (const T ) const;
	const Vector operator / (const T ) const;

	// Boolean Operators
	bool operator==(const Vector &) const;
	bool operator!=(const Vector &) const;

	// Vector Operations
	Vector operator - (void) const;
	Vector normalize(void) const;
	T operator*(const Vector &) const;
		
	T magnitude() const;
	T dot(const Vector&) const;
	Vector<T,3> cross(const Vector<T,3>&) const;
	// Technical Information
	unsigned int size();
};

////////////////////////////////////////////////////////////////////////
// Constructors
////////////////////////////////////////////////////////////////////////

template<class T, unsigned int n>
Vector<T,n>::Vector()
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

//Uniform seed of t
template<class T, unsigned int n>
Vector<T,n>::Vector(T t)
{
	for(unsigned int i=0; i<n; i++)
		x[i] = t;
}

template<class T, unsigned int n>
Vector<T,n>::Vector(T X, ...)
{
	x[0] = X;
	va_list args;
	va_start(args, X);
		for(int i=1; i<n; i++)	
			x[i] = va_arg(args, T);
	va_end(args);
}

template<class T, unsigned int n>
Vector<T,n>::~Vector(void)
{
}

//////////////////////////////////////////////////////////
// Accessors
//////////////////////////////////////////////////////////

template<class T, unsigned int n>
T Vector<T, n>::coeff(unsigned int i) const
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
template<class T, unsigned int n>
ostream& operator << (ostream& os, const Vector<T,n> &A)
{
	for(int i=0; i<n; i++)
		os << A.coeff(i) << endl;

	return os;
}

template<class T, unsigned int n>
T Vector<T,n>::operator[](unsigned int i)
{
	return (x[i]);
}

template<class T, unsigned int n>
T Vector<T,n>::operator()(unsigned int i)
{
	return (x[i]);
}

template<class T, unsigned int n>
Vector<T,n>& Vector<T,n>::operator=(const Vector<T,n> &rhs)
{
	if(this != &rhs)
	{
		for(unsigned int i=0; i<n; i++){
			this->coeff(rhs.coeff(i),i);
		}
	}
		
	return *this;
}

template<class T, unsigned int n>
Vector<T,n>& Vector<T,n>::operator+=(const Vector<T,n> &rhs)
{
	for(unsigned int i=0; i<n; i++)
		this->coeff((this->coeff(i)+rhs.coeff(i)),i);
	return *this;
}

template<class T, unsigned int n>
Vector<T,n>& Vector<T,n>::operator-=(const Vector<T,n> &rhs)
{
	for(unsigned int i=0; i<n; i++)
		this->coeff((this->coeff(i)-rhs.coeff(i)),i);
	return *this;
}

template<class T, unsigned int n>
Vector<T,n>& Vector<T,n>::operator*=(const T t)
{
	for(unsigned int i=0; i<n; i++)
		this->coeff((this->coeff(i)*t),i);
	return *this;
}

template<class T, unsigned int n>
Vector<T,n>& Vector<T,n>::operator/=(const T t)
{
	// Division by zero not allowed, return identity;
	if(t == 0) return *this;

	for(unsigned int i=0; i<n; i++)
		this->coeff((this->coeff(i)/t),i);
	return *this;

}

template<class T, unsigned int n>
const Vector<T,n> Vector<T,n>::operator+(const Vector<T,n> &rhs) const
{
	Vector<T,n> rs = *this;
	rs += rhs;
	return rs;
}

template<class T, unsigned int n>
const Vector<T,n> Vector<T,n>::operator-(const Vector<T,n> &rhs) const
{
	Vector<T,n> rs = *this;
	rs -= rhs;
	return rs;
}

template<class T, unsigned int n>
const Vector<T,n> Vector<T,n>::operator*(const T rhs) const
{
	Vector<T,n> rs = *this;
	rs *= rhs;
	return rs;
}

template<class T, unsigned int n>
const Vector<T,n> Vector<T,n>::operator/(const T rhs) const
{
	Vector<T,n> rs = *this;
	rs /= rhs;
	return rs;
}

template<class T, unsigned int n>
bool Vector<T,n>::operator==(const Vector<T,n> &rhs) const
{
	int j=0;
	for(unsigned int i=0; i<n; i++){
		//Increase j by one for each true value here
		if(this->coeff(i) == rhs.coeff(i))
			j++;
	}
	
	//If j==n it means that every checked coefficient returned true
	if(j==n)
		return true;
	else
		return false;
}

template<class T, unsigned int n>
bool Vector<T,n>::operator!=(const Vector<T,n> &rhs) const
{
	return !(*this == rhs);
}

template<class T, unsigned int n>
Vector<T,n> Vector<T,n>::operator - (void) const 
{
	Vector<T,n> res = *this;
	res*=-1;
	return res;
}

//////////////////////////////////////////////////////////
// Vector Operations
//////////////////////////////////////////////////////////

template<class T, unsigned int n>
T Vector<T,n>::magnitude() const 
{
	T res = 0;
	for(unsigned int i=0; i<n; i++)
		res += pow(x[i],2);

	return sqrt(res);
}

template<class T, unsigned int n>
Vector<T,n> Vector<T,n>::normalize(void) const 
{
	Vector<T,n> lhs = *this;
	T mag = lhs.magnitude();
	lhs /= mag;
	return lhs;
}

template<class T, unsigned int n>
T Vector<T,n>::dot(const Vector &rhs) const 
{
	Vector<T,n> lhs = *this;
	T res = 0;
	for(unsigned int i=0; i<n; i++)
		res += (lhs.coeff(i)*rhs.coeff(i));
	return res;
}

template<class T, unsigned int n>
T Vector<T,n>::operator*(const Vector &rhs) const 
{
	return Vector<T,n>::dot(rhs);
}

template<class T, unsigned int n>
Vector<T,3> Vector<T,n>::cross(const Vector<T,3> &rhs) const 
{
	Vector<T,3> res;
	Vector<T,3> lhs = *this;

	res.coeff((lhs.coeff(1)*rhs.coeff(2))-(lhs.coeff(2)*rhs.coeff(1)),0);
	res.coeff((lhs.coeff(2)*rhs.coeff(0))-(lhs.coeff(0)*rhs.coeff(2)),1);
	res.coeff((lhs.coeff(0)*rhs.coeff(1))-(lhs.coeff(1)*rhs.coeff(0)),2);

	return res;
}

//////////////////////////////////////////////////////////
// Technical Information
//////////////////////////////////////////////////////////

template<class T, unsigned int n>
unsigned int Vector<T,n>::size()
{
	return n;
}

//////////////////////////////////////////////////////////
// Typedefs
/////////////////////////////////////////////////////////
typedef Vector<double,2> Vector2d;
typedef Vector<double,3> Vector3d;
typedef Vector<int,2> Vector2i;
typedef Vector<int,3> Vector3i;
