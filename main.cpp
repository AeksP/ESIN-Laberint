//g++ -c .cpp
//g++ -o main.exe main.cpp -lesin -Wno-deprecated 
#include "cambra.hpp"
#include <sstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//legal matrices?
typedef vector <vector <string> >Matriu;

int main(){
	paret p("S");
	cout<<p<<endl;
	cambra c(true,true);
	//cout<<c<<endl;
	Matriu mathlab(4,vector<string>(12));
	int fila = 4;
	for(int i = 0; i < fila; i++){
		int j = 0;
		string s;
		getline(cin,s);
		istringstream ss(s);
		// fila0: mathlab[i] **********
		char caracter;
		while(ss >> caracter){
			mathlab[i][j]=caracter;
			++j;
		}
	}
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 12; j++) cout<<mathlab[i][j];
		cout<<endl;
	}
}

/*
g++ -c cambra.cpp -Wno-deprecated
g++ -c main.cpp -Wno-deprecated
g++ -o main.exe main.o cambra.o -lesin
*/