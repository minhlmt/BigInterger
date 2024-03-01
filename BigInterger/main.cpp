#include <iostream>

#include "BigInteger.h"
using namespace std;

int main(int argc, char* argv[])
{
	//BigInteger a("123456789123456789123456789123456789");
	//BigInteger c = a.powMod(500, 7);
	//cout << string(c);

	BigInteger a("213216546548749871532121354654654897987984651321354687987");
	BigInteger b("2365465413212154654874984416543513212316546874897465465456451619846548941687864547874987");
	BigInteger plus = a + b;
	BigInteger substract = a - b;
	BigInteger mul = a * b;
	BigInteger divide = a / b;

	
	cout << string(divide) << endl;
	
	return 0;

}

