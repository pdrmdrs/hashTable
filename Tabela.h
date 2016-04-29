//
//  Tabela.h
//  TabelaHash
//
//  Created by Eiji Adachi Medeiros Barbosa on 23/04/16.
//  Copyright (c) 2016 Eiji Adachi Medeiros Barbosa. All rights reserved.
//

#ifndef __TabelaHash__Tabela__
#define __TabelaHash__Tabela__

typedef struct tpItem
{
    char * conteudo;
} * Item;

typedef struct tpChave
{
    char *chave;
} * Chave;

typedef enum {
	linear,
    quadratica,
	doubleHashing
} tpSondagem ; 

typedef struct tpTabela
{
    Item * itens;
    Chave* chaves;
    int tamanho;
    int qtdItens;
    tpSondagem sondagem;
} * Tabela;

/* INÍCIO: Funções já implementadas */
Tabela TAB_CriarTabela(int, tpSondagem sondagem = quadratica);
void TAB_DestruirTabela(Tabela);
Chave TAB_CriarChave(const char*);
Item TAB_CriarItem(const char*);
void TAB_DestruirItem(Item);
void TAB_DestruirChave(Chave);
void TAB_Imprimir(Tabela);
 /* FIM: Funções já implementadas */


/* INÍCIO: Funções que devem ser implementadas */
bool TAB_Inserir(Tabela, Chave, Item, bool checarTamanho = true);
bool TAB_Remover(Tabela, Chave);
Item TAB_Buscar(Tabela, Chave);

bool TAB_ChecarTamanho(Tabela, bool aumentando);
/* FIM: Funções que devem ser implementadas */

/* Constantes para serem usadas na função de remoção */
const Item ITEM_REMOVIDO = ((Item)(-11));
const Chave CHAVE_REMOVIDA = ((Chave)(-17));

#endif /* defined(__TabelaHash__Tabela__) */
