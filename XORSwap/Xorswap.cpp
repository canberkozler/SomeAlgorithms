#include <iostream>

void xorswap(int &x, int &y) {
	x ^= y,	y ^= x,	x ^= y;
}

int main(int argc, char const *argv[]) {
	int x = 10, y = 5;
	xorswap(x, y); //make sure parameters are not x reference to the same value 

	std::cout << "x: " << x << " y: " << y << "\n";
}