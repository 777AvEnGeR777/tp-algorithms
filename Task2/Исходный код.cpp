#include <assert.h>
#include <cmath>
#include <iostream>

/*
��������� ������� ��������� n-���������, ��������� ������������ ����� ������. ������� ��������
���������� ������, ����� ��������������� ������������� ���������� ���� ������ � ������� ������
������ ������� �������.
n < 1000, ���������� < 10000.
��������. ��� ���������� ������� n-��������� ����� ��������� ����� ��������������� ��������
�������� ��� ������ �������� ��������������.
*/

struct Coordinate {
	int x;
	int y;
};

// ������� ������� �������������� ����� ����� �������� �������� S = 0.5 * �����_��������� * ������
double GetArea(Coordinate* coordinates, int n) {
	double area = 0;

	for(int i = 0; i < n; i++) {
		area += 0.5 * (coordinates[(i + 1) % n].y + coordinates[i].y) *
			(coordinates[(i + 1) % n].x - coordinates[i].x); 
	}

	// ���������� ������ �������, �.� ������� ��������������� � ����� ���� �������������
	return std::abs(area);	
}

int main() {
	int n = 0;
	std::cin >> n;

	assert(n < 1000);

	Coordinate* coordinates = new Coordinate[n];

	for(int i = 0; i < n; i++) {
		int x = 0, y = 0;
		std::cin >> x >> y;

		coordinates[i].x = x;
		coordinates[i].y = y;
	}

	double area = GetArea(coordinates, n);

	std::cout.precision(2);
	std::cout << area;

	delete[] coordinates;

	return 0;
}