/*
 * CapstoneMain.cpp
 *
 *  Created on: Apr 11, 2020
 *      Author: Lesle
 */
#include <algorithm>
#include <iostream>
#include <time.h>

#include "BinarySearchTree.hpp"
#include "HashTable.hpp"
#include "LinkedList.hpp"
#include "Vector.hpp"
#include "Capstone.hpp"
using namespace std;

class CapstoneMain{


};
	int main(){
		char ans;
		cout << "Would you like to enter a new bid? (Y or N) " << endl;
		cin >> ans;
		if(ans == ('Y'|'y')){
			llMain();
		}
		else if(ans == ('N' | 'n')){
			int choice = 0;
			while (choice != 9) {
			cout << "Which field would you like to search by: " << endl;
			cout << "1. Id: " << endl;
			cout << "2. Title: " << endl;
			cout << "3. Fund: " << endl;
			cout << "4. Amount: " << endl;
			cout << "9. Exit System: " << endl;
			cout << "Enter choice: ";
			cin >> choice;

			switch (choice) {

			       case 1:
			    	   htMain();

			    	   break;
			       case 2:
			    	   vMain();


			    	   break;
			       case 3:
			    	   llMain();



			    	   break;
			       case 4:
			    	   bstMain();

					   break;


			}
			}
			cout << "Good bye." << endl;
		}
		else{
			cout << "That is not a valid entry, please try again: " << endl;
		}



	//bstMain();
	//htMain();
	//llMain();

	return 0;

}


