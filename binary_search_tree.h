#pragma once

#include <cstdint>
#include <initializer_list>
#include <optional>

using std::optional;

using CountType = uint32_t;



template <typename KeyType, typename ValueType>
class BinarySearchTree
{
public:
	enum struct Color : bool {red = true, black = false};
	struct Node
	{
		KeyType key;
		ValueType value;
		Color color = Color::black;  // Color of parent link, only for RBT
		Node* left  = nullptr;
		Node* right = nullptr;
//		CountType subtree_size = 0;  // Number of nodes in subtree
	};
	
	BinarySearchTree() = default;  // Default constructor
	BinarySearchTree(std::initializer_list<std::pair<KeyType, ValueType>> init);
	BinarySearchTree(const BinarySearchTree& other);  // Copy constructor
	BinarySearchTree(BinarySearchTree&& other);       // Move constructor
	
	~BinarySearchTree();
	
	BinarySearchTree<KeyType, ValueType>& operator =(const BinarySearchTree& other);  // Copy assignment
	BinarySearchTree<KeyType, ValueType>& operator =(BinarySearchTree&& other);       // Move assignment

	const Node* GetRoot() const;
	
	CountType Size() const;
	bool Empty() const;
	
	bool Insert(const KeyType& key, const ValueType& value);
	bool Insert(KeyType&& key, ValueType&& value);
	void Put(const KeyType& key, const ValueType& value);
	
	ValueType& At(const KeyType& key);
	const ValueType& At(const KeyType& key) const;
	optional<ValueType> Get(const KeyType& key) const;
	
	ValueType& operator [](const KeyType& key);
		
	KeyType& MinKey() const;
	KeyType& MaxKey() const;
	
	KeyType& FloorKey(  const KeyType& key) const;  // Largest key <= given key
	KeyType& CeilingKey(const KeyType& key) const;  // Smallest key >= given key
	
	void EraseMin();
	void Erase(const KeyType& key);  // Hibbard deletion (1962)
	void Clear();  // Erases all elements from the BST
	
	template <typename Oper> void TraverseInorder(Oper op);
	void PrintInorder() /*const*/;

protected:
	Node* root_ = nullptr;
	CountType size_ = 0;
//	CountType Size(Node* node) { return (node ? node->subtree_size : 0); }
	
	Node* MinKey(Node* node) const;
	Node* MaxKey(Node* node) const;
	
	Node* FloorKey(Node* node, const KeyType& key) const;
	Node* CeilingKey(Node* node, const KeyType& key) const;
	
	void TraversePreorderIns(Node* node, BinarySearchTree* bst);
	void TraversePostorderDel(Node* node);
	template <typename Oper> void TraverseInorder(Node* node, Oper op);

private:
	Node* Put(Node* node, const KeyType& key, const ValueType& value);	

	Node* EraseMin(Node* node);
	Node* Update(Node* node);
	Node* Erase(Node* node, const KeyType& key);
	
	template <typename KeyType2, typename ValueType2>
	friend bool operator ==(const BinarySearchTree<KeyType2, ValueType2>& lhs, 
		const BinarySearchTree<KeyType2, ValueType2>& rhs);
};



template <typename KeyType, typename ValueType>
bool Compare(typename BinarySearchTree<KeyType, ValueType>::Node* n1, 
             typename BinarySearchTree<KeyType, ValueType>::Node* n2);

template <typename KeyType, typename ValueType>
bool operator ==(const BinarySearchTree<KeyType, ValueType>& lhs, 
                 const BinarySearchTree<KeyType, ValueType>& rhs);
