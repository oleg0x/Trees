#pragma once

#include "binary_search_tree.h"



template <typename KeyType, typename ValueType>
class RedBlackTree : public BinarySearchTree<KeyType, ValueType>
{
public:
	void Put(const KeyType& key, const ValueType& value);
	void Erase(const KeyType& key);

private:
	bool IsRed(typename RedBlackTree::Node* node);
	typename RedBlackTree::Node* RotateLeft(typename RedBlackTree::Node* node);
	typename RedBlackTree::Node* RotateRight(typename RedBlackTree::Node* node);
	void FlipColors(typename RedBlackTree::Node* node);
	
	typename RedBlackTree::Node* Put(typename RedBlackTree::Node* node, 
	                                 const KeyType& key, const ValueType& value);
	
	typename RedBlackTree::Node* MoveRedLeft(typename RedBlackTree::Node* node);
	typename RedBlackTree::Node* MoveRedRight(typename RedBlackTree::Node* node);
	typename RedBlackTree::Node* Balance(typename RedBlackTree::Node* node);
	
	typename RedBlackTree::Node* EraseMin(typename RedBlackTree::Node* node);
	typename RedBlackTree::Node* Erase(typename RedBlackTree::Node* h, const KeyType& key);
};
