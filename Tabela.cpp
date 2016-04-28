//
//  Tabela.cpp
//  TabelaHash
//
//  Created by Eiji Adachi Medeiros Barbosa on 23/04/16.
//  Copyright (c) 2016 Eiji Adachi Medeiros Barbosa. All rights reserved.
//

#include "Tabela.h"
#include <iostream>
#include <cstring>
#include <stdlib.h>

long PreHash(Chave);
short Hash(long, int);
void Redimensionar(Tabela, int);
void Expandir(Tabela);
void Reduzir(Tabela);

int pegarIndiceDaChave(Tabela, Chave);


/*
    Função que insere um par (chave, item) na tabela.
 
    !!! Use as funções PreHash e Hash para achar o índice onde serão inseridos a chave e o item.
 
    !!! Caso a chave já exista na tabela, o item deve ser atualizado na tabela. !!!
 
    !!! Trate colisões por sondagem linear. !!!
 
    !!! Lembre-se que numa inserção podem existir posições marcadas como NULL e como ITEM_REMOVIDO e CHAVE_REMOVIDA. !!!
 
    !!! Faça redimensionamento dinâmico caso o fator de carga seja maior do que 0.5. Cheque se é necessário fazer redimensionamento após inserir com sucesso na tabela. !!!
 
 */
bool TAB_Inserir(Tabela tabela, Chave chave, Item item, bool checarTamanho)
{

    if(!(tabela && chave)) return false;

    int deslocamento = 0;

    do
    {

        int indice = (Hash(PreHash(chave), tabela->tamanho)+deslocamento) % tabela->tamanho;

        if(tabela->itens[indice] == NULL || tabela->chaves[indice] == CHAVE_REMOVIDA)//espaço vazio, pode inserir
        {
            tabela->itens[indice] = item;
            tabela->chaves[indice] = chave;
            tabela->qtdItens++;

            if(checarTamanho) TAB_ChecarTamanho(tabela, true);

            return true;
        }
        else if(strcmp(tabela->chaves[indice]->chave, chave->chave) == 0)//chave já existe, portanto, devo atualizar o valor do seu item
        {
            tabela->itens[indice] = item;
            tabela->chaves[indice] = chave;

            if(checarTamanho) TAB_ChecarTamanho(tabela, true);

            return true;
        }

        deslocamento++;

    }
    while(deslocamento < tabela->tamanho);

    return false;
}


/*

 Função que checa o fator de carga da tabela, a fim de fazer o seu redimensionamento.

*/
bool TAB_ChecarTamanho(Tabela tabela, bool aumentando){

    double alfa = ((double)tabela->qtdItens) / tabela->tamanho;

    if(alfa > 0.5 && aumentando)//redimensionar a tabela, dobrando o seu tamanho
    {
        int tamanho = tabela->tamanho;
        Item * itensAux = tabela->itens;
        Chave * chavesAux = tabela->chaves;

        tabela->tamanho = tabela->tamanho*2 + 1;
        tabela->qtdItens = 0;
        tabela->itens = new Item[tabela->tamanho];
        tabela->chaves = new Chave[tabela->tamanho];
        for(int i = 0; i < tabela->tamanho; i++){
            tabela->itens[i] = NULL;
            tabela->chaves[i] = NULL;
        }

        for(int i = 0; i < tamanho; i++){
            if(chavesAux[i] != NULL && chavesAux[i] != CHAVE_REMOVIDA){
                TAB_Inserir(tabela, chavesAux[i], itensAux[i], false);
            }

        }

        delete[] itensAux;
        delete[] chavesAux;

        itensAux = 0;
        chavesAux = 0;

        return true;
    }
    else if(alfa < 0.25 && !aumentando)//redimensionar a tabela, diminuindo seu tamanho pela metade
    {
        int tamanho = tabela->tamanho;
        Item * itensAux = tabela->itens;
        Chave * chavesAux = tabela->chaves;

        tabela->tamanho = tabela->tamanho/2 % 2 ? tabela->tamanho/2 : (tabela->tamanho/2) +1;

        tabela->qtdItens = 0;
        tabela->itens = new Item[tabela->tamanho];
        tabela->chaves = new Chave[tabela->tamanho];
        for(int i = 0; i < tabela->tamanho; i++){
            tabela->itens[i] = NULL;
            tabela->chaves[i] = NULL;
        }

        for(int i = 0; i < tamanho; i++){
            if(chavesAux[i] != NULL && chavesAux[i] != CHAVE_REMOVIDA){
                TAB_Inserir(tabela, chavesAux[i], itensAux[i], false);
            }

        }

        delete[] itensAux;
        delete[] chavesAux;

        itensAux = 0;
        chavesAux = 0;

        return true;
    }

    return false;
    
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

    int indice = pegarIndiceDaChave(tabela, chave);

    if(indice > -1){
        tabela->chaves[indice] = CHAVE_REMOVIDA;
        tabela->qtdItens--;

        TAB_ChecarTamanho(tabela, false);

        return true;
    }

    return false;
}

/*
 Função que busca um item na tabela a partir de uma chave.
 
 !!! Use as funções PreHash e Hash para achar o índice de onde está a chave. !!!
 
 !!! Lembre-se que numa busca podem existir posições marcadas como NULL e como ITEM_REMOVIDO e CHAVE_REMOVIDA. !!!
 
 !!! Trate colisões por sondagem linear. !!!
 
 */
Item TAB_Buscar(Tabela tabela, Chave chave)
{
    int indice = pegarIndiceDaChave(tabela, chave);

    return indice > -1 ? tabela->itens[indice] : NULL;
}


/*

 Função que retorna o valor do índice na tabela, dada uma chave qualquer.

*/
int pegarIndiceDaChave(Tabela tabela, Chave chave){

    if(!(tabela && chave))  return -1; 

    int deslocamento = 0;

    do
    {
        int indice = (Hash(PreHash(chave), tabela->tamanho)+deslocamento) % tabela->tamanho;

        if((tabela->chaves[indice] != CHAVE_REMOVIDA) && (tabela->chaves[indice] != NULL) && (strcmp(tabela->chaves[indice]->chave, chave->chave) == 0))
        {
            return indice;
        }

        deslocamento++;
    }
    while(deslocamento < tabela->tamanho);

    return -1;

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