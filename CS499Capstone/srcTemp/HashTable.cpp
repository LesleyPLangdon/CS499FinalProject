//============================================================================
// Completed by: Lesley Potts-Langdon
// Class	   : CS260
// Date        : 2/11/2018
// Name        : HashTable.cpp
// Author      : John Watson
// Version     : 1.0
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

/*
#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
//#include "CS499Capstone.hpp"
//#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double htStrToDouble(string str, char ch);

struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

*
 * Define a class containing data members and methods to
 * implement a hash table with chaining.

class HashTable {

private:
    // FIXME (1): Define structures to hold bids
	struct Node {
		Bid htBid;
		unsigned key;
		Node* next;

		// default constructor
		Node() {
			//key = 0;
			key = UINT_MAX;
			next = nullptr;
		}

		// constructor to take htBid
		Node(Bid aBid) : Node() {
			htBid = aBid;
		}

		// constructor with htBid and key
		Node(Bid aBid, unsigned aKey) : Node(aBid){
			key = aKey;
		}
	};
	vector<Node> nodes;

	unsigned int hash(int key);

public:
    HashTable();
    virtual ~HashTable();
    void Insert(Bid htBid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
};


*
 * Display the htBid information to the console (std::out)
 *
 * @param htBid struct containing the htBid info

void htDisplayBid(Bid htBid) {
    cout << htBid.bidId << ": " << htBid.title << " | " << htBid.amount << " | "
            << htBid.fund << endl;
    return;
}

*
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out

double htStrToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}
*
 * Default constructor

HashTable::HashTable() {
    // FIXME (2): Initialize the structures used to hold bids
	nodes.resize(DEFAULT_SIZE);
}

*
 * Destructor

HashTable::~HashTable() {
    // FIXME (3): Implement logic to free storage when class is destroyed
	nodes.erase(nodes.begin());
}

*
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash

unsigned int HashTable::hash(int key) {
    // FIXME (4): Implement logic to calculate a hash value
	return key  % DEFAULT_SIZE;
}

*
 * Insert a htBid
 *
 * @param htBid The htBid to insert

void HashTable::Insert(Bid htBid) {
    // FIXME (5): Implement logic to insert a htBid
	//atoi converts ASCII string to integer
	//c_str converts full string to string or chars
	unsigned key = hash(atoi(htBid.bidId.c_str()));


	//&(nodes.at(key)) returns address of nodes.at(key)
	Node* oldNode = &(nodes.at(key));

	//no node at address
	if (oldNode == nullptr) {
		Node* newNode = new Node(htBid, key);
		nodes.insert(nodes.begin() + key, (*newNode));
	} else {
		// node is found but empty
		if (oldNode->key == UINT_MAX) {
			oldNode->key = key;
			oldNode->htBid = htBid;
			oldNode->next = nullptr;
		} else{
			// find the next open node
			while (oldNode->next != nullptr) {
				oldNode = oldNode->next;
			}
			oldNode->next = new Node(htBid, key);
		}
	}
}

*
 * Print all bids

void HashTable::PrintAll() {
    // FIXME (6): Implement logic to print all bids

		//cout << "Test print";

		// declares node pointer printNode
		Node* printNode;

		// for loop to iterate through nodes vector
		for(unsigned int i = 0; i < DEFAULT_SIZE; i++){
			printNode = &(nodes.at(i));

			if (printNode->key != UINT_MAX){
				cout << printNode->htBid.bidId << ": " << printNode->htBid.title << " | "
					 << printNode->htBid.amount << " | " << printNode->htBid.fund << endl;


			// while loop to iterate through each bucket
			while (printNode->next != nullptr) {
				printNode = printNode->next;
				cout << printNode->htBid.bidId << ": " << printNode->htBid.title << " | "
					 << printNode->htBid.amount << " | " << printNode->htBid.fund << endl;

			}
			}
		}
}

*
 * Remove a htBid
 *
 * @param bidId The htBid id to search for

void HashTable::Remove(string bidId) {
    // FIXME (7): Implement logic to remove a htBid
	//unsigned key = hash(atoi(bidId.c_str()));
	//nodes.erase(nodes.begin() + key);
	Bid htBid;
	unsigned key = hash(atoi(bidId.c_str()));

	    Node* node = &(nodes.at(key));
	    Node* tempNode = node->next;
	    Node* sucNode = tempNode->next;

	    if (node == nullptr || node->key == UINT_MAX){
	    	return;
	    }

	    if (node != nullptr && node->key != UINT_MAX && node->htBid.bidId.compare(bidId) == 0) {
	    	nodes.erase(nodes.begin() + key);
	    	return;
	    }

	    while(node != nullptr) {
	    	if (tempNode->key != UINT_MAX && tempNode->htBid.bidId.compare(bidId) == 0) {

	    		node->next = sucNode;
	    	}
	    	node = node->next;
	    	tempNode = node->next;
	    	sucNode = tempNode->next;
	    }

	    return;

}

*
 * Search for the specified bidId
 *
 * @param bidId The htBid id to search for

Bid HashTable::Search(string bidId) {
    Bid htBid;

    // FIXME (8): Implement logic to search for and return a htBid
    unsigned key = hash(atoi(bidId.c_str()));

    Node* node = &(nodes.at(key));

    if (node == nullptr || node->key == UINT_MAX){
    	return htBid;
    }

    if (node != nullptr && node->key != UINT_MAX && node->htBid.bidId.compare(bidId) == 0) {
    	return node->htBid;
    }

    while(node != nullptr) {
    	if (node->key != UINT_MAX && node->htBid.bidId.compare(bidId) == 0) {
    		return node->htBid;
    	}
    	node = node->next;
    }


    return htBid;
}

//============================================================================
// Static methods used for testing
//============================================================================



*
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read

void htLoadBids(string csvPath, HashTable* hashTable) {
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
            Bid htBid;
            htBid.bidId = file[i][1];
            htBid.title = file[i][0];
            htBid.fund = file[i][8];
            htBid.amount = htStrToDouble(file[i][4], '$');

            //cout << "Item: " << htBid.title << ", Fund: " << htBid.fund << ", Amount: " << htBid.amount << endl;

            // push this htBid to the end
            hashTable->Insert(htBid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}



*
 * The one and only main() method

int htMain(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98109";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98109";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid htBid;

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
            htLoadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            htBid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!htBid.bidId.empty()) {
                htDisplayBid(htBid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
*/
