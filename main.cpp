/*
David Chen
C++ 2018
Hash Table Program
+ Random Generator
*/

#include <iostream>
#include <cstring>
#include <iomanip>
#include <stdlib.h>
#include <time.h>
#include <fstream>

using namespace std;

//Student struct declaration
struct Student
{
  string firstname;
  string lastname;
  int studentid;
  float gpa;
  
  Student* next = NULL;
};

//function declaration
void add(Student*, Student** &, int &); //add to the hash table
void print(Student**, int);
void remove(int ID, Student** &table, int length);
int hashStudent(Student*, int); //this is the hash function that will return an index
string generateFirst(); //this will generate a random first name
string generateLast(); //this will generate a random last name

int main() {
	cout << "Welcome to Student List.  Type ADD to add students, PRINT to print student information, and DELETE to remove a student's information." << endl;
	cout << "Additionally, type GENERATE to randomly generate and add new students.  Finally, type QUIT to quit." << endl;

	srand(time(NULL));
	
	char invalid = 'y';
	char input[20];
	//for generate
	int ID = 101010;
	//start size
	int length = 100;
	Student** table = new Student*[length];
	//set all pointers to NULL
	for(int i = 0; i <= length; i++) {
		table[i] = NULL;
	}
	
	while (invalid == 'y'){
		cout << "Enter command: " << endl;
		cin >> input;
		if (!strcmp(input, "ADD")){
			Student* a = new Student;
			cout << "Enter first name: " << endl;
			cin >> a->firstname;
			cout << "Enter last name: " << endl;
			cin >> a->lastname;
			cout << "Enter student id (6 digits only): " << endl;
			cin >> a->studentid;
			cout << "Enter GPA: " << endl;
			cin >> a->gpa;
			add(a, table, length);
		}else if (!strcmp(input, "PRINT")){
			print(table, length);
		}else if (!strcmp(input, "DELETE")){
			int ID;
			// it is the user's responsibility to enter a correct id
			cout << "Enter Valid ID Number: " << endl;
			cin >> ID;
			remove(ID, table, length); 
		}else if (!strcmp(input, "GENERATE")) {
			int number = 0;
			int iterations = 0;
			cout << "# of students: " << endl;
			cin >> number;
			while(iterations < number) {
				Student* a = new Student;
				a->firstname = generateFirst();
				a->lastname = generateLast();
				a->studentid = ID;
				double decimal = (double)rand()/(RAND_MAX);
				int integer = rand() % 5;
				a->gpa = decimal + integer;
				add(a, table, length);
				ID++; 
				iterations++;
			}
			cout << "Success: " << number << " students generated." << endl;
		}else if (!strcmp(input, "QUIT")){
			break;
		}else {
			cout << "Invalid input.  Would you like to try again?  Press y for yes and n for no. ";
			cin >> invalid;
		}
	}
	return 0;
}

//add to the hash table
void add(Student* a, Student** &table, int & length) {
	int index = hashStudent(a, length);
	cout << "Hash: " << index << endl;
	cout << a->firstname << endl;
	
	if (table[index] == NULL) {
		table[index] = a;
	} else { //chain
		Student* head = table[index];
		int counter = 1;
		while (head->next != NULL) {
			head = head->next;
			counter++;
		}
		head->next = a;
		//overflow chain (need to resize table)
		if (counter >= 3) {
			cout << "Overflowed" << endl;
			Student** newTable = new Student*[length*2];
			int newlen = length*2;
			for(int i = 0; i < newlen; i++) {
				newTable[i] = NULL;
			}
			// cout << "SPOT 101 " << newTable[101] << endl;
			for(int i = 0; i < length; i++) {
				Student* head = table[i];
				while(head != NULL) {
					Student* next = head->next;
					head->next = NULL;
					add(head, newTable, newlen);
					head = next;
				}
			}
			
			table = newTable;
			length = newlen;
		}
	}
}

void print(Student** table, int length) {
	for(int i = 0; i < length; i++) {
		cout << i << endl;
		Student* head = table[i];
		while(head != NULL) {
			cout << head->lastname << ", " << head->firstname << " | " << head->studentid << " | " << setprecision(3) << head->gpa << endl;
			head = head->next;
		}
	}
}

void remove(int ID, Student** &table, int length) {
	int index = ID % length;
	Student* head = table[index];
	Student* temp = head;
	if (head->studentid == ID) {
		table[index] = head->next;
		delete head;
	} else {
		while(head->studentid != ID) {
			temp = head;
			head = head->next;
		}
		//there are two cases here (if head->next == NULL or != NULL)
		Student* todelete = head;
		temp->next = head->next;
		delete todelete;
	}
}


//this is the hash function that will return an index
int hashStudent(Student* a, int length) {
	//iterate through the string and add up the ASCII values
	// int total = 0;
	// for (string::iterator it = a->firstname.begin(); it != a->firstname.end(); it++) {
		// total += *it;
	// }
	// return (total % length);
	
	//hash based on ID
	return (a->studentid % length); //better hash function
	
}

//this will generate a random first name	
string generateFirst() {
	ifstream file;
	string fileName = "firstnames.txt";
	file.open(fileName);

	string array[50];
	for (int i = 0; i < 50; i++) {
		file >> array[i];
	}
	int integer = rand() % 50;
	return array[integer];
}

//this will generate a random last name	
string generateLast() {
	ifstream file;
	string fileName = "lastnames.txt";
	file.open(fileName);

	string array[50];
	for (int i = 0; i < 50; i++) {
		file >> array[i];
	}
	int integer = rand() % 50;
	return array[integer];
}	
