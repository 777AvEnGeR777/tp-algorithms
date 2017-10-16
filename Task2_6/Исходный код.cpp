#include <iostream>
/*
	дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 10^6 .
	отсортировать массив методом MSD по битам (бинарный QuickSort).
*/

// Возвращает бит находящийся на позиции bitPos
int Digit(unsigned long long number, int bitPos) {
	unsigned long long bit = number & (1LL << bitPos);
	return bit >> bitPos;
}

void BinaryQuickMSDSort(unsigned long long* arr, int left, int right, int bit) {
	if(right <= left || bit < 0)
		return;
	int i = left, j = right;
	while(i != j)
	{
		while(Digit(arr[i], bit) == 0 && i < j) 
			i++;
		while(Digit(arr[j], bit) == 1 && i < j)
			j--;
		std::swap(arr[i], arr[j]);
	}
	if(Digit(arr[right], bit) == 0)
		j++;
	BinaryQuickMSDSort(arr, left, j - 1, bit - 1);
	BinaryQuickMSDSort(arr, j, right, bit - 1);
}

int main() {
	int n = 0;
	std::cin >> n;

	unsigned long long* arr = new unsigned long long[n];

	for(int i = 0; i < n; i++) {
		std::cin >> arr[i];
	}

	BinaryQuickMSDSort(arr, 0, n - 1, 63);

	for(int i = 0; i < n; i++)
		std::cout << arr[i] << " ";

	delete[] arr;
	return 0;
}