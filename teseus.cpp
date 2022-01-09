#include "teseus.hpp"

  void MATHLAB(const laberint & M, bool** matr, int i, int j, int filresta, int resta){
    posicio pos(i,j);
    cambra c = M(pos);
    if(c.porta_oberta(paret::NORD)){
      matr[pos.first-1+filresta][pos.second-1+resta] = c.porta_oberta(paret::NORD);
      matr[pos.first-2+filresta][pos.second-1+resta] = c.porta_oberta(paret::NORD);
    }
    if(c.porta_oberta(paret::EST)){
      matr[pos.first-1+filresta][pos.second-1+resta] = c.porta_oberta(paret::EST);
      matr[pos.first-1+filresta][pos.second+resta] = c.porta_oberta(paret::EST);
    }
    if(c.porta_oberta(paret::SUD)){
      matr[pos.first-1+filresta][pos.second-1+resta] = c.porta_oberta(paret::SUD);
      matr[pos.first+filresta][pos.second-1+resta] = c.porta_oberta(paret::SUD);
    }
    if(c.porta_oberta(paret::OEST)){
      matr[pos.first-1+filresta][pos.second-1+resta] = c.porta_oberta(paret::OEST);
      matr[pos.first-1+filresta][pos.second-2+resta] = c.porta_oberta(paret::OEST);
    }
  }

  bool caminable(bool** matr, bool** visitado, int i, int j, int filas, int columnas){
    //std::cout<<"z"<<std::endl;
    //std::cout<<"caminable i: "<<i<<" caminable j: "<<j<<std::endl;
    //std::cout<<"fila: "<<(filas*2)-1<<" columnas: "<<(columnas*2)-1<<std::endl;
    //std::cout<<(matr[i][j] == 1)<<" "<<not visitado[i][j]<<std::endl;
    //if(i == 4 and j == 4) std::cout<<(matr[i][j] == 1)<<visitado[i][j]<<std::endl;
    return(i >= 0 and i < (filas*2)-1 and j >= 0 and j < (columnas*2)-1 and matr[i][j] == 1 and not visitado[i][j]);
  }

  bool encontrarCamino(bool** matr, bool** visitado, int i, int j, int x, int y, std::list<posicio> & L, std::list<posicio> &vacia, int filas, int columnas, nat a, nat b){
    if( i == x and j == y){

      std::cout<<"final i: "<<i<<" final j: "<<j<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);

    std::cout<<"VACIA: "<<std::endl;
      for (std::list<posicio>::iterator it=vacia.begin(); it!=vacia.end(); ++it){
        std::cout<<(*it).first<<"-"<<(*it).second<<" ";
      }
      std::cout<<std::endl;
    std::cout<<"L: "<<std::endl;
      for (std::list<posicio>::iterator it=L.begin(); it!=L.end(); ++it){
        std::cout<<(*it).first<<"-"<<(*it).second<<" ";
      }
      std::cout<<std::endl;

      //std::list<posicio> aux;
      std::list<posicio>::iterator it=L.begin();
      while(not L.empty() and ((*it).first != a or (*it).second != b)){
        ++it;
        L.pop_front();
      }

    std::cout<<"POST L: "<<std::endl;
      for (std::list<posicio>::iterator it=L.begin(); it!=L.end(); ++it){
        std::cout<<(*it).first<<"-"<<(*it).second<<" ";
      }

      if(vacia.empty()){
        while(not L.empty()){
          vacia.push_back(L.front());
          L.pop_front();
        }
      }
      else if(vacia.size() > L.size()){
        while(not vacia.empty()){
          vacia.pop_back();
        }
        while(not L.empty()){
          vacia.push_back(L.front());
          L.pop_front();
        }
      }else if(vacia.size() < L.size()){
        while(not L.empty()){
          L.pop_back();
        }

      }

      return true;
    }
    //std::cout<<"eyyy"<<std::endl;
    visitado[i][j] = true;
    bool a1 = false, a2 = false, a3 = false, a4 = false;
    std::cout<<"i: "<<i<<" j: "<<j<<std::endl;
    //SUD
    if((a1 = caminable(matr, visitado, i+1, j, filas, columnas))){
      //std::cout<<"a"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      if(not encontrarCamino(matr, visitado, i+1, j, x, y, L, vacia, filas, columnas, a, b)){
        if(not L.empty()){
          std::cout<<pos.first<<"---"<<pos.second<<std::endl;
          std::cout<<(L.back()).first<<"+++"<<(L.back()).second<<std::endl;


          std::cout<<"LSUD: "<<std::endl;
      for (std::list<posicio>::iterator it=L.begin(); it!=L.end(); ++it){
        std::cout<<(*it).first<<"-"<<(*it).second<<" ";
      }
      std::cout<<std::endl;


          while(not L.empty() and L.back() != pos){
            L.pop_back();
          }
        }
      }

    }
    //E
    if((a2 = caminable(matr, visitado, i, j+1, filas, columnas))){
      //std::cout<<"b"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      if(not encontrarCamino(matr, visitado, i, j+1, x, y, L, vacia, filas, columnas, a, b)){
        if(not L.empty()){
          std::cout<<pos.first<<"---"<<pos.second<<std::endl;
          std::cout<<(L.back()).first<<"+++"<<(L.back()).second<<std::endl;


  std::cout<<"LE: "<<std::endl;
      for (std::list<posicio>::iterator it=L.begin(); it!=L.end(); ++it){
        std::cout<<(*it).first<<"-"<<(*it).second<<" ";
      }
      std::cout<<std::endl;


          while(not L.empty() and L.back() != pos){
            L.pop_back();
          }
        }
      }
    }
    //N
    if((a3 = caminable(matr, visitado, i-1, j, filas, columnas))){
      //std::cout<<"c"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      if(not encontrarCamino(matr, visitado, i-1, j, x, y, L, vacia, filas, columnas, a, b)){
        if(not L.empty()){
          std::cout<<pos.first<<"---"<<pos.second<<std::endl;
          std::cout<<(L.back()).first<<"+++"<<(L.back()).second<<std::endl;

std::cout<<"LN: "<<std::endl;
      for (std::list<posicio>::iterator it=L.begin(); it!=L.end(); ++it){
        std::cout<<(*it).first<<"-"<<(*it).second<<" ";
      }
      std::cout<<std::endl;



          while(not L.empty() and L.back() != pos){
            L.pop_back();
          }
        }
      }
    }
    //O
    if((a4 = caminable(matr, visitado, i, j-1, filas, columnas))){
      //std::cout<<"d"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      if(not encontrarCamino(matr, visitado, i, j-1, x, y, L, vacia, filas, columnas, a, b)){
        if(not L.empty()){
          std::cout<<pos.first<<"---"<<pos.second<<std::endl;
          std::cout<<(L.back()).first<<"+++"<<(L.back()).second<<std::endl;



std::cout<<"LO: "<<std::endl;
      for (std::list<posicio>::iterator it=L.begin(); it!=L.end(); ++it){
        std::cout<<(*it).first<<"-"<<(*it).second<<" ";
      }
      std::cout<<std::endl;



          while(not L.empty() and L.back() != pos){
            L.pop_back();
          }
        }
      }
    }


  visitado[i][j] = false;
    return (a1 or a2 or a3 or a4);
  }

  void teseus::buscar(const laberint & M, const posicio & inici, const posicio & final, std::list<posicio> & L) throw(error){
    
  nat filas = M.num_files();
  nat columnas = M.num_columnes();
  if(inici.first > filas or inici.first == 0 or inici.second > columnas or inici.second == 0 or
    final.first > filas or final.first == 0 or final.second > columnas or final.second == 0)  throw error(IniciFinalNoValid);
  else{

    bool** matriu;
    matriu = new bool*[(filas*2)-1];	//Array de cambras
    for(nat i = 0; i < (filas*2)-1; ++i){	//Matriz de cambras
      matriu[i] = new bool[(columnas*2)-1];
    }

    for(nat i = 0; i < (filas*2)-1; ++i){
      for(nat j = 0; j < (columnas*2)-1; ++j){
        matriu[i][j] = 0;
      }
    }
    posicio inicimatriu;
    posicio finalmatriu;
    //########################## MATRIZ ##########################################
      int filresta = 0;
      for(nat i = 1; i <= (filas*2)-1; ++i){
        int resta = 0;
        for(nat j = 1; j <= (columnas*2)-1; ++j){
          
            if(i%2 != 0 and j%2 != 0) {
              if(inici.first == i-filresta and inici.second == j-resta){
                inicimatriu.first = i;
                inicimatriu.second = j;
              }
              if(final.first == i-filresta and final.second == j-resta){
                finalmatriu.first = i;
                finalmatriu.second = j;
              }
              MATHLAB(M, matriu, i-filresta, j-resta, filresta, resta);
              resta++;
            }
            
        }
        if(i%2 != 0) filresta++;
      }
    //####################################################################

    std::cout<<"Matriz"<<std::endl; 
    for(nat i = 1; i <= (filas*2)-1; ++i){
      for(nat j = 1; j <= (columnas*2)-1; ++j){
        std::cout<<matriu[i-1][j-1]<<" ";
      }
      std::cout<<std::endl;
    }

    bool** visitado;
    visitado = new bool*[(filas*2)-1];	//Array de cambras
    for(nat i = 0; i < (filas*2)-1; ++i){	//Matriz de cambras
      visitado[i] = new bool[(columnas*2)-1];
    }
    for(nat i = 0; i < (filas*2)-1; ++i){
      for(nat j = 0; j < (columnas*2)-1; ++j){
        visitado[i][j] = 0;
      }
    }
    
    std::list<posicio> vacia;
    encontrarCamino(matriu, visitado, inicimatriu.first-1, inicimatriu.second-1, finalmatriu.first-1, finalmatriu.second-1, L, vacia, filas, columnas, inicimatriu.first-1, inicimatriu.second-1);


    if(vacia.size() != 0){
      std::list<posicio> RESULTAT;
      filresta = 0;
        for(nat i = 1; i <= (filas*2)-1; ++i){
          int resta = 0;
          for(nat j = 1; j <= (columnas*2)-1; ++j){
            
              if( (i%2 != 0) and (j%2 != 0)) {
                if(i == vacia.front().first+1 and j == vacia.front().second+1){
                  posicio POS = vacia.front();
                  vacia.pop_front();
                  if(vacia.size() > 0) vacia.pop_front();
                  POS.first = POS.first + 1 - filresta;
                  POS.second = POS.second + 1 - resta;
                  RESULTAT.push_back(POS);
                  
                }
                resta++;
              }
              
          }
          if(i%2 != 0) filresta++;
        }

        L = RESULTAT;
        /*if( (final.first != L.back().first or final.second != L.back().second) or (inici.first != L.front().first or inici.second != L.front().second) ){
          throw error(SenseSolucio);
        }*/
      }else throw error(SenseSolucio);


    }
  }

  