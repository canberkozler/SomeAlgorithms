#include <iostream>


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
}