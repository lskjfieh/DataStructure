#pragma once
#include <iostream>
using namespace std;
namespace Key {
	template <class K>
	struct BSTreeNode {

		BSTreeNode<K>* _left;
		BSTreeNode<K>* _right;
		K _key;

		BSTreeNode(const K& key)
			: _left(nullptr)
			, _right(nullptr)
			, _key(key)
		{}
	};

	//class BinarySearchTree {
	template<class K>
	class BSTree {
		typedef BSTreeNode<K> Node;
	public:
		bool Insert(const K& key) {
			if (_root == nullptr) {
				_root = new Node(key);
				return true;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key) {
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else {
					return false;
				}
			}

			cur = new Node(key);
			if (parent->_key < key) {
				parent->_right = cur;
			}
			else {
				parent->_left = cur;
			}
			return true;
		}
		bool Find(const K& key) {
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key) {
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else {
					return true;
				}
			}
			return false;
		}
		bool Erase(const K& key) {
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key) {
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key) {
					parent = cur;
					cur = cur->_left;
				}
				else {
					// 开始删除
					//1. 左为空
					//2. 右为空
					//3. 左右都不为空
					if (cur->_left == nullptr) {
						if (cur == _root) {
							_root = cur->_right;
						}
						else {
							if (cur == parent->_left) {
								parent->_left = cur->_right;
							}
							else {
								parent->_right = cur->_right;
							}
						}
						delete cur;
						cur = nullptr;
					}
					else if (cur->_right == nullptr) {
						if (_root == cur) {
							_root = cur->_left;
						}
						else {
							if (cur == parent->_left) {
								parent->_left = cur->_left;
							}
							else {
								parent->_right = cur->_left;
							}
						}
						delete cur;
						cur = nullptr;
					}
					else {
						//替换法删除
						Node* minParent = cur;
						Node* min = cur->_right;
						while (min->_left)
						{
							minParent = min;
							min = min->_left;
						}
						//cur->_key = min->_key;
						swap(cur->_key, min->_key);
						if (minParent->_left == min)
						{
							minParent->_left = min->_right;
						}
						else {
							minParent->_right = min->_right;
						}
						delete min;
					}
					return true;
				}
			}
			return false;
		}
		void InOrder() {
			_InOrder(_root);
			cout << endl;
		}

		/*----------------------------------------------------*/
		bool FindR(const K& key) {
			return _FindR(_root, key);
		}
		bool InsertR(const K& key) {
			return _InsertR(_root, key);
		}
		bool EraseR(const K& key) {
			return _EraseR(_root, key);
		}

		~BSTree() {
			_Destory(_root);
		}
		// c++11的用法，强制编译器生成默认的构造
		BSTree() = default;
		BSTree(const BSTree<K>& t) {
			_root = _Copy(t._root);
		}
		BSTree<K>& operator=(BSTree<K> t) {
			swap(_root, t._root);
			return *this;
		}
	private:
		Node* _Copy(Node* root) {
			if (root == nullptr) {
				return nullptr;
			}
			Node* copyRoot = new Node(root->_key);
			copyRoot->_left = _Copy(root->_left);
			copyRoot->_right = _Copy(root->_right);
			return copyRoot;
		}
		void _Destory(Node*& root) {
			if (root == nullptr) {
				return;
			}
			_Destory(root->_left);
			_Destory(root->_right);
			delete root;
			root = nullptr;
		}
		bool _EraseR(Node*& root, const K& key) {
			if (root == nullptr) {
				return false;
			}
			if (root->_key < key) {
				return _EraseR(root->_right, key);
			}
			else if (root->_key > key) {
				return _EraseR(root->_left, key);
			}
			else {
				Node* del = root;
				if (root->_left == nullptr) {
					root = root->_right;
				}
				else if (root->_right == nullptr) {
					root = root->_left;
				}
				else {
					// 找右树的最左节点
					Node* min = root->_right;
					while (min->_left) {
						min = min->_left;
					}
					swap(root->_key, min->_key);
					return _EraseR(root->_right, key);
				}
				delete del;
				return true;
			}
		}
		bool _InsertR(Node*& root, const K& key) {
			if (root == nullptr) {
				root = new Node(key);
				return true;
			}
			if (root->_key < key) {
				return _InsertR(root->_right, key);
			}
			else if (root->_key > key) {
				return _InsertR(root->_left, key);
			}
			else {
				return false;
			}
		}
		bool _FindR(Node* root, const K& key) {
			if (root == nullptr) {
				return false;
			}
			if (root->_key < key) {
				return _FindR(root->_right);
			}
			else if (root->_key > key) {
				return _FindR(root->_left, key);
			}
			else {
				return true;
			}
		}
		void _InOrder(Node* root) {
			if (root == nullptr) {
				return;
			}
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}
	private:
		Node* _root = nullptr;

	};
	void TestBSTree1() {
		BSTree<int> t;
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		for (auto e : a) {
			t.Insert(e);
		}
		// 排序+去重
		t.InOrder();

		t.EraseR(3);
		t.InOrder();

		t.EraseR(8);
		t.InOrder();

		for (auto e : a) {
			t.EraseR(e);
			t.InOrder();
		}
	}
	void TestBSTree3() {
		BSTree<int> t;
		int a[] = { 8, 3, 1, 10, 6, 4, 7, 14, 13 };
		for (auto e : a) {
			t.InsertR(e);
		}
		BSTree<int> copy = t;
		copy.InOrder();
		t.InOrder();

		BSTree<int> t1;
		t1.Insert(2);
		t1.Insert(1);
		t1.Insert(3);

		copy = t1;
		copy.InOrder();
		t1.InOrder();
	}
}

namespace KeyValue {
	template <class K, class V>
	struct BSTreeNode {

		BSTreeNode<K, V>* _left;
		BSTreeNode<K, V>* _right;
		K _key;
		V _value;

		BSTreeNode(const K& key, const V& value)
			: _left(nullptr)
			, _right(nullptr)
			, _key(key)
			, _value(value)
		{}
	};

	//class BinarySearchTree {
	template<class K, class V>
	class BSTree {
		typedef BSTreeNode<K, V> Node;
	public:
		bool Insert(const K& key, const V& value) {
			if (_root == nullptr) {
				_root = new Node(key, value);
				return true;
			}
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key) {
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else {
					return false;
				}
			}

			cur = new Node(key, value);
			if (parent->_key < key) {
				parent->_right = cur;
			}
			else {
				parent->_left = cur;
			}
			return true;
		}
		Node* Find(const K& key) {
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur)
			{
				if (cur->_key < key) {
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_key > key)
				{
					parent = cur;
					cur = cur->_left;
				}
				else {
					return cur;
				}
			}
			return nullptr;
		}
		bool Erase(const K& key) {
			// ...
			return true;
		}

		void InOrder() {
			_InOrder(_root);
			cout << endl;
		}

	private:
		void _InOrder(Node* root) {
			if (root == nullptr) {
				return;
			}
			_InOrder(root->_left);
			cout << root->_key << ":" << root->_value << endl;
			_InOrder(root->_right);
		}
	private:
		Node* _root = nullptr;

	};
	
	void TestBSTree1() {
		BSTree<string, string> dict;
		dict.Insert("sort", "排序");
		dict.Insert("left", "左边");
		dict.Insert("haha", "哈哈");
		dict.Insert("string", "字符串");
		dict.Insert("insert", "插入");

		string str;
		while (cin >> str) {
			BSTreeNode<string, string>* ret = dict.Find(str);
			if (ret) {
				cout << "对应的中文:" << ret->_value << endl;
			}
			else {
				cout << "->无此单词" << endl;
			}
		}
	}
	void TestBSTree2() {
		//统计水果出现的次数
		string arr[] = { "苹果", "苹果", "香蕉", "香蕉", "草莓", "香蕉", "芒果", "香蕉", "芒果", "芒果" };

		BSTree<string, int> countTree;
		for (auto& str : arr) {
			BSTreeNode<string, int>* ret = countTree.Find(str);
			if (ret) {
				ret->_value++;
			}
			else {
				countTree.Insert(str, 1);
			}
		}
		countTree.InOrder();
	}
}