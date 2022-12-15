// ClassScheduleBST.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <fstream>
#include "CSVparser.hpp"

using namespace std;

// define a structure to hold course information
struct Course {
	string courseNum;
	string courseName;
	vector<string> preReqs;

	Course() {}
};

// Internal structure for tree node
struct Node {
	Course course;
	Node* left;
	Node* right;

	Node() {
		left = nullptr;
		right = nullptr;
	}

	Node(Course aCourse) : Node() {
		this->course = aCourse;
	}
};

class CourseBST {

private:
	Node* root;

	void addNode(Node* node, Course course);
	void printSampleSchedule(Node* node);
	void printCourseInformation(Node* node, string courseNum);


public:
	CourseBST();
	virtual ~CourseBST();
	void DeleteRecursive(Node* node);
	void Insert(Course course);
	int NumPrerequisiteCourses(Course course);
	void PrintSampleSchedule();
	void PrintCourseInformation(string courseNum);

};

CourseBST::CourseBST() {
	root = nullptr;
}

CourseBST::~CourseBST() {
	DeleteRecursive(root);
}

void CourseBST::DeleteRecursive(Node* node) {
	if (node) {
		DeleteRecursive(node->left);
		DeleteRecursive(node->right);
		delete node;
	}
}

void CourseBST::Insert(Course course) {
	if (root == nullptr)
		root = new Node(course);
	else
		this->addNode(root, course);
}

int CourseBST::NumPrerequisiteCourses(Course course) {
	int count = 0;
	for (unsigned int i = 0; i < course.preReqs.size(); i++) {
		if (course.preReqs.at(i).length() > 0)
			count++;
	}
	return count;
}

void CourseBST::PrintSampleSchedule() {
	this->printSampleSchedule(root);
}

void CourseBST::PrintCourseInformation(string courseNum) {
	this->printCourseInformation(root, courseNum);
}

void CourseBST::addNode(Node* node, Course course) {

	// Current courseNum is less than the current node's courseNum
	if (node->course.courseNum.compare(course.courseNum) > 0) {
		if (node->left == nullptr)
			node->left = new Node(course);
		else
			this->addNode(node->left, course);
	}
	// Current courseNum is equal or greater than the current node's courseNum
	else {
		if (node->right == nullptr)
			node->right = new Node(course);
		else
			this->addNode(node->right, course);
	}
}

void CourseBST::printSampleSchedule(Node* node) {

	if (node != nullptr) {
		printSampleSchedule(node->left);
		cout << node->course.courseNum << ", " << node->course.courseName << endl;
		printSampleSchedule(node->right);
	}
	return;
}

void CourseBST::printCourseInformation(Node* curr, string courseNum) {

	// Traverse BST until bottom reached or matching courseNum found
	while (curr != nullptr) {

		// Passed courseNum matches the current courseNum
		if (curr->course.courseNum.compare(courseNum) == 0) {

			// Display course & get num prereqs
			cout << endl << curr->course.courseNum << ", " << curr->course.courseName << endl;
			unsigned int size = NumPrerequisiteCourses(curr->course);
			cout << "Prerequisite(s): ";

			// If prereqs exist, display each prereq with proper formatting
			unsigned int i = 0;
			for (i = 0; i < size; i++) {
				cout << curr->course.preReqs.at(i);
				if (i != size - 1)
					cout << ", ";
			}
			// If no prereqs, inform user and return to stop the search
			if (i == 0)
				cout << "No prerequisites required.";
			cout << endl;
			return;
		}

		// Passed courseNum is smaller than the current courseNum so traverse left
		else if (courseNum.compare(curr->course.courseNum) < 0)
			curr = curr->left;

		// Passed courseNum is larger than the current courseNum so traverse right
		else
			curr = curr->right;
	}
	// nullptr has been reached but course hasn't been found/ printed, so inform user
	cout << "Course " << courseNum << " not found." << endl;
}


bool loadCourses(string csvPath, CourseBST* BST) {
	try {
		ifstream courseFile(csvPath);

		if (courseFile.is_open()) {
			while (!courseFile.eof()) {

				// A vector will hold each csv that a course contains
				vector<string> courseInfo;
				string courseData;

				getline(courseFile, courseData);
				while (courseData.length() > 0) {

					// Get substring of each course data, add to vector & delete from str
					unsigned int comma = courseData.find(',');
					if (comma < 100) {  // Any data field is allowed 99 chars or less
						courseInfo.push_back(courseData.substr(0, comma));
						courseData.erase(0, comma + 1);
					}
					// Add the last course after the final comma
					else {
						courseInfo.push_back(courseData.substr(0, courseData.length()));
						courseData = "";
					}
				}

				// Load the separated values into a course, insert into BST & close file
				Course course;
				course.courseNum = courseInfo[0];
				course.courseName = courseInfo[1];

				for (unsigned int i = 2; i < courseInfo.size(); i++) {
					course.preReqs.push_back(courseInfo[i]);
				}
				BST->Insert(course);
			}
			courseFile.close();
			return true;
		}
	}
	catch (csv::Error& e) {
		cerr << e.what() << endl;
	}
	return false;
}
		

int main(int argc, char* argv[]) {

	// Process command line argument
	string csvPath, courseId;
	switch (argc) {
	case 2:
		csvPath = argv[1];
		break;
	case 3:
		csvPath = argv[1];
		courseId = argv[2];
		break;
	default:
		csvPath = "";
		break;
	}

	CourseBST* coursesBST = nullptr;
	cout << "\nWelcome to the course planner!\n" << endl;
	string choice = "0";
	int userChoice = choice[0] - '0';

	while (userChoice != 9) {

		cout << "   1. Load Data Structure" << endl;
		cout << "   2. Print Course List" << endl;
		cout << "   3. Print Course" << endl;
		cout << "   9. Exit" << endl;
		cout << "\nWhat would you like to do? ";
		cin >> choice;

		// Check if user choice is a double digit
		if (choice.length() == 1)
			userChoice = choice[0] - '0';
		else
			userChoice = 0;

		bool success;

		// Handle users choice from menu
		switch (userChoice) {

			// Instantiate BST, get file path name & load courses into BST
		case 1:

			if (coursesBST == nullptr)
				coursesBST = new CourseBST();
			if (csvPath.length() == 0) {
				cout << "Enter the file name that contains the course data: ";
				cin >> csvPath;
			}
			// Determine if the file was opened/ loaded successfully
			success = loadCourses(csvPath, coursesBST);
			if (success)
				cout << "Courses have been loaded.\n" << endl;
			else
				cout << "File not found.\n" << endl;
			csvPath = "";
			break;

			// Validate that a BST exists & print a sample schedule
		case 2:

			if (coursesBST != nullptr && success) {
				cout << "Here is a sample schedule:\n" << endl;
				coursesBST->PrintSampleSchedule();
				cout << endl;
			}
			else
				cout << "Load courses first - option 1\n" << endl;
			break;

			// Validate that a BST exists & search/ display course info
		case 3:

			if (coursesBST != nullptr && success) {
				if (courseId.length() == 0) {
					cout << "What course do you want to know about? ";
					cin >> courseId;
					for (auto& userChoice : courseId) userChoice = toupper(userChoice);
				}
				coursesBST->PrintCourseInformation(courseId);
				cout << endl;
			}
			else
				cout << "Load courses first - option 1\n" << endl;
			courseId = "";
			break;

			// User entered invalid data or exited the program
		default:

			if (userChoice != 9)
				cout << choice << " is not a valid option\n" << endl;
			break;
		}
	}
	cout << "\nThank you for using the course planner!" << endl;

	return 0;
}