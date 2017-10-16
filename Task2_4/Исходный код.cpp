#include <iostream>
#include <assert.h>
/*
	Реализуйте стратегию выбора опорного элемента “медиана трёх”. Функцию Partition
	реализуйте методом прохода двумя итераторами от конца массива к началу.
*/

// Возвращает индекс медианы трех в массиве
int FindMedianOfThree(int* arr, int start, int end) {
	int mid = (start + end) / 2;

	if(arr[start] > arr[mid]) {
		if(arr[start] < arr[end])
			return start;
		return (arr[mid] > arr[end]) ? mid : end;
	} 

	if(arr[end] > arr[mid])
		return mid;
	return (arr[start] > arr[end]) ? start : end;
}

int Partition(int* arr, int left, int right) {
	if(left == right)
		return left;

	assert(right > left);
	// i указывает на место для вставки первого элемента большего опорного, j - на первый нерассмотренный элемент
	int i = right - 1;
	int j = i;
	int median = FindMedianOfThree(arr, left, right);
	std::swap(arr[median],arr[right]);

	for(; j >= left; j--) {
		if(arr[j] > arr[right]) {
			std::swap(arr[i], arr[j]);
			i--;
		}
	}
		
	std::swap(arr[i + 1], arr[right]);
	return i + 1;
}

int findStatistics(int* arr, int size, int k) {
	assert(k >= 0);

	int left = 0;
	int right = size - 1;

	while (true)
	{
		int pivotPos = Partition(arr, left, right);

		if(pivotPos == k)
			return arr[k];
		else if(pivotPos > k)
			right = pivotPos;
		else
			left = pivotPos + 1;
	}
}

int main() {
	int n = 0, k = 0;
	std::cin >> n >> k;

	int* arr = new int[n];

	for(int i = 0; i < n; i++) {
		int value = 0;
		std::cin >> value;
		arr[i] = value;
	}

	std::cout << findStatistics(arr, n, k);

	delete[] arr;
	return 0;
}