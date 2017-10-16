/*
	Дано число N и N строк. Каждая строка содержит команду
	добавления или удаления натуральных чисел, а также запрос на получение k-ой
	порядковой статистики. Команда добавления числа A задается положительным числом A,
	команда удаления числа A задается отрицательным числом “-A”. Запрос на получение
	k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса -
	O(log n).
*/

#include <iostream>

class AVLTree {
private:
	struct TreeNode
	{
		int value;
		int height;
		TreeNode* left;
		TreeNode* right;
		TreeNode(int _value): value(_value), height(1), left(nullptr), right(nullptr) {}
		~TreeNode();
	};
	TreeNode* root;

	int GetHeight(TreeNode* node);
	int GetSize(TreeNode* node);
	int BalanceFactor(TreeNode* node);
	TreeNode* RotateLeft(TreeNode* node);
	TreeNode* RotateRight(TreeNode* node);
	TreeNode* RotateLeftRight(TreeNode* node);
	TreeNode* RotateRightLeft(TreeNode* node);
	TreeNode* Balance(TreeNode* node);
	TreeNode* FindMin(TreeNode* node);
	TreeNode* RemoveMin(TreeNode* node);
	TreeNode* Insert(TreeNode* node, int value);
	TreeNode* Remove(TreeNode* node, int value);
	int findKStatistics(TreeNode* node, int k);
public:
	AVLTree(): root(nullptr) {}
	~AVLTree();
	void Add(int value);
	void Delete(int value);
	int KStatistics(int k);
};

AVLTree::TreeNode::~TreeNode() {
	if(left != nullptr)
		delete left;
	if(right != nullptr)
		delete right;
}

AVLTree::~AVLTree() {
	delete root;
}

int AVLTree::GetHeight(TreeNode* node) {
	int height = 0;
	if (node != nullptr) {
		int leftHeight = GetHeight(node->left);
		int rightHeight = GetHeight(node->right);
		int maxHeight = std::max(leftHeight, rightHeight);
		height = maxHeight + 1;
	}
	return height;
}

int AVLTree::GetSize(TreeNode* node) {
	if(node == nullptr)
		return 0;
	return GetSize(node->left) + GetSize(node->right) + 1;
}

int AVLTree::BalanceFactor(TreeNode* node) {
	int leftHeight = GetHeight(node->left);
	int rightHeight = GetHeight(node->right);
	int balanceFactor= leftHeight - rightHeight;
	return balanceFactor;
}

AVLTree::TreeNode* AVLTree::RotateLeft(TreeNode* node) {
	TreeNode* secondNode = node->left;
	node->left = secondNode->right;
	secondNode->right = node;
	if(node == root)
		root = secondNode;
	return secondNode;
}

AVLTree::TreeNode* AVLTree::RotateRight(TreeNode* node) {
	TreeNode* secondNode = node->right;
	node->right = secondNode->left;
	secondNode->left = node;
	if(node == root)
		root = secondNode;
	return secondNode;
}

AVLTree::TreeNode* AVLTree::RotateLeftRight(TreeNode* node) {
	TreeNode* secondNode = node->left;
	node->left = RotateRight(secondNode);
	return RotateLeft(node);
}

AVLTree::TreeNode* AVLTree::RotateRightLeft(TreeNode* node) {
	TreeNode* secondNode = node->right;
	node->right = RotateLeft(secondNode);
	return RotateRight(node);
}

AVLTree::TreeNode* AVLTree::Balance(TreeNode* node) {
	int balanceFactor = BalanceFactor(node);

	if(balanceFactor > 1) {
		if(BalanceFactor(node->left) > 0)
			node = RotateLeft(node);
		else
			node = RotateLeftRight(node);
	}
	else if(balanceFactor < -1) {
		if(BalanceFactor(node->right) > 0)
			node = RotateRightLeft(node);
		else
			node = RotateRight(node);
	}

	return node;
}

AVLTree::TreeNode* AVLTree::Insert(TreeNode* node, int value) {
	if(node == nullptr) {
		node = new TreeNode(value);
		return node;
	}
	else if(value < node->value) {
		node->left = Insert(node->left, value);
		node = Balance(node);
	}
	else if (value >= node->value) {
		node->right = Insert(node->right, value);
		node = Balance(node);
	}
	return node;
}

AVLTree::TreeNode* AVLTree::FindMin(TreeNode* node) {
	return node->left ? FindMin(node->left) : node;
}

AVLTree::TreeNode* AVLTree::RemoveMin(TreeNode* node) {
	if(node->left == nullptr)
		return node->right;
	node->left = RemoveMin(node->left);
	return Balance(node);
}

AVLTree::TreeNode* AVLTree::Remove(TreeNode* node, int value) {
	if(node == nullptr)
		return 0;
	if(value < node->value)
		node->left = Remove(node->left, value);
	else if(value > node->value)
		node->right = Remove(node->right, value);
	else {
		TreeNode* left = node->left;
		TreeNode* right = node->right;
		node->left = nullptr;
		node->right = nullptr;
		
		if(right == nullptr) {
			delete node;
			return left;
		}

		TreeNode* min = FindMin(right);
		min->right = RemoveMin(right);
		min->left = left;
		delete node;

		return Balance(min);
	}
	return Balance(node);
}

void AVLTree::Add(int value) {
	root = Insert(root, value);
}

void AVLTree::Delete(int value) {
	root = Remove(root, value);
}

int AVLTree::findKStatistics(TreeNode* node, int k) {
	int r = GetSize(node->left);
	if (r == k)
		return node->value;
	else if(r > k)
		return findKStatistics(node->left, k);
	else
		return findKStatistics(node->right, k - r - 1);
}

int AVLTree::KStatistics(int k) {
	return findKStatistics(root, k);
}

int main() {
	int n = 0;
	std:: cin >> n;

	AVLTree tree;
	for(int i = 0; i < n; i++) {
		int command = 0, k = 0;
		std::cin >> command >> k;
		if(command < 0) {
			command = -command;
			tree.Delete(command);
		}
		else {
			tree.Add(command);
		}
		std::cout << tree.KStatistics(k) << std::endl;
	}

	return 0;
}