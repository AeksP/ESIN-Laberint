//g++ -c .cpp
//g++ -o main.exe main.cpp -lesin -Wno-deprecated 
#include "cambra.hpp"
#include "laberint.hpp"
#include <iostream>
using namespace std;

int main(){
	paret p("S");
	cout<<p<<endl;
	cambra c(true,true);
	//cout<<c<<endl;
	laberint l(7,7);
}

/*
g++ -c cambra.cpp -Wno-deprecated
g++ -c main.cpp -Wno-deprecated
g++ -o main.exe main.o cambra.o -lesin
*/