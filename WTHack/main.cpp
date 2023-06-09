#include <iostream>
#include "backinserter.h"
#include <algorithm>
#include <vector>
#include "ostreamIterator.h"
#include <random>
#include <chrono>

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
		std::cout << "\nby Back Inserter.\n";
		std::cout << "ivec2 size: " << ivec2.size() << "\n";
		std::copy(ivec1.begin(), ivec1.end(), BackInserter(ivec2));
		std::cout << "ivec2 size: " << ivec2.size() << "\n";
	}

	// OstreamIterator
	{
		std::vector<int> ivec{ 123,233,5,1,2,344,22};
		std::cout << "\nby Ostream Iterator.\n";
		std::copy(ivec.begin(), ivec.end(), OstreamIterator<int>{std::cout, "-"});
		std::cout<<"\n\n";

		std::mt19937 eng{std::random_device{}()};

		std::generate_n(OstreamIterator<int>{std::cout}, 20, eng); // print 20 number randomly into standard output stream.
	}
}