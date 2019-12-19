/*
 Whitney Goodey
 Assignment 5
 comicsCollection Linked List
 Implementation file for Comic Book Database
 Sources: None
 */

#include "comicsCollection.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

//default constructor
comicsCollection::comicsCollection() {
	count = 0;
	head = nullptr;
	tail = nullptr;
	current = nullptr;
	newNode = nullptr;
	while (count == 0) {
		cout << "\nPlease enter the name of the database file to load: ";
		cin.getline(fileName, STR_SIZE, '\n');
		count = loadData();
		//if not found, reprompt
		if (count == -1) {
			count = 0;
			cout << "Error loading comics. File not found." << endl << endl;
		}
	}
	cout << count << " records loaded." << endl << endl;
}

//destructor
comicsCollection::~comicsCollection() {
	//loop to deallocate memory
	comicData *temp;
	current = head;
	while (current != nullptr) {
		delete[] current->title;
		current->title = nullptr;
		delete[] current->author;
		current->author = nullptr;
		delete[] current->volume;
		current->volume = nullptr;
		delete[] current->publisher;
		current->publisher = nullptr;
		temp = current;
		current = current->next;
		delete temp;
	}
}

int comicsCollection::loadData() {
	//open file. return error if not open
	ifstream database;
	database.open(fileName);
	if (!database.is_open()) {
		return -1;
	}
	else {
		count = 0;
		char input[STR_SIZE];
		while (!database.eof()) {
			//create new struct for list
			newNode = new comicData;
			newNode->prev = nullptr;
			newNode->next = nullptr;
			
			//copy line to input
			//create new cstring of length equal to input + 1
			//copy input into member
			
			//title
			database.getline(input, STR_SIZE, ',');
			newNode->title = new char[strlen(input) + 1];
			strcpy(newNode->title, input);
			
			//author
			database.getline(input, STR_SIZE, ',');
			newNode->author = new char[strlen(input) + 1];
			strcpy(newNode->author, input);
			
			//volume
			database.getline(input, STR_SIZE, ',');
			newNode->volume = new char[strlen(input) + 1];
			strcpy(newNode->volume, input);
			
			//publisher
			database.getline(input, STR_SIZE, ',');
			newNode->publisher = new char[strlen(input) + 1];
			strcpy(newNode->publisher, input);
			
			//copy year, price, and copies into newNode
			database.getline(input, STR_SIZE, ',');
			newNode->year = atoi(input);
			database.getline(input, STR_SIZE, ',');
			newNode->price = atof(input);
			database.getline(input, STR_SIZE, '\n');
			newNode->copies = atoi(input);
			
			//increment counter and insert into sorted list
			insertNode();
			
			//if next line is empty, exit loop
			if (database.peek() == '\n') {
				break;
			}
		}
		database.close();
		return count;
	}
}

void comicsCollection::addData() {
	char input[STR_SIZE];
	
	//reset newNode
	newNode = new comicData;
	newNode->prev = nullptr;
	newNode->next = nullptr;
	newNode->year = '\0';
	newNode->price = '\0';
	newNode->copies = '\0';
	
	//copy line to input
	//create new cstring of length equal to input + 1
	//copy input into member
	
	//title
	cout << "What is the title of the comic? ";
	cin.getline(input, STR_SIZE);
	newNode->title = new char[strlen(input) + 1];
	strcpy(newNode->title, input);
	//author
	cout << "What is the author? ";
	cin.getline(input, STR_SIZE);
	newNode->author = new char[strlen(input) + 1];
	strcpy(newNode->author, input);
	//volume
	cout << "What is the volume number/name? ";
	cin.getline(input, STR_SIZE);
	newNode->volume = new char[strlen(input) + 1];
	strcpy(newNode->volume, input);
	//publisher
	cout << "Who is the publisher? ";
	cin.getline(input, STR_SIZE);
	newNode->publisher = new char[strlen(input) + 1];
	strcpy(newNode->publisher, input);
	
	//make sure input matches year type
	while (newNode->year == '\0') {
		cout << "What year was it published? ";
		cin >> newNode->year;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invalid input. Try again." << endl;
		}
	}
	//make sure input matches price type
	while (newNode->price == '\0') {
		cout << "What is the price? ";
		cin >> newNode->price;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invalid input. Try again." << endl;
		}
	}
	//make sure input matches copies type
	while (newNode->copies == '\0') {
		cout << "How many copies? ";
		cin >> newNode->copies;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(256, '\n');
			cout << "Invalid input. Try again." << endl;
		}
	}
	//clear input stream, insert node, confirm addition.
	cin.ignore(256, '\n');
	insertNode();
	cout <<  "\nSuccesfully added \"" << newNode->title << "\" to the database." << endl << endl;
}

void comicsCollection::insertNode() {
	//if list is empty set newNode as head and tail
	if (head == nullptr) {
		head = newNode;
		tail = newNode;
	}
	//if at least one item is in the list already
	else {
		//traverse list until new node's title is greater than an existing node
		current = head;
		while (current != nullptr && strcmp(newNode->title, current->title) > 0) {
			current = current->next;
		}
		//if new node is first in the list
		if (current == head) {
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
		else {
			//if new node falls somewhere in the middle of the list
			if (current != nullptr) {
				current->prev->next = newNode;
				newNode->prev = current->prev;
				newNode->next = current;
				current->prev = newNode;
			}
			//if new node is last in list
			else {
				tail->next = newNode;
				newNode->prev = tail;
				tail = newNode;
			}
		}
	}
	count++;
	current = nullptr;
}

void comicsCollection::writeData() {
	ofstream database;
	database.open(fileName);
	current = head;
	while (current != nullptr) {
		database << current->title << ',';
		database << current->author << ',';
		database << current->volume << ',';
		database << current->publisher << ',';
		database << current->year << ',';
		database << current->price << ',';
		database << current->copies << '\n';
		current = current->next;
	}
}

void comicsCollection::printHeader() {
	//print header
	for (int i = 0; i < DASHES; i++){
		cout << '-';
	}
	cout << endl;
	cout << left << setw(26) << "Title" << setw(20) << "Author" << setw(30) <<  "Volume" << setw(20) << "Publisher" << setw(6) << "Year" << setw(7) << " Price" << setw(6) << "Copies" << endl;
	for (int i = 0; i < DASHES; i++){
		cout << '-';
	}
	cout << endl;
}

void comicsCollection::print() {
	cout << left << fixed << setprecision(2);
	cout << setw(26) << current->title;
	cout << setw(20) << current->author;
	cout << setw(30) << current->volume;
	cout << setw(20) << current->publisher;
	cout << setw(6) << current->year;
	cout << right << setw(6) << current->price;
	cout << setw(5) << current->copies << endl;
}

void comicsCollection::printAll() {
	//print contents of comics
		current = head;
		while (current != nullptr) {
			print();
			current = current->next;
		}
}

void comicsCollection::search() {
	//variables
	char key[STR_SIZE];
	char response;
	int matches = 0;
	current = head;
	cout << "Search by (T)itle or (A)uthor? ";
	cin.get(response);
	response = tolower(response);
	cin.ignore(256, '\n');
	
	if (response == 't') {
		cout << "What is the title? ";
		cin.getline(key, STR_SIZE, '\n');
		//search title at current for key
		while (current != nullptr) {
			//if search substring (case insensitive) is found in title
			if (strcasestr(current->title, key) != NULL) {
				matches++;
				if (matches == 1) {
					printHeader();
				}
				print();
				current = current->next;
			}
			else {
				current = current->next;
			}
		}
	}
	else if (response == 'a') {
		cout << "Who is the author? ";
		cin.getline(key, STR_SIZE, '\n');
		//search author at current for key
		while (current != nullptr) {
			//if search substring (case insensitive) is found in title
			if (strcasestr(current->author, key) != NULL) {
				matches++;
				if (matches == 1) {
					printHeader();
				}
				print();
				current = current->next;
			}
			else {
				current = current->next;
			}
		}
	}
	else {
		cout << "Invalid input." << endl;
	}
	cout << endl;
	if (matches == 0) {
		cout << "No matches for \""<< key << "\" found in the database." << endl << endl;
	}
}

void comicsCollection::deleteData() {
	//variables
	char key[STR_SIZE];
	int num = '\0';
	bool found = false;
	current = head;
	
	cout << "Please enter a title to delete: ";
	cin.getline(key, STR_SIZE, '\n');
	while (!found && current != nullptr) {
		//if search term matches title
		if (strcmp(current->title, key) == 0) {
			found = true;
			break;
		}
		current = current->next;
	}
	
	
	
	
	if (found) {
		while (num == '\0') {
			//get input on how many to delete
			cout << "How many copies would you like to remove? ";
			cin >> num;
			//if type mismatch
			if (cin.fail()) {
				cin.clear();
				cin.ignore(256, '\n');
				cout << "Invalid input. Try again." << endl << endl;
			}
		}
		//clear instream
		cin.clear();
		cin.ignore(256, '\n');
		
		//subtract num from copies
		current->copies -= num;
		if (current->copies <= 0) {
			//if list has only one node
			if (current->prev == nullptr && current->next == nullptr) {
				head = nullptr;
				tail = nullptr;
			}
			//if node is first in list
			else if (current->prev == nullptr) {
				current->next->prev = nullptr;
				head = current->next;
			}
			//if node is last in list
			else if (current->next == nullptr) {
				current->prev->next = nullptr;
				tail = current->prev;
			}
			//if node is in the middle
			else {
				current->prev->next = current->next;
				current->next->prev = current->prev;
			}
			
			//delete current node
			delete[] current->title;
			delete[] current->author;
			delete[] current->volume;
			delete[] current->publisher;
			
			if (current != nullptr) {
				delete current;
				current = nullptr;
			}
			cout << "\"" << key <<"\" was successfully deleted." << endl;
		}
		else if (current->copies > 0) {
			cout << "There is/are " << current->copies << " copies of " << key << " in the database." << endl;
		}
	}
	else {
		cout << "No matches for \""<< key << "\" found in the database." << endl;
	}
}

void comicsCollection::total() {
	double total = 0;
	current = head;
	while (current != nullptr) {
		total += current->price * current->copies;
		current = current->next;
	}
	cout << "There are " << count << " comics." << endl;
	cout << "The total value of the inventory is: $" << fixed << setprecision(2) << total;
}
