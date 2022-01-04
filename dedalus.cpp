#include "dedalus.hpp"

void dedalus::construir(laberint & M) throw(error){
    laberint l;
    l = M;
    int size = M.num_files() * M.num_columnes();
    particio<int> p(1.25*size);
}
