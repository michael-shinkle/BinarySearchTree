//============================================================================
// Name        : Project2.cpp
// Author      : Michael Shinkle
// Version     : 1.0
// Description : Load and display course list using binary search tree
//============================================================================

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// define a struct to hold course information
struct Course {
	string courseId;
	string courseName;
	vector<string> prereqs;
};

//forward declarations
void displayCourse(Course course);
void displayPrereqs(Course course);

// Internal structure for tree node
struct Node {
	Course course;
	Node *left;
	Node *right;

	//default constructor
	Node() {
		this->left = nullptr;
		this->right = nullptr;
	}

	//initialize with a course
	Node(Course course) :
			Node() {
		this->course = course;
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
	Node *root;

	void addNode(Node *node, Course course);
	void inOrder(Node *node);
	void validateInOrder(Node *node);

public:
	BinarySearchTree();
	void InOrder();
	void Insert(Course course);
	Course Search(string courseId);
	void ValidateCourses();
};

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
	//initialize housekeeping variables
	//root is equal to nullptr
	this->root = nullptr;
}

//Public accessor to inOrder function
void BinarySearchTree::InOrder() {
	// call inOrder function and pass root
	this->inOrder(this->root);
}

/*
 * Inserts course into binary search tree
 *
 * @param course Course to insert
 */
void BinarySearchTree::Insert(Course course) {
	// if root equal to null ptr root is equal to new node course
	if (this->root == nullptr) {
		this->root = new Node(course);
	}
	// else add Node root and course
	else {
		this->addNode(this->root, course);
	}
}

/*
 * Search for a course in binary search tree
 *
 * @param courseId CourseID to search for
 */
Course BinarySearchTree::Search(string courseId) {
	// set current node equal to root
	Node *currNode = this->root;
	// keep looping downwards matching courseID found or until bottom reached
	while (currNode != nullptr) {
		// if match found, return current course
		if (courseId.compare(currNode->course.courseId) == 0) {
			return currNode->course;
		}
		// if course is smaller than current node then traverse left
		else if (courseId.compare(currNode->course.courseId) < 0) {
			currNode = currNode->left;
		} else {
			// else larger so traverse right
			currNode = currNode->right;
		}
	}
	// not found so create empty course and return that
	Course course;
	return course;
}

//public accessor to validateInOrder function
void BinarySearchTree::ValidateCourses() {
	// call validateInOrder function and pass root
	validateInOrder(this->root);
}

/**
 * Add a course to some node (recursive)
 *
 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node *node, Course course) {
	// inserting a course into the tree
	// if node is larger then add to left
	if (node->course.courseId.compare(course.courseId) > 0) {
		// if no left node
		if (node->left == nullptr) {
			// this node becomes left
			node->left = new Node(course);
		}
		// else recurse down the left tree
		else {
			this->addNode(node->left, course);
		}
	}
	// else add to right
	else {
		// if no right node
		if (node->right == nullptr) {
			// this node becomes right
			node->right = new Node(course);
		}
		//else
		else {
			// recurse down the right tree
			this->addNode(node->right, course);
		}
	}
}

/*
 * Prints nodes in binary search tree alphanumerically (recursive)
 *
 * @param *node Node to begin descending down branches from
 */
void BinarySearchTree::inOrder(Node *node) {
	//if node is not equal to null ptr
	if (node != nullptr) {
		//InOrder left
		inOrder(node->left);
		//output courseID, courseName
		displayCourse(node->course);
		//InOder right
		inOrder(node->right);
	}
}

/*
 * Validates the data in binary search tree (recursively)
 *
 * @param node* Node to begin descending down branches from
 */
void BinarySearchTree::validateInOrder(Node *node) {
	// if node is not equal to null ptr
	if (node != nullptr) {
		//validate in order left
		validateInOrder(node->left);
		//if node has prereqs
		if (!node->course.prereqs.empty()) {
			//iterate through prereqs
			for (size_t i = 0; i < node->course.prereqs.size(); i++) {
				// search for course using prereq as key
				Course course = this->Search(node->course.prereqs[i]);
				// if not found, data is corrupted, exit program
				if (course.courseId.empty()) {
					cout << "Corrupted Data" << endl << "Exiting Program"
							<< endl;
					exit(1);
				}
			}
		}
		//validate in order right
		validateInOrder(node->right);
	}
}

/**
 * Display the course id and name to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayCourse(Course course) {
	cout << course.courseId << ", " << course.courseName << endl;
}

/**
 * Display the course prerequisites to the console (std::out)
 *
 * @param course struct containing the course info
 */
void displayPrereqs(Course course) {
	for (size_t i = 0; i < course.prereqs.size(); i++) {
		if (i < course.prereqs.size() - 1) {
			cout << course.prereqs[i] << ", ";
		} else {
			cout << course.prereqs[i] << endl;
		}
	}
}

/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @param *bst Container to insert courses into
 */
void loadCourses(string csvPath, BinarySearchTree *bst) {
	string line;

	cout << "Loading CSV file " << csvPath << endl;
	//open file using input stream
	ifstream courseFile(csvPath);
	if (courseFile.is_open()) {
		//iterate through lines in file
		while (getline(courseFile, line)) {
			//initialize variables
			Course course;
			vector<string> lineSplit;
			char delim = ',';
			int delimIndex = 0;
			// iterate through string looking for delimiter character
			for (size_t i = 0; i < line.length(); i++) {
				//if delimiter character found
				if (line[i] == delim) {
					//append substring to lineSplit without delimiter
					lineSplit.push_back(
							line.substr(delimIndex, i - delimIndex));
					//delimiter index is character after delimiter
					delimIndex = i + 1;
				}
				// reached end of line
				else if (i == (line.length() - 1)) {
					//append substring to lineSplit, + 1 ensures last char is copied
					lineSplit.push_back(
							line.substr(delimIndex, (i - delimIndex + 1)));
				}
			}

			//index 0 is courseId
			course.courseId = lineSplit[0];
			//index 1 is courseName
			course.courseName = lineSplit[1];
			//Remaining indices are prereqs
			course.prereqs = { lineSplit.begin() + 2, lineSplit.end() };
			//Add course to binary search tree
			bst->Insert(course);
		}
		//close file
		courseFile.close();
	} else {
		cout << "Unable to open file." << endl;
	}
}

int main() {
	// declare variables
	string csvPath = "courseList.csv";
	string courseKey;
	int choice = 0;

	// initialize binary search tree
	BinarySearchTree *bst;
	bst = new BinarySearchTree();

	Course course;

	cout << "Welcome to the course planner." << endl << endl;
	do {
		cout << "1. Load Data Structure." << endl;
		cout << "2. Print Course List." << endl;
		cout << "3. Print Course." << endl;
		cout << "9. Exit" << endl << endl;
		cout << "What would you like to do?";
		cin >> choice;

		switch (choice) {
		case 1:
			loadCourses(csvPath, bst);
			bst->ValidateCourses();
			cout << endl;
			break;
		case 2:
			cout << "Here is a sample schedule: " << endl << endl;
			bst->InOrder();
			cout << endl;
			break;
		case 3:
			cout << "What course do you want to know about?";
			cin >> courseKey;
			//converts to upper case if input is lower case
			transform(courseKey.begin(), courseKey.end(), courseKey.begin(),
					::toupper);

			course = bst->Search(courseKey);
			// if course found display id and name
			if (!course.courseId.empty()) {
				displayCourse(course);
				// if course has prereqs display them
				if (!course.prereqs.empty()) {
					cout << "Prerequisites: ";
					displayPrereqs(course);
				}
			}
			// else not found
			else {
				cout << endl << "Course ID " << courseKey << " not found."
						<< endl << endl;
			}
			cout << endl;
			break;
		case 9:
			cout << "Thank you for using the course planner!" << endl;
			exit(0);
		default:
			cout << choice << " is not a valid option" << endl << endl;
		}
	} while (choice != 9);

	return 0;
}
