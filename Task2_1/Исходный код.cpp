#include <iostream>
#include <assert.h>
using std::cin;
using std::cout;

/*
	������ N ����� �� ���������. ������� (N-1)-������� �������������������� ���������
	�������, ���������� ����� ��� ��� �����.
	�������� : ������� ������� �� �����, ������� ���������� ���������� x. ���� ����� �����
	���������, �� ����������� ����� � ���������� ����������� y.
	����� �� ������� ����������� � ������� �������� ����� ����� �� ��������� ����� �� ����
	��������� �����.
*/

struct Coordinate {
	int x;
	int y;

	Coordinate(): x(0), y(0) {}
	Coordinate(int _x, int _y): x(_x), y(_y) {}  
};

bool CoordinateComparer(const Coordinate& left, const Coordinate& right) {
	return (left.x < right.x) || (left.x == right.x && left.y < right.y);
}

struct AngleFunctor
{
private:
	Coordinate pivot;
public:
	AngleFunctor (const Coordinate _pivot): pivot(_pivot) {}
	bool operator()(const Coordinate& left, const Coordinate& right); 
};

bool AngleFunctor::operator()(const Coordinate& left, const Coordinate& right) {
	// ���������� ������� � ������ �(x1, y1) � B(x2, y2) ����� (x2 - x1, y2 - y1)
	Coordinate firstVector(left.x - pivot.x, left.y - pivot.y);
	Coordinate secondVector(right.x - pivot.x, right.y - pivot.y);

	// ������� ���� ��������
	int direction = firstVector.x * secondVector.y - firstVector.y * secondVector.x;

	return direction < 0;
}

template <class T, class COMPARER>
void InsertionSort(T* arr, int len, COMPARER& comparer) {
	for(int i = 1, j = 0; i < len; i++) {
		T temp = arr[i];
		for(j = i - 1; j >= 0 && comparer(temp, arr[j]); j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}

int main() {
	int n = 0;
	cin >> n;

	Coordinate* arr = new Coordinate[n];

	for(int i = 0; i < n; i++) {
		int x = 0, y = 0;
		cin >> x >> y;
		Coordinate coordinate(x, y);
		arr[i] = coordinate;
	}

	InsertionSort(arr, n, CoordinateComparer);

	// ����� ������ ������� - ����� � ������������ ������������ x � y
	AngleFunctor angleFunctor(arr[0]);

	InsertionSort(arr + 1, n - 1, angleFunctor);

	for(int i = 0; i < n; i++) {
		cout << arr[i].x << " " << arr[i].y << "\n";
	}

	delete[] arr;

	return 0;
}