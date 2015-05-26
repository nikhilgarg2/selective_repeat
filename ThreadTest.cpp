#include <iostream>
#include <pthread.h>
using namespace std;

void * DoSomething(void *ptr){
	cout<<"Hello"<<endl;
	pthread_exit((void *)"I quit");
}

int main(){
	pthread_t testThread;
	int a  = 5;
	void *status; 
	int rc = pthread_create(&testThread, NULL, DoSomething, NULL);
	cout<<"hi"<<endl;
	pthread_join(testThread, &status);
	cout<<((char*)status)<<endl;
	pthread_exit(NULL);
	return 0;
}