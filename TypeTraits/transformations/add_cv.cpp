template <typename T> struct addCV { using type = const volatile T; };
template <typename T> struct addConst { using type = const T ; };
template <typename T> struct addVolatile{ using type = volatile T; };

template<typename T>
using addCV_t = typename addCV<T>::type;

template<typename T>
using addConst_t = typename addConst<T>::type;

template<typename T>
using addVolatile_t = typename addVolatile<T>::type;


int main()
{
	addCV_t<int> x1{};
	addCV_t<int *> x2{};
	addConst_t<int *> x3{};
	addConst_t<const int *> x4{};
	addVolatile_t<int *> x5{};
	addVolatile_t<const int *> x6{};
}