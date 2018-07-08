/*  main.cpp
 *
 *  Created on: Jul 6, 2018
 *      Author: Yeiniel*/

#include <iostream>
#include <vector>

using namespace std;

void MathLimited(int listValue, int middle, int value, int& limitedRight,
		int& limitedLeft) {
	if (listValue > value) {
		limitedRight = middle - 1;
	} else {
		limitedLeft = middle + 1;
	}
}

int BinarySearchFor(vector<int> list, int value) {
	for (int middle = 0, limitedLeft = 0, limitedRight = (int) list.size();
			limitedLeft <= limitedRight;) {

		middle = (limitedRight + limitedLeft) / 2;

		int listValue = list[middle];
		if (listValue == value) {
			return middle;
		}

		MathLimited(listValue, middle, value, limitedRight, limitedLeft);
	}
	return -1;
}
int BinarySearchRecursive(vector<int> list, int value, int limitedLeft,
		int limitedRight, int middle) {

	if (limitedLeft > limitedRight) {
		return -1;
	}

	middle = (limitedRight + limitedLeft) / 2;

	int listValue = list[middle];
	if (listValue == value) {
		return middle;
	}

	MathLimited(listValue, middle, value, limitedRight, limitedLeft);
	return BinarySearchRecursive(list, value, limitedLeft, limitedRight, middle);
}
int BinarySearchRecursive(vector<int> list, int value) {
	return BinarySearchRecursive(list, value, 0, (int) list.size(), 0);
}

// O(log n)
int ExponentialSearch(vector<int> list, int value) {
	if (value == 0) {
		return -1;
	}

	int bound = 1;
	int size = (int) list.size();
	while (bound < size && list[bound] < value) {
		bound *= 2;
	}

	return BinarySearchRecursive(list, value, bound / 2, min(bound, size), 0);
}

//O(log log n)
int InterpolationSearch(vector<int> list, int value) {

	int limitedLeft = 0;

	for (int limitedRigth = ((int) list.size() - 1), middle = 0, cont = 0;
			(list[limitedLeft] != value && cont <= limitedRigth); cont++) {

		middle = limitedLeft
				+ ((value - list[limitedLeft]) * (limitedRigth - limitedLeft))
						/ (list[limitedRigth] - list[limitedLeft]);

		if (list[middle] > value)
			limitedRigth = middle - 1;
		else {
			limitedLeft = list[middle] < value ? middle + 1 : middle;
		}
		cont++;
	}

	return list[limitedLeft] == value ? limitedLeft : -1;
}

//O(log n)
int TernarySearchRecursive(vector<int> list, int limitedLeft, int limitedRigth,
		int value) {

	if (limitedLeft > limitedRigth) {
		return -1;
	}

	int sizeSet = limitedRigth - limitedLeft;
	int tercio = limitedLeft + (sizeSet / 3);
	int dostercio = limitedLeft + (sizeSet * 2) / 3;

	if (list[tercio] == value) {
		return tercio;
	} else if (list[tercio] > value) {
		return TernarySearchRecursive(list, limitedLeft, tercio - 1, value);
	}

	if (list[dostercio] == value) {
		return dostercio;
	} else if (list[dostercio] < value) {
		return TernarySearchRecursive(list, dostercio + 1, limitedRigth, value);
	}

	return TernarySearchRecursive(list, tercio + 1, dostercio - 1, value);;
}
int TernarySearchFor(vector<int> list, int value) {

	for (int limitedLeft = 0, limitedRigth = (int) list.size();
			limitedLeft <= limitedRigth;) {

		int sizeSet = limitedRigth - limitedLeft;
		int tercio = limitedLeft + (sizeSet / 3);
		int dostercio = limitedLeft + (sizeSet * 2) / 3;

		if (list[tercio] == value) {
			return tercio;
		} else if (list[tercio] > value) {
			limitedRigth = tercio - 1;
		} else if (list[dostercio] == value) {
			return dostercio;
		} else if (list[dostercio] < value) {
			limitedLeft = dostercio + 1;
		}

		limitedLeft = tercio + 1;
		limitedRigth = dostercio - 1;
	}

	return -1;
}

int SearchLinealFor(vector<int> list, int value) {
	for (int i = 0; i < (int) list.size(); i++) {
		if (list[i] == value) {
			return i;
		}
		if (list[i] > value) {
			return -1;
		}
	}
	return -1;
}

int main() {

	vector<int> list = { 7, 7, 8, 15, 45, 50, 77, 78 };
	cout << "Position = " <<TernarySearchRecursive(list, 0, (int)list.size(), 15) << endl;

	return 0;
}
