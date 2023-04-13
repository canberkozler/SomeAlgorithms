template <typename T>
struct typeIdentity {
	using type = T;
};

template <typename T>
struct removeConst : typeIdentity<T>{};

template<typename T>
struct removeConst<const T> : typeIdentity<T>{};

template <typename T>
using removeConst_t = typename removeConst<T>::type;