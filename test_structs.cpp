#include "test_structs.h"
#include <iostream>

using std::cout, std::cerr, std::ostream;



KeyStruct::KeyStruct(int d) : data {d}
{
	cout << "KeyStruct(int), data = " << data << '\n';
}



KeyStruct::KeyStruct(const KeyStruct& ks) : data {ks.data}
{
	cout << "KeyStruct(const KeyStruct&), data = " << data << '\n';
}



KeyStruct::~KeyStruct()
{
	cout << "~KeyStruct(), data = " << data << '\n';
}



KeyStruct& KeyStruct::operator=(const KeyStruct& ks)
{
	data = ks.data;
	return *this;
}



bool operator ==(const KeyStruct& lhs, const KeyStruct& rhs)
{
	return lhs.data == rhs.data;
}



bool operator <(const KeyStruct& lhs, const KeyStruct& rhs)
{
	return lhs.data < rhs.data;
}



bool operator >(const KeyStruct& lhs, const KeyStruct& rhs)
{
	return lhs.data > rhs.data;
}



ostream& operator <<(ostream& os, const KeyStruct& key)
{
	return os << key.data;
}


//-----------------------------------------------------------------------------


ValueStruct::ValueStruct() : data {0}
{
	cout << "ValueStruct(), data = 0\n";
}



ValueStruct::ValueStruct(char ch) : data {ch}
{
	cout << "ValueStruct(char), data = " << data << '\n';
}



ValueStruct::ValueStruct(const ValueStruct& vs) : data {vs.data}
{
	cout << "ValueStruct(const ValueStruct&), data = " << data << '\n';
}



ValueStruct::~ValueStruct()
{
	cout << "~ValueStruct(), data = " << data << '\n';
}



ValueStruct& ValueStruct::operator=(const ValueStruct& vs)
{
	data = vs.data;
	return *this;
}



bool operator ==(const ValueStruct& lhs, const ValueStruct& rhs)
{
	return lhs.data == rhs.data;
}



ostream& operator <<(ostream& os, const ValueStruct& val)
{
	return os << val.data;
} 
