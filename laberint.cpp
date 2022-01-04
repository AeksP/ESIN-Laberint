
#include "laberint.hpp"
#include <string>
using namespace std;

laberint::laberint(nat num_fil, nat num_col) throw(error){
	if(num_fil == 0 or num_col == 0) throw error(FilsColsIncorrecte);
	else{
		_puntero = new cambra*[num_fil];	//Array de cambras
		for(nat i = 0; i < num_fil; ++i){	//Matriz de cambras
			_puntero[i] = new cambra[num_col];
		}
		_fila = num_fil;
		_columna = num_col;
	}
}

laberint::laberint(std::istream & is) throw(error){
	nat fila;
	nat columna;

	is>>fila;
	is>>columna;

	_columna = columna;
	_fila = fila;

	_puntero = new cambra*[_fila];	//Array de cambras
	for(nat i = 0; i < _fila; ++i){	//Matriz de cambras
		_puntero[i] = new cambra[_columna];
	}

	string s;
	int contx = 0, conty = 0;
	getline(is,s);	//Hay que dejarlo, es el salto de linea de los numeros
	//cout<<"test"<<s<<endl;
	for( nat i = 0; i < (_fila*2); ++i){
		getline(is,s);
		//cout<<"testdentro"<<s<<endl;
		if(i != 0){	//No hace nada pq es la pared
			conty = 0;
			for( nat j = 0; j < (_columna*2)+1; ++j ){	//j = 1
				if(i%2 != 0){	// AHORA IMPAR, miro este/oeste
					if(j%2 == 0 and j != 0 and (j != (_columna*2)) ){	//Si no es paret oeste ni es cambra ni es paret este
						if(s[j] == ' '){
							obre_porta(paret::EST,posicio(contx,conty));	//Abro este y oeste
						}
						++conty;
					}
				}
				else{	// AHORA PAR
					if( j%2 != 0){	//Estamos en paret sud/norte
						if(s[j] == ' '){
							obre_porta(paret::SUD,posicio(contx,conty));	//Abro sud y norte
						}
						++conty;
					}
				}
			}
			if( i%2 == 0)	contx++;
		}
	}
	//cout<<"he acabado"<<endl;
}

laberint::laberint(const laberint & l) throw(error){
	_fila = l._fila;
	_columna = l._columna;

	_puntero = new cambra*[_fila];	//Array de cambras
	for(nat i = 0; i < _fila; ++i){	//Matriz de cambras
		_puntero[i] = new cambra[_columna];
	}

	for(nat i = 0; i < l._fila; ++i){
		for(nat j = 0; j < l._columna; ++j){
			_puntero[i][j] = l._puntero[i][j];
		}
	}
}
laberint& laberint::operator=(const laberint & l) throw(error){
		if(this != &l){
			laberint laux(l);
			cambra **paux = _puntero;
			_puntero = laux._puntero;
			laux._puntero = paux;	//Se borra el _puntero original
			
			_fila = laux._fila;
			_columna = laux._columna;
			//cout<<"a"<<endl;
		}
		return *this;
}
laberint::~laberint() throw(){
	if(_puntero != NULL){	//Por si acaso?
		for(nat i = 0; i < _fila; ++i){
			delete [] _puntero[i];
		}
		
		//cout<<"b"<<endl;
		//delete _puntero;
	}
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
	}else return _puntero[pos.first][pos.second];
}

void laberint::obre_porta(paret p, const posicio & pos) throw(error){
	if(pos.first < _fila and pos.second < _columna){
		if(p == paret::NORD){
			if(pos.first == 0){
				cout<<"ERROR, exterior norte"<<endl;
				throw error(PortaExterior);
			}
			else{
				_puntero[pos.first][pos.second].obre_porta(p);	//Abro norte
				_puntero[pos.first-1][pos.second].obre_porta(paret::SUD);	//Abro sud de arriba
			}
		}else if(p == paret::EST){
			if(pos.second == _columna-1){
				cout<<"ERROR, exterior este"<<endl;
				throw error(PortaExterior);
			}
			else{
				_puntero[pos.first][pos.second].obre_porta(p);	//Abro este
				_puntero[pos.first][pos.second+1].obre_porta(paret::OEST);	//Abro oest de derecha
			}
		}else if(p == paret::SUD){
			if(pos.first == _fila-1){
				cout<<"ERROR, exterior sud"<<endl;
				throw error(PortaExterior);
			}
			else{
				_puntero[pos.first][pos.second].obre_porta(p); //Abro sud
				_puntero[pos.first+1][pos.second].obre_porta(paret::NORD);	//Abro norte de abajo
			}
		}else if(p == paret::OEST){	//p == paret::OEST
			if(pos.second == 0){
				cout<<"ERROR, exterior oest"<<endl;
				throw error(PortaExterior);
			}
			else{
				_puntero[pos.first][pos.second].obre_porta(p);
				_puntero[pos.first][pos.second-1].obre_porta(paret::EST);
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
				_puntero[pos.first][pos.second].tanca_porta(p);	//Cierro norte
				_puntero[pos.first-1][pos.second].tanca_porta(paret::SUD);	//Cierro sud de arriba
			}
		}else if(p == paret::EST){
			if(pos.second == _columna-1){
				cout<<"ERROR, exterior este (cerrar)"<<endl;
				throw error(PortaExterior);
			}
			else{
				_puntero[pos.first][pos.second].tanca_porta(p);	//Cierro este
				_puntero[pos.first][pos.second+1].tanca_porta(paret::OEST);	//Cierro oest de derecha
			}
		}else if(p == paret::SUD){
			if(pos.first == _fila-1){
				cout<<"ERROR, exterior sud (cerrar)"<<endl;
				throw error(PortaExterior);
			}
			else{
				_puntero[pos.first][pos.second].tanca_porta(p); //Cierro sud
				_puntero[pos.first+1][pos.second].tanca_porta(paret::NORD);	//Cierro norte de abajo
			}
		}else if(p == paret::OEST){	//p == paret::OEST
			if(pos.second == 0){
				cout<<"ERROR, exterior oest (cerrar)"<<endl;
				throw error(PortaExterior);
			}
			else{
				_puntero[pos.first][pos.second].tanca_porta(p);
				_puntero[pos.first][pos.second-1].tanca_porta(paret::EST);
			}
		}
	}else{
		cout<<"Error mida (cerrar)"<<endl;
		throw error(laberint::PosicioInexistent);
	}
}

void laberint::print(std::ostream & os) const throw(){
	os<<_fila<<" "<<_columna<<endl;
	string s = "";
	string pared = "";
	for(nat i = 0; i < (_columna*2) +1; ++i){
		pared += '*';
	}
	os<<pared<<endl;

	for( nat i = 0; i < _fila; ++i ){
		s = "";
		for( nat j = 0; j < _columna; ++j ){
			if( j == 0 )	os << '*';	//PARED OESTE, siempre fija
			s += '*';	//Pared oeste y esquina de la linea de abajo
			os << ' ';
			s += (_puntero[i][j].porta_oberta(paret("sud")) ? ' ' : '*');
			if(j != _columna-1 )	os << (_puntero[i][j].porta_oberta(paret("est")) ? ' ' : '*');
			else{
				os << '*';
				s += '*';				
			}
		}
		os<<endl;
		if( i != _fila-1)	os<<s<<endl;
	}

	os<<pared<<endl;
}