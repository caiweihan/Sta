#include <iostream>
#include <stack>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::endl;
using std::rand;
using std::srand;
using std::time;

#define repeat(n) for(int ______________ = (n); ______________ > 0; --______________)

int main()
{
	srand(time(nullptr));
	
	int size = 0;
	repeat(1e4) {
		switch(rand() % 3) {
		case 0:
			cout << "0 " << rand() << endl;
			size++;
			break;
			
		case 1:
			if(size > 0) {
				cout << "1\n";
				size--;
			}
			break;
			
		case 2:
			if(size > 0)
				cout << "2\n";
			break;
		}
	}
}
