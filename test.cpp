#include <iostream>
using namespace std;

int main(){
	char a = 2;
	int b = 0;
	b = a << 3;
	cout<<endl;
	cout<<(int)a<<endl;
	cout<<b<<endl;;
	int array[32];
	for (int i = 0; i < 32; ++i)
	{
		array[32-i-1] = b%2;
		b/=2;
	}
	for (int i = 0; i < 32; ++i)
	{
		cout<<array[i];
	}
	
	return 0;
}