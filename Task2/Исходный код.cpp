#include <assert.h>
#include <cmath>
#include <iostream>

/*
¬ычислить площадь выпуклого n-угольника, заданного координатами своих вершин. ¬начале вводитс€
количество вершин, затем последовательно целочисленные координаты всех вершин в пор€дке обхода
против часовой стрелки.
n < 1000, координаты < 10000.
”казание. ƒл€ вычислени€ площади n-угольника можно посчитать сумму ориентированных площадей
трапеций под каждой стороной многоугольника.
*/

struct Coordinate {
	int x;
	int y;
};

// —читаем площадь многоугольника через сумму площадей трапеций S = 0.5 * сумма_оснований * высота
double GetArea(Coordinate* coordinates, int n) {
	double area = 0;

	for(int i = 0; i < n; i++) {
		area += 0.5 * (coordinates[(i + 1) % n].y + coordinates[i].y) *
			(coordinates[(i + 1) % n].x - coordinates[i].x); 
	}

	// ¬озвращаем модуль площади, т.к площадь ориентированна€ и может быть отрицательной
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