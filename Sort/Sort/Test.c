#include "Sort.h"
void TestInSertSort() {
	int a[] = {9, 1, 2, 5, 7, 4, 8, 6, 3, 5};
	InserSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}
void TestShellSort() {
	int a[] = { 9, 1, 2, 5, 7, 4, 8, 6, 3, 5 };
	ShellSort(a, sizeof(a) / sizeof(int));
	PrintArray(a, sizeof(a) / sizeof(int));
}
int main() {
	TestInSertSort();
	TestShellSort();
	return 0;
}