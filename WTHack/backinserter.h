#pragma once

template<typename C>
class BackInsertIterator {
private:
	C& mc;
public:
	explicit BackInsertIterator(C& c) : mc(c){}
	BackInsertIterator& operator*() { return *this; }
	BackInsertIterator& operator++() { return *this; }
	BackInsertIterator& operator++(int) { return *this; }
	BackInsertIterator& operator=(const typename C::value_type& val) {
		mc.push_back(val);
		return *this;
	}
};

template<typename C>
inline BackInsertIterator<C> BackInserter(C& x) {
	return BackInsertIterator<C>(x);
}