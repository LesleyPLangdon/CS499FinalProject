/*
 * Name			:	LinkedList.hpp
 * Author		:	Lesley Potts-Langdon (constructors, method stubs and some base code were supplied,
 * 						all method code and logic produced by author)
 * Start Date	:	April 14, 2020
 * Submitted	:	May 30, 2020 (phase one, all files accessible from CapstoneMain.cpp main() method)
 * Description	:	Class to create a Linked List with
 * 		methods for loading, adding, displaying, searching and removing.
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
	Bid Search();
	int Size();
};

/*
 * Default constructor
 */
LinkedList::LinkedList() {
	// FIXME (2): Initialize housekeeping variables
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
 * Remove a specified bid
 *
 * @param bidId The bid id to remove from the list
 */
void LinkedList::Remove() {
	// Implement remove logic
	string bidId;
	cout << "Which bid would you like to remove? (use 98109 for test purposes)"
			<< endl;
	cin >> bidId;
	if (head != nullptr) {
		//special case if head is the node to be removed
		if (head->bid.bidId.compare(bidId) == 0) { //compares id values, if they match it returns 0
			Node* tempNode = head->next; //assign node after one to be removed to a temp node
			delete head;
			head = tempNode;   //assign node following one removed to head
			size--;   //decrement size
		} else {
			Node* current = head;   //node pointer current points to head
			//loop through linked list and search for match
			while (current->next != nullptr) {
				//compare method will return 0 if values are equal
				if (current->next->bid.bidId.compare(bidId) == 0) {
					//points to node to be removed
					Node* tempNode = current->next;

					//make current node the one after the one to be removed
					current->next = tempNode->next;

					//delete selected node
					delete tempNode;
					size--;			//decrement size
					return;
				}
				current = current->next;
			}
		}
	}
}

/*
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid LinkedList::Search() {
	// Implement search logic
	string bidId;
	cout << "Enter Bid ID for search: (use 98109 for test purposes) " << endl;
	cin >> bidId;
	Node* current = head;

	//loop through linked list and search for match
	while (current != nullptr) {
		//compare method will return 0 if values are equal
		if (current->bid.bidId.compare(bidId) == 0) {
			return current->bid;
		}
		current = current->next;
	}
	Bid bid;
	return bid;
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

			cout << bid.bidId << ": " << bid.title << " | " << bid.fund << " | "
					<< bid.amount << endl;

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
		cout << "  5. Remove Bid" << endl;
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
			ticks = clock();

			bid = bidList.Search();

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

		case 5:
			bidList.Remove();

			break;
		}
	}

	cout << "Good bye." << endl;

	return 0;
}

#endif /* LINKEDLIST_HPP_ */
