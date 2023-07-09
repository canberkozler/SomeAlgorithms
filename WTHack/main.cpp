#include <iostream>
#include "backinserter.h"
#include <algorithm>
#include <vector>

int main()
{
	{
		int a[3] = { 3, 5, 7 };
		int i = 0;

		a[i] = i++;

		for (auto ival : a)
			std::cout << ival << " ";

		std::cout << "\n";
	}

	{
		int temp = 10;
		temp = ++temp; //ub  before C++17

		std::cout << "temp = " << temp << "\n";
	}

	// BackInserter
	{
		std::vector<int> ivec1(10, 4), ivec2;
		std::cout << "ivec2 size: " << ivec2.size() << "\n";
		std::copy(ivec1.begin(), ivec1.end(), BackInserter(ivec2));
		std::cout << "ivec2 size: " << ivec2.size() << "\n";
	}
}