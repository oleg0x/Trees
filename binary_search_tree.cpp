#include "binary_search_tree.h"
#include "test_structs.h"
#include <functional>
#include <iostream>
#include <string>

using std::cout, std::cerr, std::string, std::function;


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree(
	std::initializer_list<std::pair<KeyType, ValueType>> init)
{
	for ( auto it = init.begin(); it != init.end(); ++it )
		Insert(it->first, it->second);
}



template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::TraversePreorderIns(Node* node, BinarySearchTree* bst)
{
	if ( node )
	{
		bst->Insert(node->key, node->value);
		TraversePreorderIns(node->left, bst);
		TraversePreorderIns(node->right, bst);
	}
}



template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree(const BinarySearchTree& other)
{
	TraversePreorderIns(other.root_, this);
	cout << "BinarySearchTree(const BinarySearchTree&),  size = " << size_ << ".\n";
}



template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::BinarySearchTree(BinarySearchTree&& other)
	: root_ {other.root_}, size_ {other.size_}
{
	other.root_ = nullptr;
	other.size_ = 0;
	cout << "BinarySearchTree(BinarySearchTree&&),  size = " << size_ << ".\n";
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::TraversePostorderDel(Node* node)
{
	if ( node )
	{
		TraversePostorderDel(node->left);
		TraversePostorderDel(node->right);
		delete node;
		--size_;
	}
}



template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>::~BinarySearchTree()
{
	TraversePostorderDel(root_);
	cout << "~BinarySearchTree(),  size = " << size_ << ".\n";
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>& 
BinarySearchTree<KeyType, ValueType>::operator=(const BinarySearchTree& other)
{
	auto copy_other = new BinarySearchTree<KeyType, ValueType>(other);
	TraversePostorderDel(root_);
	root_ = copy_other->root_;
	size_ = copy_other->size_;
	return *this;
}



template <typename KeyType, typename ValueType>
BinarySearchTree<KeyType, ValueType>& 
BinarySearchTree<KeyType, ValueType>::operator=(BinarySearchTree&& other)
{
	if ( &other != this )
	{
		TraversePostorderDel(root_);
		root_ = other.root_;
		size_ = other.size_;
		other.root_ = nullptr;
		other.size_ = 0;
	}
	return *this;
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
CountType BinarySearchTree<KeyType, ValueType>::Size() const
{
	return size_;
}



template <typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::Empty() const
{
	return size_ == 0;
};


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::Insert(const KeyType& key, const ValueType& value)
{
//	cout << "Insert(const KeyType&, const ValueType&)\n";
	Node** node = &root_;  // Using pointer-to-pointer lets avoid checking of insertion to the root
	while ( *node )
	{ 
		const KeyType& cur_key = (*node)->key;
		if      (key < cur_key)  node = &(*node)->left;
		else if (key > cur_key)  node = &(*node)->right;
		else  return false;
	}
	*node = new Node {key, value};
	++size_;
	return true;
}



template <typename KeyType, typename ValueType>
bool BinarySearchTree<KeyType, ValueType>::Insert(KeyType&& key, ValueType&& value)
{
//	cout << "Insert(KeyType&& key, ValueType&&)\n";
	Node** node = &root_;  // Using pointer-to-pointer lets avoid checking of insertion to the root
	while ( *node )
	{ 
		const KeyType& cur_key = (*node)->key;
		if      (key < cur_key)  node = &(*node)->left;
		else if (key > cur_key)  node = &(*node)->right;
		else  return false;
	}
	*node = new Node {std::move(key), std::move(value)};
	++size_;
	return true;
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::Put(Node* node, const KeyType key, const ValueType value)
{
	if ( !node )
	{
		++size_;
		return new Node {key, value};
	}
	if      ( key < node->key )  node->left = Put(node->left,  key, value);
	else if ( key > node->key )  node->right = Put(node->right, key, value);
	else  node->value = value;
//	node->subtree_size = 1 + Size(node->left) + Size(node->right);
	return node;
}



template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::Put(const KeyType key, const ValueType value)
{
	root_ = Put(root_, key, value);
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
ValueType& BinarySearchTree<KeyType, ValueType>::At(const KeyType& key)
{
	Node** node = &root_;  // Using pointer-to-pointer lets avoid checking of insertion to the root
	while ( *node )
	{ 
		const KeyType& cur_key = (*node)->key;
		if      (key < cur_key)  node = &(*node)->left;
		else if (key > cur_key)  node = &(*node)->right;
		else  return (*node)->value;
	}
	throw std::out_of_range("Key not found!");
}



template <typename KeyType, typename ValueType>
const ValueType& BinarySearchTree<KeyType, ValueType>::At(const KeyType& key) const
{
	Node* const* node = &root_;  // Using pointer-to-pointer lets avoid checking of insertion to the root
	while ( *node )
	{ 
		const KeyType& cur_key = (*node)->key;
		if      (key < cur_key)  node = &(*node)->left;
		else if (key > cur_key)  node = &(*node)->right;
		else  return (*node)->value;
	}
	throw std::out_of_range("Key not found!");
}



template <typename KeyType, typename ValueType>
optional<ValueType> BinarySearchTree<KeyType, ValueType>::Get(KeyType key) const
{
	Node* node = root_;
	while ( node )
	{
		if      ( key < node->key )  node = node->left;
		else if ( key > node->key )  node = node->right;
		else  return node->value;
	}
	return {};
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
ValueType& BinarySearchTree<KeyType, ValueType>::operator [](const KeyType& key)
{
	Node** node = &root_;  // Using pointer-to-pointer lets avoid checking of insertion to the root
	while ( *node )
	{ 
		const KeyType& cur_key = (*node)->key;
		if      (key < cur_key)  node = &(*node)->left;
		else if (key > cur_key)  node = &(*node)->right;
		else  return (*node)->value;
	}
	*node = new Node {key, ValueType()};
	++size_;
	return (*node)->value;
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
KeyType& BinarySearchTree<KeyType, ValueType>::MinKey() const
{
	Node* node = root_;
	for ( ; node->left; node = node->left ) ;
	return node->key;
}



template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::MinKey(Node* node) const
{
	for ( ; node->left; node = node->left ) ;
	return node;
}



template <typename KeyType, typename ValueType>
KeyType& BinarySearchTree<KeyType, ValueType>::MaxKey() const
{
	Node* node = root_;
	for ( ; node->right; node = node->right ) ;
	return node->key;
}



template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::MaxKey(Node* node) const
{
	for ( ; node->right; node = node->right ) ;
	return node;
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node* 
BinarySearchTree<KeyType, ValueType>::FloorKey(Node* node, KeyType key) const
{
	if ( !node )  return nullptr;
	if ( key == node->key )  return node;
	if ( key < node->key )   return FloorKey(node->left, key);
	Node* child = FloorKey(node->right, key);
	return (child ? child : node);
}



template <typename KeyType, typename ValueType>
KeyType& BinarySearchTree<KeyType, ValueType>::FloorKey(const KeyType& key) const
{
	Node* node = FloorKey(root_, key);
	if ( !node )  throw std::out_of_range("Key is less than MinKey!");
	return node->key;
}



template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node* 
BinarySearchTree<KeyType, ValueType>::CeilingKey(Node* node, KeyType key) const
{
	if ( !node )  return nullptr;
	if ( key == node->key )  return node;
	if ( key > node->key )   return CeilingKey(node->right, key);
	Node* child = CeilingKey(node->left, key);
	return (child ? child : node);
}



template <typename KeyType, typename ValueType>
KeyType& BinarySearchTree<KeyType, ValueType>::CeilingKey(const KeyType& key) const
{
	Node* node = CeilingKey(root_, key);
	if ( !node )  throw std::out_of_range("Key is bigger than MaxKey!");
	return node->key;
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::EraseMin(Node* node)
{
	if ( node )
	{
		if ( !node->left )
		{
			Node* temp = node->right;
			delete node;
			--size_;
			return temp;
		}
		node->left = EraseMin(node->left);
//		node->count = 1 + Size(node->left) + Size(node->right);
	}
	return node;
}



template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::EraseMin()
{
	root_ = EraseMin(root_);
}



template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::Update(Node* node)
{
	if ( !node->left )  return node->right;
	node->left = Update(node->left);
	return node;
}



template <typename KeyType, typename ValueType>
typename BinarySearchTree<KeyType, ValueType>::Node*
BinarySearchTree<KeyType, ValueType>::Erase(Node* node, const KeyType& key)
{
	if ( !node )  return nullptr;
	if      ( key < node->key )  node->left  = Erase(node->left, key);
	else if ( key > node->key )  node->right = Erase(node->right, key);
	else  // key == node->key
	{
		if ( !node->right || !node->left )
		{
			Node* temp = (!node->right ? node->left : node->right);
			delete node;
			--size_;
			return temp;
		}
		Node* temp = node;
		node = MinKey(temp->right);  // Min in the right subtree
		node->right = Update(temp->right);
		node->left = temp->left;
		delete temp;
		--size_;
	}
//	node->subtree_size = Size(node->left) + Size(node->right) + 1;
	return node;
}



template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::Erase(const KeyType& key)
{
	root_ = Erase(root_, key);
}



template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::Clear()
{
	TraversePostorderDel(root_);
	root_ = nullptr;
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
template <typename Oper>
void BinarySearchTree<KeyType, ValueType>::TraverseInorder(Node* node, Oper op)
{
	if ( node )
	{
		TraverseInorder(node->left, op);
		op(node->key, node->value);
		TraverseInorder(node->right, op);
	}
}



template <typename KeyType, typename ValueType>
template <typename Oper> 
void BinarySearchTree<KeyType, ValueType>::TraverseInorder(Oper op)
{
	TraverseInorder(root_, op);
}



template <typename KeyType, typename ValueType>
void BinarySearchTree<KeyType, ValueType>::PrintInorder()
{
	cout << "Size = " << size_ << ": ";
	if ( root_ )  TraverseInorder( root_, 
		[](const KeyType& key, const ValueType& value)
			{ cout << '(' << key << ", " << value << ") "; } );
	else  cout << "tree is empty.";
	cout << '\n';
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
bool Compare(typename BinarySearchTree<KeyType, ValueType>::Node* n1, 
             typename BinarySearchTree<KeyType, ValueType>::Node* n2)
{
/*	return n1 && n2 
		? n1->key == n2->key && Compare<KeyType, ValueType>(n1->left, n2->left) && 
			Compare<KeyType, ValueType>(n1->right, n2->right)
		: !n1 && !n2;*/
	
	if ( n1 && n2 )
		return n1->key == n2->key && n1->value == n2->value &&
			Compare<KeyType, ValueType>(n1->left, n2->left) && 
			Compare<KeyType, ValueType>(n1->right, n2->right);
	else  return !n1 && !n2;
}



template <typename KeyType, typename ValueType>
bool operator ==(const BinarySearchTree<KeyType, ValueType>& lhs,
                 const BinarySearchTree<KeyType, ValueType>& rhs)
{
	return Compare<KeyType, ValueType>(lhs.root_, rhs.root_);
}


//-----------------------------------------------------------------------------


template class BinarySearchTree<int, char>;
template class BinarySearchTree<int, string>;
template class BinarySearchTree<char, int>;
template class BinarySearchTree<int16_t, float>;
template class BinarySearchTree<string, double>;
template class BinarySearchTree<int, float>;
template class BinarySearchTree<int16_t, int16_t>;
template class BinarySearchTree<char, int16_t>;
template class BinarySearchTree<KeyStruct, ValueStruct>;

template void BinarySearchTree<int, string>::TraverseInorder( 
	function<void (int, string)> );

template bool operator ==( const BinarySearchTree<int, char>&, 
	const BinarySearchTree<int, char>& );
template bool operator ==( const BinarySearchTree<int16_t, int16_t>&, 
	const BinarySearchTree<int16_t, int16_t>& );
template bool operator ==( const BinarySearchTree<int, string>&, 
	const BinarySearchTree<int, string>& );
