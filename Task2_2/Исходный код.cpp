#include <iostream>
#include <assert.h>
#include <vector>
using std::vector;

/*
	Дан массив натуральных чисел A[0..n), n не превосходит 10^8. Так же задан размер некотрого окна
	(последовательно расположенных элементов массива) в этом массиве k, k<=n. Требуется для
	каждого положения окна (от 0 и до n-k) вывести значение максимума в окне. Скорость работы O(n
	log n), память O(k).
	Формат входных данных. Вначале вводится n - количество элементов массива. Затем вводится n
	строк со значением каждого элемента. Затем вводится k - размер окна.
	Формат выходных данных. Разделенные пробелом значения максимумов для каждого положения
	окна.
*/

template<class T>
class Heap {
private:
	vector<T> heap;
	void SiftDown(int index);
	void SiftUp(int index);
	void BuildHeap();
public:
	Heap(vector<T> arr, int size);
	void Add(T value);
	T ExtractMax();
	T Max();
};

template<class T>
Heap<T>::Heap(vector<T> arr, int size) {
	assert(size > 0);

	for(int i = 0; i < size; i++)
		heap.push_back(arr[i]);
	BuildHeap();
}

template<class T>
void Heap<T>::SiftDown(int index) {
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	int largest = index;

	if(left < heap.size() && heap[left] > heap[index])
		largest = left;
	if(right < heap.size() && heap[right] > heap[largest])
		largest = right;

	if(largest != index) {
		std::swap(heap[index], heap[largest]);
		SiftDown(largest);
	}
}

template<class T>
void Heap<T>::SiftUp(int index) {
	while (index > 0)
	{
		int parent = (index - 1) / 2;
		if(heap[index] <= heap[parent])
			return;
		std::swap(heap[index], heap[parent]);
		index = parent;
	}
}

template<class T>
void Heap<T>::BuildHeap() {
	for(int i = heap.size() / 2 - 1; i >= 0; i--)
		SiftDown(i);
}

template<class T>
void Heap<T>::Add(T value) {
	heap.push_back(value);
	SiftUp(heap.size() - 1);
}

template<class T>
T Heap<T>::ExtractMax() {
	T returnValue = heap.front();
	heap[0] = heap.back();
	heap.pop_back();
	SiftDown(0);
	return returnValue;
}

template<class T>
T Heap<T>::Max() {
	return heap.front();
}

struct Object
{
	int index;
	int value;
	Object(): index(0), value(0) {}
	Object(int _index, int _value): index(_index), value(_value) {}
	bool operator<(const Object& right) const { return value < right.value; }
	bool operator>(const Object& right) const { return right < *this; }
	bool operator<=(const Object& right) const { return !(right < *this); }
	bool operator>=(const Object& right) const { return !(*this < right); }
};

int main() {
	int n = 0;
	std::cin >> n;
	
	vector<Object> arr;
	for(int i = 0; i < n; i++) {
		int value = 0;
		std::cin >> value;
		Object obj(i, value);
		arr.push_back(obj);
	}

	int windowSize = 0;
	std::cin >> windowSize;

	Heap<Object> heap(arr, windowSize);

	for(int i = windowSize; i < n; i++) {
		while(heap.Max().index < i - windowSize)
			heap.ExtractMax();
		std::cout << heap.Max().value << " ";
		heap.Add(arr[i]);
	}

	while(heap.Max().index < n - windowSize)
			heap.ExtractMax();
	std::cout << heap.Max().value << std::endl;

	return 0;
}