#include "Heap.h"
#include <time.h>

void HeapSort(int* a, int n) {
	// 向上调整建堆 O(N*logN)
	//for (int i = 1; i < n; ++i) {
	//	AdjustUp(a, i);
	//}
	// 向下调整 O(N)

	for (int i = (n - 1 - 1) / 2; i >= 0; --i) {
		AdjustDown(a, n, i);
	}
	int end = n - 1;
	// O(N * logN)
	while (end > 0){
		Swap(&a[0], &a[end]);
		AdjustDown(a, end, 0);
		--end;
	}

}



void TestHeap() {
	/*HP hp;
	HeapInit(&hp);
	int a[] = { 27,15,19,18,28,34,65,49,25,37 };
	for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
		HeapPush(&hp, a[i]);
	}
	HeapPrint(&hp);

	HeapPush(&hp, 10);
	HeapPrint(&hp);

	HeapTop(&hp);
	HeapPrint(&hp);

	HeapTop(&hp);
	HeapTop(&hp);

	HeapPrint(&hp);
	HeapPrint(&hp);*/

	int a[] = { 27,15,19,18,28,34,65,49,25,37 };
	HeapSort(a, sizeof(a) / sizeof(int));

}

void PrintTopK(int* a, int n, int k)
{
	// 1. 建堆--用a中前k个元素建堆
	int* kMinHeap = (int*)malloc(sizeof(int) * k);
	assert(kMinHeap);
	for (int i = 0; i < k; ++i) {
		kMinHeap[i] = a[i];
	}
	for (int i = (k - 1 - 1) / 2; i >= 0; --i) {
		AdjustDown(kMinHeap, k, i);
	}
	// 2. 将剩余n-k个元素依次与堆顶元素交换，不满则则替换
	for (int j = k; j < n; ++j) {
		if (a[j] > kMinHeap[0]) {
			kMinHeap[0] = a[j];
			AdjustDown(kMinHeap, k, 0);
		}
	}
	for (int i = 0; i < k; ++i) {
		printf("%d ", kMinHeap[i]);
	}
	printf("\n");
}
void TestTopk()
{
	int n = 10000;
	int* a = (int*)malloc(sizeof(int) * n);
	srand(time(0));
	for (int i = 0; i < n; ++i)
	{
		a[i] = rand() % 1000000;
	}
	a[5] = 1000000 + 1;
	a[1231] = 1000000 + 2;
	a[531] = 1000000 + 3;
	a[5121] = 1000000 + 4;
	a[115] = 1000000 + 5;
	a[2335] = 1000000 + 6;
	a[9999] = 1000000 + 7;
	a[76] = 1000000 + 8;
	a[423] = 1000000 + 9;
	a[3144] = 1000000 + 10;

	PrintTopK(a, n, 10);
}
int main() {
	//TestHeap();

	TestTopk();
	return 0;
}