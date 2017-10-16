#include <iostream>
#include <algorithm>
#include <cstring>
/*
	Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j:
	если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. Последовательность
	может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
*/

void Merge(int* leftArray, int leftLength, int* rightArray, int rightLength, int* c) {
	int i = 0, j = 0;
	while(i < leftLength && j < rightLength)
	{
		if(leftArray[i] < rightArray[j])
		{
			c[i + j] = leftArray[i];
			i++;
		} else {
			c[i + j] = rightArray[j];
			j++;
		}
	}

	if(i == leftLength) {
		for(; j < rightLength; j++) 
			c[i + j] = rightArray[j];
	} else {
		for(; i < leftLength; i++)
			c[i + j] = leftArray[i];
	}
}

void MergeSort(int* arr, int len) {
	if(len <= 1)
		return;

	int firstLen = len / 2;
	int secondLen = len - firstLen;

	MergeSort(arr, firstLen);
	MergeSort(arr + firstLen, secondLen);

	int* tempArray = new int[len];
	Merge(arr, firstLen, arr + firstLen, secondLen, tempArray);
	memcpy(arr, tempArray, len * sizeof(int));

	delete[] tempArray;
}

int main() {
	int n = 0, k = 0;
	std::cin >> n >> k;

	
	int* leftArray = new int[k];
	int* rightArray = new int[k];
	int* mergedArray = new int[2 * k];
	// Запишем первые k элементов 
	for(int i = 0; i < k; i++) {
		std::cin >> leftArray[i];
	}
	// И отсортируем их
	MergeSort(leftArray, k);

	if(n == k) {
		for(int i = 0; i < k; i++)
			std::cout << leftArray[i] << " ";
		return 0;
	}

	// Запишем следующие k элементов, после чего сольем их в один массив и выведем первые k элементов
	for(int i = k; i < n; i++) {
		std::cin >> rightArray[i % k];
		if((i + 1) % k == 0) {
			MergeSort(rightArray, k);
			Merge(leftArray, k, rightArray, k, mergedArray);
			for(int j = 0; j < k; j++) {
				std::cout << mergedArray[j] << " ";
			}
			// Если массив делится на k нацело, то выводим и вторую часть слитого массива
			if(i + 1 == n) {
				for(int j = k; j < 2 * k; j++) {
					std::cout << mergedArray[j] << " ";
				}
			}
			// Скопируем в левый массив правый массив
			for(int j = 0; j < k; j++)
				leftArray[j] = mergedArray[j + k];
		}
	}

	// Если массив не делится нацело на k, то сливаем остаток
	if(n % k != 0) {
		MergeSort(rightArray, n % k);
		Merge(leftArray, k, rightArray, n % k, mergedArray);
		for(int i = 0; i < k + (n % k); i++) {
			std::cout << mergedArray[i] << " ";
		}
	}

	delete[] leftArray;
	delete[] rightArray;
	delete[] mergedArray;
	return 0;
}