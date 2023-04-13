template <typename T> struct removePointer { typedef T type; };
template <typename T> struct removePointer<T*> { typedef T type; };
template <typename T> struct removePointer<T* const> { typedef T type; };
template <typename T> struct removePointer<T* volatile> { typedef T type; };
template <typename T> struct removePointer<T* const volatile> { typedef T type; };

template <typename T>
using removePointer_t = typename removePointer<T>::type;