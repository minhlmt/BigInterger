#include <iostream>

#include "BigInteger.h"
using namespace std;

int main(int argc, char* argv[])
{
	//BigInteger a("123456789123456789123456789123456789");
	//BigInteger c = a.powMod(500, 7);
	//cout << string(c);

	BigInteger a("213216546548749871532121354654654897987984651321354687987");
	BigInteger b("345566");
	BigInteger plus = a + b;
	BigInteger substract = a - b;
	BigInteger mul = a * b;
	BigInteger divide = a / b;

	
	cout << string(substract) << endl;
	
	return 0;

}

