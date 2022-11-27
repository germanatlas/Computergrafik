#pragma once
#include <iostream>
using namespace std;

//insert helloworld here
void helloworld() {
	cout << "Hello World!" << endl;
}

//insert sumup here
int sumup(int* arr, int length) {

	int sum = 0;

	for (int i = 0; i < length; i++) {

		sum += *(arr + i);

	}

	return sum;

}

//insert sumup_input here
int sumup_input(int* arr) {

	int length = -1,
		sum = 0;
	while (length < 0) {

		cout << "Length of the array\t> ";
		cin >> length;

	}

	for (int i = 0; i < length; i++) {
		sum += *(arr + i);
	}

	return sum;

}