/*
 * Name			:	LinkedList.hpp
 * Author		:	Lesley Potts-Langdon (constructors, method stubs and some base code were supplied,
 * 						all method code and logic produced by author)
 * Start Date	:	April 14, 2020
 * Submitted	:	May 30, 2020 (phase one, all files accessible from CapstoneMain.cpp main() method)
 * Description	:	Class to create a Linked List with
 * 		methods for loading, adding, displaying, searching and removing.
 * 		Will search by fund but can only remove by BidID
 */

#ifndef LINKEDLIST_HPP_
#define LINKEDLIST_HPP_

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"
#include "Capstone.hpp"
using namespace std;

//============================================================================
// Linked-List class definition
//============================================================================

/*
 * Define a class containing data members and methods to
 * implement a linked-list.
 */
class LinkedList {

private:
	// Internal structure for list entries, housekeeping variables

	struct Node {
		Bid bid; //declare instance of Bid struct
		Node* next; //Node pointer to variable next

		//default constructor for struct Node
		Node() {
			next = nullptr; //sets next pointer to null important for finding end
		}
		//constructor to initialize a node with a bid
		Node(Bid aBid) {
			bid = aBid;
			next = nullptr;
		}

	};
	Node* head;
	Node* tail;
	int size = 0;

public:
	LinkedList();
	virtual ~LinkedList();
	void Append(Bid bid);
	void Prepend(Bid bid);
	void PrintList();
	void Remove();
	void Search();
	int Size();

};

/*
 * Default constructor
 */
LinkedList::LinkedList() {
	// Initialize housekeeping variables
	head = nullptr;
	tail = nullptr;
}

/*
 * Destructor
 */
LinkedList::~LinkedList() {
}

/*
 * Append a new bid to the end of the list
 */
void LinkedList::Append(Bid bid) {
	// Implement append logic
	Node* node = new Node(bid); //new node pass bid

	if (head == nullptr) {
		head = node;
		//tail = node;
	} else {
		if (tail != nullptr) {
			tail->next = node;
		}
	}
	//new node is always the tail
	tail = node;
	size++;

}

/*
 * Prepend a new bid to the start of the list
 */
void LinkedList::Prepend(Bid bid) {
	// Implement prepend logic
	Node* node = new Node(bid); //new node pass bid

	if (head != nullptr) {
		node->next = head;
	}

	head = node;
	size++; //increment size
}

/*
 * Simple output of all bids in the list
 */
void LinkedList::PrintList() {
	// Implement print logic
	Node* current = head; //set current to the head node

	//loop through linked list and print info from each node
	while (current != nullptr) {
		cout << current->bid.bidId << ": " << current->bid.title << " | "
				<< current->bid.amount << " | " << current->bid.fund << endl;
		current = current->next;
	}
}



/*
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
void LinkedList::Search() {
	// Implement search logic

	LinkedList searchResults;
	Node* current = head;
	string srchFund;
	cout << "Enter fund for search: (use general fund for test purposes) " << endl;
	cin.ignore();
	getline(cin, srchFund);

	//loop through linked list and search for match
	while (current != nullptr) {
		//compare method will return 0 if values are equal

		if (current->bid.fund.compare(srchFund) == 0) {
			searchResults.Append(current->bid);

		}
		current = current->next;
	}


	searchResults.PrintList();
}

/*
 * Returns the current size (number of elements) in the list
 */
int LinkedList::Size() {
	return size;
}

//============================================================================
// Static methods used for testing
//============================================================================

/*
 * Load a CSV file containing bids into a LinkedList
 *
 * @return a LinkedList containing all the bids read
 */
void llLoadBids(LinkedList *list) {
	string csvPath;
	cout
			<< "What file would you like to load: (use eBid_Monthly_Sales_Dec_2016.csv for test purposes) "
			<< endl;
	cin >> csvPath;
	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser
	csv::Parser file = csv::Parser(csvPath);

	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {

			// initialize a bid using data from current row (i)
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');


			// add this bid to the end
			list->Append(bid);
		}
	} catch (csv::Error &e) {
		std::cerr << e.what() << std::endl;
	}
}

/*
 * Linked List main method.  Actual main() method directs here when the user
 *       selects to search by fund.
 *
 *
 */
int llMain() {

	clock_t ticks;

	LinkedList bidList;

	Bid bid;

	int choice = 0;
	while (choice != 9) {
		cout << "Menu:" << endl;
		cout << "  1. Enter a Bid" << endl;
		cout << "  2. Load Bids" << endl;
		cout << "  3. Display All Bids" << endl;
		cout << "  4. Find Bid" << endl;
		cout << "  9. Exit" << endl;
		cout << "Enter choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			bid = getBid();
			bidList.Append(bid);
			displayBid(bid);

			break;

		case 2:
			ticks = clock();

			llLoadBids(&bidList);

			cout << bidList.Size() << " bids read" << endl;

			ticks = clock() - ticks; // current clock ticks minus starting clock ticks
			cout << "time: " << ticks << " milliseconds" << endl;
			cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds"
					<< endl;

			break;

		case 3:
			bidList.PrintList();

			break;

		case 4:



			bidList.Search();



			break;


		}
	}

	cout << "Good bye." << endl;

	return 0;
}

#endif /* LINKEDLIST_HPP_ */
