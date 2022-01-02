#include "particio.hpp"
using util::hash;

template <typename T>
long particio<T>::h(int k){
    long y = ((k * k * MULT) << 20) >> 4;
    return y;
}
template <typename T>
void particio<T>::esborra_nodes(node_hash *p){
    //std::cout<<"borra"<<std::endl;
    //cambiar ex jutge examen
    if(p != NULL){
        esborra_nodes(p->_seg);
        delete p;
	}
}

template <typename T>
particio<T>::particio(nat n) throw(error){
    _M = n + n*0.25;
    _taula = new node_hash*[_M];
    for(nat i = 0; i < _M; ++i){
        _taula[i] = NULL;
    }
}

template <typename T>
particio<T>::particio(const particio & p) throw(error){
    _quants = p._quants;
    _ngrups = p._ngrups;
    _M = p._M;
    _taula = new node_hash*[_M];
    for(nat i = 0; i < _M; ++i){
        //_taula[i] = p._taula[i];
        node_hash* Q = p._taula[i];
        while(Q != NULL){
            node_hash* P = new node_hash;
            P->_k = Q->_k;
                                    P->_seg = Q->_seg;
                                    P->_delegat = Q->_delegat;
            P->_rep = Q->_rep;
            P->_hijos = Q->_hijos;

            Q = Q->_seg;
        }
    }

    //otro for para delegados
    //int D = hash(Q->_delegat->_k)
    //int V = Q->_delegat->_k
    //_taula[D] tienes la "V"
    //buscas la "V" y "P->_delegado = V"

}

template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){
		if(this != &p){
			particio aux(p);
			node_hash** paux = _taula;
			_taula = aux._taula;
			aux._taula = paux;	//Se borra el _taula original

            _quants = p._quants;
            _ngrups = p._ngrups;
            _M = p._M;
		}
		return *this;
}

template <typename T>
particio<T>::~particio() throw(){
    for(nat i = 0; i < _M; ++i){
       esborra_nodes(_taula[i]); 
    }
}

template <typename T>
void particio<T>::afegir(const T &x) throw(error){
    int i = h(x);
    //int i = hash<T>(x);
    node_hash* p = _taula[i];
    node_hash* n = new node_hash;    //el nuevo node_hash por añadir
    bool trobat = false;
    bool afegit = false;
    while( p != NULL and not trobat and not afegit){
        if(p->_k == x){
            trobat = true;  //Estás dentro y te vas
        }
        else{
            if(p->_seg == NULL and not trobat and not afegit){
                p->_seg = n;
                afegit = true;
            }
            else    p = p->_seg;
        }
    }
    if(not trobat or afegit){
        n->_k = x;
        n->_seg = NULL;
        n->_delegat = n;
        n->_rep = true;
        n->_hijos = 0;
        _ngrups++;
    }
    else delete n;
}

template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){
    int i = h(x);
    int j = h(y);
    //Controlar error
    if(_taula[i] == NULL or _taula[j] == NULL)  throw error(ElemInexistent);
    //buscar
    node_hash* p = _taula[i];
    node_hash* q = _taula[j];
    bool trobat = false;
    while(p != NULL and not trobat){
        if(p->_k != x){
            p = p->_seg;
        }else{
            trobat = true;
        }
    }
    bool trobat2 = false;
    while(q != NULL and not trobat2){
        if(q->_k != y){
            q = q->_seg;
        }else{
            trobat2 = true;
        }
    }
    if(trobat and trobat2){
        if(p->_delegat != q->_delegat){ //Hacemos quickunion
            if(not p->_rep){    //No hace falta?
                while(p != NULL and not p->_rep){
                    p = p->_delegat;
                }
            }
            if(not q->_rep){
                while(q != NULL and not q->_rep){
                    q = q->_delegat;
                }
            }

            if(p->_hijos < q->_hijos){  //unes P a Q
                p->_delegat = q;    //tu delegado es q
                p->_rep = false;    //ya no eres delegado

                q->_hijos += p->_hijos + 1; //los hijos de P + "p"
            }else{  //else unes Q a P
                q->_delegat = p;
                q->_rep = false;

                p->_hijos += q->_hijos + 1;
            }
            --_ngrups;
        } //else Son iguales y no hace nada
    }
    else throw error(ElemInexistent);
}

template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
    int i = h(x);
    int j = h(y);
    node_hash* p = _taula[i];
    node_hash* q = _taula[j];
    if(_taula[i] == NULL or _taula[j] == NULL)  throw error(ElemInexistent);
    while(p != NULL and not p->_rep){
        p = p->_delegat;
    }
    while(q != NULL and not q->_rep){
        q = q->_delegat;
    }
    if(p->_delegat == q->_delegat)    return true;
    else return false;

}

template <typename T>
nat particio<T>::size() const throw(){
    return _ngrups;
}

template <typename T>
nat particio<T>::num_elements() const throw(){
    return _quants;
}

template <typename T>
nat particio<T>::num_maxim() const throw(){
    return _M + _M*0.25;
}