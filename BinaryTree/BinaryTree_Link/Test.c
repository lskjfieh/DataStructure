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
// ǰ����� ����
void PreOrder(BTNode* root) {
	if (root == NULL) {
		printf("# ");
		return;
	}
	printf("%d ", root->data);
	PreOrder(root->left);
	PreOrder(root->right);
}
// �������
void InOrder(BTNode* root) {
	if (root == NULL) {
		printf("# ");
		return;
	}

	PreOrder(root->left);
	printf("%d ", root->data);
	PreOrder(root->right);
}

// �������
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
// �ֶ���֮
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
// ���K������
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
// ����������
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

// ����������ֵΪx�Ľ��
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

//������� һ�ֹ�����ȱ��� ��������
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

// �ж϶������Ƿ�����ȫ������
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
			//�������Ժ��������������
			break;
		}
	}
	//1���������ȫ�ǿգ�������ȫ������
	//2������պ��滹�зǿգ�������ȫ������
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
	printf("���������");
	LevelOrder(root);

	TreeSize(root);
	printf("TreeSize:%d\n", count);

	printf("TreeSize2:%d\n", TreeSize2(root));
	printf("leafCount:%d\n", TreeLeafSize2(root));
	printf("Tree2Level: %d\n", TreeKLevel(root, 2));
	printf("deep��%d\n", TreePath(root));

	printf("Is TreeComplete: %d\n", TreeComplete(root)); 
	TreeDestroy(root);
	root = NULL;
	return 0;
}