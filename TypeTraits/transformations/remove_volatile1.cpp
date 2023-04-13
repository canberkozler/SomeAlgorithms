template <typename T> struct removeVolatile { using type = T; };
template <typename T> struct removeVolatile<volatile T> { using type = T; };

template< class T >
using removeVolatile_t = typename removeVolatile<T>::type;


int main()
{
	removeVolatile_t<int> x1{};
	removeVolatile_t<volatile int> x2{};
	removeVolatile_t<volatile int *> x3{};
	removeVolatile_t<int * volatile> x4{};
}