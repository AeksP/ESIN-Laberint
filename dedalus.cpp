#include "dedalus.hpp"
using util::Random;

void dedalus::construir(laberint & M) throw(error){
    //laberint l;
    //l = M;
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
    std::cout<<"AQUIIIIIII"<<std::endl;
    nat contador = 0;
    while(contador != size-1){
    
        nat fil = Rfil(1, filas);
        nat col = Rcol(1, columnas);
        std::cout<<"filcol: "<<fil<<"-"<<col<<std::endl;
        nat paret = paret::NO_DIR;
        posicio C(fil, col);
        cambra CAM = M(C);
// 0 1 2 3 4
// N E S O NODIR
        if(fil == 0+1){  //Tienes pared norte
            while(paret == paret::NORD or paret == paret::NO_DIR or CAM.porta_oberta(paret)){
                paret = Rpar(1,3);
            }
        }
        if(col == 0+1){   //Tienes pared oeste
            while(paret == paret::OEST or paret == paret::NO_DIR or CAM.porta_oberta(paret)){
                paret = Rpar(0,2);
            }
        }
        if(fil == filas-1+1){   //Tienes pared sud
            while(paret == paret::SUD or paret == paret::NO_DIR or CAM.porta_oberta(paret)){
                paret = Rpar(0,3);
            }
        }
        if(col == columnas-1+1){   //Tienes pared este
            while(paret == paret::EST or paret == paret::NO_DIR or CAM.porta_oberta(paret)){
                paret = Rpar(0,3);
            }
        }
        /*if(fil != 1 and col != 1 and fil != filas and col != columnas){
            paret = Rpar(0,3);
        }*/
        //Paret que no sea exterior ni abierta
        //std::cout<<"Cprima"<<std::endl;
        posicio Cprim;
        if(paret == paret::NORD){
            Cprim.first = fil-1;
            Cprim.second = col;
            std::cout<<"Nord"<<std::endl;
            //posicio Cprim(fil-1, col);
        }
        else if(paret == paret::SUD){
            Cprim.first = fil+1;
            Cprim.second = col;
            std::cout<<"Sud"<<std::endl;
            //posicio Cprim(fil+1, col);
        }
        else if(paret == paret::OEST){
            Cprim.first = fil;
            Cprim.second = col-1;
            std::cout<<"Oest"<<std::endl;
            //posicio Cprim(fil, col-1);
        }
        else if(paret == paret::EST){
            Cprim.first = fil;
            Cprim.second = col+1;
            std::cout<<"Est"<<std::endl;
            //posicio Cprim(fil, col+1);
        }
        //Ahora tenemos la posicion de nuestra cambra adyacente 
        std::cout<<"C: "<<fil<<"-"<<col<<std::endl;
        std::cout<<"Pared: "<<paret<<std::endl;
        std::cout<<"Cprim: "<<Cprim.first<<"-"<<Cprim.second<<std::endl;
        std::cout<<"Mateix GRUP 1: "<<(columnas*C.first) + C.second - columnas <<" ....2: "<<(columnas*Cprim.first) + Cprim.second - columnas<<std::endl;
        if(not p.mateix_grup((columnas*C.first) + C.second - columnas, (columnas*Cprim.first) + Cprim.second - columnas)){
            //std::cout<<"reloco amigo"<<std::endl;
            M.obre_porta(paret, C);   //Abres camino
            std::cout<<"aqui llego"<<std::endl;
            p.unir( (columnas*C.first) + C.second - columnas, (columnas*Cprim.first) + Cprim.second - columnas);   //Ahora son del mismo grupo
            contador++;
        }//else no fem res
        std::cout<<"HE ACABADO"<<std::endl;
    }
}
