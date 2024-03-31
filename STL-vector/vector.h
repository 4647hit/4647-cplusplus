#pragma once
namespace Vector
{
	template<class T>
	class vector
	{
	public:
		typedef T* iterator;
		typedef const T* const_iterator;
		vector()
		{
		}
		vector(const vector<T>& s)
		{
			_start = new T[s._endofstorage - s._start];
			_finish = _start + (s.size());
			_endofstorage = _start + (s._endofstorage - s._start);
			for (size_t i = 0; i < s.size(); i++)
			{
				_start[i] = s._start[i];
			}
		}
		void reserve(size_t n) // 存在迭代器失效问题
		{
			size_t len = capacity();
			size_t count = size();
			if (n > len)
			{
				iterator it = new T[n];
				if (_start == nullptr)
				{
					_start = it;
				}
				else
				{
					iterator cp = it;
					//不要用memcpy 会出现浅拷贝， T为string时
					for (size_t i = 0; i < size(); i++)
					{
						*it = _start[i];
						it++;
					}
					delete[] _start;
					_start = cp;
				}
				_endofstorage = _start + n;
				_finish = _start + count;
			}
		}
		void push_back(const T& val)
		{
			if (capacity() == 0)
			{
				reserve(4);
			}
			if (_finish == _endofstorage)
			{
				reserve(size() + 1);
			}
			*_finish = val;
			_finish++;
		}

		iterator insert(iterator pos, const T& val)
		{
			assert(pos < end() && pos >= begin());
			size_t len = pos - _start;
			if (_finish == _endofstorage)
			{
				reserve(size() * 2);
			}
			pos = _start + len;
			iterator it = _finish;
			_finish++;
			while (it != pos)
			{
				*it = *(it - 1);
				it--;
			}
			*pos = val;
			return pos + 1;
		}
		iterator insert(iterator pos, iterator Begin, iterator End)  //插入后，pos可能会造成外部的迭代器失效
		{
			assert(pos < end() && pos >= begin());
			size_t len = pos - _start;
			size_t n = End - Begin;
			if (n + _finish >= _endofstorage)
			{
				reserve(n + size());
			}
			pos = _start + len;
			iterator newend = n + size() + _start - 1;
			iterator newfinish = end() - 1;
			while (newend != _finish - 1)
			{
				*newend = (*newfinish);
				newend--, newfinish--;
			}
			while (Begin != End)
			{
				*pos = *Begin;
				Begin++;
				pos++;
			}
			_finish = n + size() + _start;
			return pos + 1;
		}

		iterator erase(iterator pos)
		{
			assert(pos < end() && pos >= begin());
			iterator it = pos;
			while (pos < end() - 1)
			{
				*pos = *(pos + 1);
				 pos++;
			}
			_finish--;
			return pos + 1;
		}
		void swap(vector<T>& s)
		{
			std::swap(_endofstorage, s._endofstorage);
			std::swap(_start, s._start);
			std::swap(_finish, s, _finish);
		}
		void pop_back()
		{
			assert(size() > 0);
			_finish -= 1;
		}
		T& operator[](size_t i)
		{
			assert(i >= 0 && i < size());
			return _start[i];
		}
		void clear()
		{
			size_t n = size();
			_finish -= n;
		}
		T& front()
		{
			assert(size() > 0);
			return _start[0];
		}
		iterator begin()
		{
			return _start;
		}
		iterator end()
		{
			return _finish;
		}
		const_iterator begin() const
		{
			return _start;
		}
		const_iterator end() const
		{
			return _finish;
		}
		size_t size() const
		{
			return (_finish - _start);
		}
		size_t capacity() const
		{
			return (_endofstorage - _start);
		}
		~vector()
		{
			delete[] _start;
			_start = nullptr;
			_finish = nullptr;
			_endofstorage = nullptr;
		}


	private:
		iterator _start = nullptr;
		iterator _finish = nullptr;// 左闭右开
		iterator _endofstorage = nullptr;
	};
	template<class T>
	ostream& operator<<(ostream& cout, const vector<T> & s)
	{
		for (auto e : s)
		{
			cout << e << " ";
		}
		cout << endl;
		return cout;
	}
	void test1()
	{
		vector<int> cmp;
		cmp.reserve(10);
		for (size_t i = 0; i < 9; i++)
		{
			cmp.push_back(i);
		}

		cout << cmp;
		cout << endl;
		cmp.pop_back();
		cout << cmp;
		cout << cmp.size() << endl;
		cmp.clear();
	}


	void test2()
	{
		vector<int> c;
		for (size_t i = 0; i < 8; i++)
		{
			c.push_back(i);
		}
		cout << c;
		c.insert(c.begin(), 100);
		vector<int> v;
		v.push_back(1);
		v.push_back(2);
		v.insert(v.begin() + 1, c.begin(), c.end());//存在问题
		cout << v;
		cout << c;
	}


	void test3()
	{
		vector<string> s;
		s.push_back("healloc");
		vector<string> m(s);
		m[0].pop_back();
		cout << m;
	}

	void test4()
	{
		vector<int> s;
		for (size_t i = 0; i < 9; i++)
		{
			s.push_back(i);
		}
		cout << s;
		s.erase(s.begin() + 4);
		cout << s << endl;
	}
}
