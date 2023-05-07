#pragma once

#include <iostream>
#include <random>
#include <string>
#include <map>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <vector>
#include <exception>
#include <iterator>
#include <array>

namespace Exception{
	class BoundaryException : public std::exception{
	public:
    	const char* what() const noexcept override
    	{
        	return "Error: Misrepresentation!";
    	}
	};

}

namespace mRand{
	std::mt19937& eng(){
		static std::mt19937 eng{std::random_device{}()};
		return eng;
	}

	void genNRandInteger(size_t N){
		std::uniform_int_distribution<int> dist;

		for (int i = 0; i < N; ++i)
			std::cout << dist(mRand::eng()) << '\n';
	}

	void genNRandInteger(size_t N, size_t beg, size_t end){
		if(beg>end){
			throw Exception::BoundaryException{};
		}
		std::uniform_int_distribution dist{beg, end};

		std::vector<int> ivec(N);
		std::generate(ivec.begin(), ivec.end(), [&]() { return dist(mRand::eng()); });

		/*
		std::vector<int> ivec;
		ivec.reserve(N);
		std::generate_n(back_inserter(ivec), N, [&](){ return dist(mRand::eng()); });
		*/

		for (auto i : ivec)
			std::cout << i << ' ';
	}

	void normalDistCalc(double mn, double stdev){
		// std::normal_distribution<> dist; // mu: 0 sigma: 1
		std::normal_distribution<> dist(mn, stdev);

		std::cout << "Mean   = " << dist.mean() << '\n';
		std::cout << "stddev = " << dist.stddev() << "\n\n";

		std::map<int, int> mymap;

		for (int k = 0; k < 1000; ++k)
		{
			mymap[lround(dist(mRand::eng()))]++;
		}

		for (const auto &[val, count] : mymap)
			std::cout << std::setw(2) << val << " " << std::string(count, '*') << '\n';
	}

	void genNRandFloating(size_t N){
		std::uniform_real_distribution dist{0., 1.};
		std::cout.precision(12);
		for (int i = 0; i < N; ++i)
			std::cout << dist(mRand::eng()) << "\n";
	}

	void ShuffleVector(std::vector<int>& ivec){
		while (true) {
			copy(ivec.begin(), ivec.end(), std::ostream_iterator<int>{std::cout, "  "});
			std::cout.put('\n');
			shuffle(ivec.begin(), ivec.end(), mRand::eng());
			(void)getchar();
			system("cls");
		}
	}

	void ShuffleString(std::string& s){
		while (true) {
			std::cout << s << '\n';
			shuffle(s.begin(), s.end(), mRand::eng());
			(void)getchar();
			system("cls");
		}
	}

	void rollDice(size_t N){
		std::default_random_engine loc_eng{std::random_device{}()};

		std::array<double, 6> w8s{10.0, 10.0, 10.0, 10.0, 10.0, 10.0};
		// std::array<double, 6> cheated_w8s{10.0, 10.0, 10.0, 10.0, 10.0, 14.0};

		std::discrete_distribution<size_t> dist{begin(w8s), end(w8s)};
		std::map<size_t, size_t> results;

		for (size_t i{}; i < N; ++i)
			++results[dist(loc_eng)];

		for (const auto &[die, count] : results)
			std::cout << "dice value " << die + 1 << " : " << count << '\n';
	}
}

namespace RandEngines{
	std::mt19937 eng1; // default seed
	std::mt19937 eng2(78254u);
	std::mt19937 eng3(std::random_device{}());
	std::mt19937 eng4(std::chrono::steady_clock::now().time_since_epoch().count());

	std::default_random_engine eng5{std::random_device{}()};
}






