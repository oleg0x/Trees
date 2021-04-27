#include "red-black_tree.h"
#include "test_structs.h"
#include <iostream>
#include <string>

using std::cout, std::cerr, std::string;



template <typename KeyType, typename ValueType>
bool RedBlackTree<KeyType, ValueType>::IsRed(typename RedBlackTree::Node* node)
{
	if ( !node )  return false;  // null links are black
	return node->color == RedBlackTree::Color::red;
}



template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::RotateLeft(typename RedBlackTree::Node* node)
{
	typename RedBlackTree::Node* x = node->right;
	node->right = x->left;
	x->left = node;
	x->color = node->color;
	node->color = RedBlackTree::Color::red;
	return x;
}



template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::RotateRight(typename RedBlackTree::Node* node)
{
	typename RedBlackTree::Node* x = node->left;
	node->left = x->right;
	x->right = node;
	x->color = node->color;
	node->color = RedBlackTree::Color::red;
	return x;
}



template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::FlipColors(typename RedBlackTree::Node* node)
{
	node->color = static_cast<typename RedBlackTree::Color>(
		!static_cast<bool>(node->color));
	if ( node->left )  node->left->color = static_cast<typename RedBlackTree::Color>(
		!static_cast<bool>(node->left->color));
	if ( node->right )  node->right->color = static_cast<typename RedBlackTree::Color>(
		!static_cast<bool>(node->right->color));
}



template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::Put(typename RedBlackTree::Node* node, const KeyType& key, const ValueType& value)
{
	if ( !node )
	{
		++this->size_;
		return new typename RedBlackTree::Node {key, value, RedBlackTree::Color::red};
	}
	if      ( key < node->key )  node->left  = Put(node->left,  key, value);
	else if ( key > node->key )  node->right = Put(node->right, key, value);
	else  node->value = value;
	
	if ( IsRed(node->right) && !IsRed(node->left) )       node = RotateLeft(node);
	if ( IsRed(node->left)  && IsRed(node->left->left) )  node = RotateRight(node);
	if ( IsRed(node->left)  && IsRed(node->right))        FlipColors(node);
	
	return node;
}



template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::Put(const KeyType& key, const ValueType& value)
{
	this->root_ = Put(this->root_, key, value);
	this->root_->color = RedBlackTree::Color::black;
}


//-----------------------------------------------------------------------------


template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::MoveRedLeft(typename RedBlackTree::Node* node)
{
	FlipColors(node);
	if ( IsRed(node->right->left) )
	{
 		node->right = RotateRight(node->right);
		node = RotateLeft(node);
		FlipColors(node);  // ???
	}
	return node;
}



template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::MoveRedRight(typename RedBlackTree::Node* node)
{
	FlipColors(node);
	if ( IsRed(node->left->left) )
	{
		node = RotateRight(node);
		FlipColors(node);  // ???
	}
	return node;
}



template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::Balance(typename RedBlackTree::Node* node)
{
	if ( IsRed(node->right) && !IsRed(node->left) )       node = RotateLeft(node);
	if ( IsRed(node->left)  && IsRed(node->left->left) )  node = RotateRight(node);
	if ( IsRed(node->left)  && IsRed(node->right))        FlipColors(node);
	return node;
}



template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::EraseMin(typename RedBlackTree::Node* node)
{
	if ( !node->left )  return nullptr;
	if ( !IsRed(node->left) && !IsRed(node->left->left) )  node = MoveRedLeft(node);
	node->left = EraseMin(node->left);
	return Balance(node);
}



template <typename KeyType, typename ValueType>
typename RedBlackTree<KeyType, ValueType>::Node*
RedBlackTree<KeyType, ValueType>::Erase(typename RedBlackTree::Node* h, const KeyType& key)
{
	if ( key < h->key )
	{
		if ( !IsRed(h->left) && !IsRed(h->left->left) )  h = MoveRedLeft(h);
		h->left = Erase(h->left, key);
	}
	else
	{
		if ( IsRed(h->left) )  h = RotateRight(h);
		if ( key == h->key && h->right == nullptr )
		{
			delete h;
			return nullptr;
		}
//		if ( !IsRed(h->right) && !IsRed(h->right->left) )  h = MoveRedRight(h);
		if ( h->left && !IsRed(h->right) && !IsRed(h->right->left) )  h = MoveRedRight(h);
		if ( key == h->key )
		{
			typename RedBlackTree::Node* x = this->MinKey(h->right);
			h->key = x->key;
			h->value = x->value;
			h->right = EraseMin(h->right);
			delete x;
		}
		else  h->right = Erase(h->right, key);
	}
	return Balance(h);
}



template <typename KeyType, typename ValueType>
void RedBlackTree<KeyType, ValueType>::Erase(const KeyType& key)
{
	if ( this->Get(key) )
	{
		if ( !IsRed(this->root_->left) && !IsRed(this->root_->right) )
			this->root_->color = RedBlackTree::Color::red;
		this->root_ = Erase(this->root_, key);
		if ( !this->Empty() )  this->root_->color = RedBlackTree::Color::black;
		--this->size_;
	}
}


//-----------------------------------------------------------------------------


template class RedBlackTree<int, char>;
template class RedBlackTree<int16_t, int16_t>;
template class RedBlackTree<string, double>;
template class RedBlackTree<KeyStruct, ValueStruct>;
