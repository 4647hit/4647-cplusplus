
ainclude <stdio.h> once


template<class iterator,class ref, class ptr>
struct Reverse_iterator
{
	typedef Reverse_iterator<iterator,ref,ptr> self;
	iterator my;
	Reverse_iterator(iterator it)
		:my(it)
	{}
	self& operator++()
	{
		--my;
		return *this;
	}
	ref operator*()
	{
		iterator tmp = my;
		--tmp;
		return *tmp;
	}
	//self operator++(int)
	//{
	//	self tmp = my;
	//	++my;
	//	return tmp;
	//}
	//self& operator--()
	//{
	//	++my;
	//	return *this;
	//}
	//self operator--(int)
	//{
	//	self tmp = my;
	//	++my;
	//	return tmp;
	//}
	bool operator!=(iterator it)
	{
		return *it == *my;
	}
};
