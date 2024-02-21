#include <iostream>

#include "BigInteger.h"
using namespace std;

int main(int argc, char* argv[])
{
	//BigInteger a("123456789123456789123456789123456789");
	//BigInteger c = a.powMod(500, 7);
	//cout << string(c);

	BigInteger a("213212354654563213215646849846151321");
	BigInteger b("200");

	BigInteger c = a / b;

	cout << string(c);
	return 0;

}

