#include <assert.h>
#include <iostream>

/*
	Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию. A[0..n-1] и B[0..m-1].
	n >> m. Найдите их пересечение. Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1] в
	массиве A.. В процессе поиска очередного элемента B[i] в массиве A пользуйтесь результатом поиска
	элемента B[i-1].
	n, k <= 10000.
*/

// Бинарный поиск в массиве. Возвращает индекс найденного элемента или -1, если элемент не найден
int BinarySearch(int* array, int key, int start, int end) {
	while (start < end) {
		int mid = (start + end) / 2;
		if(key <= array[mid])
			end = mid;
		else
			start = mid + 1;
	}

	return (start == end && array[start] != key) ? -1 : start;
}

// Поиск правой границы для бинарного поиска от левой границы. К левой границе прибавляется 4, 8, 16 и т.д.
// пока значение элемента меньше потенциальной правой границы
int FindBorders(int* array, int length, int &leftBorder, int key) {
	
	for(int i = leftBorder + 1, offset = 4; i < length; offset << 1, i += offset) {
		if(array[i] >= key)
			return i + 1;
		else
			leftBorder = i;
	}
	return length;
}

void FindIntersection(int* arrayA, int* arrayB, bool* intersections, int n, int m) {
	int lastLeftBorder = 0;

	for(int i = 0; i < m; i++) {
		int rightBorder = FindBorders(arrayA, n, lastLeftBorder, arrayB[i]);
		int result = BinarySearch(arrayA, arrayB[i], lastLeftBorder, rightBorder);
		// Если элемент пересекается, добавляем значение в массив пересечений и переносим левую границу
		if(result != -1) {
			intersections[i] = true;
			lastLeftBorder = result;
		}
	}
}

void FillArray(int* array, int length) {
	for(int i = 0; i < length; i++) {
		std::cin >> array[i];
	}
}

int main() {
	int n = 0, m = 0;

	std::cin >> n;
	std::cin >> m;

	assert(n > 0 && m > 0);

	int* arrayA = new int[n];
	int* arrayB = new int[m];

	FillArray(arrayA, n);
	FillArray(arrayB, m);

	// Массив пересечений. True - B[i] пересекается с A[i]
	bool* intersections = new bool[m];
	for(int i = 0; i < m; i++)
		intersections[i] = false;

	FindIntersection(arrayA, arrayB, intersections, n, m);

	for(int i = 0; i < m; i++) {
		if(intersections[i])
			std::cout << arrayB[i] << " ";
	}

	delete[] arrayA;
	delete[] arrayB;
	delete[] intersections;

	return 0;
}