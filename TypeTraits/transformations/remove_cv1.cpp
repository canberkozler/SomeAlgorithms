template <typename T> struct removeCV { using type = T; };
template <typename T> struct removeCV<const T> { using type = T; };
template <typename T> struct removeCV<volatile T> { using type = T; };
template <typename T> struct removeCV<const volatile T> { typedef T type; };

template <typename T>
using removeCV_t = typename removeCV<T>::type;

int main()
{
	removeCV_t<const volatile int> x1{};
	removeCV_t<const int> x2{};
	removeCV_t<volatile int> x3{};
	removeCV_t<const int*> x4{};
	removeCV_t<const volatile int*> x5{};
	removeCV_t<int* const> x6{};
	removeCV_t<int* const volatile> x7{};
}