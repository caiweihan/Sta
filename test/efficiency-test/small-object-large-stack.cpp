#include <iostream>
#include <stack>
#include <algorithm>
#include <memory>
#include <chrono>

using std::cout;
using std::endl;
using std::allocator;
using std::stack;
using std::vector;
#define clock() std::chrono::high_resolution_clock::now()
#define castT(x) std::chrono::duration_cast<std::chrono::microseconds>(x).count()

#define repeat(n) for(int ______________ = (n); ______________ > 0; --______________)
#define loop(i, l, r) for(int i = (l), ________r = (r); i <= ________r; ++i)

template<typename T, typename Alloc = std::allocator<T> >
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
				size_t x = p ? (p->end - p->begin) * 2 : 8;
				
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
	repeat(10) {
		cout << "-----------------------------------\n";
		
		auto t = clock();
		stack<int> a;
		loop(i, 1, 1e7)
			a.push(i);
		cout << "stack  " << castT(clock() - t) << endl;
		
		t = clock();
		stack<int, vector<int> > b;
		loop(i, 1, 1e7)
			b.push(i);
		cout << "vector " << castT(clock() - t) << endl;
		
		t = clock();
		Sta<int> c;
		loop(i, 1, 1e7)
			c.push(i);
		cout << "Sta    " << castT(clock() - t) << endl;
	}
}
