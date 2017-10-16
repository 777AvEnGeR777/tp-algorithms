/* PocketSort */
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;

// Карманная сортировка по последней цифре
void PocketSort(vector<long long>& arr){
	int n = arr.size();
	if( n <= 1)
		return;
	
	int k = 10;

	// Количество элементов в каждом кармане
	vector<int> pockets(k, 0);
	for(int i = 0; i < n; i++) {
		pockets[arr[i] % 10]++;
	}
	// Преобразуем в координаты начала карманов.
	int sum = 0;
	for(int i = 0; i < k; i++) {
		int current = pockets[i];
		pockets[i] = sum;
		sum += current;
	}
	// Перемещаем элементы в результирующий массив
	vector<long long> result(n, 0);

	for(int i = 0; i < n; i++) {
		result[pockets[arr[i] % 10]++] = arr[i];
	}

	// Меняем местами. Старый удалится в деструкторе result.
	std::swap(arr, result);
}

int main() {
	int n = 0;
	cin >> n;

	vector<long long> arr (n, 0);
	for(int i = 0; i < n; i++) {
		cin >> arr[i];
	}

	PocketSort(arr);

	return 0;
}