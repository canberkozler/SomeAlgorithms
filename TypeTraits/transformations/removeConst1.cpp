template <typename T>
struct removeConst {
    using type = T;
};

template <typename T>
struct removeConst<const T> {
    using type = T;
};

template <typename T>
using removeConst_t = typename removeReference<T>::type;
