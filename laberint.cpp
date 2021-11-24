//g++ -c laberint.cpp -Wno-deprecated
#include "laberint.hpp"
#include <sstream>
#include <string>
using namespace std;

cambra _mathlab[1000][1000];	//??????????????????????????????

laberint::laberint(nat num_fil, nat num_col) throw(error){

}

laberint::laberint(std::istream & is) throw(error){
	/*string s;
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
	*/
}

laberint::laberint(const laberint & l) throw(error){
  
}
laberint& laberint::operator=(const laberint & l) throw(error){
return *this;	//solo es una prueba para compilarlo
}
laberint::~laberint() throw(){

}

nat laberint::num_files() const throw(){
	return _fila;
}
nat laberint::num_columnes() const throw(){
	return _columna;
}

cambra laberint::operator()(const posicio & pos) const throw(error){
	/*if(pos.first < _fila and pos.second < _columna){
		return _mathlab[pos.first][pos.second];
		//*this[pos.first][pos.second]; ?¿
	}else cout<<"Error, posició no inclosa al laberint"<<endl;
	//Falta un return
	*/
	
	if((pos.first >= _fila and pos.second >= _columna) or (pos.first < 0 and pos.second < 0)){
		cout<<"Error, posició no inclosa al laberint"<<endl;
	}else return _mathlab[pos.first][pos.second];
	//Falta un return 
}

void laberint::obre_porta(paret p, const posicio & pos) throw(error){
	if(pos.first < _fila and pos.second < _columna){
		if(p == paret::NORD){
			if(pos.first == 0)	cout<<"ERROR, exterior norte"<<endl;
			else{
				_mathlab[pos.first][pos.second].obre_porta(p);	//Abro norte
				_mathlab[pos.first-1][pos.second].obre_porta(paret::SUD);	//Abro sud de arriba
			}
		}else if(p == paret::EST){
			if(pos.second == _columna-1)	cout<<"ERROR, exterior este"<<endl;
			else{
				_mathlab[pos.first][pos.second].obre_porta(p);	//Abro norte
				_mathlab[pos.first][pos.second+1].obre_porta(paret::OEST);	//Abro oest de derecha
			}
		}else if(p == paret::SUD){
			if(pos.first == _fila-1)	cout<<"ERROR, exterior sud"<<endl;
			else{
				_mathlab[pos.first][pos.second].obre_porta(p); //Abro sud
				_mathlab[pos.first+1][pos.second].obre_porta(paret::NORD);	//Abro norte de abajo
			}
		}else{	//p == paret::OEST
			if(pos.second == 0)	cout<<"ERROR, exterior oest"<<endl;
			else{
				_mathlab[pos.first][pos.second].obre_porta(p);
				_mathlab[pos.first][pos.second-1].obre_porta(paret::EST);
			}
		}
	
	/*
		if(pos.second == 0 and p != paret::OEST){	
			mathlab[pos.first][0].obre_porta(p);	//El [0] es pos.second deducido por el if
		}	//no puedes usar mathlab[pos.first][0].obre_porta("OEST");
		else if(pos.second == _columna-1 and p != paret::EST){
			mathlab[pos.first][_columna-1].obre_porta(p);
		}
		else if(pos.first == 0 and p != paret::NORD){
			mathlab[0][pos.second].obre_porta(p);
		}
		else if(pos.first == _fila-1 and p != paret::SUD){
			mathlab[_fila-1][pos.second].obre_porta(p)
		}
		else{
			mathlab[pos.first][pos.second].obre_porta(p)
		}
	*/
	//Creo que lo no comentado está mejor que la idea comentada de aquí 
	}else	cout<<"Error mida"<<endl;

}

void laberint::tanca_porta(paret p, const posicio & pos) throw(error){
	if(pos.first < _fila and pos.second < _columna){
		if(p == paret::NORD){
			if(pos.first == 0)	cout<<"ERROR, exterior norte (cerrar)"<<endl;
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p);	//Cierro norte
				_mathlab[pos.first-1][pos.second].tanca_porta(paret::SUD);	//Cierro sud de arriba
			}
		}else if(p == paret::EST){
			if(pos.second == _columna-1)	cout<<"ERROR, exterior este (cerrar)"<<endl;
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p);	//Cierro este
				_mathlab[pos.first][pos.second+1].tanca_porta(paret::OEST);	//Cierro oest de derecha
			}
		}else if(p == paret::SUD){
			if(pos.first == _fila-1)	cout<<"ERROR, exterior sud"<<endl;
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p); //Cierro sud
				_mathlab[pos.first+1][pos.second].tanca_porta(paret::NORD);	//Cierro norte de abajo
			}
		}else{	//p == paret::OEST
			if(pos.second == 0)	cout<<"ERROR, exterior oest"<<endl;
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p);
				_mathlab[pos.first][pos.second-1].tanca_porta(paret::EST);
			}
		}
	}else	cout<<"Error mida"<<endl;
}

void laberint::print(std::ostream & os) const throw(){

  
}
