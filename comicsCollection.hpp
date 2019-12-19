/*
 Whitney Goodey
 Assignment 5
 comicsCollection Linked List
 Header file for Comic Book Database
 Sources: None
*/

#ifndef comicsCollection_hpp
#define comicsCollection_hpp

const int STR_SIZE = 256;
const int DASHES = 115;

struct comicData {
	char *title;
	char *author;
	char *volume;
	char *publisher;
	int year;
	double price;
	int copies;
	comicData *next;
	comicData *prev;
};                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         

class comicsCollection {
private:
	int count;
	char fileName[STR_SIZE];
	comicData *head;
	comicData *tail;
	comicData *newNode;
	comicData *current;
	
public:
	int loadData();
	void addData();
	void insertNode();
	void writeData();
	void search();
	void deleteData();
	void print();
	void printAll();
	void printHeader();
	void total();
	comicsCollection();
	~comicsCollection();
};

#endif
