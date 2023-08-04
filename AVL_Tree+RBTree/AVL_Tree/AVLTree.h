#pragma once
#include <assert.h>
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

template<class K, class V>
struct AVLTreeNode
{
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	pair<K, V> _kv;
	int _bf;  // balance factor

	AVLTreeNode(const pair<K, V>& kv)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _kv(kv)
		, _bf(0)
	{}
};

template<class K, class V>
struct AVLTree
{
	typedef AVLTreeNode<K, V> Node;
public:
	bool Insert(const pair<K, V>& kv)
	{
		if (_root == nullptr)
		{
			_root = new Node(kv);
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur)
		{
			if (cur->_kv.first < kv.first)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				return false;
			}
		}

		cur = new Node(kv);
		if (parent->_kv.first < kv.first)
		{
			parent->_right = cur;
		}
		else
		{
			parent->_left = cur;
		}

		cur->_parent = parent;

		// 控制平衡
		// 1、更新平衡因子
		while (parent)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else
			{
				parent->_bf--;
			}

			if (parent->_bf == 0)
			{
				break;
			}
			else if (abs(parent->_bf) == 1)
			{
				parent = parent->_parent;
				cur = cur->_parent;
			}
			else if (abs(parent->_bf) == 2)
			{
				// 说明parent所在子树已经不平衡了，需要旋转处理
				if (parent->_bf == 2 && cur->_bf == 1)
				{
					RotateL(parent);
				}
				else if ((parent->_bf == -2 && cur->_bf == -1))
				{
					RotateR(parent);
				}
				else if (parent->_bf == -2 && cur->_bf == 1)
				{
					RotateLR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == -1)
				{
					RotateRL(parent);
				}
				else
				{
					assert(false);
				}

				break;
			}
			else
			{
				assert(false);
			}
		}

		return true;
	}
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	bool IsBanlance() {
		return _IsBanlance(_root);
	}

private:
	bool _IsBanlance(Node* root) {
		if (root == nullptr) {
			return true;
		}
		int leftHT = Height(root->_left);
		int rightHT = Height(root->_right);
		int diff = rightHT - leftHT;

		return abs(diff) < 2
			&& _IsBanlance(root->_left)
			&& _IsBanlance(root->_right);
	}
	int Height(Node* root) {
		if (root == nullptr)
			return 0;
		return max(Height(root->_left), Height(root->_right)) + 1;
	}


	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		Node* ppNode = parent->_parent;

		subR->_left = parent;
		parent->_parent = subR;

		if (_root == parent)
		{
			_root = subR;
			subR->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subR;
			}
			else
			{
				ppNode->_right = subR;
			}

			subR->_parent = ppNode;
		}

		subR->_bf = parent->_bf = 0;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
		{
			subLR->_parent = parent;
		}

		Node* ppNode = parent->_parent;

		subL->_right = parent;
		parent->_parent = subL;

		if (_root == parent)
		{
			_root = subL;
			subL->_parent = nullptr;
		}
		else
		{
			if (ppNode->_left == parent)
			{
				ppNode->_left = subL;
			}
			else
			{
				ppNode->_right = subL;
			}

			subL->_parent = ppNode;
		}

		subL->_bf = parent->_bf = 0;
	}

	void RotateLR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		subLR->_bf = 0;
		if (bf == 1)
		{
			parent->_bf = 0;
			subL->_bf = -1;
		}
		else if (bf == -1)
		{

			parent->_bf = 1;
			subL->_bf = 0;
		}
		else if (bf == 0)
		{
			parent->_bf = 0;
			subL->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void RotateRL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		int bf = subRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);

		subRL->_bf = 0;
		if (bf == 1)
		{
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1)
		{
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else if (bf == 0)
		{
			parent->_bf = 0;
			subR->_bf = 0;
		}
		else
		{
			assert(false);
		}
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		_InOrder(root->_left);
		cout << root->_kv.first << ":" << root->_kv.second << endl;
		_InOrder(root->_right);
	}
private:
	Node* _root = nullptr;
};

void TestAVLTree1()
{
	//int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };  // 测试双旋平衡因子调节
	int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15 };
	AVLTree<int, int> t1;
	for (auto e : a)
	{
		t1.Insert(make_pair(e, e));
	}

	t1.InOrder();
	cout << "IsBalance:" << t1.IsBanlance() << endl;

}