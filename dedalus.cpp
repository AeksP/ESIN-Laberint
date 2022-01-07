#include "dedalus.hpp"
using util::Random;

void dedalus::construir(laberint & M) throw(error){
    laberint l;
    l = M;

    int size = M.num_files() * M.num_columnes();
    particio<int> p(1.25*size);
    Random filcol(13);
    int a = filcol(3,4);
    std::cout<<"filcol: "<<a<<std::endl;
}
