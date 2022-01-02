//g++ -c .cpp
//g++ -o main.exe main.cpp -lesin -Wno-deprecated 
#include <iostream>
#include "cambra.hpp"
#include "laberint.hpp"
#include "particio.hpp"
using namespace std;

ostream & operator<<(std::ostream & os, const laberint & l) {
  l.print(os);
  return os;
}

// llegeix un laberint
istream & operator>>(std::istream & is, laberint & l) {
	//cout<<"buwenas tardes"<<endl;
  l = laberint(is);
  return is;
}

int main(){
	laberint l(cin);
	cout<<l;
  
}

/*
g++ -c cambra.cpp -Wno-deprecated
g++ -c laberint.cpp -Wno-deprecated
g++ -c main.cpp -Wno-deprecated
g++ -o main.exe main.o cambra.o laberint.o -lesin
*/