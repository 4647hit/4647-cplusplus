
 once
#include<assert.h>
#include"reverse.h"
using namespace std;

namespace List
{
	template<class T>
	struct ListNode
	{
		struct ListNode<T>* prv;
		struct ListNode<T>* next;
		T data;
		ListNode(const T& x = T())
			:prv(nullptr)
			,next(nullptr)
			,data(x)
		{}

	};
	template<class T, class Ref, class Prv>
	struct _list_iterator
	{
		typedef ListNode<T> Node;
		typedef _list_iterator<T, Ref , Prv> self;
		_list_iterator(Node* x)
			:_node(x)
		{}
		self operator++(int)
		{
			self v(*this);
			_node = _node->next;
			return v;
		}
		self& operator++()
		{
			_node = _node->next;
			return *this;
		}
		self& operator--()
		{
			_node = _node->prv;
			return *this;
		}
		self operator--(int)
		{
			self v(*this);
			_node = _node->prv;
			return v;
		}
		Ref operator*()
		{
			return _node->data;
		}
		Prv operator->()
		{
			return &(_node->data);
		}
		bool operator==(const self& s)
		{
			return s._node == _node;
		}
		bool operator!=(const self& s)
		{
			return !(s._node == _node);
		}
		Node* _node;
	};
	template<class T>
	class list
	{
	public:
		typedef ListNode<T> Node;
		typedef _list_iterator<T, T&, T*> iterator;
		typedef _list_iterator<T, const T&, const T*> const_iterator;

		typedef Reverse_iterator<iterator, T&, T*> reverse_iterator;
		typedef Reverse_iterator<const_iterator, const T&, const T*> const_reverse_iterator;


	public:
		list()
		{
			head = new Node();
			head->prv = head;
			head->next = head;
		}
		~list()
		{
			Node* cur = head->next;
			while (cur != head)
			{
				Node* phead = cur;
				cur = cur->next;
				delete phead;
			}
			delete head;
		}
		void swap(list& s)
		{
			std::swap(s.head, head);
		}
		void push_back(const T& x)
		{
			Node* phead = new Node(x);
			Node* tail = head->prv;
			tail->next = phead;
			phead->prv = tail;
			phead->next = head;
			head->prv = phead;
		}
		void pop_back()
		{
			assert(head->next != head);
			Node* del = head->prv;
			head->prv = del->prv;
			del->prv->next = head;
			delete del;
		}
		void push_front(const T& x)
		{
			Node* pphead = head->next;
			Node* phead = new Node(x);
			Node* tail = pphead->prv;
			tail->next = phead;
			phead->prv = tail;
			phead->next = pphead;
			pphead->prv = phead;
		}
		void pop_front()
		{
			assert(head->next != head);
			Node* phead = head->next->next;
			Node* del = phead->prv;
			phead->prv = del->prv;
			del->prv->next = phead;
			delete del;
		}
		iterator insert(iterator pos, const T& val)
		{
			iterator it = this->begin();
			while (it != pos)
			{
				it++;
			}
			Node* cur = it._node;
			Node* newnode = new Node(val);
			newnode->next = cur->next;
			newnode->prv = cur;
			cur->next->prv = newnode;
			cur->next = newnode;
			return newnode;
		}
		iterator erase(iterator pos)
		{
			assert(this->begin() != this->end());
			Node* prv = pos._node->prv;
			Node* next = pos._node->next;
			prv->next = next;
			next->prv = prv;
			delete pos._node;
			return next;
		}
		iterator begin()
		{
			return head->next;
		}
		iterator end()
		{
			return head;
		}
		reverse_iterator rbegin()
		{
			return reverse_iterator(end());
		}
		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}
		const_iterator cbegin() const
		{
			return head->next;
		}
		const_iterator cend() const
		{
			return head;
		}
		void print()
		{
			for (const auto& e : (*this))
			{
				cout << e << endl;
			}
		}
		T& front()
		{
			return head->next->data;
		}
		T& back()
		{
			return head->prv->data;
		}
		const T& front(int)
		{
			return head->next->data;
		}
		const T& back(int)
		{
			return head->prv->data;
		}
		size_t size()
		{
			size_t i = 0;
			Node* phead = head;
			while (phead->next != phead)
			{
				phead = phead->next;
				i++;
			}
			return i;
		}
		void clear()
		{
			Node* phead = head;
			while (phead->next != phead)
			{
				phead->data = T();
			}
			return;
		}
		bool empty()
		{
			return head->next == head;
		}
	private:
		Node* head;
	};
	void test1()
	{
		list<int> s;
		for (size_t i = 0; i < 4; i++)
		{
			s.push_back(i);
		}
		auto it = s.cbegin();
		while (it != s.cend())
		{
			cout << *it << " ";
			++it;
		}
		cout << endl;

	}

	void test2()
	{
		list<int> v;
		for (size_t i = 0; i < 4; i++)
		{
			v.push_back(i);
		}
		v.push_front(4000);
		auto it = v.cbegin();
		while (it != v.cend())
		{
			cout << *it << " ";
			++it;
		}
	}

	void test3()
	{
		list<int> v;
		for (size_t i = 0; i < 4; i++)
		{
			v.push_back(i);
		}
		v.push_front(4000);
		list<int> s;
		for (size_t i = 0; i < 4; i++)
		{
			s.push_back(i);
		}
		s.swap(v);
		s.insert(s.begin(), 555);
		s.print();
	}
	void test4()
	{
		list<int> v;
		list<int>::reverse_iterator rbegin = v.rbegin();
		cout << *rbegin << endl;
	}
}
