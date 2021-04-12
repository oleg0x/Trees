#include "binary_search_tree.h"
#include "test_structs.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <string>

using namespace std;



void CtorsTest()
{
	{
		BinarySearchTree<int, char> bst;
		bst.PrintInorder();
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 0 && bst.Empty() );
	}
	
	{
		BinarySearchTree<int, char> bst1 { 
			{5, 'e'}, {8, 'h'}, {3, 'c'}, {1, 'a'}, {6, 'f'}, {4, 'd'} };
		bst1.PrintInorder();
		assert( bst1.Size() == 6 && !bst1.Empty() );
		
		BinarySearchTree<int, char> bst2(bst1);
		bst1.PrintInorder();
		bst2.PrintInorder();
		assert( bst1.Size() == 6 && !bst1.Empty() );
		assert( bst2.Size() == 6 && !bst2.Empty() );
		assert( bst1 == bst2 );
		
		BinarySearchTree<int, char> bst3(move(bst2));
		bst2.PrintInorder();
		bst3.PrintInorder();
		assert( bst2.Size() == 0 && bst2.Empty() );
		assert( bst3.Size() == 6 && !bst3.Empty() );
		assert( bst1 == bst3 && (bst2 == BinarySearchTree<int, char>()) );
	}
	
	cerr << "---------- CtorsTest is OK ----------\n\n";
}



void AssignmentTest()
{
	{
		BinarySearchTree<int16_t, int16_t> bst1 { 
			{5, 50}, {8, 80}, {3, 30}, {1, 10}, {4, 40} };
		bst1.PrintInorder();
	
		BinarySearchTree<int16_t, int16_t> bst2;
		bst2 = bst1;
		bst1.PrintInorder();
		bst2.PrintInorder();
		assert( bst1.Size() == 5 && !bst1.Empty() );
		assert( bst2.Size() == 5 && !bst2.Empty() );
		assert( bst1 == bst2 );
	
		bst2 = bst2;
		bst2.PrintInorder();
		assert( bst2.Size() == 5 && !bst2.Empty() );
		assert( bst1 == bst2 );
	
		BinarySearchTree<int16_t, int16_t> bst3;
		bst3 = move(bst1);
		bst1.PrintInorder();
		bst3.PrintInorder();
		assert( bst1.Size() == 0 && bst1.Empty() );
		assert( bst3.Size() == 5 && !bst3.Empty() );
		assert( bst3 == bst2 && (bst1 == BinarySearchTree<int16_t, int16_t>()) );
	
		bst3 = move(bst3);
		bst3.PrintInorder();
		assert( bst3.Size() == 5 && !bst3.Empty() );
		assert( bst3 == bst2 );
	}
	
	cerr << "---------- AssignmentTest is OK ----------\n\n";
}



void PutGetTest()
{
	{
		BinarySearchTree<int, string> bst;
	
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 0 && bst.Empty() );
		
		bst.Put(15, "bbbbb");
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 1 && !bst.Empty() );
		cerr << *bst.Get(15) << '\n';
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 1 && !bst.Empty() );

		bst.Put(15, "bbb");
		bst.Put(20, "ccc");
		bst.Put(10, "aaa");
		bst.PrintInorder();
		assert( bst.Size() == 3 && !bst.Empty() );
		assert( bst == (BinarySearchTree<int, string> { 
			{15, "bbb"}, {20, "ccc"}, {10, "aaa"} }) );
	
		if ( bst.Get(1).has_value() )  cerr << bst.Get(1).value();
		else  cerr << "key = 1 not found.\n";
	
		cerr << *bst.Get(10) << "  " << *bst.Get(15) << "  " << *bst.Get(20) << '\n';
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 3 && !bst.Empty() );
		assert( *bst.Get(10) == "aaa" && *bst.Get(15) == "bbb" && 
		        *bst.Get(20) == "ccc" );
	
		if ( bst.Get(20) )  cerr << *bst.Get(20) << '\n';
		else  cerr << "key = 20 not found.\n";
	}
	
	cerr << "---------- PutGetTest is OK ----------\n\n";
}



void InsertEraseTest()
{
	{
		BinarySearchTree<char, int> bst;
		assert( bst.Insert('b', 2222) == true );
		assert( bst.Insert('a', 1111) == true );
		assert( bst.Insert('c', 3333) == true );
		cerr << bst['a'] << "  " << bst['b'] << "  " << bst['c'] << '\n';
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 3 && !bst.Empty() );
		assert( bst['a'] == 1111 && bst['b'] == 2222 && bst['c'] == 3333 );
	
		assert( bst.Insert('c', 4444) == false );
		assert( bst.Insert('d', 4444) == true );
		cerr << bst['a'] << "  " << bst['b'] << "  " << bst['c'] << "  " 
		     << bst['d'] << '\n';
		assert( bst['a'] == 1111 && bst['b'] == 2222 && 
		        bst['c'] == 3333 && bst['d'] == 4444 );
	}

	{
		BinarySearchTree<int, char> bst;
		bst.Insert(5, 'e');
		bst.Insert(3, 'c');
		bst.Insert(8, 'h');
		bst.Insert(1, 'a');
		bst.Insert(4, 'd');
		bst.PrintInorder();
		assert( bst.Size() == 5 && !bst.Empty() );
		assert( bst == (BinarySearchTree<int, char> {
			{5, 'e'}, {3, 'c'}, {8, 'h'}, {1, 'a'}, {4, 'd'} }) );
		
		bst.Erase(3);
		bst.Erase(8);
		bst.PrintInorder();
		assert( bst.Size() == 3 && !bst.Empty() );
		assert( bst == (BinarySearchTree<int, char> {
			{5, 'e'}, {4, 'd'}, {1, 'a'} }) );
		
		bst.Erase(5);
		bst.Erase(1);
		bst.Erase(100);
		bst.PrintInorder();
		assert( bst.Size() == 1 && !bst.Empty() );
		assert( bst == (BinarySearchTree<int, char> { {4, 'd'} }) );
		
		bst.Erase(4);
		bst.Erase(4);
		bst.PrintInorder();
		assert( bst.Size() == 0 && bst.Empty() );
		assert( bst == (BinarySearchTree<int, char> {}) );
	}
	
	cerr << "---------- InsertEraseTest is OK ----------\n\n";
}



void AtTest()
{
	{
		BinarySearchTree<int16_t, float> bst;
		bst.Insert(1, 1.11);
		bst.Insert(2, 2.22);
		bst.Insert(3, 3.33);
		assert( bst.Size() == 3 && !bst.Empty() );
		cerr << bst.At(3) << "  " << bst.At(2) << "  " << bst.At(1) << '\n';
		assert( abs(bst.At(3) - 3.33) < 0.0001 &&
		        abs(bst.At(2) - 2.22) < 0.0001 &&
		        abs(bst.At(1) - 1.11) < 0.0001 );
		try {
			cerr << bst.At(10);
		}
		catch ( std::out_of_range& ex ) {
			cerr << "Key=10 not found!" << '\n';
		}
	}
	
	cerr << "---------- AtTest is OK ----------\n\n";	
}



void OperSquareBracketsTest()
{
	{
		BinarySearchTree<string, double> bst;
	
		bst["pi"] = 3.14159;
		bst["e"] = 2.71828;
		bst["Euler's"] = 0.57721;
		bst["Apery's"] = 1.202056;
		assert( bst.Size() == 4 && !bst.Empty() );
		assert( bst["pi"] == 3.14159 && bst["e"] == 2.71828 &&
		        bst["Euler's"] == 0.57721 && bst["Apery's"] == 1.202056 );
	
		cerr << bst["e"] << "  " << bst["pi"] << "  "
		     << bst["Apery's"] << "  " << bst["Euler's"] << '\n';
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 4 && !bst.Empty() );
		assert( bst["pi"] == 3.14159 && bst["e"] == 2.71828 &&
		        bst["Euler's"] == 0.57721 && bst["Apery's"] == 1.202056 );
	}
	
	cerr << "---------- OperSquareBracketsTest is OK ----------\n\n";
}



void MinMaxKeyTest()
{
	{
		BinarySearchTree<int, float> bst1;
		bst1[200] = 2.2;
		bst1[500] = 5.5;
		bst1[400] = 4.4;
		bst1[100] = 1.1;
		bst1[300] = 3.3;
		cerr << "Min: " << bst1.MinKey() << ",  Max: " << bst1.MaxKey() << ".\n";
		assert( bst1.MinKey() == 100 && bst1.MaxKey() == 500 );
	
		BinarySearchTree<char, int16_t> bst2;
		bst2.Insert('b', 2);
		bst2.Insert('d', 4);
		bst2.Insert('c', 3);
		bst2.Insert('a', 1);
		cerr << "Min: " << bst2.MinKey() << ",  Max: " << bst2.MaxKey() << ".\n";
		assert( bst2.MinKey() == 'a' && bst2.MaxKey() == 'd' );
	}
	
	cerr << "---------- MinMaxKeyTest is OK ----------\n\n";
}



void FloorCeilingKeyTest()
{
	{
		BinarySearchTree<int, float> bst1;
		bst1[200] = 2.2;
		bst1[500] = 5.5;
		bst1[400] = 4.4;
		bst1[100] = 1.1;
		bst1[300] = 3.3;

		try {
			cerr << "Floor(10): " << bst1.FloorKey(10);
		}
		catch ( std::out_of_range& ex ) {
			cerr << "No floor!";
		}
		cerr << ",  Ceiling(10): " << bst1.CeilingKey(10) << ".\n";
		assert( bst1.CeilingKey(10) == 100 );
	
		cerr << "Floor(150): " << bst1.FloorKey(150) 
		     << ",  Ceiling(150): " << bst1.CeilingKey(150) << ".\n";
		assert( bst1.FloorKey(150) == 100 && bst1.CeilingKey(150) == 200 );
	
		cerr << "Floor(320): " << bst1.FloorKey(320) 
		     << ",  Ceiling(320): " << bst1.CeilingKey(320) << ".\n";
		assert( bst1.FloorKey(320) == 300 && bst1.CeilingKey(320) == 400 );
	
		try {
			cerr << "Floor(510): " << bst1.FloorKey(510) 
			     << ",  Ceiling(510): " << bst1.CeilingKey(510) << ".\n";
		}
		catch ( std::out_of_range& ex ) {
			cerr << "No Ceiling!\n";
		}
		assert( bst1.FloorKey(510) == 500 );
	}
	
	cerr << "---------- FloorCeilingKeyTest is OK ----------\n\n";
}



void SizeTest()
{
	{
		BinarySearchTree<int16_t, int16_t> bst;
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
		assert( bst.Size() == 0 && bst.Empty() );
		bst.Put(5, 50);
		assert( bst.Size() == 1 && !bst.Empty() );
		bst.Insert(7, 70);
		assert( bst.Size() == 2 && !bst.Empty() );
		bst[2] = 20;
		assert( bst.Size() == 3 && !bst.Empty() );
		bst.Erase(7);
		assert( bst.Size() == 2 && !bst.Empty() );
		cerr << "Is empty: " << bst.Empty() << ",  size = " << bst.Size() << ".\n";
	}
	
	cerr << "---------- SizeTest is OK ----------\n\n";
}



void EraseMinTest()
{
	{
		BinarySearchTree<KeyStruct, ValueStruct> bst;
		bst.EraseMin();  // Erase from empty tree
		bst.PrintInorder();
		assert( bst.Size() == 0 && bst.Empty() );

		KeyStruct key1 = KeyStruct(10);
		KeyStruct key2 = KeyStruct(20);
		KeyStruct key3 = KeyStruct(30);
		KeyStruct key4 = KeyStruct(40);
		ValueStruct val1 = ValueStruct('a');
		ValueStruct val2 = ValueStruct('b');
		ValueStruct val3 = ValueStruct('c');
		ValueStruct val4 = ValueStruct('d');
	
		cerr << "Inserting keys and values...\n";
		bst.Insert(key2, val2);
		bst.Insert(key4, val4);
		bst.Insert(key1, val1);
		bst.Insert(key3, val3);
		bst.PrintInorder();
	
		cerr << "EraseMin()\n";
		bst.EraseMin();
		bst.PrintInorder();
		assert( bst.Size() == 3 && !bst.Empty() );
		assert( bst[key2] == val2 && bst[key3] == val3 && bst[key4] == val4 );
	
		cerr << "EraseMin()\n";
		bst.EraseMin();
		bst.PrintInorder();
		assert( bst.Size() == 2 && !bst.Empty() );
		assert( bst[key3] == val3 && bst[key4] == val4 );

		cerr << "EraseMin()\n";
		bst.EraseMin();
		bst.PrintInorder();
		assert( bst.Size() == 1 && !bst.Empty() );
		assert( bst[key4] == val4 );
	
		cerr << "EraseMin()\n";
		bst.EraseMin();
		bst.PrintInorder();
		assert( bst.Size() == 0 && bst.Empty() );
	
		cerr << "EraseMin()\n";
		bst.EraseMin();  // Erase from empty tree
		assert( bst.Size() == 0 && bst.Empty() );
	}
	
	cerr << "---------- EraseMinTest is OK ----------\n\n";
}



void EraseTest()
{
	{
		BinarySearchTree<KeyStruct, ValueStruct> bst;
		bst.Erase(KeyStruct(1));  // Erase from empty tree
		bst.PrintInorder();
		assert( bst.Size() == 0 && bst.Empty() );

		KeyStruct key1 = KeyStruct(10);
		KeyStruct key2 = KeyStruct(20);
		KeyStruct key3 = KeyStruct(30);
		KeyStruct key4 = KeyStruct(40);
		ValueStruct val1 = ValueStruct('a');
		ValueStruct val2 = ValueStruct('b');
		ValueStruct val3 = ValueStruct('c');
		ValueStruct val4 = ValueStruct('d');
	
		cerr << "Inserting keys and values...\n";
		bst.Insert(key2, val2);
		bst.Insert(key4, val4);
		bst.Insert(key1, val1);
		bst.Insert(key3, val3);
		bst.PrintInorder();
	
		bst.Erase(KeyStruct(2));  // Erase absent key
	
		bst.Erase(key2);
		bst.PrintInorder();
		assert( bst.Size() == 3 && !bst.Empty() );
	
		bst.Erase(key1);
		bst.PrintInorder();
		assert( bst.Size() == 2 && !bst.Empty() );
	
		bst.Erase(key3);
		bst.PrintInorder();
		assert( bst.Size() == 1 && !bst.Empty() );
	
		bst.Erase(key4);
		bst.PrintInorder();
		assert( bst.Size() == 0 && bst.Empty() );

		bst.Erase(KeyStruct(3));  // Erase absent key
	}
	
	cerr << "---------- EraseTest is OK ----------\n\n";
}



void TraverseTest()
{
	{
		BinarySearchTree<int, string> bst;
		bst.Insert(4, "DDD");
		bst.Insert(2, "BBB");
		bst.Insert(5, "EEE");
		bst.Insert(1, "AAA");
		bst.Insert(3, "CCC");
	
//		bst.TraverseInorder( [](int key, string value)
//			{ cerr << '(' << key << ", " << value << ") "; } );
		function<void(int, string)> func = [](int key, string value) 
			{ cerr << '(' << key << ", " << (value += "*") << ") "; };
		bst.TraverseInorder(func);
		cerr << '\n';
	}
	
	{
		BinarySearchTree<KeyStruct, ValueStruct> bst;

		KeyStruct key1 = KeyStruct(10);
		KeyStruct key2 = KeyStruct(20);
		KeyStruct key3 = KeyStruct(30);
		KeyStruct key4 = KeyStruct(40);
		KeyStruct key5 = KeyStruct(50);
		ValueStruct val1 = ValueStruct('a');
		ValueStruct val2 = ValueStruct('b');
		ValueStruct val3 = ValueStruct('c');
		ValueStruct val4 = ValueStruct('d');
		ValueStruct val5 = ValueStruct('e');
	
		bst.Insert(key4, val4);
		bst.Insert(key5, val5);
		bst.Insert(key2, val2);
		bst.Insert(key3, val3);
		bst.Insert(key1, val1);
		bst.PrintInorder();
	
		bst.Clear();
		bst.PrintInorder();
	}
	
	cerr << "---------- TraverseTest is OK ----------\n\n";
}



void OperEqualTest()
{
	{
		BinarySearchTree<int16_t, int16_t> bst1, bst2;
		cerr << (bst1 == bst2) << '\n';
		assert( bst1 == bst2 );
	}
	
	{
		BinarySearchTree<int16_t, int16_t> bst1 {{5, 50}};
		BinarySearchTree<int16_t, int16_t> bst2 {{3, 30}};
		BinarySearchTree<int16_t, int16_t> bst3 {{5, 50}};
		cerr << (bst1 == bst2) << ' ' << (bst1 == bst3) << ' ' 
		     << (bst2 == bst3) << '\n';
		assert( bst1 != bst2 && bst1 == bst3 && bst2 != bst3 );
	}
	
	{
		BinarySearchTree<int16_t, int16_t> bst1 { 
			{5, 50}, {8, 80}, {1, 10}, {4, 40} };
		BinarySearchTree<int16_t, int16_t> bst2 { 
			{5, 50}, {3, 30}, {8, 80}, {1, 10} };
		cerr << (bst1 == bst2) << ' ';
		assert( bst1 != bst2 );
		
		bst2.Erase(3);
		bst2.Insert(4, 40);
		cerr << (bst1 == bst2) << ' ';
		assert( bst1 == bst2 );
		
		bst2[5] = 55;
		cerr << (bst1 == bst2) << ' ';
		assert( bst1 != bst2 );
		
		bst1[5] = 55;
		cerr << (bst1 == bst2) << '\n';
		assert( bst1 == bst2 );
	}
	
	{
		BinarySearchTree<int16_t, int16_t> bst1 { {1, 10}, {2, 20} };
		bst1.PrintInorder();
		BinarySearchTree<int16_t, int16_t> bst2 { {2, 20}, {1, 10} };  // Different order
		bst2.PrintInorder();
		cerr << (bst1 == bst2) << '\n';  // They are not equal
		assert( bst1 != bst2 );  
	}
	
	cerr << "---------- OperEqualTest is OK ----------\n\n";
}
