#include <assert.h>
#include <iostream>
#include <cstring>

/*
	Дано N кубиков. Требуется определить каким количеством способов можно выстроить из этих кубиков
	пирамиду.
	Формат входных данных:
	На вход подается количество кубиков N.
	Формат выходных данных:
	Вывести число различных пирамид из N кубиков.

	Каждый вышележащий слой пирамиды должен быть не больше нижележащего.
	N <= 200.
*/

void InitCacheMatrix(long long** matrix, int cubesNumber) {
	for(int i = 0; i < cubesNumber; i++) {
		matrix[i] = new long long[cubesNumber];
		::memset(matrix[i], 0, cubesNumber * sizeof(long long));
	}
}

/* Заполняем матрицу кэша по принципу:
n - количество кубиков
k - длина основания

M(n, k), при k <= n = M(n - k, k) + M(n, k - 1)
M(n, k), при k > n = M(n, n)

При этом:
M(0, 0) = 1
M(i, 0) = 0, при i > 0
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
	
	// Количество пирамидок равно разложению M(n, n), где n - количество кубиков
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