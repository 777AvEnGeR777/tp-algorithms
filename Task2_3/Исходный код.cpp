#include <iostream>
#include <assert.h>

/*
	�� �������� ������ �������� N ��������. �������� ���������� ������ � ������� ������ �������
	������� (Li � Ri ). ����� ����� ���������� ����� �������� ������.
*/

struct Section
{
	int leftBorder;
	int rightBorder;
	Section(): leftBorder(0), rightBorder(0) {}
	Section(int left, int right): leftBorder(left), rightBorder(right) {}
};

// ��������� �� ����� �������, ���� ��� �����, �� �� ������
bool SectionComparer(const Section& left, const Section& right) {
	return (left.leftBorder < right.leftBorder) || (left.leftBorder == right.leftBorder && left.rightBorder < right.rightBorder);
}

template<class T, class COMPARER>
void SiftDown(T* arr, int size, int index, COMPARER& comparer) {
	assert(size > 0);

	int left = 2 * index + 1;
	int right = 2 * index + 2;

	int largest = index;

	if(left < size && comparer(arr[index], arr[left]))
		largest = left;
	if(right < size && comparer(arr[largest], arr[right]))
		largest = right;

	if(largest != index) {
		std::swap(arr[index], arr[largest]);
		SiftDown(arr, size, largest, comparer);
	}
}


template<class T, class COMPARER>
void BuildHeap(T* arr, int size, COMPARER& comparer) {
	assert(size > 0);

	for(int i = size / 2 - 1; i >= 0; i--)
		SiftDown(arr, size, i, comparer);
};

template<class T, class COMPARER>
void HeapSort(T* arr, int size, COMPARER& comparer) {
	assert(size > 0);

	int heapSize = size;
	BuildHeap(arr, size, comparer);
	while (heapSize > 1)
	{
		std::swap(arr[0], arr[heapSize - 1]);
		heapSize--;
		SiftDown(arr, heapSize, 0, comparer);
	}
}

int CalculatePaintedSectionLength(Section* arr, int size) {
	assert(size > 0);

	// �������� � ��������� ����� ������� ������� � ���������� ��� �����
	int length = arr[0].rightBorder - arr[0].leftBorder;
	int lastBorder = arr[0].rightBorder;

	for(int i = 1; i < size; i++) {
		// ���� ����� ������� ������� �� ������ ���������� ������, � ������ ������, �� ���������� � ���������� ������� �����
		// ������ � ���������� ������ ��������
		if(arr[i].leftBorder <= lastBorder && arr[i].rightBorder > lastBorder) {
			length += arr[i].rightBorder - lastBorder;
			lastBorder = arr[i].rightBorder;
		}
		// ���� �� ����� ������� ������� ������ ���������� ������, �� ���������� � ���������� ���� �������
		else if(arr[i].leftBorder > lastBorder) {
			length += arr[i].rightBorder - arr[i].leftBorder;
			lastBorder = arr[i].rightBorder;
		}
	}

	return length;
}

int main() {
	int n = 0;
	std:: cin >> n;

	Section* arr = new Section[n];

	for(int i = 0; i < n; i++) {
		int left = 0, right = 0;
		std::cin >> left >> right;
		Section section(left, right);
		arr[i] = section;
	}

	HeapSort(arr, n, SectionComparer);

	std::cout << CalculatePaintedSectionLength(arr, n);

	delete[] arr;

	return 0;
}