#include "cambra.hpp"
#include <iostream>
using namespace std;
 
cambra::cambra(bool n, bool s, bool e, bool o) throw(error){
  _n = n;
  _e = e;
  _s = s;
  _o = o;
}

cambra::cambra(const cambra & c) throw(error){
  *this = c;
}

cambra& cambra::operator=(const cambra & c) throw(error){
  _n = c._n;
  _e = c._e;
  _s = c._s;
  _o = c._o;
  return *this;
}

cambra::~cambra() throw(){
}

bool cambra::porta_oberta(paret p) const throw(){
	if(p == paret::NORD)	return _n;
	else if(p == paret::EST)	return _e;
	else if(p == paret::SUD)	return _s;
	else return _o; //
	//si p == paret::NO_DIR?
}

void cambra::obre_porta(paret p) throw(error){
	if(p == paret::NORD){
		//if(_n == 1) cout<<"La puerta ya está abierta."
		_n = true;
	}else if(p == paret::EST){
    _e = true;
  }else if(p == paret::SUD){
    _s = true;
  }else if(p == paret::OEST){
    _o = true;
  }
}

void cambra::tanca_porta(paret p) throw(error){
  if(p == paret::NORD){
		_n = false;
	}else if(p == paret::EST){
    _e = false;
  }else if(p == paret::SUD){
    _s = false;
  }else if(p == paret::OEST){
    _o = false;
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
