#include <assert.h>
#include <iostream>

/*
	���� ��� ������� ��������������� ����� �����, ������������� �� �����������. A[0..n-1] � B[0..m-1].
	n >> m. ������� �� �����������. ��������� ����� ������: O(m * log k), ��� k - ������� ��������� B[m-1] �
	������� A.. � �������� ������ ���������� �������� B[i] � ������� A ����������� ����������� ������
	�������� B[i-1].
	n, k <= 10000.
*/

// �������� ����� � �������. ���������� ������ ���������� �������� ��� -1, ���� ������� �� ������
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

// ����� ������ ������� ��� ��������� ������ �� ����� �������. � ����� ������� ������������ 4, 8, 16 � �.�.
// ���� �������� �������� ������ ������������� ������ �������
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
		// ���� ������� ������������, ��������� �������� � ������ ����������� � ��������� ����� �������
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

	// ������ �����������. True - B[i] ������������ � A[i]
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