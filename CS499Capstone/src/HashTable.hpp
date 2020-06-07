/*
 * Name			:	HashTable.hpp
 * Author		:	Lesley Potts-Langdon (constructors, method stubs and some base code were supplied,
 * 						all method code and logic produced by author)
 * Start Date	:	April 14, 2020
 * Submitted	:	May 30, 2020 (Milestone two - no changes needed)
 * 					June 7, 2020 (Milestone three - no changes needed
 * Description	:	Class to create a Hash Table with
 * 		methods for loading, displaying, searching and removing.
 */

#ifndef HASHTABLE_HPP_
#define HASHTABLE_HPP_

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include "CSVparser.hpp"
#include "Capstone.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
	// Define structures to hold bids
	struct Node {
		Bid bid;
		unsigned key;
		Node* next;

		// default constructor
		Node() {
			key = UINT_MAX;
			next = nullptr;
		}

		// constructor to take bid
		Node(Bid aBid) :
				Node() {
			bid = aBid;
		}

		// constructor with bid and key
		Node(Bid aBid, unsigned aKey) :
				Node(aBid) {
			key = aKey;
		}
	};
	vector<Node> nodes;

	unsigned int hash(int key);

public:
	HashTable();
	virtual ~HashTable();
	void Insert(Bid bid);
	void PrintAll();
	void Remove();
	Bid Search();
};

/**
 * Default constructor
 */
HashTable::HashTable() {
	// Initialize the structures used to hold bids
	nodes.resize(DEFAULT_SIZE);
}

/**
 * Destructor
 */
HashTable::~HashTable() {
	// Implement logic to free storage when class is destroyed
	nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
	// Implement logic to calculate a hash value
	return key % DEFAULT_SIZE;
}

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
	// Implement logic to insert a bid
	//atoi converts ASCII string to integer
	//c_str converts full string to string or chars
	unsigned key = hash(atoi(bid.bidId.c_str()));

	//&(nodes.at(key)) returns address of nodes.at(key)
	Node* oldNode = &(nodes.at(key));

	//no node at address
	if (oldNode == nullptr) {
		Node* newNode = new Node(bid, key);
		nodes.insert(nodes.begin() + key, (*newNode));
	} else {
		// node is found but empty
		if (oldNode->key == UINT_MAX) {
			oldNode->key = key;
			oldNode->bid = bid;
			oldNode->next = nullptr;
		} else {
			// find the next open node
			while (oldNode->next != nullptr) {
				oldNode = oldNode->next;
			}
			oldNode->next = new Node(bid, key);
		}
	}
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
	// Implement logic to print all bids

	// declares node pointer printNode
	Node* printNode;

	// for loop to iterate through nodes vector
	for (unsigned int i = 0; i < DEFAULT_SIZE; i++) {
		printNode = &(nodes.at(i));

		if (printNode->key != UINT_MAX) {
			cout << printNode->bid.bidId << ": " << printNode->bid.title
					<< " | " << printNode->bid.amount << " | "
					<< printNode->bid.fund << endl;

			// while loop to iterate through each bucket
			while (printNode->next != nullptr) {
				printNode = printNode->next;
				cout << printNode->bid.bidId << ": " << printNode->bid.title
						<< " | " << printNode->bid.amount << " | "
						<< printNode->bid.fund << endl;

			}
		}
	}
}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove() {
	// Implement logic to remove a bid

	string bidId;
	cout << "Which bid would you like to remove? (use 98109 for test purposes)"
			<< endl;
	cin >> bidId;
	Bid bid;
	unsigned key = hash(atoi(bidId.c_str()));

	Node* node = &(nodes.at(key));
	Node* tempNode = node->next;
	Node* sucNode = tempNode->next;

	if (node == nullptr || node->key == UINT_MAX) {
		return;
	}

	if (node != nullptr && node->key != UINT_MAX
			&& node->bid.bidId.compare(bidId) == 0) {
		nodes.erase(nodes.begin() + key);
		return;
	}

	while (node != nullptr) {
		if (tempNode->key != UINT_MAX
				&& tempNode->bid.bidId.compare(bidId) == 0) {

			node->next = sucNode;
		}
		node = node->next;
		tempNode = node->next;
		sucNode = tempNode->next;
	}

	return;

}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search() {
	string bidId;
	cout << "Enter Bid ID for search: (use 98109 for test purposes) " << endl;
	cin >> bidId;
	Bid bid;

	// Implement logic to search for and return a bid
	unsigned key = hash(atoi(bidId.c_str()));

	Node* node = &(nodes.at(key));

	if (node == nullptr || node->key == UINT_MAX) {
		return bid;
	}

	if (node != nullptr && node->key != UINT_MAX
			&& node->bid.bidId.compare(bidId) == 0) {
		return node->bid;
	}

	while (node != nullptr) {
		if (node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {
			return node->bid;
		}
		node = node->next;
	}

	return bid;
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
void htLoadBids(HashTable* hashTable) {
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
			hashTable->Insert(bid);
		}
	} catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
	}
}

/**
 * Hash Table main method, actual main() method directs here when user selects to
 * 			search by ID
 */
int htMain() {

	// Define a timer variable
	clock_t ticks;

	// Define a hash table to hold all the bids
	HashTable* bidTable;

	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Load Bids" << endl;
		cout << "  2. Display All Bids" << endl;
		cout << "  3. Find Bid" << endl;
		cout << "  4. Remove Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			bidTable = new HashTable();

			// Initialize a timer variable before loading bids
			ticks = clock();

			// Complete the method call to load the bids
			htLoadBids(bidTable);

			// Calculate elapsed time and display result
			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
					<< endl;
			break;

		case 2:
			bidTable->PrintAll();
			break;

		case 3:
			ticks = clock();

			bid = bidTable->Search();

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks

			if (!bid.bidId.empty()) {
				displayBid(bid);
			} else {
				cout << "Bid Id " << bid.bidId << " not found." << endl;
			}

			cout << "time: " << ticks << " clock ticks" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
					<< endl;
			break;

		case 4:
			bidTable->Remove();
			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}

#endif /* HASHTABLE_HPP_ */
