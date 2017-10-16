#include <assert.h>
#include <iostream>
#include <cstring>

/*
	���� N �������. ��������� ���������� ����� ����������� �������� ����� ��������� �� ���� �������
	��������.
	������ ������� ������:
	�� ���� �������� ���������� ������� N.
	������ �������� ������:
	������� ����� ��������� ������� �� N �������.

	������ ����������� ���� �������� ������ ���� �� ������ ������������.
	N <= 200.
*/

void InitCacheMatrix(long long** matrix, int cubesNumber) {
	for(int i = 0; i < cubesNumber; i++) {
		matrix[i] = new long long[cubesNumber];
		::memset(matrix[i], 0, cubesNumber * sizeof(long long));
	}
}

/* ��������� ������� ���� �� ��������:
n - ���������� �������
k - ����� ���������

M(n, k), ��� k <= n = M(n - k, k) + M(n, k - 1)
M(n, k), ��� k > n = M(n, n)

��� ����:
M(0, 0) = 1
M(i, 0) = 0, ��� i > 0
*/
void FillCacheMatrix(long long** matrix, int cubesNumber) {
	for(int i = 0; i < cubesNumber; i++) {
		for(int base = 0; base < cubesNumber; base++) {
			if(i == 0 && base == 0)
				matrix[i][base] = 1;
			else if(base == 0)
				matrix[i][base] = 0;
			else if(base > i)
				matrix[i][base] = matrix[i][i];
			else
				matrix[i][base] = matrix[i - base][base] + matrix[i][base - 1];		
		}
	}
}

long long CountPiramidsNumber(int cubesNumber) {
	
	long long** cacheMatrix = new long long*[++cubesNumber];
	InitCacheMatrix(cacheMatrix, cubesNumber);
	FillCacheMatrix(cacheMatrix, cubesNumber);
	
	// ���������� ��������� ����� ���������� M(n, n), ��� n - ���������� �������
	long long piramidsCount = cacheMatrix[cubesNumber - 1][cubesNumber - 1];

	for(int i = 0; i < cubesNumber; i++) {
		delete[] cacheMatrix[i];
	}
	delete[] cacheMatrix;

	return piramidsCount;
}

int main() {
	int n = 0;
	std::cin >> n;

	assert(n >= 0 && n <= 200);

	std::cout << CountPiramidsNumber(n);

	return 0;
}