//g++ -c .cpp
//g++ -o main.exe main.cpp -lesin -Wno-deprecated 
#include <iostream>
#include "cambra.hpp"
#include "laberint.hpp"
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
	//paret p("S");
	//cout<<p<<endl;
	//cambra c(true,true);
	//cout<<c<<endl;
	laberint l(cin);
	//laberint l;
	/*posicio lol;
	lol.first = 0;
	lol.second = 0;
	l.obre_porta(p,lol);*/
	//cout<<l;
	//cout<<"separacion"<<endl;
	//posicio ded;
	//ded.first = 0;
	//ded.second = 1;
	//posicio ded2;
	//ded.first = 0;
	//ded.second = 2;
	//l.obre_porta(paret::EST,ded);
	//l.obre_porta(paret::OEST,ded2);
	cout<<l;

	//laberint l2(5,5);
	//cin>>l;
	//cout<<"cout"<<endl;
	//cout<<l;
}

/*
g++ -c cambra.cpp -Wno-deprecated
g++ -c laberint.cpp -Wno-deprecated
g++ -c main.cpp -Wno-deprecated
g++ -o main.exe main.o cambra.o laberint.o -lesin
*/