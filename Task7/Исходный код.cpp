#include <assert.h>
#include <iostream>
#include <algorithm>

/*
	В большой IT-фирме есть только одна переговорная комната. Желающие посовещаться заполняют заявки с
	желаемым временем начала и конца. Ваша задача определить максимальное количество заявок, которое
	может быть удовлетворено.
	Число заявок <= 100000.
	Формат входных данных:
	Вход содержит только пары целых чисел — начала и концы заявок.
	Формат выходных данных:
	Выход должен содержать натуральное число — максимальное число заявок.
*/

struct Request {
	int begin;
	int end;
};

// Сравнение заявок по времени окончания
bool CompareRequests(Request first, Request second) {
	return first.end < second.end;
}

class CRequestVector {
private:
	Request* buffer;
	int size;
	int capacity;
	void double_capacity();
public:
	CRequestVector();
	~CRequestVector() { delete[] buffer; }
	const Request& operator[](int index) const;
	Request& operator[](int index);
	void push_back(Request value);
	void sort();
};

CRequestVector::CRequestVector() {
	buffer = new Request[10];
	size = 0;
	capacity = 10;
}

const Request& CRequestVector::operator[](int index) const {
	assert(index >= 0);
	assert(index < size);
	return buffer[index];
}

Request& CRequestVector::operator[](int index) {
	assert(index >= 0);
	assert(index < size);
	return buffer[index];
}

void CRequestVector::double_capacity() {
	int newCapacity = 2 * capacity;
	Request* newBuffer = new Request[newCapacity];

	for(int i = 0; i < size; i++) {
		newBuffer[i] = buffer[i];
	}

	delete[] buffer;
	buffer = newBuffer;
	capacity = newCapacity;
}

void CRequestVector::push_back(Request value) {
	if(size == capacity)
		double_capacity();
	buffer[size++] = value;
}

void CRequestVector::sort() {
	std::sort(buffer, buffer + size, CompareRequests);
}

int main() {
	CRequestVector requests;
	
	int begin = 0, end = 0, requestsCount = 0;

	while(std::cin >> begin >> end) {
		Request request;
		request.begin = begin;
		request.end = end;
		requests.push_back(request);
		requestsCount++;
	}

	// Сортируем заявки по дате окончания и берем все заявки у которых время начала не меньше последнего
	// времени окончания
	requests.sort();
	int currentEnd = requests[0].end;
	int result = 1;
	for(int i = 1; i < requestsCount; i++) {
		if(requests[i].begin >= currentEnd)	{
			result++;
			currentEnd = requests[i].end;
		}
	}

	std::cout << result;

	return 0;
}