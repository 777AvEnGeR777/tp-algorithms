#include <iostream>
#include <vector>
#include <stack>
#include <cstdio>

using std::vector;

#define MAX_SORT_SIZE 32
/*
	ќтсортировать массив целых чисел за наименьшее врем€.
	¬ывести каждое дес€тое число в отсортированном массиве.
	–азрешаетс€ использовать произвольный тип сортировки.
	¬рем€ работы не более 10 секунд.

	Test:
	IN						OUT
	3 0 2 1 5 4 21 4 6 5	21

*/

void InsertionSort(vector<int> &arr, int start, int end) {
	for(int i = start + 1, j = start; i < end; i++) {
		int temp = arr[i];
		for(j = i - 1; j >= 0 && temp < arr[j]; j--) {
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = temp;
	}
}

int FindMedianOfThree(vector<int> &arr, int start, int end) {
	int mid = (start + end + 1) / 2;

	if(arr[start] > arr[mid]) {
		if(arr[start] < arr[end])
			return start;
		return (arr[mid] > arr[end]) ? mid : end;
	} 

	if(arr[end] > arr[mid])
		return mid;
	return (arr[start] > arr[end]) ? start : end;
}

int Partition(vector<int> &arr, int start, int end) {
	if(end - start <= 1)
		return 0;
	int pivot = FindMedianOfThree(arr, start, end - 1);
	std::swap(arr[pivot], arr[end - 1]);
	int i = start, j = end - 2;
	while (i <= j) {
		for(; arr[i] < arr[end - 1]; i++);
		for(; j >= start && ! (arr[j] < arr[end - 1]); j--);
		if(i < j)
			std::swap(arr[i++], arr[j--]);
	}
	std::swap(arr[i], arr[end - 1]);
	return i;
}

// √раницы сортировки массива
struct Borders
{
	int start;
	int end;
	Borders(): start(0), end(0) {}
	Borders(int _start, int _end): start(_start), end(_end) {}
};

void QuickSort(vector<int> &arr, int start, int end) { 
	std::stack<Borders> s;   
	Borders fullBorder(start, end);
	s.push(fullBorder);
	while (!s.empty()) {
		Borders border = s.top();
		s.pop();

		if (border.end <= border.start)
			continue;
		if(border.end - border.start <= MAX_SORT_SIZE) {
			InsertionSort(arr, border.start, border.end);
			continue;
		}
        int i = Partition(arr, border.start, border.end);
		if (i - 1 > border.end - i) {
            s.push(Borders(border.start, i));
            s.push(Borders(i + 1, border.end));
		}
        else {
           s.push(Borders(i + 1, border.end));
           s.push(Borders(border.start, i));
		}
	}
}

bool read_int(int &out) {
	int c = getchar();
    int x = 0;

    if (c == EOF)
        return false;
    for (; '0' <= c && c <= '9' ; c = getchar()) {
        x = x * 10 + c - '0';
    }
    out = x;
    return true;
}

void print_int(int value) {
	if(value / 10 != 0)
		print_int(value / 10);
	putchar(value % 10 + '0');
}

int main() {
	vector<int> vect;
	int value = 0;
	
	while(read_int(value)) {
		vect.push_back(value);
	}

	std::cout << std::endl;

	QuickSort(vect, 0, vect.size());

	for(int i = 9; i < vect.size(); i += 10) {
		print_int(vect[i]);
		putchar(' ');
	}

	return 0;
}