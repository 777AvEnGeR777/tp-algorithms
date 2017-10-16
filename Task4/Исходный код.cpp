#include <assert.h>
#include <iostream>

#define INITIAL_SIZE 10
/*
	–еализовать дек с динамическим зацикленным буфером.
*/


class Deck {
private:
	int *buffer;
	int size;
	int capacity;
	int head;
	int tail;
	void double_capacity();
public:
	Deck();
	~Deck();
	void push_front(int value);
	void push_back(int value);
	int pop_front();
	int pop_back();
};

Deck::Deck() {
	buffer = new int[INITIAL_SIZE];
	size = 0;
	capacity = INITIAL_SIZE;
	head = 1;
	tail = 0;
}

Deck::~Deck() {
	delete[] buffer;
}

void Deck::double_capacity() {
	int* newBuffer = new int[2 * capacity];

	// «аполн€ем новый буфер от головы дека до хвоста
	for(int i = head, j = 0; j <= size; ++i %= capacity, j++) {
		newBuffer[j] = buffer[i];
	}

	delete[] buffer;
	buffer = newBuffer;
	capacity = capacity * 2;
	head = 0;
	tail = size - 1;
}

void Deck::push_back(int value) {
	// «аталкиваем значение в хвост, если достигнут конец массива, переходим на его начало
	++tail %= capacity;
	buffer[tail] = value;
	size++;

	if(size == capacity)
		double_capacity();
}

void Deck::push_front(int value) {
	// ≈сли голова дека находитс€ в начале массива, то переносим ее в конец, иначе идем влево по массиву
	if(head == 0)
		head = capacity - 1;
	else
		head--;

	buffer[head] = value;
	size++;

	if(size == capacity)
		double_capacity();
}

int Deck::pop_front() {
	if(size == 0)
		return -1;

	size--;
	int value = buffer[head];
	++head %= capacity;

	return value;
}

int Deck::pop_back() {
	if(size == 0)
		return -1;

	size--;
	int value = buffer[tail];

	if(tail == 0)
		tail = capacity - 1;
	else
		tail--;

	return value;
}

int main() {
	int n = 0;
	std::cin >> n;

	assert(n > 0 && n <= 1000000);

	Deck deck;
	int command = 0, value = 0;
	bool result = true;

	for(int i = 0; i < n; i++) {
		std::cin >> command >> value;
		
		switch(command) {
			case 1:
				deck.push_front(value);
				break;
			case 2:
				if(value != deck.pop_front())
					result = false;
				break;
			case 3:
				deck.push_back(value);
				break;
			case 4:
				if(value != deck.pop_back())
					result = false;
				break;
			default:
				assert(false);
		}
	}

	if(result)
		std::cout << "YES";
	else
		std::cout << "NO";
}
