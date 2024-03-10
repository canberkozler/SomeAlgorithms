#include<iostream>

int gcd(int a,int b)
{
	if(!b)
	 	return a;
	else
	 	return gcd(b,(a%b));
}

int main()
{
	std::cout << "Enter the two numbers to calculate gcd:\n";
	int a,b;
	std::cin >> a >> b;
	std::cout <<"Gcd(" << a << ", " << b << ") is "<< gcd(a,b);
}