#include "teseus.hpp"

  void MATHLAB(const laberint & M, bool** matr, int i, int j, int filresta, int resta){
    posicio pos(i,j);
    cambra c = M(pos);
    //std::cout<<"hola"<<c.porta_oberta(paret::NORD)<<std::endl;
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
    //std::cout<<"buenas: "<<i <<"-"<<j<<std::endl;
    return(i >= 0 and i < (filas*2)-1 and j >= 0 and j < (columnas*2)-1 and matr[i][j] == 1 and not visitado[i][j]);
  }

  void encontrarCamino(bool** matr, bool** visitado, int i, int j, int x, int y, std::list<posicio> & L_min, std::list<posicio> & L, int filas, int columnas){
    if( i == x and j == y){
      posicio pos(i,j);
      L.push_back(pos);
      if(L_min.size() > L.size()){
        L_min = L;
      }else L_min = L;
      return;
    }

    visitado[i][j] = true;
    //SUD
    if(caminable(matr, visitado, i+1, j, filas, columnas)){
      //std::cout<<"entro sud"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      encontrarCamino(matr, visitado, i+1, j, x, y, L_min, L, filas, columnas);
    }
    //E
    if(caminable(matr, visitado, i, j+1, filas, columnas)){
      //std::cout<<"entro este"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      encontrarCamino(matr, visitado, i, j+1, x, y, L_min, L, filas, columnas);
    }
    //N
    if(caminable(matr, visitado, i-1, j, filas, columnas)){
      //std::cout<<"entro sunort"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      encontrarCamino(matr, visitado, i-1, j, x, y, L_min, L, filas, columnas);
    }
    //O
    if(caminable(matr, visitado, i, j-1, filas, columnas)){
      //std::cout<<"entro oest"<<std::endl;
      posicio pos(i,j);
      L.push_back(pos);
      encontrarCamino(matr, visitado, i, j-1, x, y, L_min, L, filas, columnas);
    }

  visitado[i][j] = false;

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

    //std::cout<<"Matriz"<<std::endl; 
    for(nat i = 1; i <= (filas*2)-1; ++i){
      for(nat j = 1; j <= (columnas*2)-1; ++j){
        //std::cout<<matriu[i-1][j-1]<<" ";
      }
      //std::cout<<std::endl;
    }
    //std::cout<<"Holaaa:"<<sizeof(matriu)<<"D: "<<sizeof(matriu[0][0])<<"DD: "<<sizeof(matriu)/sizeof(matriu[0][0])<<std::endl;
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
    //std::cout<<"IMF: "<<inicimatriu.first<<"IMS: "<<inicimatriu.second<<std::endl;
    //std::cout<<"FMF: "<<finalmatriu.first<<"FMS: "<<finalmatriu.second<<std::endl;
    encontrarCamino(matriu, visitado, inicimatriu.first-1, inicimatriu.second-1, finalmatriu.first-1, finalmatriu.second-1, L, vacia, filas, columnas);

    std::list<posicio> RESULTAT;
    filresta = 0;
      for(nat i = 1; i <= (filas*2)-1; ++i){
        int resta = 0;
        for(nat j = 1; j <= (columnas*2)-1; ++j){
          
            if( (i%2 != 0 /*and i == L.front().first*/) and (j%2 != 0 /*and j == L.front().second*/)) {
              if(i == L.front().first+1 and j == L.front().second+1){
                //std::cout<<"RUST: "<<L.front().first<<" - "<<L.front().second<<std::endl;
                posicio POS = L.front();
                L.pop_front();
                if(L.size() > 0) L.pop_front();
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
    }
  }

  