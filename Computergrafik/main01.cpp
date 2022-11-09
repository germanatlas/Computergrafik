#include <iostream>
#include "functions01.h"

int main01() {
    int test_array[5] = { 1,2,3,4,5 };

    helloworld();
std:cout << sumup(test_array, 5) << endl;
    std::cout << sumup_input(test_array) << endl;

    std::cout << "You did it, everything is set up, geat job! :) ";
    return 0;
}