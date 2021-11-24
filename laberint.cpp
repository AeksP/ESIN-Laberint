#include "laberint.hpp"
#include <sstream>
#include <vector>
#include <string>

typedef vector<string> fila;
typedef vector<fila> matriu;

explicit laberint::laberint(nat num_fil=5, nat num_col=5) throw(error){

}

explicit laberint::laberint(std::istream & is) throw(error){
string s;
getline(is,s);  //Fila y columna
istringstream ss(s);

ss >> _fila;
ss >> _columna;

matriu mathlab;

for(int i = 0; i < _fila+1; i++){
    int j = 0;
    getline(is,s);
    istringstream ss(s);
    // fila0: mathlab[i] **********
    char caracter;
    while(ss >> caracter){
        mathlab[i][j].push_back(caracter);
        ++j;
    }
}

}

laberint::laberint(const laberint & l) throw(error){
  
}
laberint& laberint::operator=(const laberint & l) throw(error){

}
laberint::~laberint() throw(){

}

nat laberint::num_files() const throw(){

}
nat laberint::num_columnes() const throw(){

}

cambra laberint::operator()(const posicio & pos) const throw(error){

}

void laberint::obre_porta(paret p, const posicio & pos) throw(error){


}

void laberint::tanca_porta(paret p, const posicio & pos) throw(error){

}
void laberint::print(std::ostream & os) const throw(){

  
}