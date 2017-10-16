/*
	Реализуйте структуру данных типа “множество строк” на основе динамической
	хеш-таблицы с открытой адресацией. Хранимые строки непустые и состоят из строчных
	латинских букв.

	Хеш-функция строки должна быть реализована с помощью вычисления значения
	многочлена методом Горнера.
	Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте
	при добавлении элементов в случае, когда коэффициент заполнения таблицы достигает
	3/4.

	Структура данных должна поддерживать операции добавления строки в множество,
	удаления строки из множества и проверки принадлежности данной строки множеству.

	Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
	g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
*/

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using std::string;

class HashTable {
public:
	HashTable();
	bool Add(const string &key);
	bool Remove(const string &key);
	bool Has(const string &key);
private:
	static const int initialSize;
	static const int a;
	enum ElementState { FREE, BUSY, DELETED	};
	struct Element {
		std::string value;
		ElementState state;
		Element(): value(""), state(FREE) {}
		Element(const std::string &str): value(str), state(BUSY) {}
	};

	std::vector<Element> table;
	int tableElementsCount;
	int Hash(const std::string &str);
	int Hash(const std::string &str, int m);
	void Rehash();

};

const int HashTable::initialSize = 8;
const int HashTable::a = 61;

HashTable::HashTable(): table(initialSize), tableElementsCount(0) {}

bool HashTable::Add(const string &key) {
	int index = Hash(key);
	int insertIndex = -1;
	for(int i = 0; i < table.size(); i++) {
		if(table[index].state == BUSY && table[index].value == key)
			return false;
		else if(table[index].state == DELETED && insertIndex == -1)
			insertIndex = index;
		else if(table[index].state == FREE) {
			if(insertIndex == -1)
				insertIndex = index;
			break;
		}
		index = (index + i + 1) % table.size();
	}
	Element element(key);
	table[insertIndex] = element;
	tableElementsCount++;

	if(tableElementsCount / table.size() >= 0.75)
		Rehash();

	return true;
}

bool HashTable::Remove(const string &key) {
	int index = Hash(key);

	for(int i = 0; i < table.size(); i++) {
		if(table[index].state == BUSY && table[index].value == key) {
			table[index].value.clear();
			table[index].state = DELETED;
			tableElementsCount--;
			return true;
		}
		else if(table[index].state == FREE)
			return false;
		index = (index + i + 1) % table.size();
	}
	return false;

}

bool HashTable::Has(const string &key) {
	int index = Hash(key);
	for(int i = 0; i < table.size(); i++) {
		if(table[index].state == BUSY && table[index].value == key)
			return true;
		else if(table[index].state == FREE)
			return false;
		index = (index + i + 1) % table.size();
	}
	return false;
}

int HashTable::Hash(const string &str) {
	int hash = 0;
	for(int i = 0; i < str.length(); i++)
		hash = hash * a + str[i];
	hash %= table.size();
	return hash;
}

int HashTable::Hash(const string &str, int m) {
	int hash = 0;
	for(int i = 0; i < str.length(); i++)
		hash = hash * a + str[i];
	hash %= m;
	return hash;
}

void HashTable::Rehash() {
	int newSize = 2 * table.size();
	std::vector<Element> newTable(newSize);

	for(int i = 0; i < table.size(); i++) {
		if(table[i].state == DELETED || table[i].state == FREE)
			continue;

		int index = Hash(table[i].value, newSize);

		for(int probe = 0; probe < newSize; probe++) {	
			if(newTable[index].state == FREE) {
				newTable[index] = table[i];
				break;
			}
			index = (index + probe + 1) % newSize;
		}

	}

	table.swap(newTable);
}

int main() {
	char command = 0;
	string str;

	HashTable hashTable;

	while (std::cin >> command >> str) {
		switch (command) {
		case '+':
			std::cout << (hashTable.Add(str) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (hashTable.Remove(str) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			std::cout << (hashTable.Has(str) ? "OK" : "FAIL") << std::endl;
			break;
		default:
			assert(false);
			break;
		}
	}

	return 0;
}