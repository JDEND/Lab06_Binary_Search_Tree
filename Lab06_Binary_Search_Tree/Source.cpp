#include<iostream>
#include<time.h>
#include "BST_ADT.h"
using std::cout;
using std::cin;
using std::endl;

class TestData {
public:
	void setKey(int newKey) {
		keyField = newKey;
	}

	int getKey() const {
		return keyField;
	} // Returns the key  

private:

	int keyField; // Key for the data item  
};

int main() {
	BSTree<TestData, int> testTree;
	TestData testData;           
	int inputKey;       

	srand(time(NULL));

	cout << "Inputting 7 random values" << endl;
	for (int i = 0; i < 7; i++) {
		inputKey = rand() %100 + 1;
		testData.setKey(inputKey);
		testTree.insert(testData);
	}
	
	testTree.showStructure();
	cout << endl;

	int temp;
	cout << "Enter the number you wish to find the keys greater than" << endl;
	cin >> temp;

	cout << "Greater Than: ";
	testTree.writeGreaterThan(temp);
	cout << endl;
	cout << "Preorder tree traversal: ";
	testTree.writePreorder();



	return 0;
}