#include <iostream>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>

#include "backinserter.h"
#include "ostreamIterator.h"
#include "summer.h"
#include "counter.h"

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

		std::cout<<"\n";
	}
	
	{// Summer
		std::cout <<"Sum of 3 and 2: " <<sum(3, 2) << "\n";
		std::cout <<"Sum of numbers(3.14159, 2.71828, 232.23, 11, 233.22): " << sum(3.14159, 2.71828, 232.23, 11, 233.22) << "\n";
	
		std::cout << "Sum of numbers(10.77, 23. ,22.24, 34.52, 76.35): " << summer(10.77, 23. ,22.24, 34.52, 76.35) << "\n";

		std::cout << "Sum of 0 to 42 is equals to " << sequential_number_summer<42>{}<< "\n";
	}

	{ // Counter
		Count<15>();
	}
}