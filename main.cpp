#include <iostream>

void CtorsTest();
void AssignmentTest();
void PutGetTest();
void InsertEraseTest();
void AtTest();
void OperSquareBracketsTest();
void MinMaxKeyTest();
void FloorCeilingKeyTest();
void SizeTest();
void EraseMinTest();
void EraseTest();
void TraverseTest();
void OperEqualTest();

void RBTPutGetTest();
void RBTEraseTest();
void RBTEraseTest2();



int main()
{
	std::cerr << std::boolalpha;
	
	CtorsTest();
	AssignmentTest();
	
	PutGetTest();
	InsertEraseTest();
	
	AtTest();
	OperSquareBracketsTest();
	
	MinMaxKeyTest();
	FloorCeilingKeyTest();
	
	SizeTest();
	
	EraseMinTest();
	EraseTest();
	
	TraverseTest();
	
	OperEqualTest();

	RBTPutGetTest();
	RBTEraseTest();
	RBTEraseTest2();
}
