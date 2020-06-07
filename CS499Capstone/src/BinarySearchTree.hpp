/*
 * Name			:	BinarySearchTree.hpp
 * Author		:	Lesley Potts-Langdon (constructors, method stubs and some base code were supplied,
 * 						all method code and logic produced by author)
 * Start Date	:	April 14, 2020
 * Submitted	:	May 30, 2020 (phase one, all files accessible from CapstoneMain.cpp main() method)
 * 					June 7, 2020 (phase two, use BST to search for a bid by the bid amount
 * Description	:	Class to create a Binary Search Tree with
 * 		methods for loading, displaying, searching.
 */

#ifndef BINARYSEARCHTREE_HPP_
#define BINARYSEARCHTREE_HPP_
#include <algorithm>
#include <iostream>
#include <time.h>
#include "Capstone.hpp"
#include "CSVparser.hpp"
using namespace std;

// Internal structure for tree node
struct BstNode {
	Bid bid;
	BstNode *left;
	BstNode *right;

	// default constructor
	BstNode() {
		left = nullptr;
		right = nullptr;
	}

	// initialize with a bid
	BstNode(Bid aBid) :
			BstNode() {
		bid = aBid;
	}
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
	BstNode* root;

	void addNode(BstNode* node, Bid bid);
	void inOrder(BstNode* node);
	void postOrder(BstNode* node);
	void preOrder(BstNode* node);


public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Bid bid);
	void PostOrder();
	void PreOrder();
	void Search();

};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	// initialize housekeeping variables
	root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
	// recurse from root deleting every node
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::InOrder() {
	inOrder(root);
}

/**
 * Traverse the tree in post-order
 */
void BinarySearchTree::PostOrder() {
	postOrder(root);
}

/**
 * Traverse the tree in pre-order
 */
void BinarySearchTree::PreOrder() {
	preOrder(root);
}

/**
 * Insert a bid
 */
void BinarySearchTree::Insert(Bid bid) {
	// Implement inserting a bid into the tree
	if (root == nullptr) {
		root = new BstNode(bid);
	} else {
		this->addNode(root, bid);
	}
}



/**
 * Search for a bid
 */
void BinarySearchTree::Search() {
	// Implement searching the tree for a bid
	double bidAmount;
	cout << "Enter Bid Amount for search:" << endl;
	cin >> bidAmount;
	BstNode* current = root;
	int results = 0;
	// keep looping downwards until bottom reached or matching bidId found
	while (current != nullptr) {
		// if match found, return it
		if (current->bid.amount == (bidAmount)) {
			cout << current->bid.bidId << ": " << current->bid.title << " | " << current->bid.amount << " | "
						<< current->bid.fund << endl;
			results ++;
			//return current->bid;
		}
		// if bid is smaller than current node then traverse left
		if (bidAmount > (current->bid.amount)) {
			current = current->left;
			// else larger so traverse right
		} else {
			current = current->right;
		}
	}
	if (results ==0) {
		cout << "Bid Amount " << bidAmount << " not found." << endl;
	}

//	Bid bid;
//	return bid;
	return;
}

/**
 * Add a bid to some node (recursive)
 *
 * @param node Current node in tree
 * @param bid Bid to be added
 */
void BinarySearchTree::addNode(BstNode* node, Bid bid) {
	// Implement inserting a bid into the tree

	// if node is larger then add to left
	if (node->bid.amount < (bid.amount)) {
		// if no left node
		if (node->left == nullptr) {
			// this node becomes left
			node->left = new BstNode(bid);
		} else {
			// recurse down the left node
			this->addNode(node->left, bid);
		}
	} else {
		// if no right node
		if (node->right == nullptr) {
			// this node becomes right
			node->right = new BstNode(bid);
		} else {
			// recurse down the left node
			this->addNode(node->right, bid);
		}
	}
}

void BinarySearchTree::inOrder(BstNode* node) {
	if (node != nullptr) {
		inOrder(node->left);
		cout << node->bid.bidId << ": " << node->bid.title << " | "
				<< node->bid.amount << " | " << node->bid.fund << endl;
		inOrder(node->right);
	}
}

void BinarySearchTree::postOrder(BstNode* node) {
	if (node != nullptr) {
		postOrder(node->left);
		postOrder(node->right);
		cout << node->bid.bidId << ": " << node->bid.title << " | "
				<< node->bid.amount << " | " << node->bid.fund << endl;
	}
}

void BinarySearchTree::preOrder(BstNode* node) {
	if (node != nullptr) {
		cout << node->bid.bidId << ": " << node->bid.title << " | "
				<< node->bid.amount << " | " << node->bid.fund << endl;
		preOrder(node->left);
		preOrder(node->right);
	}
}



//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void bstLoadBids(BinarySearchTree* bst) {
	string csvPath;
	cout
			<< "What file would you like to load: (use eBid_Monthly_Sales_Dec_2016.csv for test purposes) "
			<< endl;
	cin >> csvPath;
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);

	// read and display header row - optional
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;

	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			// push this bid to the end
			bst->Insert(bid);
		}
	} catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
	}
}

/**
 * BST main() method. Actual main() method will route to here when user selects
 * 		to search by the bit amount.
 */
int bstMain() {

	// Define a timer variable
	clock_t ticks;

	// Define a binary search tree to hold all bids
	BinarySearchTree* bst;

	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Find Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			bst = new BinarySearchTree();

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			bstLoadBids(bst);

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
					<< endl;
			break;

		case 2:
			bst->InOrder();
			break;

		case 3:
			bst->Search();
			break;


		}
	}

	cout << "Good bye." << endl;

	return 0;
}

#endif /* BINARYSEARCHTREE_HPP_ */
