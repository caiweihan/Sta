#include <iostream>
#include <stack>

using std::cin;
using std::cout;
using std::endl;
using std::stack;

#define repeat(n) for(int ______________ = (n); ______________ > 0; --______________)

int main()
{
	stack<int> sta;
	repeat(1e4) {
		int op;
		cin >> op;
		
		if(op == 0) {
			int x;
			cin >> x;
			
			sta.push(x);
		}
		
		else if(op == 1)
			sta.pop();
		
		else
			cout << sta.top() << ' ';
	}
}
