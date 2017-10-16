/*
	���� ����� N < 10^6 � ������������������ ��� ����� ����� �� [-2^31 ..2^31 ] ������ N.
	��������� ��������� ������ �� N �����, ����������������� ������ ����� {Xi, Yi}.
	������ ���� ����� {Xi, Yi} ���������� ���� Xi � ��������� Yi � ���������� ������.
	���������� ���� � ��������� ������ ���������� ������ ������� ���������,
	������������� �� ������:
		* ��� ���������� ���� (x, y) ���������� ����� �� ����� �� ���� P � �������
		�����������. ����� �������� ��������� ��������� �� ����� x ���, ����� �
		������ ��������� ��� ����� ������ x, � �� ������ ������ ��� ����� x.
		������������ ��� ������ �������� ��������� ��� ������ ���� (x, y). ����� ����
		�������� �� ����� ���� P.
	��������� ����� ������� ������ ������ �� ������ Xi ������� �� ������ 2.

	��������� ������� ������ �������� ������ ������ � ����������� ������. �������
	����� ���� ������������.
*/

#include <iostream>
#include <queue>
#include <assert.h>

class BinaryTree {
private:
	struct TreeNode
	{
		int value;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int _value): value(_value), left(nullptr), right(nullptr) {}
		~TreeNode();
	};
	int getDepth(TreeNode* node);
public:
	void Add(int value);
	int Depth();
	TreeNode* root;
	BinaryTree(): root(nullptr) {}
	~BinaryTree();
};

BinaryTree::~BinaryTree() {
	delete root;
}

BinaryTree::TreeNode::~TreeNode() {
	if(left != nullptr)
		delete left;
	if(right != nullptr)
		delete right;
}

void BinaryTree::Add(int value) {
	TreeNode* node = new TreeNode(value);
	if(root == nullptr) {
		root = node;
		return;
	}

	TreeNode* currentNode = root;

	while (true) { 
		if(node->value >= currentNode->value) {
			if(currentNode->right == nullptr) {
				currentNode->right = node;
				return;
			}
			currentNode = currentNode->right;
		}
		else {
			if(currentNode->left == nullptr) {
				currentNode->left = node;
				return;
			}
			currentNode = currentNode->left;
		}
	}
}

int BinaryTree::Depth() {
	return getDepth(root);
}

int BinaryTree::getDepth(TreeNode* node) {
	if(node == nullptr)
		return 0;

	TreeNode* currentNode = root;
	std::queue<TreeNode*> queue;
	queue.push(currentNode);
	int depth = 0;

	while(true) {
		int nodeCount = queue.size();
        if (nodeCount == 0)
			return depth;
		depth++;
 
        while (nodeCount > 0)
        {
			currentNode = queue.front();
            queue.pop();
			if (currentNode->left != nullptr)
                queue.push(currentNode->left);
			if (currentNode->right != nullptr)
                queue.push(currentNode->right);
            nodeCount--;
        }
	}

	return depth;

}

class Treap {
private:
	struct TreapNode
	{
		int value;
		int priority;
		TreapNode* left;
		TreapNode* right;
		TreapNode(int _value, int _priority): value(_value), priority(_priority),
			left(nullptr), right(nullptr) {}
		~TreapNode();
	};
	int getDepth(TreapNode* node, int depth);
public:
	void Add(int value, int priority);
	void Split(TreapNode* currentNode, int key, TreapNode* &left, TreapNode*& right);
	int Depth();
	TreapNode* root;
	Treap(): root(nullptr) {}
	~Treap();
};

Treap::~Treap() {
	delete root;
}

Treap::TreapNode::~TreapNode() {
	if(left != nullptr)
		delete left;
	if(right != nullptr)
		delete right;
}

void Treap::Add(int value, int priority) {
	TreapNode* node = new TreapNode(value, priority);
	if(root == nullptr) {
		root = node;
		return;
	}

	// ��� ��� � ��������� ��� ������ �� �������� ���������� ������� ��������� ��� ����������
	// ������� ��������
	TreapNode** currentNode = &root;

	while (true) {
		if(node->priority >= (*currentNode)->priority) {
			TreapNode *left = nullptr;
			TreapNode *right = nullptr;
			Split(*currentNode, node->value, left, right);
			node->left = left;
			node->right = right;
			if(*currentNode == root)
				root = node;
			*currentNode = node;
			return;
		}
		else if(node->value >= (*currentNode)->value) {
			if((*currentNode)->right == nullptr) {
				(*currentNode)->right = node;
				return;
			}
			currentNode = &((*currentNode)->right);
		}
		else {
			if((*currentNode)->left == nullptr) {
				(*currentNode)->left = node;
				return;
			}
			currentNode = &((*currentNode)->left);
		}
	}
}

void Treap::Split(TreapNode* currentNode, int key, TreapNode* &left, TreapNode* &right) {
	if(currentNode == nullptr) {
		left = nullptr;
		right = nullptr;
	} 
	else if(currentNode->value <= key) {
		Split(currentNode->right, key, currentNode->right, right);
		left = currentNode;
	}
	else {
		Split(currentNode->left, key, left, currentNode->left);
		right = currentNode;
	}

}

int Treap::Depth() {
	return getDepth(root, 0);
}

int Treap::getDepth(TreapNode* node, int depth) {
	if(node == nullptr)
		return depth;
	return std::max(getDepth(node->left, depth + 1), getDepth(node->right, depth + 1));
}

int main() {
	int n = 0;
	std::cin >> n;

	BinaryTree binaryTree;
	Treap treap;

	for(int i = 0; i < n; i++) {
		int value = 0, priority = 0;
		std::cin >> value >> priority;
		binaryTree.Add(value);
		treap.Add(value, priority);
	}

	std::cout << binaryTree.Depth() - treap.Depth();

	return 0;
}