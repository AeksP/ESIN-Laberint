#include "cambra.hpp"
 #include <iostream>
 using namepsace std;
 
explicit cambra::cambra(bool n=false, bool s=false, bool e=false, bool o=false){
  cout<<"test"<<endl;
  //explicit = Si tienes cambra c2(true,true)
  //Tendrás una cambra con n=true, s=true, e=false, o=false
  
  //Meter metodo privado para guardar si la puerta está abierta o no?
}

cambra::~cambra(){

}

bool cambra::porta_oberta(paret p) const{
	//Usar metodos privados que guardan puerta abierta aqui? (Sería _n, _s etc)
	if(p == paret::NORD)	return _n;
	else if(p == paret::EST)	return _e;
	else if(p == paret::SUD)	return _s;
	else if(p == paret::OEST)	return _o;
	//Poner algo por si p == paret::NO_DIR?
}

void cambra::obre_porta(paret p){
	if(p == paret::NORD){	//Mejor esto que p == 0
		//if(_n == 1) cout<<"La puerta ya está abierta."  //No sé si hace falta
		_n = 1;
	}
}
