#include <assert.h>
#include <iostream>
#include <string>

#define INIT_SIZE 10
/*
	���� ��������� � ��������� ������. ��������� ���, ��������� ������� ��������� � ����������� ������.
	��������� �� �������� ������������� �����.
	���������� �������� <= 100.
	������ ������� ������. 
	������, ��������� �� �������� "0123456789-+x/()"
	�������������, ��� ������� ��������� ���������, ��� ������� �� 0, ��������� � ����� ������. �������
	�������������.
	������ �������� ������.
	�������� ���������.
*/

template <typename T>
class CStack {
private:
	T* buffer;
	int size;
	int top;
	void double_size();
public:
	CStack();
	~CStack();
	void push(T value);
	T pop();
	T stack_top();
	bool is_empty() { return top == -1; }
};

template <typename T>
CStack<T>::CStack() {
	buffer = new T[INIT_SIZE];
	size = INIT_SIZE;
	top = -1;
}

template <typename T>
CStack<T>::~CStack() {
	delete[] buffer;
}

template <typename T>
void CStack<T>::double_size() {
	T* newBuffer = new T[size * 2];
	for(int i = 0; i <= top; i++) {
		newBuffer[i] = buffer[i];
	}

	delete[] buffer;
	buffer = newBuffer;
	size *= 2;
}

template <typename T>
void CStack<T>::push(T value) {
	if(top + 1 == size)
		double_size();

	buffer[++top] = value;
}

template <typename T>
T CStack<T>::pop() {
	assert(top != -1);
	return buffer[top--];
}

template <typename T>
T CStack<T>::stack_top() {
	assert(top != -1);
	return buffer[top];
}

bool IsDigit(char symbol) {
	if(symbol >= '0' && symbol <= '9')
		return true;
	return false;
}

// ������������ �������� ������� ���������� (+,-). ���� ���� ������ ��� �� ������� ����������� ������,
// �� ����������� �������� � ����. ����� ����������� �� ����� �������� � ����������� ������ �� ���������
// ����������� ������ ��� ���� ���� �� ��������, ����� ����������� �������� � ����
void HandleLowPriorityOperation(CStack<char> &stack, char operation, std::string &postfixExpression) {
	while(!stack.is_empty() && stack.stack_top() != '(')
		postfixExpression += stack.pop();
	stack.push(operation);
}

// ������������ �������� �������� ���������� (*,/). ���� ���� ������, �� ������� ����������� ������ ���
// �������� ������� ����������, �� ����������� �������� � ����. ����� ����������� �� ����� �������� � 
// ����������� ��������� �� ��������� ����������� ������ ��� �������� ������� ����������, ����� ����
// ����������� � ���� ��������
void HandleHighPriorityOperation(CStack<char> &stack, char operation, std::string &postfixExpression) {
	while(!stack.is_empty() && stack.stack_top() != '(' && stack.stack_top() != '+' && stack.stack_top() != '-')
		postfixExpression += stack.pop();

	if(!stack.is_empty() && stack.stack_top() != '(')
		postfixExpression += stack.pop();
	stack.push(operation);
}

void HandleOperation(CStack<char> &stack, char operation, std::string &postfixExpression) {
	switch (operation)
		{
			case '+':
			case '-':
				HandleLowPriorityOperation(stack, operation, postfixExpression);
				break;
			case '*':
			case '/':
				HandleHighPriorityOperation(stack, operation, postfixExpression);
				break;
			case '(': 
				stack.push('(');
				break;
			case ')':
				// ����������� �� ����� �������� � ����������� ������ �� ����������� ������ 
				while(stack.stack_top() != '(')
					postfixExpression += stack.pop();
				stack.pop();
				break;
			default:
				assert(false);
		}
}

// ��������� �� ��������� ������ � �����������
std::string PostfixExpression(std::string &expression) {
	CStack<char> stack;
	std::string postfixExpression;
	bool prevIsDigit = false;

	for(unsigned int i = 0; i < expression.length(); i++) {
		// ���� � ������ ���� ����� ����� ��������� �� � ����������� ������
		if(IsDigit(expression[i])) {
			postfixExpression += expression[i];
			prevIsDigit = true;
			continue;
		}

		// ���� ����� � ����� �����������, �� ������ ����� ����� ������
		if(prevIsDigit) {
			postfixExpression += ' ';
			prevIsDigit = false;
		}

		HandleOperation(stack, expression[i], postfixExpression);		
	}

	// ����������� �� ����� ��� ���������� �������� � ���������� �� � ����������� ������
	while(stack.is_empty() == false)
		postfixExpression += stack.pop();

	return postfixExpression;
}

void CalculateOperation(CStack<int> &stack, char operation) {
	int secondOperator = stack.pop();
	int firstOperator = stack.pop();
	switch (operation)
	{
		case '+':
			firstOperator += secondOperator;
			break;
		case '-':
			firstOperator -= secondOperator;
			break;
		case '*':
			firstOperator *= secondOperator;
			break;
		case '/':
			firstOperator /= secondOperator;
			break;
		default:
			assert(false);
			break;
	}
	stack.push(firstOperator);
}

int CalculateExpression(std::string &postfixExpression) {
	CStack<int> stack;
	
	std::string stringNumber = "";
	bool prevIsDigit = false;
	for(unsigned int i = 0; i < postfixExpression.length(); i++) {
		
		// �������� ����� � �����
		if(IsDigit(postfixExpression[i])) {
			stringNumber += postfixExpression[i];
			prevIsDigit = true;
			continue;
		}

		int cubesNumber = 0;

		// ��������� ��������� ����� �� ������ � int � ����������� ��� � ����
		if(prevIsDigit) {
			cubesNumber = atoi(stringNumber.c_str());
			stringNumber = "";
			stack.push(cubesNumber);
			prevIsDigit = false;
		}

		if(postfixExpression[i] == ' ')
			continue;

		CalculateOperation(stack,postfixExpression[i]);
	}
	return stack.pop();
}

int main()
{
	std::string expression;
	std::cin >> expression;

	std::string postfixExpression = PostfixExpression(expression);

	std::cout << CalculateExpression(postfixExpression);

	return 0;
}