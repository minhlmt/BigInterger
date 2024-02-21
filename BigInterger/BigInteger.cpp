#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <typeinfo>
#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include "BigInteger.h"
#define MAX 10000 // for strings
using namespace std;

BigInteger::BigInteger() // empty constructor initializes zero
{
	number = "0";
	sign = false;
}
//-------------------------------------------------------------
BigInteger::BigInteger(string s) // "string" constructor
{
	if (isdigit(s[0])) // if not signed
	{
		setNumber(s);
		sign = false; // +ve
	}
	else
	{
		setNumber(s.substr(1));
		sign = (s[0] == '-');
	}
}

//-------------------------------------------------------------
BigInteger::BigInteger(int n) // "int" constructor
{
	stringstream ss;
	string s;
	ss << n;
	ss >> s;


	if (isdigit(s[0])) // if not signed
	{
		setNumber(s);
		setSign(false); // +ve
	}
	else
	{
		setNumber(s.substr(1));
		setSign(s[0] == '-');
	}
}
//-------------------------------------------------------------
void BigInteger::setNumber(string s)
{
	number = s;
}
//-------------------------------------------------------------
const string& BigInteger::getNumber() // retrieves the number
{
	return number;
}
//-------------------------------------------------------------
void BigInteger::setSign(bool s)
{
	sign = s;
}
//-------------------------------------------------------------
const bool& BigInteger::getSign()
{
	return sign;
}
//-------------------------------------------------------------
// returns the absolute value
BigInteger BigInteger::absolute()
{
	return BigInteger(getNumber()); // +ve by default
}
//-------------------------------------------------------------
void BigInteger::operator = (BigInteger b)
{
	setNumber(b.getNumber());
	setSign(b.getSign());
}
//-------------------------------------------------------------
bool BigInteger::operator == (BigInteger b)
{
	return equals((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator != (BigInteger b)
{
	return !equals((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator > (BigInteger b)
{
	return greater((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator < (BigInteger b)
{
	return less((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator >= (BigInteger b)
{
	return equals((*this), b)
		|| greater((*this), b);
}
//-------------------------------------------------------------
bool BigInteger::operator <= (BigInteger b)
{
	return equals((*this), b)
		|| less((*this), b);
}

//-------------------------------------------------------------
BigInteger BigInteger::operator + (BigInteger b)
{
	BigInteger addition;
	if (getSign() == b.getSign()) // both +ve or -ve
	{
		addition.setNumber(add(getNumber(), b.getNumber()));
		addition.setSign(getSign());
	}
	else // sign different
	{
		if (absolute() > b.absolute())
		{
			addition.setNumber(subtract(getNumber(), b.getNumber()));
			addition.setSign(getSign());
		}
		else
		{
			addition.setNumber(subtract(b.getNumber(), getNumber()));
			addition.setSign(b.getSign());
		}
	}
	if (addition.getNumber() == "0") // avoid (-0) problem
		addition.setSign(false);

	return addition;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator - (BigInteger b)
{
	b.setSign(!b.getSign()); // x - y = x + (-y)
	return (*this) + b;
}
//-------------------------------------------------------------
BigInteger BigInteger::operator * (BigInteger b)
{
	BigInteger mul;

	mul.setNumber(multiply(getNumber(), b.getNumber()));
	mul.setSign(getSign() != b.getSign());

	if (mul.getNumber() == "0") // avoid (-0) problem
		mul.setSign(false);

	return mul;
}
//-------------------------------------------------------------
// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator / (BigInteger b)
{
	//long long den = toInt(b.getNumber());
	BigInteger div;

	div.setNumber(divide(getNumber(), b.getNumber()));
	div.setSign(getSign() != b.getSign());

	if (div.getNumber() == "0") // avoid (-0) problem
		div.setSign(false);

	return div;
}
//-------------------------------------------------------------
// Warning: Denomerator must be within "long long" size not "BigInteger"
BigInteger BigInteger::operator % (BigInteger b)
{
	BigInteger rem;
	rem.setNumber(modulo(getNumber(), b.getNumber()));
	rem.setSign(false);

	if (rem.getNumber() == "0") // avoid (-0) problem
		rem.setSign(false);

	return rem;
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator += (BigInteger b)
{
	(*this) = (*this) + b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator -= (BigInteger b)
{
	(*this) = (*this) - b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator *= (BigInteger b)
{
	(*this) = (*this) * b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator /= (BigInteger b)
{
	(*this) = (*this) / b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger& BigInteger::operator %= (BigInteger b)
{
	(*this) = (*this) % b;
	return (*this);
}
//-------------------------------------------------------------
BigInteger BigInteger::powMod(BigInteger m, BigInteger n)
{
	BigInteger x = *this;
	BigInteger res = 1;
	while (string(m).compare("0")) {
		if (m % 2 == 1)
		{
			res *= x;
			//res %= n;
		}
		x *= x;

		//x %= n;
		m /= 2;

	}
	return res;
}
//-------------------------------------------------------------
BigInteger::operator string() // for conversion from BigInteger to string
{
	string signedString = (getSign()) ? "-" : ""; // if +ve, don't print + sign
	signedString += number;
	return signedString;
}
//-------------------------------------------------------------

bool BigInteger::equals(BigInteger n1, BigInteger n2)
{
	return n1.getNumber() == n2.getNumber()
		&& n1.getSign() == n2.getSign();
}


//-------------------------------------------------------------
bool BigInteger::less(BigInteger n1, BigInteger n2)
{
	bool sign1 = n1.getSign();
	bool sign2 = n2.getSign();

	if (sign1 && !sign2) // if n1 is -ve and n2 is +ve
		return true;

	else if (!sign1 && sign2)
		return false;

	else if (!sign1) // both +ve
	{
		if (n1.getNumber().length() < n2.getNumber().length())
			return true;
		if (n1.getNumber().length() > n2.getNumber().length())
			return false;
		return n1.getNumber() < n2.getNumber();
	}
	else // both -ve
	{
		if (n1.getNumber().length() > n2.getNumber().length())
			return true;
		if (n1.getNumber().length() < n2.getNumber().length())
			return false;
		return n1.getNumber().compare(n2.getNumber()) > 0; // greater with -ve sign is LESS
	}
}
bool BigInteger::less(string n1, string n2)
{
	if (n1.length() < n2.length())
		return true;
	if (n1.length() > n2.length())
		return false;
	return n1 < n2;
}
//-------------------------------------------------------------
bool BigInteger::greater(BigInteger n1, BigInteger n2)
{
	return !equals(n1, n2) && !less(n1, n2);
}


//-------------------------------------------------------------
// adds two strings and returns their sum in as a string
string BigInteger::add(string number1, string number2)
{
	string add = (number1.length() > number2.length()) ? number1 : number2;
	char carry = '0';
	int differenceInLength = abs((int)(number1.size() - number2.size()));

	if (number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0'); // put zeros from left

	else// if(number1.size() < number2.size())
		number1.insert(0, differenceInLength, '0');

	for (int i = add.size() - 1; i >= 0; i--)
	{
		add[i] = ((carry - '0') + (number1[i] - '0') + (number2[i] - '0')) + '0';
		if (i != 0)
		{
			if (add[i] > '9')
			{
				add[i] -= 10;
				carry = '1';
			}
			else {
				carry = '0';
			}
		}
	}
	if (add[0] > '9') {
		add[0] -= 10;
		add.insert(0, 1, '1');
	}
	carry = '0';
	return add;
}

//-------------------------------------------------------------
// subtracts two strings and returns their sum in as a string
string BigInteger::subtract(string number1, string number2)
{
	string sub = (number1.length() > number2.length()) ? number1 : number2;
	int differenceInLength = abs((int)(number1.size() - number2.size()));

	if (number1.size() > number2.size())
		number2.insert(0, differenceInLength, '0');

	else
		number1.insert(0, differenceInLength, '0');

	for (int i = number1.length(); i >= 0; i--) {
		if (number1[i] < number2[i]) {
			number1[i] += 10;
			number1[i - 1]--;
		}
		sub[i] = (number1[i] - '0') - (number2[i] - '0') + '0';
	}

	while (sub[0] == '0' && sub.length() != 1) // erase leading zeros
		sub.erase(0, 1);

	return sub;
}

//-------------------------------------------------------------
// multiplies two strings and returns their sum in as a string
string BigInteger::multiply(string n1, string n2)
{
	if (n1.length() > n2.length())
		n1.swap(n2);

	string res = "0";
	for (int i = n1.length() - 1; i >= 0; i--)
	{
		string temp = n2;
		int currentDigit = n1[i] - '0';
		int carry = 0;

		for (int j = temp.length() - 1; j >= 0; j--)
		{
			temp[j] = ((temp[j] - '0') * currentDigit) + carry;

			if (temp[j] > 9)
			{
				carry = (temp[j] / 10);
				temp[j] -= (carry * 10);
			}
			else
				carry = 0;

			temp[j] += '0'; // back to string mood
		}

		if (carry > 0)
			temp.insert(0, 1, (carry + '0'));

		temp.append((n1.length() - i - 1), '0'); // as like mult by 10, 100, 1000, 10000 and so on
		res = add(res, temp); // O(n)
	}

	while (res[0] == '0' && res.length() != 1) // erase leading zeros
		res.erase(0, 1);

	return res;
}

string BigInteger::divide(string str1, string str2) {
	if (str2.length() == 1 && str2[0] == '0')
		return "Error divide 0";
	else if (less(str1, str2)) {
		return "0";
	}
	else {
		string res = "";
		string substr1 = str1.substr(0, str2.length());
		if ((less(substr1, str2))) {
			substr1 = str1.substr(0, str2.length() + 1);
		}
		int index = substr1.length() - 1;
		while (index < str1.length()) {
			if (less(substr1, str2)) {
				substr1 += str1[index];
			}
			if (substr1[0] == '0') {
				substr1.erase(0, 1);
			}
			for (int i = 1; i <= 10; i++) {
				int i_temp = i;
				string mul = multiply(to_string(i), str2);
				if (less(mul, substr1) || mul == substr1) {
					if (index == str1.length()) {
						res += to_string(i_temp);
						break;
					}
					continue;
				}
				if (!less(mul, substr1)) {
					i_temp = i_temp - 1;
				}
				res += to_string(i_temp);
				substr1 = subtract(substr1, multiply(to_string(i_temp), str2));
				break;
			}
			index++;
		}
		return res;
	}

}
string BigInteger::modulo(string str1, string str2) {
	string quotient = divide(str1, str2);
	string mul = multiply(quotient, str2);
	string res = subtract(str1, mul);
	return res;
}

//-------------------------------------------------------------
// converts long long to string
string BigInteger::toString(long long n)
{
	stringstream ss;
	string temp;

	ss << n;
	ss >> temp;

	return temp;
}

//-------------------------------------------------------------
// converts string to long long
long long BigInteger::toInt(string s)
{
	long long sum = 0;

	for (int i = 0; i < s.length(); i++)
		sum = (sum * 10) + (s[i] - '0');

	return sum;
}

#endif