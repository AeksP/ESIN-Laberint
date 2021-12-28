#include "particio.hpp"
template <typename T>
long particio<T>::h(int k){
    long y = ((k * k * MULT) << 20) >> 4;
    return y;
}
template <typename T>
void particio<T>::esborra_nodes(node_hash *p){

}

template <typename T>
particio<T>::particio(nat n) throw(error){
    _M = n; //maxim 
    _taula = new node_hash*[_M];
    for(int i = 0; i < _M; ++i){
        _taula[i] = NULL;
    }
}

template <typename T>
particio<T>::particio(const particio & p) throw(error){
    *this = p;
}

template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){
    return *this = p;
}

template <typename T>
particio<T>::~particio() throw(){

}

template <typename T>
void particio<T>::afegir(const T &x) throw(error){
std::cout <<x <<std::endl;
}

template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){
std::cout <<x <<std::endl;
std::cout <<y <<std::endl;
}

template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
    std::cout <<x <<std::endl;
    std::cout <<y <<std::endl;
    return true;
}

template <typename T>
nat particio<T>::size() const throw(){
    return 1;
}

template <typename T>
nat particio<T>::num_elements() const throw(){
    return 1;
}

template <typename T>
nat particio<T>::num_maxim() const throw(){
    return 1;
}