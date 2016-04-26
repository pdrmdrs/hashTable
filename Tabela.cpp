//
//  Tabela.cpp
//  TabelaHash
//
//  Created by Eiji Adachi Medeiros Barbosa on 23/04/16.
//  Copyright (c) 2016 Eiji Adachi Medeiros Barbosa. All rights reserved.
//

#include "Tabela.h"
#include <iostream>

long PreHash(Chave);
short Hash(long, int);
void Redimensionar(Tabela, int);
void Expandir(Tabela);
void Reduzir(Tabela);

/*
    Função que insere um par (chave, item) na tabela.
 
    !!! Use as funções PreHash e Hash para achar o índice onde serão inseridos a chave e o item.
 
    !!! Caso a chave já exista na tabela, o item deve ser atualizado na tabela. !!!
 
    !!! Trate colisões por sondagem linear. !!!
 
    !!! Lembre-se que numa inserção podem existir posições marcadas como NULL e como ITEM_REMOVIDO e CHAVE_REMOVIDA. !!!
 
    !!! Faça redimensionamento dinâmico caso o fator de carga seja maior do que 0.5. Cheque se é necessário fazer redimensionamento após inserir com sucesso na tabela. !!!
 
 */
bool TAB_Inserir(Tabela tabela, Chave chave, Item item)
{
    std::cout << "\n\n !!! Função TAB_Inserir ainda não foi implementada. Implemente esta função para poder executar os testes corretamente. !!!\n\n" << std::endl;
    
    exit(-1);
}

/*
 Função que remove a chave da tabela, bem como seu respectivo item.
 
 !!! Use as funções PreHash e Hash para achar o índice de onde está a chave. !!!
 
 !!! Use as constantes ITEM_REMOVIDO e CHAVE_REMOVIDA para indicar as posições onde estavam a chave e o item removido. !!!
 
 !!! Trate colisões por sondagem linear. !!!
 
 !!! Faça redimensionamento dinâmico caso o fator de carga seja menor do que 0.25. Cheque se é necessário fazer redimensionamento após remover com sucesso da tabela. !!!
 
 */
bool TAB_Remover(Tabela tabela, Chave chave)
{
    std::cout << "\n\n !!! Função TAB_Remover ainda não foi implementada. Implemente esta função para poder executar os testes corretamente. !!!\n\n" << std::endl;
    
    exit(-1);
}

/*
 Função que busca um item na tabela a partir de uma chave.
 
 !!! Use as funções PreHash e Hash para achar o índice de onde está a chave. !!!
 
 !!! Lembre-se que numa busca podem existir posições marcadas como NULL e como ITEM_REMOVIDO e CHAVE_REMOVIDA. !!!
 
 !!! Trate colisões por sondagem linear. !!!
 
 */
Item TAB_Buscar(Tabela tabela, Chave chave)
{
    std::cout << "\n\n !!! Função TAB_Buscar ainda não foi implementada. Implemente esta função para poder executar os testes corretamente. !!!\n\n" << std::endl;
    
    exit(-1);
}

void TAB_Imprimir(Tabela tabela)
{
    for(int i = 0; i < tabela->tamanho; i++)
    {
        std::cout << "T[" << i << "] = ";
        Item item = tabela->itens[i];
        Chave chave = tabela->chaves[i];
        if( item == NULL )
        {
            std::cout << "NULO" << std::endl;
        }
        else if( item == ITEM_REMOVIDO )
        {
            std::cout << "REMOVIDO" << std::endl;
        }
        else
        {
            std::cout << chave->chave << ":" << item->conteudo << std::endl;
        }
    }
}

short Hash(long valor, int n)
{
    int indice = (valor & 0x7FFFFFFF) % n;
    return indice;
}

long PreHash(Chave chave)
{
    char *str = chave->chave;
    
    long hash = 0;
    
    int c;
    
    while ( (c = *str++) )
    {
        // Uma função hash bem melhor seria: hash = c + (hash << 6) + (hash << 16) - hash;
        // Estamos usando a mais simples abaixo para aumentar o número de colisões a fim de testar os métodos de tratamento de colisão
        hash += c;
    }
    
    return hash;
}

Tabela TAB_CriarTabela(int tamanhoInicial)
{
    if( tamanhoInicial <= 0 )
    {
        return NULL;
    }
    
    Tabela tabela = new tpTabela;
    
    tabela->tamanho = tamanhoInicial;
    tabela->qtdItens = 0;
    
    tabela->itens = new Item[tamanhoInicial];
    tabela->chaves = new Chave[tamanhoInicial];
    
    for(int i = 0; i < tabela->tamanho; i++)
    {
        tabela->itens[i] = NULL;
        tabela->chaves[i] = NULL;
    }
    
    return tabela;
}

void TAB_DestruirTabela(Tabela tabela)
{
    for(int i = 0; i < tabela->tamanho; i++)
    {
        Item item = tabela->itens[i];
        if( item != NULL && item != ITEM_REMOVIDO )
        {
            TAB_DestruirItem(item);
        }
        Chave chave = tabela->chaves[i];
        if( chave != NULL && chave != CHAVE_REMOVIDA )
        {
            TAB_DestruirChave(chave);
        }
    }
    
    delete tabela->itens;
    
    delete tabela->chaves;
    
    delete tabela;
}

void TAB_DestruirItem(Item item)
{
    delete item->conteudo;
    delete item;
}

void TAB_DestruirChave(Chave c)
{
    delete c->chave;
    delete c;
}

Item TAB_CriarItem(const char* c)
{
    Item item = new tpItem;
    item->conteudo = new char[strlen(c)+1];
    strcpy(item->conteudo, c);
    return item;
}

Chave TAB_CriarChave(const char* c)
{
    Chave chave = new tpChave;
    chave->chave = new char[strlen(c)+1];
    strcpy(chave->chave, c);
    return chave;
}