#include "Heap.h"

void Swap(HPDataType* p1, HPDataType* p2) {
	HPDataType tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}
void HeapPrint(HP* php) {
	assert(php);
	for (int i = 0; i < php->size; ++i) {
		printf("%d ", php->a[i]);
	}
	printf("\n");
}

void HeapInit(HP* php) {
	assert(php);
	php->a = NULL;
	php->size = php->capacity = 0;
}

void HeapDestroy(HP* php) {
	assert(php);
	free(php->a);
	php->a = NULL;
	php->size= php->capacity = 0;
}
//向上调整
void AdjustUp(HPDataType* a, int child) {
	int parent = (child - 1) / 2;
	while (child > 0) {
		if (a[child] < a[parent]) {
			Swap(&a[child], &a[parent]);
			child = parent;
			parent = (child - 1) / 2;
		}
		else {
			break;
		}
	}
}
void HeapPush(HP* php, HPDataType x) {
	assert(php);
	if (php->size == php->capacity) {
		//扩容
		int newcapacity = php->capacity == 0 ? 4 : php->capacity * 2;
		HPDataType* tmp = (HPDataType*)realloc(php->a, sizeof(HPDataType)*newcapacity);
		if (tmp == NULL) {
			printf("realloc fail\n");
			exit(-1);
		}
		php->a = tmp;
		php->capacity = newcapacity;
	}
	php->a[php->size] = x;
	php->size++;
	AdjustUp(php->a, php->size - 1);

}
//向下调整
void AdjustDown(HPDataType* a, int size, int parent) {
	int child = parent * 2 + 1;
	while(child < size)
	{
		if (child+1 < size && a[child + 1] < a[child]) {
			++child;
		}
		if (a[child] < a[parent]) {
			Swap(&a[child], &a[parent]);
			parent = child;
			child = parent * 2 + 1;
		}
		else {
			break;
		}
	}
}
void HeapPop(HP* php) {
	assert(php);
	assert(php->size > 0);

	Swap(php->a[0], php->a[php->size - 1]);
	php->size--;
	AdjustDown(php->a, php->size, 0);

}
HPDataType HeapTop(HP* php) {
	assert(php);
	assert(php->size > 0);
	return php->a[0];
}

bool HeapEmpty(HP* php) {
	assert(php);
	return php->size == 0;
}
int HeapSize(HP* php) {
	assert(php);
	return php->size;
}
void Swap(HPDataType* p1, HPDataType* p2);
void HeapPrint(HP* php);
void HeapInit(HP* php);
void HeapDestroy(HP* php);
void HeapPush(HP* php, HPDataType x);
void HeapPop(HP* php);
HPDataType HeapTop(HP* php);
bool HeapEmpty(HP* php);
int HeapSize(HP* php);