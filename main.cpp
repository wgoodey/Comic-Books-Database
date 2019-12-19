/*
 Whitney Goodey
 Assignment 5
 comicsCollection Dynamic
 Main source file for Comic Book Database
 Sources: None
 */

#include <iostream>
#include "comicsCollection.hpp"

using namespace std;

int main() {
	//declare variables
	char response = '\0';
	char save = '\0';
	
	//prompt for database file
	comicsCollection stuartsComics;
	
	//main menu
	while (response != 'q') {
		cout << "What would you like to do?" << endl;
		cout << "(S)earch for a comic, (A)dd a comic, (D)elete comic, ";
		cout << "(L)ist all comics, (T)otal inventory, or (Q)uit: ";
		cin.get(response);
		response = tolower(response);
		cin.ignore(256, '\n');
		cout << endl;
		
		switch(response) {
			case 's':
				stuartsComics.search();
				break;
				
			case 'a':
				stuartsComics.addData();
				break;
				
			case 'd':
				stuartsComics.deleteData();
				cout << endl;
				break;
				
			case 'l':
				stuartsComics.printHeader();
				stuartsComics.printAll();
				cout << endl;
				break;
				
			case 't':
				stuartsComics.total();
				cout << endl << endl;
				break;
				
			case 'q':
				//ask to save changes until user gives input 
				while (save != 'y' && save != 'n') {
					cout << "Would you like to save your changes (y/n)? ";
					cin.get(save);
					save = tolower(save);
					cin.ignore(256, '\n');
					if (save == 'y') {
						cout << "Saving changes...";
						stuartsComics.writeData();
						cout << "Exiting program." << endl << endl;
					}
					else if (save == 'n') {
						cout << "Exiting program." << endl << endl;
					}
					else
						cout << "\nInvalid input. Please make a selection." << endl;
				}
				break;
				
			default:
				cout << "Invalid input. Please make a selection." << endl;
				break;
		}
		
	}
	//exit program
	return 0;
}
