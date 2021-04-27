#pragma once

#include <iostream>

using std::ostream;



struct KeyStruct
{
	explicit KeyStruct(int d);
	KeyStruct(const KeyStruct& ks);
	~KeyStruct();
	KeyStruct& operator =(const KeyStruct& ks);
	int data;
};

bool operator ==(const KeyStruct& lhs, const KeyStruct& rhs);
bool operator <(const KeyStruct& lhs, const KeyStruct& rhs);
bool operator >(const KeyStruct& lhs, const KeyStruct& rhs);
ostream& operator <<(ostream& os, const KeyStruct& key);



struct ValueStruct
{
	ValueStruct();
	explicit ValueStruct(char ch);
	ValueStruct(const ValueStruct& vs);
	~ValueStruct();
	ValueStruct& operator =(const ValueStruct& vs);
	char data;
};

bool operator ==(const ValueStruct& lhs, const ValueStruct& rhs);
ostream& operator <<(ostream& os, const ValueStruct& val);
