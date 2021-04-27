#include "red-black_tree.h"
#include "test_structs.h"
#include <cassert>
#include <functional>
#include <iostream>
#include <string>

using namespace std;



void RBTPutGetTest()
{
	{
		RedBlackTree<int, char> rbt;
		assert( rbt.Size() == 0 && rbt.Empty() );
	
		rbt.Put(15, 'b');
		rbt.Put(20, 'c');
		rbt.Put(10, 'a');
		assert( rbt.Size() == 3 && !rbt.Empty() );

		auto p = rbt.GetRoot();
		cout << p->key << " - " << p->value << '\n';
		assert( p->key == 15 && p->value == 'b' );
		p = rbt.GetRoot()->left;
		cout << p->key << " - " << p->value << '\n';
		assert( p->key == 10 && p->value == 'a' );
		p = rbt.GetRoot()->right;
		cout << p->key << " - " << p->value << '\n';
		assert( p->key == 20 && p->value == 'c' );

		cerr << *rbt.Get(10) << "  " << *rbt.Get(15) << "  " 
		     << *rbt.Get(20) << '\n';
		rbt.PrintInorder();
	}
	cerr << "---------- RBTPutGetTest is OK ----------\n\n";
}



void RBTEraseTest()
{
	{
		RedBlackTree<int16_t, int16_t> rbt;
		rbt.PrintInorder();
		assert( rbt.Size() == 0 && rbt.Empty() );
		
		rbt.Insert(555, 5555);
		rbt.PrintInorder();
		assert( rbt.Size() == 1 && !rbt.Empty() );
		rbt.Erase(555);
		rbt.PrintInorder();
		assert( rbt.Size() == 0 && rbt.Empty() );

		rbt.Insert(1, 10);
		rbt.Insert(2, 20);
		rbt.PrintInorder();
		assert( rbt.Size() == 2 && !rbt.Empty() );
		
		rbt.Erase(2);
		rbt.PrintInorder();
		assert( rbt.Size() == 1 && !rbt.Empty() );
		rbt.Erase(1);
		rbt.PrintInorder();
		assert( rbt.Size() == 0 && rbt.Empty() );
	}
	{
		RedBlackTree<string, double> rbt;
		rbt.Erase("xxxxx");  // Erase from empty tree
		assert( rbt.Size() == 0 && rbt.Empty() );
	
		rbt.Put("bb", 2.2);
		rbt.Put("aa", 1.1);
		rbt.Put("dd", 4.4);
		rbt.Put("cc", 3.3);
		rbt.Put("ee", 5.5);
		assert( rbt.Size() == 5 && !rbt.Empty() );
		rbt.PrintInorder();
		
		rbt.Erase("cc");
		rbt.PrintInorder();
		rbt.Erase("bb");
		rbt.PrintInorder();
		assert( rbt.Size() == 3 && !rbt.Empty() );
		rbt.Erase("dd");
		rbt.PrintInorder();
		rbt.Erase("xxx");  // Erase absent key
		assert( rbt.Size() == 2 && !rbt.Empty() );
		rbt.Erase("aa");
		rbt.PrintInorder();
		rbt.Erase("ee");
		rbt.PrintInorder();
		assert( rbt.Size() == 0 && rbt.Empty() );
		rbt.Erase("dd");
		assert( rbt.Size() == 0 && rbt.Empty() );
	}
	cerr << "---------- RBTEraseTest is OK ----------\n\n";
}



void RBTEraseTest2()
{
	{
		RedBlackTree<KeyStruct, ValueStruct> rbt;
		rbt.Erase(KeyStruct(1));  // Erase from empty tree
		rbt.PrintInorder();
		assert( rbt.Size() == 0 && rbt.Empty() );

		KeyStruct key1(10);
		KeyStruct key2(20);
		KeyStruct key3(30);
		KeyStruct key4(40);
		KeyStruct key5(50);
		ValueStruct val1('a');
		ValueStruct val2('b');
		ValueStruct val3('c');
		ValueStruct val4('d');
		ValueStruct val5('e');
	
		cerr << "Inserting keys and values...\n";
		rbt.Insert(key2, val2);
		rbt.Insert(key4, val4);
		rbt.Insert(key1, val1);
		rbt.Insert(key5, val5);
		rbt.Insert(key3, val3);
		rbt.PrintInorder();
		assert( rbt.Size() == 5 && !rbt.Empty() );
	
		rbt.Erase(KeyStruct(2));  // Erase absent key
		assert( rbt.Size() == 5 && !rbt.Empty() );
	
		rbt.Erase(key3);
		rbt.PrintInorder();
		assert( rbt.Size() == 4 && !rbt.Empty() );
	
		rbt.Erase(key4);
		rbt.PrintInorder();
		assert( rbt.Size() == 3 && !rbt.Empty() );
	
		rbt.Erase(key2);
		rbt.PrintInorder();
		assert( rbt.Size() == 2 && !rbt.Empty() );
	
		rbt.Erase(key1);
		rbt.PrintInorder();
		assert( rbt.Size() == 1 && !rbt.Empty() );
		
		rbt.Erase(key5);
		rbt.PrintInorder();
		assert( rbt.Size() == 0 && rbt.Empty() );

		rbt.Erase(KeyStruct(3));  // Erase absent key
	}
	cerr << "---------- RBTEraseTest2 is OK ----------\n\n";
}
