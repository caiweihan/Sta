#include <cstdlib>

using std::system;

#define repeat(n) for(int ______________ = (n); ______________ > 0; --______________)

int main()
{
	repeat(1000) {
		system("gen.exe > check_test.in");
		system("Sta.exe < check_test.in > diff1.out");
		system("stack.exe < check_test.in > diff2.out");
		
		if(system("fc diff1.out diff2.out"))
			return 0;
	}
}
