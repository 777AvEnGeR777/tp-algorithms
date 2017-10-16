/* 
	Реализация очереди
*/

#include <assert.h>
#include <iostream>

class CQueueOnList {
private:
	struct CLIstNode {
		int Data;
		CLIstNode* Next;

		CLIstNode(int data) : Data(data), Next(0) {}
	};
	CLIstNode* head;
	CLIstNode* tail;
public:
	CQueueOnList();
	~CQueueOnList();

	void Enqueue(int value);
	int Dequeue();
};

CQueueOnList::CQueueOnList() :
	head(0),
	tail(0)
{
}

CQueueOnList::~CQueueOnList() {
	while (head != 0) {
		CLIstNode* next = head->Next;
		delete head;
		head = next;
	}
}

void CQueueOnList::Enqueue(int value) {
	if(tail == 0) {
		assert(head == 0);
		tail = new CLIstNode(value);
		head = tail;
	} else {
		assert(head != 0);
		tail->Next = new CLIstNode(value);
		tail = tail->Next;
	}
}

int CQueueOnList::Dequeue() {
	if(head == 0) {
		assert(tail == 0);
		return -1;
	}

	assert(tail != 0);

	int value = head->Data;
	CLIstNode* toDelete = head;
	head = head->Next;
	delete toDelete;
	if(head == 0) {
		tail = 0;
	}

	return value;
}

int main() {
	int requestsCount = 0;
	std::cin >> requestsCount;

	CQueueOnList queue;

	for(int i = 0; i < requestsCount; i++) {
		int requestType = 0;
		int requestValue = 0;
		std::cin >> requestType >> requestValue;
		switch (requestType) {
			case 2:
				if(queue.Dequeue() != requestValue) {
					std::cout << "NO";
					return 0;
				}
				break;
			case 3:
				queue.Enqueue(requestValue);
				break;
			default:
				assert(false);
		}
	}
	std::cout << "YES";
	return 0;
}