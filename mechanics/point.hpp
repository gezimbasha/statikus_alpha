#pragma once
#include "../math/vector.hpp"
#include <vector>
using namespace std;

// Standard axis enumeration
enum axis {
	x,
	y,
	z
};

template<class T, unsigned int n>
class Point
{
private:
	Vector<T,n> m_vPosition;
	Vector<T,n> m_vForces;
public:
	Point();
	Point(Vector<T,n> pos);
	Point(T, ...);
	~Point(void);

	// Position Accessors
	Vector<T,n> position();
	T component(axis);
	void setPosition(Vector<T,n>);
	
	// Forces
	Vector<T,n> force();
	void addForce(Vector<T,n>);
	void addForces(Vector<T,n>,...);

	// Distance
	T distance(Point);
	T distance(Point,axis);

	// Mechanics
	Vector<T,n> torque(Point);
};

/////////////////////////////////////////////
// Constructors
////////////////////////////////////////////

template<class T, unsigned int n>
Point<T,n>::Point()
{
}

template<class T, unsigned int n>
Point<T,n>::Point(Vector<T,n> pos) : m_vPosition(pos)
{
}

template<class T, unsigned int n>
Point<T,n>::Point(T x, ...)
{
	auto x0 = x;
	m_vPosition.coeff(x0,0);
	va_list args;
	va_start(args, x);
		for(int i=1; i<n; i++)	
			m_vPosition.coeff(va_arg(args, T),i);
	va_end(args);
}

template<class T, unsigned int n>
Point<T,n>::~Point()
{
}

///////////////////////////////////////////////
// Accessors
//////////////////////////////////////////////

template<class T, unsigned int n>
Vector<T,n> Point<T,n>::position()
{
	return m_vPosition;
}

template<class T, unsigned int n>
void Point<T,n>::setPosition(Vector<T,n> v)
{
	m_vPosition = v;
}

template<class T, unsigned int n>
T Point<T,n>::component(axis i)
{
	return m_vPosition.coeff(i);
}

template<class T, unsigned int n>
T Point<T,n>::distance(Point<T,n> pos)
{
	Vector<T,n> dist = this->position()-pos.position();
	return dist.magnitude();
}

template<class T, unsigned int n>
T Point<T,n>::distance(Point<T,n> pos, axis i)
{
	Vector<T,n> dist = this->position()-pos.position();
	return dist.coeff(i);
}

/////////////////////////////////////////////
// Force Accessors
////////////////////////////////////////////

template<class T, unsigned int n>
Vector<T,n> Point<T,n>::force()
{
	return m_vForces;
}

template<class T, unsigned int n>
void Point<T,n>::addForce(Vector<T,n> F)
{
	m_vForces += F;
}


template<class T, unsigned int n>
void Point<T,n>::addForces(Vector<T,n> V, ...)
{
	typedef Vector<T,n> F;
	F F0 = V;
	m_vForces += F0;
	va_list args;
	va_start(args, V);	
	m_vForces += va_arg(args,F);
	va_end(args);
}

/////////////////////////////////////////////
// Mechanics
////////////////////////////////////////////

template<class T, unsigned int n>
Vector<T,n> Point<T,n>::torque(Point<T,n> P)
{
	Point<T,n> tmp = *this;
	Vector<T,n> df =  P.position()-tmp.position();
	return df.cross(P.force());
}

/////////////////////////////////////////////
// Typedefs
////////////////////////////////////////////

typedef Point<double,2> Point2d;
typedef Point<double,3> Point3d;