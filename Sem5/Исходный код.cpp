#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using std::string;

const int TableSize = 0;

//Хэш функция, опирающаяся на первый символ строки
int Hash(const std::string&key, int tableSize) {
	assert(tableSize > 0);
	if(key.empty())
		return 0;
	return key[0] % tableSize;
}

class CHashTable {
public:
	CHashTable();
	~CHashTable();
	bool Has(const string& key) const;
	bool Add(const string& key);
	bool Remove(const string& key);
private:
	struct CHashTableNode {
		string Key;
		CHashTableNode* Next;

		explicit CHashTableNode(const string& key, CHashTableNode* next) : Key(key), Next(next) {}
	};

	std::vector<CHashTableNode*> internalTable;
};

CHashTable::CHashTable() : internalTable(TableSize, nullptr) {}

CHashTable::~CHashTable() {
	for(int i = 0; i < internalTable.size; i++) {
		for(CHashTableNode* node = internalTable[i]; node != nullptr;) {
			CHashTableNode* next = node->Next;
			delete node;
			node = next;
		}
	}
}

bool CHashTable::Add(const string& key) {
	int hash = Hash(key, TableSize);
	for(CHashTableNode* node = internalTable[hash]; node != nullptr; node = node->Next) {
		if(node->Key == key) 
			return false;
	}

	internalTable[hash] = new CHashTableNode(key, internalTable[hash]);
	return true;
}

bool CHashTable::Remove(const string& key) {
	int hash = Hash(key, TableSize);

	// Храним в node указатель на ту область памяти, которая хранит указатель на элемент списка.
	// Если этот элемент списка надо удалить, то обновляем адрес на 
	for(CHashTableNode** node = &internalTable[hash]; *node != nullptr; node = &(*node)->Next) {
		if((*node)->Key == key) {
			CHashTableNode* toDelete = *node;
			*node = toDelete->Next;
			delete toDelete;
			return true;
		}
	}
	return false;
}

bool CHashTable::Has(const string& key) const {
	int hash = Hash(key, TableSize);
	for(CHashTableNode* node = internalTable[hash]; node != nullptr; node = node->Next) {
		if(node->Key == key) 
			return true;
	}
	return false;

}

int main()
{
	CHashTable table;
	char command = 0;
	std::string value;
	while (std::cin >> command >> value)
	{
		switch (command)
		{
		case '+':
			std::cout << (table.Add(value) ? "OK" : "FAIL") << std::endl;
			break;
		case '-':
			std::cout << (table.Remove(value) ? "OK" : "FAIL") << std::endl;
			break;
		case '?':
			std::cout << (table.Has(value) ? "OK" : "FAIL") << std::endl;
			break;
		default:
			assert(false);
			break;
		}
	}
	return 0;
}