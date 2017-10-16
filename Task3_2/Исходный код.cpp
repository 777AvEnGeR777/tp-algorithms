/*
	ƒано число N < 10^6 и последовательность целых чисел из [-2^31 ..2^31 ] длиной N.
	“ребуетс€ построить бинарное дерево, заданное наивным пор€дком вставки.
	“.е., при добавлении очередного числа K в дерево с корнем root, если root->Key <= K, то
	узел K добавл€етс€ в правое поддерево root; иначе в левое поддерево root.
	–екурси€ запрещена.

	¬ыведите элементы в пор€дке in-order (слева направо).
*/

#include <iostream>
#include <stack>

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
public:
	void Add(int value);
	void InOrder();
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

void BinaryTree::InOrder() {
	TreeNode* currentNode = root;
	std::stack<TreeNode*> stack;

	while (true) {
		if(currentNode != nullptr) {
			stack.push(currentNode);
			currentNode = currentNode->left;
			continue;
		}
		else {
			if(!stack.empty()) {
				currentNode = stack.top();
				stack.pop();

				std::cout << currentNode->value << " ";

				currentNode = currentNode->right;
			} else {
				break;
			}
		}
	}
}

int main() {
	int n = 0;
	std::cin >> n;

	BinaryTree tree;

	for(int i = 0; i < n; i++) {
		int value = 0;
		std::cin >> value;
		tree.Add(value);
	}

	tree.InOrder();

	return 0;
}