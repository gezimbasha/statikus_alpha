#pragma once

#include "../math/Vector.hpp"

template<class T>
class Force
{
private:
	Vector<T,3> m_tPosition;
	Vector<T,3> m_tForce;
	double m_xAngle, m_yAngle, m_zAngle;
	
public:
	Force(void);
	Force(Vector<T,3> pos, Vector<T,3> force);
	Force(T x, T y, T z, T fx, T fy, T fz);
	~Force();

};