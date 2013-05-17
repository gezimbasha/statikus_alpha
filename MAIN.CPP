#include <iostream>
#include "math/Vector.hpp"
#include "mechanics/point.hpp"

using namespace std;

int main()
{
	Vector<double,n> A;

	cout << "Madhesia e A = " << A.size() << endl;

	for(int i=0; i<n; i++)
		cout << "A[" << i << "]=" << A.coeff(i) << endl;

	A.coeff(3.95, 19);
		
	for(int i=0; i<n; i++)
		cout << "A[" << i << "]=" << A.coeff(i) << endl;

	return 0;
}
