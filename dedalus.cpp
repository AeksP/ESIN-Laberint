#include "dedalus.hpp"
using util::Random;

void dedalus::construir(laberint & M) throw(error){
    Random Rfil(13);
    Random Rcol(20);
    Random Rpar(5);
    nat filas = M.num_files();
    nat columnas = M.num_columnes();
    nat size = filas * columnas;
    particio<int> p(1.25*size);

    for(nat i = 1; i <= filas; ++i){
        for(nat j = 1; j <= columnas; ++j){
            std::cout<<(columnas*i)+j - columnas<<" ";
            p.afegir((columnas*i)+j - columnas);
        }
        std::cout<<std::endl;
    }
    nat contador = 0;
    while(contador < size-1){ 

        nat fil = Rfil(1, filas);
        nat col = Rcol(1, columnas);
        nat paret = paret::NO_DIR;

        posicio C(fil, col);
        cambra CAM = M(C);

        while( (paret == paret::NORD and fil == 1) or (paret == paret::SUD and fil == filas) or (paret == paret::OEST and col == 1) or (paret == paret::EST and col == columnas) or paret == paret::NO_DIR){

        if(fil == 0+1){  //Tienes pared norte
            while(paret == paret::NORD or paret == paret::NO_DIR){
                paret = Rpar(1,3);
            }
        }
        if(col == 0+1){   //Tienes pared oeste
            while(paret == paret::OEST or paret == paret::NO_DIR){
                paret = Rpar(0,2);
            }
        }
        if(fil == filas-1+1){   //Tienes pared sud
            while(paret == paret::SUD or paret == paret::NO_DIR){
                paret = Rpar(0,3);
            }
        }
        if(col == columnas-1+1){   //Tienes pared este
            while(paret == paret::EST or paret == paret::NO_DIR){
                paret = Rpar(0,3);
            }
        }
        if(fil != 1 and col != 1 and fil != filas and col != columnas){ //Para cuando está dentro
            paret = Rpar(0,3);
        }
        }

        //Paret que no sea exterior ni abierta
        posicio Cprim;
        if(paret == paret::NORD){
            Cprim.first = fil-1;
            Cprim.second = col;
        }
        else if(paret == paret::SUD){
            Cprim.first = fil+1;
            Cprim.second = col;
        }
        else if(paret == paret::OEST){
            Cprim.first = fil;
            Cprim.second = col-1;
        }
        else if(paret == paret::EST){
            Cprim.first = fil;
            Cprim.second = col+1;
        }
        //Ahora tenemos la posicion de nuestra cambra adyacente 
        if(not p.mateix_grup((columnas*C.first) + C.second - columnas, (columnas*Cprim.first) + Cprim.second - columnas)){
            M.obre_porta(paret, C);   //Abres camino
            p.unir( (columnas*C.first) + C.second - columnas, (columnas*Cprim.first) + Cprim.second - columnas);   //Ahora son del mismo grupo
            contador++;
        }//else no fem res
    }
}
