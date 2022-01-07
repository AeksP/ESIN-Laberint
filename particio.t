#include "particio.hpp"
using util::hash;

template <typename T>
long particio<T>::h(int k){
    long y = ((k * k * MULT) << 20) >> 4;
    return y;
}
template <typename T>
void particio<T>::esborra_nodes(node_hash *p){

    if(p != NULL){
        esborra_nodes(p->_seg);
        delete p;
	}
}

template <typename T>
particio<T>::particio(nat n) throw(error){
    _quants = 0;
    _ngrups = 0;
    _M = n + n*0.25;
    nat M = _M;
    _taula = new node_hash*[M];
    for(nat i = 0; i < M; ++i){
        _taula[i] = NULL;
    }
}

template <typename T>
particio<T>::particio(const particio & p) throw(error){
    //std::cout<<"copia"<<std::endl;
    _quants = p._quants;
    _ngrups = p._ngrups;
    _M = p._M;
    nat M = _M;
    _taula = new node_hash*[M];
    for(nat i = 0; i < M; ++i){
        node_hash* Q = p._taula[i];
        node_hash* n = new node_hash;
        _taula[i] = n;
        //std::cout<<Q<<" and "<<_taula[i]<<" i:"<<i<<std::endl;
        if(Q == NULL){
            _taula[i] = NULL;
            delete n;
        }else{
            while(Q != NULL){
                n->_k = Q->_k;
                n->_rep = Q->_rep;
                n->_hijos = Q->_hijos;
                if(Q->_seg != NULL){
                    node_hash* nn = new node_hash;
                    n->_seg = nn;
                    n = n->_seg;
                }else n->_seg = NULL;

                Q = Q->_seg;
            }
        }
        //std::cout<<"FINAL: "<<Q<<" and "<<_taula[i]<<" i:"<<i<<std::endl;
    }
    //Asignar delegados
    for(nat i = 0; i < M; ++i){
        //std::cout<<"core"<<std::endl;
        node_hash* Q = p._taula[i];
        //std::cout<<"dumped"<<std::endl;
        node_hash* P = _taula[i];
        //std::cout<<"DELEGADOS P: "<<P->_k<<" and "<<i<<std::endl;
        //std::cout<<"DELEGADOS Q: "<<Q->_k<<" and "<<i<<" and2 "<<p._taula[i]->_delegat->_k<<std::endl;
        while(Q != NULL){
            //std::cout<<"NUMERO Q: "<<Q->_k<<" i: "<<i<<" delegat: "<<Q->_delegat->_k<<std::endl;
            //std::cout<<"DELEGADOS Q: "<<Q->_k<<" i: "<<i<<" delegat: "<<Q->_delegat->_k<<std::endl;
            int index = hash<T>(Q->_delegat->_k) % M;
            int clauD = Q->_delegat->_k;
            //std::cout<<"Q: "<<Q->_k<<" | delegat Q: "<<Q->_delegat->_k<<" | clauD: "<<clauD<<std::endl;
            node_hash* bd = _taula[index];  //bd está en la fila del delegado de P
            //std::cout<<"delegados BD: "<<bd->_k<<" i: "<<i<<std::endl;
            while(bd != NULL and bd->_k != clauD ){    //(bd nunca debería de ser NULL)
                //std::cout<<"while: "<<std::endl;
                bd = bd->_seg;
            }
            //Ya tienes el delegado en bd y lo asignas
            P->_delegat = bd;
            //std::cout<<"DELEGADOS Q: "<<Q->_k<<" i: "<<i<<" delegat: "<<Q->_delegat->_k<<std::endl;
            Q = Q->_seg;
            P = P->_seg;
            //std::cout<<"delegados BD: "<<bd->_k<<" i: "<<i<<" delegat: "<<bd->_delegat->_k<<std::endl;
            //std::cout<<"DELEGADOS Q: "<<Q->_k<<" i: "<<i<<" delegat: "<<Q->_delegat->_k<<std::endl;
        }
    }
    //std::cout<<"copia final"<<std::endl;
}

template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){
            //std::cout<<"ibai hazlo"<<std::endl;
		if(this != &p){
            //std::cout<<"freeman"<<std::endl;
			particio praux(p);
            //std::cout<<"foskit"<<std::endl;
			node_hash** paux = _taula;
			_taula = praux._taula;
			praux._taula = paux;	//Se borra el _taula original
            //std::cout<<"dorito"<<std::endl;
            nat AUX = _quants;
            _quants = praux._quants;
            praux._quants = AUX;

            AUX = _ngrups;
            _ngrups = praux._ngrups;
            praux._ngrups = AUX;

            float AUX2 = _M;
            _M = praux._M;
            praux._M = AUX2;
            //std::cout<<"igual"<<std::endl;
		}
		return *this;
}

template <typename T>
particio<T>::~particio() throw(){
    //std::cout<<"destructor"<<std::endl;
    nat M = _M;
    for(nat i = 0; i < M; ++i){
       esborra_nodes(_taula[i]); 
    }
    delete [] _taula;
    //std::cout<<"destru"<<std::endl;
}

template <typename T>
void particio<T>::afegir(const T &x) throw(error){
    int M = _M;
    if(_quants < _M/1.25){
        //int i = h(x);
        int i = hash<T>(x) % M;
        node_hash* p = _taula[i];
        //std::cout<<"aa"<<std::endl;
        node_hash* n = new node_hash;    //el nuevo node_hash por añadir
        bool trobat = false;
        bool afegit = false;
        //std::cout<<p<<" and "<<_taula[i]<<" i:"<<i<<std::endl;
        if(_taula[i] == 0){   //para el primero no tendrás que recorrer nada
            afegit = true;
            _taula[i] = n;
        }

        while( p != NULL and not trobat and not afegit){
            //std::cout<<"bb"<<std::endl;
            if(p->_k == x){
                //std::cout<<"aaaaaa"<<std::endl;
                trobat = true;  //Estás dentro y te vas
            }
            else{
                //std::cout<<"dddddd"<<std::endl;
                if(p->_seg == NULL and not trobat and not afegit){
                    p->_seg = n;
                    afegit = true;
                }
                else    p = p->_seg;
            }
        }
    //std::cout<<"cc"<<std::endl;
        if(not trobat or afegit){
            n->_k = x;
            n->_seg = NULL;
            n->_delegat = n;
            n->_rep = true;
            n->_hijos = 0;
            _ngrups++;
            _quants++;
        } else delete n;

    //std::cout<<"AL ACABAR: "<<p<<" and "<<_taula[i]<<" i:"<<i<<std::endl;
    }else{
        /*int i = hash<T>(x);
        node_hash* p = _taula[i];
        std::cout<<p<<" and "<<_taula[i]<<" i:"<<i<<std::endl;
        throw error(ParticioPlena);*/

        if(_M == 0) throw error(ParticioPlena);
        bool repetido = false;
        int i = hash<T>(x) % M;
        node_hash* p = _taula[i];
        while( p != NULL and not repetido){
            if(p->_k == x){
                repetido = true;  //Estás dentro y te vas
            }
            p = p->_seg;
        }
        if(not repetido) throw error(ParticioPlena);
    }
}

template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){
    if(_M == 0) throw error(ElemInexistent);
    int M = _M;
    int i = hash<T>(x) % M;
    int j = hash<T>(y) % M;
    //Controlar error
    //std::cout<<" espacio "<<std::endl;
    //if(_taula[i] == NULL or _taula[j] == NULL)  throw error(ElemInexistent);
    //buscar
    //std::cout<<i<<"--"<<j<<std::endl;
    //std::cout<<_taula[1]<<"--"<<_taula[2] <<"--" <<_taula[3] <<"--" <<_taula[0]<<std::endl;
    //std::cout<<p<<" espacio "<<q<<std::endl;
        if(not mateix_grup(x,y)){ //Hacemos quickunion
            --_ngrups;
            node_hash* p = _taula[i];
            node_hash* q = _taula[j];

            while(p != NULL and p->_k != x){
                p = p->_seg;
            }
            while(q != NULL and q->_k != y){
                q = q->_seg;
            }

            while(p != NULL and not p->_rep){
                p = p->_delegat;
            }
            while(q != NULL and not q->_rep){
                q = q->_delegat;
            }

            if(p->_hijos < q->_hijos){  //unes P a Q
                p->_delegat = q;    //tu delegado es q
                p->_rep = false;    //ya no eres delegado

                q->_hijos += p->_hijos + 1; //los hijos de P + "p"
                //std::cout<<"P-Q delegatP: "<<p->_delegat->_k<<" delegat2: "<<q->_delegat->_k<<std::endl;
            }else{  //else unes Q a P
                q->_delegat = p;
                q->_rep = false;

                p->_hijos += q->_hijos + 1;
                //std::cout<<"Q-P delegat: "<<p->_delegat->_k<<" delegat2: "<<q->_delegat->_k<<std::endl;
            } //else Son iguales y no hace nada
        }
        
}

template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
    if(_M == 0) throw error(ElemInexistent);
    int M = _M;
    int i = hash<T>(x) % M;
    int j = hash<T>(y) % M;
    node_hash* p = _taula[i];
    node_hash* q = _taula[j];
    if(_taula[i] == NULL or _taula[j] == NULL)  throw error(ElemInexistent);

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
        while(p != NULL and not p->_rep){
            p = p->_delegat;
        }
        while(q != NULL and not q->_rep){
            q = q->_delegat;
        }
        //std::cout<<"mateixgrup delegat: "<<p->_delegat->_k<<" delegat2: "<<q->_delegat->_k<<std::endl;
        if(p->_delegat == q->_delegat)    return true;
        else return false;
    }else throw error(ElemInexistent);

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
    return _M/1.25;
}