template <typename T> struct removeConst { using type = T; };
template <typename T> struct removeConst<const T> { using type = T; };

template<typename T>
using removeConst_t = typename removeConst<T>::type;


int main()
{
	removeConst_t<const volatile int> x1{};
	removeConst_t<const int> x2{};
	removeConst_t<volatile int> x3{};
	removeConst_t<const int*> x4{};
	removeConst_t<int* const> x5{};
}