//g++ -c laberint.cpp -Wno-deprecated
#include "laberint.hpp"
#include <sstream>
#include <string>
using namespace std;

laberint::laberint(nat num_fil, nat num_col) throw(error){
	//COST N*M
	cambra c;
	for(nat i = 0; i < num_fil; ++i){
		for(nat j = 0; j < num_col; ++j){
			_mathlab[i][j] = c;
		}
	}
	_fila = num_fil;
	_columna = num_col;
}

laberint::laberint(std::istream & is) throw(error){
	int n;
	is>>n;
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
		//COST N*M
  *this = l;
}
laberint& laberint::operator=(const laberint & l) throw(error){
		//COST N*M
	for(nat i = 0; i < l._fila; ++i){
		for(nat j = 0; j < l._columna; ++j){
			_mathlab[i][j] = l._mathlab[i][j];
		}
	}
	_fila = l._fila;
	_columna = l._columna;
	return *this;
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
	if(pos.first >= _fila and pos.second >= _columna){
		cout<<"Error, posició no inclosa al laberint"<<endl;
		throw error(laberint::PosicioInexistent);
	}else return _mathlab[pos.first][pos.second];
}

void laberint::obre_porta(paret p, const posicio & pos) throw(error){
	if(pos.first < _fila and pos.second < _columna){
		if(p == paret::NORD){
			if(pos.first == 0){
				cout<<"ERROR, exterior norte"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].obre_porta(p);	//Abro norte
				_mathlab[pos.first-1][pos.second].obre_porta(paret::SUD);	//Abro sud de arriba
			}
		}else if(p == paret::EST){
			if(pos.second == _columna-1){
				cout<<"ERROR, exterior este"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].obre_porta(p);	//Abro norte
				_mathlab[pos.first][pos.second+1].obre_porta(paret::OEST);	//Abro oest de derecha
			}
		}else if(p == paret::SUD){
			if(pos.first == _fila-1){
				cout<<"ERROR, exterior sud"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].obre_porta(p); //Abro sud
				_mathlab[pos.first+1][pos.second].obre_porta(paret::NORD);	//Abro norte de abajo
			}
		}else if(p == paret::OEST){	//p == paret::OEST
			if(pos.second == 0){
				cout<<"ERROR, exterior oest"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].obre_porta(p);
				_mathlab[pos.first][pos.second-1].obre_porta(paret::EST);
			}
		}
	}else{
		cout<<"Error mida"<<endl;
		throw error(laberint::PosicioInexistent);
	}

}

void laberint::tanca_porta(paret p, const posicio & pos) throw(error){
	if(pos.first < _fila and pos.second < _columna){
		if(p == paret::NORD){
			if(pos.first == 0){
				cout<<"ERROR, exterior norte (cerrar)"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p);	//Cierro norte
				_mathlab[pos.first-1][pos.second].tanca_porta(paret::SUD);	//Cierro sud de arriba
			}
		}else if(p == paret::EST){
			if(pos.second == _columna-1){
				cout<<"ERROR, exterior este (cerrar)"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p);	//Cierro este
				_mathlab[pos.first][pos.second+1].tanca_porta(paret::OEST);	//Cierro oest de derecha
			}
		}else if(p == paret::SUD){
			if(pos.first == _fila-1){
				cout<<"ERROR, exterior sud (cerrar)"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p); //Cierro sud
				_mathlab[pos.first+1][pos.second].tanca_porta(paret::NORD);	//Cierro norte de abajo
			}
		}else if(p == paret::OEST){	//p == paret::OEST
			if(pos.second == 0){
				cout<<"ERROR, exterior oest (cerrar)"<<endl;
				throw error(PortaExterior);
			}
			else{
				_mathlab[pos.first][pos.second].tanca_porta(p);
				_mathlab[pos.first][pos.second-1].tanca_porta(paret::EST);
			}
		}
	}else{
		cout<<"Error mida (cerrar)"<<endl;
		throw error(laberint::PosicioInexistent);
	}
}

void laberint::print(std::ostream & os) const throw(){
	//COST N*M
	for(nat i = 0; i < _fila; ++i){
		for(nat j = 0; j < _columna; ++j){
			string s = "*";
			os << '*' <<
		}
		cout<<string<<endl;
	}
}
/*
***** nnn
* * * nnn
***** ccc
* * * ccc
***** ccc
* * *
*****
* * * sss
***** sss
*/


/*for(nat i = 0; i < _fila; ++i){
		for(nat j = 0; j < _columna; ++j){

			if(j > 0 and boolsud == 0){
				j--;
				boolsud = 1;
			}
			//os << '*' << (_mathlab[i][j].porta_oberta(paret("nord")) ? ' ' : '*') << '*' << endl;
			//os << (_mathlab[i][j].porta_oberta(paret("oest")) ? ' ' : '*') << ' ';
			//os << (_mathlab[i][j].porta_oberta(paret("est")) ? ' ' : '*') << endl;
			//os << '*' << (_mathlab[i][j].porta_oberta(paret("sud")) ? ' ' : '*') << '*';
			if(j == 0 and i == 0){	//NO preguntas norte oeste
				os << "**";	//NORTE
				os << '*';	//OESTE
				//PREGUNTO ESTE Y SUD
			os << ' '<< (_mathlab[i][j].porta_oberta(paret("est")) ? ' ' : '*');
			os << '*' << (_mathlab[i][j].porta_oberta(paret("sud")) ? ' ' : '*');
			}
			else if(i == 0){
				os << '*';	//OESTE
				//PreguntO ESTE Y SUD
			}
			else if(j == 0){ //Eres una cambra del techo
				os << '*';	//NORTE
				//PreguntO ESTE Y SUD
			}
			else if(j == _columna-1){
				os<< "***";	//NORTE
				os<<' '<<'*';
				os<< (_mathlab[i][j].porta_oberta(paret("sud")) ? ' ' : '*') << '*';
			}
			//else{	//ESTOY EN UN LUGAR NO ESPEDCIAL
			//	//PREGUNTO ESTE Y SUD
			//	os<<""
			//}
		
		
			if(j == 0)	os <<'*';	//paret
			os << ' '<< (_mathlab[i][j].porta_oberta(paret("est")) ? ' ' : '*');
		
			if(boolsud = 1){
				boolsud = 0;
				j++;
			}
		}
		cout<<string<<endl;
	}*/