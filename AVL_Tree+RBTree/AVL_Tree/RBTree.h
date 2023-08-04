#pragma once
enum Colour
{
    RED,
    BLACK
};
template <class K, class V>
struct RBTreeNode
{

    RBTreeNode<K, V>* _left;
    RBTreeNode<K, V>* _right;
    RBTreeNode<K, V>* _parent;

    pair<K, V> _kv;
    Colour _col;

    RBTreeNode(const pair<K, V>& kv)
        : _left(nullptr), _right(nullptr), _parent(nullptr), _kv(kv)
    {
    }
};

template <class K, class V>
struct RBTree
{
    typedef RBTreeNode<K, V> Node;

public:
    bool Insert(const pair<K, V>& kv)
    {
        if (_root == nullptr)
        {
            _root = new Node(kv);
            _root->_col = BLACK;
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
        cur->_col = RED;
        if (parent->_kv.first < kv.first)
        {
            parent->_right = cur;
        }
        else
        {
            parent->_left = cur;
        }

        cur->_parent = parent;

        while (parent && parent->_col == RED)
        {
            Node* grandfather = parent->_parent;
            assert(grandfather);
            assert(grandfather->_col == BLACK);
            // �ؼ�������
            if (parent == grandfather->_left)
            {
                Node* uncle = grandfather->_right;
                // ���һ��uncle������Ϊ�죬��ɫ+�������ϴ���
                if (uncle && uncle->_col == RED)
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    // ������grandfather��Ϊcurrent���д���
                    cur = grandfather;
                    parent = cur->_parent;
                }
                // �����+����uncle�����ڻ�uncle����Ϊ��ɫ
                else
                {
                    // �����:����+��ɫ
                    //     g
                    //   p   u
                    // c
                    if (cur == parent->_left)
                    {
                        RotateR(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        // �����:����+�ҵ���+��ɫ
                        //     g
                        //   p   u
                        //     c
                        RotateL(parent);
                        RotateR(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break;
                }
            }
            else
            {
                Node* uncle = grandfather->_left;
                // ���һ�������Ǻ�ɫ
                if (uncle && uncle->_col == RED)
                {
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    // ������grandfather��Ϊcurrent���д���
                    cur = grandfather;
                    parent = cur->_parent;
                }
                // �����+����uncle�����ڻ�uncle����Ϊ��ɫ
                else
                {
                    // �����:����+��ɫ
                    //     g
                    //   u   p
                    //         c
                    if (cur == parent->_right)
                    {
                        RotateL(grandfather);
                        parent->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    else
                    {
                        // �����:�ҵ���+����+��ɫ
                        //     g
                        //   u   p
                        //     c
                        RotateR(parent);
                        RotateL(grandfather);
                        cur->_col = BLACK;
                        grandfather->_col = RED;
                    }
                    break;
                }
            }
        }
        _root->_col = BLACK;
        return true;
    }
    void InOrder()
    {
        _InOrder(_root);
        cout << endl;
    }
    bool IsBanlance()
    {
        if (_root == nullptr)
        {
            return true;
        }
        if (_root->_col == RED)
        {
            cout << "���ڵ㲻�Ǻ�ɫ" << endl;
            return false;
        }
        // ��ɫ�ڵ�������׼ֵ
        int benchmark = 0;
        Node* cur = _root;
        while (cur)
        {
            if (cur->_col == BLACK) {
                ++benchmark;
            }
            cur = cur->_left;
        }
        return PrevCheck(_root, 0, benchmark);
    }

private:
    bool PrevCheck(Node* root, int blackNum, int benchmark)
    {
        if (root == nullptr)
        {
            /*cout << blackNum << endl;
            return;*/
            if (blackNum != benchmark)
            {
                cout << "ĳ����ɫ�ڵ�����������" << endl;
                return false;
            }
            else {
                return true;
            }
        }
        if (root->_col == RED && root->_parent->_col == RED)
        {
            cout << "���ں�ɫ�������ڵ�" << endl;
            return false;
        }
        if (root->_col == BLACK)
        {
            ++blackNum;
        }
        return PrevCheck(root->_left, blackNum, benchmark)
            && PrevCheck(root->_right, blackNum, benchmark);
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

void TestRBTree1()
{
    // int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };  // ����˫��ƽ�����ӵ���
    int a[] = { 16, 3, 7, 11, 9, 26, 18, 14, 15, 4, 2, 6, 1, 3, 5, 15, 7 };
    RBTree<int, int> t1;
    for (auto e : a)
    {
        t1.Insert(make_pair(e, e));
    }

    t1.InOrder();
    cout << "IsBalance:" << t1.IsBanlance() << endl;

}