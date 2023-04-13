template <typename T > struct removeReference     {using type = T;};
template <typename T > struct removeReference<T&> {using type = T;};
template <typename T > struct removeReference<T&&>{using type = T;};

template <typename T>
using removeReference_t = typename removeReference<T>::type;

int main()
{
	removeReference_t<int&> x{ 1 }; 
	removeReference_t<int&&> y{ 1 };
}