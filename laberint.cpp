//g++ -c laberint.cpp -Wno-deprecated
#include "laberint.hpp"
//#include <sstream>
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
	//COST N*M
	int fila;
	int columna;
	is>>fila;
	is>>columna;
	_columna = columna;
	_fila = fila;
	
	string s;
	int contx = 0, conty = 0;
	//string ignoro;
	getline(is,s);	//Hay que dejarlo, es el salto de linea de los numeros
	//cout<<"test"<<s<<endl;
	for( nat i = 0; i < (_fila*2); ++i){	//(_fila*2)
		getline(is,s);
		//cout<<"testdentro del for"<<s<<endl;
		//contx = 0;	esto está mal
		if(i != 0){
			conty = 0;
			for( nat j = 0; j < (_columna*2)+1; ++j ){
				if(i%2 != 0){	// ***AHORA IM****PAR, miro este
					if(j%2 == 0 and j != 0 and (j != (_columna*2)+1) ){	//Si no es paret oeste ni es cambra ni es paret este
						if(s[j] == ' '){
							//cout<<"jota:"<<j<<endl;
							//cout<<"mi s es este:"<<s<<endl;
							//cout<<"prueba:"<<s[j]<<"TT"<<endl;
							//cout<<"aqui entra verdad?"<<endl;
							_mathlab[contx][conty].obre_porta(paret::EST);	//Abro este
							_mathlab[contx][conty+1].obre_porta(paret::OEST);	//Abro oest
						}
						//cout<<"X:"<<contx<<" + Y:"<<conty<<endl;
						//++contx;
						++conty;
					}
				}
				else{	// ****AHORA PAR**** IMPAR
					//cout<<"aqui entra verdad?"<<endl;
					if( j%2 != 0){	//Estamos en paret sud/norte
						if(s[j] == ' '){
							_mathlab[contx][conty].obre_porta(paret::SUD);	//Abro norte
							_mathlab[contx+1][conty].obre_porta(paret::NORD);	//Abro sud
						}
						//cout<<"x:"<<contx<<" - y:"<<conty<<endl;
						++conty;
					}
				}
			}
			if( i%2 == 0)	contx++;
		}
	}
	//getline(is,s); sigue sin funcionar
	cout<<"he acabado"<<endl;
}
//bst, hash, 
//find ,union de les particions, el quick union es mejor (en vez de apuntar todos al delegado, se va creando un arbol)
//bst tiene fesq, fdret y otro puntero para su delegado
//hash lo mismo, tienen sus punteros y le añades uno extra a su delegado

//dedalus, posicio: x*y = 1,2,3,4,5,...
laberint::laberint(const laberint & l) throw(error){
		//COST N*M
		//cambiamos esto y lo ponemos al reves
  *this = l;
}
laberint& laberint::operator=(const laberint & l) throw(error){
		//COST N*M
		//l1 = l2;
		//delete l1 i despues copias l2 en otro sitio temporal i haces return de ese?;
		//aux(l2)
		//l1 = aux;
		//aux = l1;
		//y al acabar se borra "aux" que has hecho que sea l1
		//ha enseñado la implementacion de cua
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
				_mathlab[pos.first][pos.second].obre_porta(p);	//Abro este
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
			s += (_mathlab[i][j].porta_oberta(paret("sud")) ? ' ' : '*');
			if(j != _columna-1 )	os << (_mathlab[i][j].porta_oberta(paret("est")) ? ' ' : '*');
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

/*
***********
* * * * * *
***********
* * * * * *
***********
* * * * * *
***********
* * * * * *
***********
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
	
