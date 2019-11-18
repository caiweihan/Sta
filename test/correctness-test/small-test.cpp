#include <iostream>
#include <memory>

using std::cout;
using std::endl;
using std::allocator;

template<typename T, typename Alloc = std::allocator<T>, int init_size = 512 / sizeof(T) >
class Sta
{
public:
	typedef T			value_type;
	typedef T&			reference;
	typedef T*			pointer;
	typedef const T&	const_reference;
	typedef size_t		size_type;
	
	Sta():
		p(nullptr),
		garbage(nullptr)
	{}
	
	~Sta()
	{
		if(garbage) {
			alloc.deallocate(garbage->begin, garbage->end - garbage->begin);
			delete garbage;
		}
		
		if(p) {
			Node *temp;
			for(T *i = p->begin; i <= it; i++)
				alloc.destroy(i);
			alloc.deallocate(p->begin, p->end - p->begin);
			temp = p;
			p = p->pre;
			delete temp;
			
			while(p) {
				for(T *i = p->begin; i != p->end; i++)
					alloc.destroy(i);
				alloc.deallocate(p->begin, p->end - p->begin);
				temp = p;
				p = p->pre;
				delete temp;
			}
		}
	}
	
	void push(T x)
	{
		++it;
		if(! p || it == p->end) {
			if(garbage) {
				it = garbage->begin;
				p = garbage;
				garbage = nullptr;
			}
			
			else {
				size_t x = p ? (p->end - p->begin) * 2 : init_size;
				
				it = alloc.allocate(x);
				p = new Node{ p, it, it + x };
			}
		}
		
		alloc.construct(it, x);
	}
	
	void pop()
	{
		alloc.destroy(it);
		
		if(it == p->begin) {
			if(garbage) {
				alloc.deallocate(garbage->begin, garbage->end - garbage->begin);
				delete garbage;
			}
			garbage = p;
			
			p = p->pre;
			if(p)
				it = p->end - 1;
		}
		
		else
			it--;
	}
	
	T& top()
	{ return *it; }
	
	bool empty()
	{ return ! p; }
	
	size_t size()
	{ return p ? p->end - p->begin + it - p->begin - 7 : 0; }
	
private:
	struct Node
	{
		Node *pre;
		T *begin;
		T *end;
	};
	
	T *it;
	Node *p;
	Node *garbage;
	
	Alloc alloc;
};

int main()
{
	Sta<int> sta;
	sta.push(1);
	cout << sta.top() << ' ' << sta.size() << endl;
	sta.push(9);
	sta.push(7);
	sta.push(4);
	sta.push(-1);
	cout << sta.top() << ' ' << sta.size() << endl;
	sta.pop();
	cout << sta.top() << ' ' << sta.size() << endl;
	sta.pop();
	sta.pop();
	cout << sta.top() << ' ' << sta.size() << endl;
}
