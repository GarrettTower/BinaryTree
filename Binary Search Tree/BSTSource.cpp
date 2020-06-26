/*
*	Garrett Tower
*	Southern New Hampshire University
*	CS-499 Computer Science Capstone
*	Professor Penmatsa
*	May 13, 2020
*
*	Algorithms and Data Structure
*      - Binary Tree -
*
*****************************************
*
* https://www.geeksforgeeks.org/binary-tree-data-structure/
* https://www.geeksforgeeks.org/binary-search-tree-set-1-search-and-insertion/
* https://www.tutorialspoint.com/cplusplus-program-to-perform-operations-in-a-bst
* https://en.cppreference.com/w/cpp/language/pointer
* https://www.bogotobogo.com/cplusplus/binarytree.php
* https://www.youtube.com/watch?v=zuuAPYiMYDA
* https://www.youtube.com/watch?v=log-68bnS1g
*
*/

#include <iostream>
#include <queue>

using namespace std;

// Node struct to hold 3 properties of nodes
struct Node {
	int key;
	// Pointers to store memory addresses of left & right children
	Node *left;		// Cannot store Node within Node - can only point toward the Node
	Node *right;
};

// Return pointer towards node
Node* createNode(int key) {
	Node *node = new Node();
	// Point at different properties of the node
	node->key = key;
	node->left = NULL;
	node->right = NULL;

	return node;
}
// Breadth First Search/Level Order Traversal
Node* search(Node* root, int key) {
	if (root == NULL) {
		cout << "Tree is empty" << endl;
		return NULL;
	}
	// Initialize a queue to store nodes level by level
	queue<Node*> q;
	// Set to NULL in case node being searched for is not found
	Node* out = NULL;
	q.push(root);

	// Continue testing while queue is not empty
	while (!q.empty()) {

		Node* temp = q.front();
		// Pop first element in queue so it won't be tested in subsequent iterations
		q.pop();

		// Check if key being search for is found in queue
		if (temp->key == key) { 
			out = temp; cout << "Searching for node... Found: " << key << endl;
		}
		// Elements pushed to queue if node found
		if (temp->left != NULL) {
			q.push(temp->left);
		}
		if (temp->right != NULL) {
			q.push(temp->right);
		}
	}
	return out;
}
// Insert first available open slot
void insert(Node **root, int key) {
	if (*root == NULL) {
		cout << "Tree is empty... Creating tree\n" << endl;
		*root = createNode(key);
		return;
	}
	// Assuming the tree is not empty
	Node* nodeToInsert = createNode(key);
	queue<Node*> q;
	q.push(*root);

		while (! q.empty()) {
			Node *temp = q.front();
			q.pop();

			// Checks left first
			if (temp->left == NULL) {
				temp->left = nodeToInsert;
				return;
			}
			else {
				q.push(temp->left);
			}
			// Checks right
			if (temp->right == NULL) {
				temp->right = nodeToInsert;
				return;
			}
			else {
				q.push(temp->right);
			}
		}
}

void setDeepestRightNULL(Node *root, Node *deepestRight) {
	queue<Node*> q;
	q.push(root);
	Node *temp;

	while (!q.empty()) {
		temp = q.front();
		q.pop();
		if (temp->left != NULL) {
			if (temp->left == deepestRight) {
				cout << "Deepest Right Node Found" << endl;
				temp->left = NULL;
				return;
			}
			else {
				q.push(temp->left);
			}
		}
		if (temp->right != NULL) {
			if (temp->right == deepestRight) {
				cout << "Deepest Right Node Found" << endl;
				temp->right = NULL;
				return;
			}
			else {
				q.push(temp->right);
			}
		}
	}
}

void deleteNode(Node* root, int key) {
	Node *nodeToDelete = search(root, key);

	if (nodeToDelete != NULL) {
		queue<Node*> q;
		q.push(root);
		Node *temp;
		while (!q.empty()) {
			temp = q.front();
			q.pop();

			if (temp->left != NULL) {
				q.push(temp->left);
			}
			if (temp->right != NULL) {
				q.push(temp->right);
			}
			// Store the deepest right key in temp
			int deepestRightKey = temp->key;
			// Find node that points to deepestRightKey
			setDeepestRightNULL(root, temp);
			// Delete the nodeToDelete
			nodeToDelete->key = deepestRightKey;
		}
	}
}

int main() {

	int userChoice;

	cout << "Enter desired operation for Binary Tree\n" << endl;
	cout << "1. Create tree with Breadth First Traversal\n" <<
			"2. Create tree with createNode function\n" <<
			"3. Create tree with Breadth First Traversal\n" << endl;

	cout << "Please enter the number associated with the desired function: ";
	cin >> userChoice;

	if (userChoice == 1) {
		/* Create root and begin tree with the insert method */
					Node* root = NULL;
					/* Fill in tree in order */
					for (int i = 1; i <= 7; i++) {
						insert(&root, i);
					}
					cout << root->key << endl;
					cout << root->left->key << endl;
					cout << root->right->key << endl;
					cout << root->left->left->key << endl;
					cout << root->left->right->key << endl;
					cout << root->right->left->key << endl;
					cout << root->right->right->key << endl;

					Node* node = search(root, 4);

						//      1
						//     / \
						//    2   3
						//   / \ / \
						//  4  5 6  7
	}
	else if (userChoice == 2) {
				/* Create root and begin tree with the createNode method */
				Node *root = createNode(1);

				root->left = createNode(2);
				root->left->left = createNode(4);
				root->left->left->left = createNode(7);

				root->right = createNode(3);
				root->right->left = createNode(5);
				root->right->right = createNode(9);
				root->right->left->right = createNode(8);

				Node *node = search(root, 8);

				//        1
				//       / \
				//      2   3
				//     /   / \
				//    4   5   9 
				//   /     \
				//  7       8
	}
	else if (userChoice == 3) {
				/* Create root and begin tree with the insert method */
				Node* root = NULL;
				/* Fill in tree in order */
				for (int i = 1; i <= 6; i++) {
					insert(&root, i);
				}
				cout << "Structure of tree before deleteNode" << endl;
				cout << root->key << endl;
				cout << root->left->key << endl;
				cout << root->right->key << endl;
				cout << root->left->left->key << endl;
				cout << root->left->right->key << endl;
				cout << root->right->left->key << "\n" << endl;

				//      1
				//     / \
				//    2   3
				//   / \ / 
				//  4  5 6  

				deleteNode(root, 6);
				cout << "Structure of tree after deleteNode" << endl;
				cout << root->key << endl;
				cout << root->left->key << endl;
				cout << root->right->key << endl;
				cout << root->left->left->key << endl;
				cout << root->left->right->key << endl;
				cout << root->right->left->key << "\n" << endl;
	}
	else {
		cout << "Invalid input - Exiting program" << endl;
		return 0;
	}
	return 0;
}