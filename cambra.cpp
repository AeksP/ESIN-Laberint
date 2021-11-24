#include "cambra.hpp"
#include <iostream>
using namespace std;
 
cambra::cambra(bool n, bool s, bool e, bool o) throw(error){
  _n = n;
  _e = e;
  _s = s;
  _o = o;
  //casting
  //explicit = Si tienes cambra c2(true,true)
  //Tendrás una cambra con n=true, s=true, e=false, o=false
  
  //Meter metodo privado para guardar si la puerta está abierta o no?
}

cambra::cambra(const cambra & c) throw(error){
  *this = c;
}

cambra& cambra::operator=(const cambra & c) throw(error){
  //return this(c);//MIRAR VERY IMPORTANT
  _n = c._n;
  _e = c._e;
  _s = c._s;
  _o = c._o;
  return *this;
}

cambra::~cambra() throw(){
}

bool cambra::porta_oberta(paret p) const throw(){
	//Usar metodos privados que guardan puerta abierta aqui? (Sería _n, _s etc)
	if(p == paret::NORD)	return _n;
	else if(p == paret::EST)	return _e;
	else if(p == paret::SUD)	return _s;
	else return _o; //
	//Poner algo por si p == paret::NO_DIR?
}

void cambra::obre_porta(paret p) throw(error){
	if(p == paret::NORD){	//Mejor esto que p == 0
		//if(_n == 1) cout<<"La puerta ya está abierta."  //No sé si hace falta
		_n = 1;
	}else if(p == paret::EST){
    _e = 1;
  }else if(p == paret::SUD){
    _s = 1;
  }else if(p == paret::OEST){
    _o = 1;
  }
}

void cambra::tanca_porta(paret p) throw(error){
  if(p == paret::NORD){
		_n = 0;
	}else if(p == paret::EST){
    _e = 0;
  }else if(p == paret::SUD){
    _s = 0;
  }else if(p == paret::OEST){
    _o = 0;
  }  
}

bool cambra::operator==(const cambra & c) const throw(){
  if(_n == c._n and _e == c._e and _s == c._s and _o == c._o) return true;
  else return false;
}
bool cambra::operator!=(const cambra & c) const throw(){
  return not (*this==c);
}

bool cambra::operator<(const cambra & c) const throw(){
  if((_n + _e + _s + _o) == (c._n + c._e + c._s + c._o)){
    if(_n < c._n)  return true;
    else if(_e < c._e)  return true;
    else if(_s < c._s)  return true;
    else return true; //
  }
  else if((_n + _e + _s + _o) < (c._n + c._e + c._s + c._o)) return true;
  else return false;
}
