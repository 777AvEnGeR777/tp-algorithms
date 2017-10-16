#include <assert.h>
#include <iostream>

/* Вывести квадраты натуральных чисел от 1 до n, используя только O(n) операций сложения и
   вычитания (умножением пользоваться нельзя).
   n <= 1000
*/


// Используем свойство (n+1)^2=n^2+2n+1 для расчета квадратов последующих чисел 
void GetSquares(int* squares, int n) {
	assert(n > 0);
	int prevSquare = 1;
	for(int i = 1; i <= n; i++) {
		squares[i - 1] = prevSquare;
		prevSquare += i + i + 1;
	}
}

int main() {
	int n = 0;
	std::cin >> n;

	int* squares = new int[n];
	for(int i = 0; i < n; i++)
		squares[i] = 0;

	GetSquares(squares, n);

	for(int i = 0; i < n; i++)
		std::cout << squares[i] << " ";

	delete[] squares;

	return 0;
}