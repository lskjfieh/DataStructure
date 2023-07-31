#include "Sort.h"

void PrintArray(int* a, int n) {
	for (int i = 0; i < n; i++) {
		printf("%d ", a[i]);
	}
	printf("\n");
}
void InserSort(int* a, int n) {
	// [0,end]有序，把end+1位置的值插入，保持有序
	for (int i = 0; i < n - 1; ++i) {
		int end = i;
		int tmp = a[end + 1];
		while (end >= 0) {
			if (tmp < a[end]) {
				a[end + 1] = a[end];
				--end;
			}
			else {
				break;
			}
		}
		a[end + 1] = tmp;
	}
}
void ShellSort(int* a, int n) {
	//int gap = 3;
	//for (int j = 0; j < gap; ++j) {
	//	for (int i = 0; i < n - gap; i += gap) {
	//		int end = i;
	//		int tmp = a[end + gap];
	//		while (end >= 0)
	//		{
	//			if (tmp < a[end]) {
	//				a[end + gap] = a[end];
	//				end -= gap;
	//			}
	//			else {
	//				break;
	//			}
	//		}
	//		a[end + gap] = tmp;
	//	}
	//}
	int gap = n;
	while (gap > 1) {
		gap = gap / 3 + 1;
		for (int i = 0; i < n - gap; ++i) {
			int end = i;
			int tmp = a[end + gap];
			while (end >= 0)
			{
				if (tmp < a[end]) {
					a[end + gap] = a[end];
					end -= gap;
				}
				else {
					break;
				}
			}
			a[end + gap] = tmp;
		}
	}

	
}