//
//  main.cpp
//  TabelaHash
//
//  Created by Eiji Adachi Medeiros Barbosa on 23/04/16.
//  Copyright (c) 2016 Eiji Adachi Medeiros Barbosa. All rights reserved.
//
#include "TesteTabela.h"
#include <iostream>

using namespace std;

int main(int argc, const char * argv[]) {
    
    bool passouTeste = testar_Criar();
    
    if(passouTeste)
    {
        passouTeste = testar_Inserir();
    }
    if(passouTeste)
    {
        passouTeste = testar_Remover();
    }
    if(passouTeste)
    {
        passouTeste = testar_Buscar();
    }
    if(passouTeste)
    {
        passouTeste = testar_Tudo();
    }
    
    if(passouTeste)
    {
        cout << "\nTodos os testes rodaram sem falhas." << endl;
    }
    else
    {
        cout << "\nForam encontradas falhas na implementação da Tabela. Ver mensagens de erro acima." << endl;
    }
    
    return 0;
}
