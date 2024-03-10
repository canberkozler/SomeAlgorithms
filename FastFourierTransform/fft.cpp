#include <complex>
#include <iostream>
#include <iomanip>
#include <valarray>
#include <cmath>
#include <vector>

using Complex = std::complex<double>;
using CompArr = std::valarray<Complex>;

// recursive fft (in-place)
void fft(CompArr& x){
    if (x.size() < 2) 
        return;

    CompArr even = x[std::slice(0, x.size()/2, 2)];
    CompArr  odd = x[std::slice(1, x.size()/2, 2)];
 
    fft(even);
    fft(odd);

    for (size_t k{}; k < x.size()/2; ++k){
        Complex t = std::polar(1.0, 2 * M_PI * k / x.size()) * odd[k];
        x[k] = even[k] + t;
        x[k + x.size()/2] = even[k] - t;
    }
}

int main(){
    std::cout << "Enter no. of test cases: ";
	int t;
	std::cin>>t;
	while(t--){
        std::cout << "\nEnter n (for order of the polynomial): ";
		std::size_t n;
		std::cin >> n;
	    std::vector<Complex> test(n);
	    for (std::size_t i{}; i < n; ++i)
	    {
	    	double real, imag;
	    	std::cin>>real>>imag;
	    	test[i].real(real);
	    	test[i].imag(imag);
	    }

	    CompArr data(test.data(), n);

	    fft(data);
	 
	    for (std::size_t i{}; i < n; ++i){
	        std::cout << std::fixed << std::setprecision(6) << data[i].real() << " " << data[i].imag() << std::endl;
	    }
	}
}