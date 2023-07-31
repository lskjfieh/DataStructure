#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Queue.h"
typedef int BTDataType;
typedef struct BinaryTreeNode {
	struct BinaryTreeNode* left;
	struct BinaryTreeNode* right;
	BTDataType data;
}BTNode;

BTNode* BuyNode(BTDataType x) {
	BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	assert(node);
	node->data = x;
	node->left = NULL;
	node->right = NULL;
	return node;
}
BTNode* CreatBinaryTree()
{
	BTNode* node1 = BuyNode(1);
	BTNode* node2 = BuyNode(2);
	BTNode* node3 = BuyNode(3);
	BTNode* node4 = BuyNode(4);
	BTNode* node5 = BuyNode(5);
	BTNode* node6 = BuyNode(6);

	node1->left = node2;
	node1->right = node4;
	node2->left = node3;
	node4->left = node5;
	node4->right = node6;
	return node1;
}
// 前序遍历 分治
void PreOrder(BTNode* root) {
	if (root == NULL) {
		printf("# ");
		return;
	}
	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}
// 中序遍历
void InOrder(BTNode* root) {
	if (root == NULL) {
		printf("# ");
		return;
	}

	PreOrder(root->left);
	printf("%d ", root->data);
	PreOrder(root->right);
}

// 后序遍历
void PostOrder(BTNode* root) {
	if (root == NULL) {
		printf("# ");
		return;
	}

	PreOrder(root->left);
	PreOrder(root->right);
	printf("%d ", root->data);

}
int count = 0;
void TreeSize(BTNode* root) {
	if (root == NULL) {
		return;
	}
	++count;
	TreeSize(root->left);
	TreeSize(root->right);
}
// 分而治之
int TreeSize2(BTNode* root) {
	return root == NULL ? 0 :
		TreeSize2(root->left) + TreeSize2(root->right) + 1;
}

int TreeLeafSize2(BTNode* root) {
	if (root == NULL)
		return 0;
	else if(root->left == NULL && root->right == NULL){
		return 1;
	}
	else {
		return TreeLeafSize2(root->left) + TreeLeafSize2(root->right);
	}
}
// 求第K层结点数
int TreeKLevel(BTNode* root, int k) {
	assert(k >= 1);
	if (root == NULL) {
		return 0;
	}
	if (k == 1) {
		return 1;
	}
	return TreeKLevel(root->left, k - 1) + TreeKLevel(root->right, k - 1);
}
// 求二叉树深度
int  TreePath(BTNode* root) {
	if (root == NULL) {
		return 0;
	}
	else {
		int leftDepth = TreePath(root->left);
		int rightDepth = TreePath(root->right);
		return (leftDepth > rightDepth) ? (leftDepth + 1) : (rightDepth + 1);
	}
}

// 二叉树查找值为x的结点
BTNode* TreeFind(BTNode* root, BTDataType x) {
	if (root == NULL)
		return NULL;
	if (root->data == x) {
		return root;
	}
	BTNode* ret1 = TreeFind(root->left, x);
	if (ret1)
		return ret1;

	BTNode* ret2 = TreeFind(root->left, x);
	if (ret2)
		return ret2;

	return NULL;
}

void TreeDestroy(BTNode* root) {
	if (root == NULL) {
		return;
	}
	TreeDestroy(root->left);
	TreeDestroy(root->right);
	printf("%p:%d\n", root, root->data);
	free(root);

}

//层序遍历 一种广度优先遍历 借助队列
void LevelOrder(BTNode* root) {
	Queue q;
	QueueInit(&q);
	if (root) {
		QueuePush(&q, root);
	}
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		printf("%d ", front->data);
		QueuePop(&q);
		if (front->left) {
			QueuePush(&q, front->left);
		}
		if (front->right) {
			QueuePush(&q, front->right);
		}
	}
	printf("\n");
	QueueDestroy(&q);
}

// 判断二叉树是否是完全二叉树
bool TreeComplete(BTNode* root) {
	Queue q;
	QueueInit(&q);
	if (root) {
		QueuePush(&q, root);
	}
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front) {
			QueuePush(&q, front->left);
			QueuePush(&q, front->right);
		}
		else {
			//遇到空以后，则跳出层序遍历
			break;
		}
	}
	//1、如果后面全是空，则是完全二叉树
	//2、如果空后面还有非空，则不是完全二叉树
	while (!QueueEmpty(&q))
	{
		BTNode* front = QueueFront(&q);
		QueuePop(&q);
		if (front) {
			QueueDestroy(&q);
			return false;
		}
	}
	QueueDestroy(&q);
	return true;
}

int main() {
	BTNode* root = CreatBinaryTree();
	PreOrder(root);
	printf("\n");
	InOrder(root);
	printf("\n");
	PostOrder(root);
	printf("\n");
	printf("层序遍历：");
	LevelOrder(root);

	TreeSize(root);
	printf("TreeSize:%d\n", count);

	printf("TreeSize2:%d\n", TreeSize2(root));
	printf("leafCount:%d\n", TreeLeafSize2(root));
	printf("Tree2Level: %d\n", TreeKLevel(root, 2));
	printf("deep：%d\n", TreePath(root));

	printf("Is TreeComplete: %d\n", TreeComplete(root)); 
	TreeDestroy(root);
	root = NULL;
	return 0;
}