//
//  TesteTabela.cpp
//  TabelaHash
//
//  Created by Eiji Adachi Medeiros Barbosa on 24/04/16.
//  Copyright (c) 2016 Eiji Adachi Medeiros Barbosa. All rights reserved.
//

#include "TesteTabela.h"
#include "Tabela.h"
#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

bool testar_Criar()
{
    cout << "INÍCIO: Teste Criar" << endl;
    
    Tabela tabela = TAB_CriarTabela(0);
    
    if( tabela != NULL )
    {
        cout << "\t*ERRO - Teste Criar: Ao receber parâmetro tamanho <= 0 deve retornar nulo." << endl;
        return false;
        
    }

    bool resultado = true;

    int tamanhoDesejado = 7;
    
    tabela = TAB_CriarTabela(tamanhoDesejado);
    
    if( tabela == NULL )
    {
        cout << "\t*ERRO - Teste Criar: Tabela retornada é nula." << endl;
        resultado = false;
    }
    else if( tabela->tamanho != tamanhoDesejado )
    {
        cout << "\t*ERRO - Teste Criar: Tabela deveria ter tamanho igual a " << tamanhoDesejado << ", mas foi criada com tamanho igual a " << tabela->tamanho << endl;
        resultado = false;
    }
    else if( tabela->qtdItens != 0 )
    {
        cout << "\t*ERRO - Teste Criar: Tabela deveria ter quantidade de elementos igual a 0, mas foi criada com tamanho igual a " << tabela->tamanho << endl;
        resultado = false;
    }
    else if( tabela->itens == NULL )
    {
        cout << "\t*ERRO - Teste Criar: Tabela foi criada com array de itens igual a nulo." << endl;
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    cout << "FIM: Teste Criar" << endl;
    
    return resultado;
}

bool testar_Buscar_CasoNormal()
{
    Tabela tabela = TAB_CriarTabela(13);
    
    char chavesStr[5][10] = {"chave", "echav", "vecha", "avech", "havec"};
    char conteudosStr[5][10] = {"C1", "C2", "C3", "C4", "C5"};
    
    for( int i = 0; i < 5; i++)
    {
        Item it = TAB_CriarItem((char*)conteudosStr[i]);
        Chave ch = TAB_CriarChave((char*)chavesStr[i]);
        
        TAB_Inserir(tabela, ch, it);
    }
    
    Item item = TAB_CriarItem((char*)"Conteudo");
    Chave chave = TAB_CriarChave((char*)"acehv");
    
    TAB_Inserir(tabela, chave, item);
    
    Item retornado = TAB_Buscar(tabela, chave);
    
    bool resultado = true;
    
    if( retornado == NULL )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Normal: Buscou por chave igual a '" << chave->chave << ", mas retornou NULO." << endl;
        
        resultado = false;
    }
    else if( retornado != item )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Normal: Buscou por chave '" << chave->chave << "', mas não retornou item esperado. Esperado era: " << chave->chave << ":" << item->conteudo << "'." << endl;
        
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return resultado;
}

bool testar_Buscar_CasoExcepcional()
{
    cout << "\t  - Caso Excpecional - Tentando buscar numa tabela nula" << endl;
    Item item = TAB_Buscar(NULL, NULL);
    
    bool resultado = true;
    
    if( item != NULL )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Excepcional: Função TAB_Buscar não deveria aceitar tabela de entrada nula." << endl;
        resultado = false;
    }
    
    Tabela tabela = TAB_CriarTabela(17);
    
    cout << "\t  - Caso Excpecional - Tentando buscar uma chave nula numa tabela" << endl;
    item = TAB_Buscar(tabela, NULL);
    
    if( item != NULL )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Excepcional: Função TAB_Buscar não deveria aceitar chave de entrada nula." << endl;
        resultado = false;
    }
    
    Chave chave = TAB_CriarChave((char*)"acehv");
    
    item = TAB_Buscar(tabela, chave);
    
    cout << "\t  - Caso Excpecional - Tentando buscar numa tabela vazia" << endl;
    if( item != NULL )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Excepcional: Busca numa tabela vazia retornou item diferente de nulo." << endl;
        resultado = false;
    }
    
    char chavesStr[5][10] = {"chave", "echav", "vecha", "avech", "havec"};
    char conteudosStr[5][10] = {"C1", "C2", "C3", "C4", "C5"};
    
    for( int i = 0; i < 5; i++)
    {
        Item it = TAB_CriarItem((char*)conteudosStr[i]);
        Chave ch = TAB_CriarChave((char*)chavesStr[i]);
        
        TAB_Inserir(tabela, ch, it);
    }
    
    
    item = TAB_Buscar(tabela, chave);
    
    cout << "\t  - Caso Excpecional - Tentando buscar uma chave que não existe na tabela" << endl;
    if( item != NULL )
    {
        cout << "\t*ERRO - Teste Buscar - Caso Excepcional: Busca por uma chave que não existe na tabela retornou item diferente de nulo. Chave buscada: '" << chave->chave << "'." << endl;
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return resultado;
}

bool testar_Buscar_ComRemocoes()
{
    Tabela tabela = TAB_CriarTabela(17);
    
    char chavesStr[5][10] = {"chave", "echav", "vecha", "avech", "havec"};
    char conteudosStr[5][10] = {"C1", "C2", "C3", "C4", "C5"};
    
    for( int i = 0; i < 5; i++)
    {
        Item it = TAB_CriarItem((char*)conteudosStr[i]);
        Chave ch = TAB_CriarChave((char*)chavesStr[i]);
        
        TAB_Inserir(tabela, ch, it);
        
        if(i%2==1)
        {
            TAB_Remover(tabela, ch);
        }
    }
    
    Item item = TAB_CriarItem((char*)"Conteudo");
    Chave chave = TAB_CriarChave((char*)"acehv");
    
    TAB_Inserir(tabela, chave, item);
    
    item = TAB_Buscar(tabela, chave);
    
    bool resultado = true;
    
    if( item == NULL )
    {
        cout << "\t*ERRO - Teste Buscar - Com remoções: Após algumas remoções, busca por uma chave que existe na tabela retornou item nulo. Chave buscada: '" << chave->chave << "'." << endl;
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return resultado;
}

bool testar_Buscar()
{
    cout << "\nINÍCIO: Testes Buscar" << endl;
    
    bool resultado = true;
    
    cout << "\tTeste Buscar - Caso Normal" << endl;
    resultado = testar_Buscar_CasoNormal();
    
    if(resultado)
    {
        cout << "\tTeste Buscar - Caso Excepcional" << endl;
        resultado = testar_Buscar_CasoExcepcional();
    }
    if(resultado)
    {
        cout << "\tTeste Buscar - Com Remoções" << endl;
        resultado = testar_Buscar_ComRemocoes();
    }
    
    cout << "FIM: Testes Buscar" << endl;
    
    return resultado;
}

bool testar_Inserir_CasoNormal()
{
    int tamanho = 17;
    Tabela tabela = TAB_CriarTabela(tamanho);
    
    bool inseriu = true;
    
    for(int i = 0; i < tamanho/2 && inseriu; i++)
    {
        char* chaveStr = new char[20];
        // Estou criando chaves diferentes mas que darão colisão
        if( i%3==0 )
        {
            sprintf(chaveStr, "chave-%d", i);
        }
        else if( i%3==1 )
        {
            sprintf(chaveStr, "cveha-%d", i-1);
        }
        else
        {
            sprintf(chaveStr, "vecha-%d", i-2);
        }
        
        char* conteudo = new char[20];
        sprintf(conteudo, "conteudo-%d", i);
        
        Chave chave = TAB_CriarChave(chaveStr);
        delete chaveStr;
        
        Item item = TAB_CriarItem(conteudo);
        delete conteudo;
        
        int tamanhoAntes = tabela->tamanho;
        int qtdElementoAntes = tabela->qtdItens;
        
        inseriu = TAB_Inserir(tabela, chave, item);
        
        // Verifica se o elemento está de fato guardado na tabela
        bool achou = false;
        for(int i = 0; i < tabela->tamanho; i++)
        {
            if( tabela->itens[i] == item && tabela->chaves[i] == chave )
            {
                achou = true;
                break;
            }
        }
        if(!achou)
        {
            cout << "\t*ERRO - Teste Inserir_CasoNormal: Não foram encontradas na tabela o Item e/ou a Chave passada como parâmetros." << endl;
            inseriu = false;
            break;
        }
        
        int tamanhoDepois = tabela->tamanho;
        int qtdElementoDepois = tabela->qtdItens;
        
        if( tamanhoAntes != tamanhoDepois )
        {
            cout << "\t*ERRO - Teste Inserir_CasoNormal: Tamanho foi modificado incorretamente. Tamanho só pode ser modificado quando ocorre redimensionamento." << endl;
            inseriu = false;
            break;
        }
        if( qtdElementoAntes != qtdElementoDepois-1 )
        {
            cout << "\t*ERRO - Teste Inserir_CasoNormal: Quantidade de elementos não foi incrementada corretamente." << endl;
            inseriu = false;
            break;
        }
    }
    
    TAB_DestruirTabela(tabela);
    
    return inseriu;
}

bool testar_Inserir_CasoExcepcional()
{
    int tamanho = 17;
    
    cout << "\t  - Caso Excpecional - Tentando inserir numa tabela nula" << endl;
    bool inseriu = TAB_Inserir(NULL, NULL, NULL);
    
    if( inseriu )
    {
        cout << "\t*ERRO - Teste Inserir_CasoExcepcional: Função TAB_Inserir não deveria aceitar tabela nula como entrada." << endl;
    }
    
    Tabela tabela = TAB_CriarTabela(tamanho);

    cout << "\t  - Caso Excpecional - Tentando inserir item e chave nulos numa tabela" << endl;
    inseriu = TAB_Inserir(tabela, NULL, NULL);
    
    if( inseriu )
    {
        cout << "\t*ERRO - Teste Inserir_CasoExcepcional: Não deveria ser possível inserir item com chave nula." << endl;
    }
    
    TAB_DestruirTabela(tabela);
    
    return !inseriu;
}

bool testar_Inserir_Redimensionamento()
{
    int tamanho = 1117;
    
    Tabela tabela = TAB_CriarTabela(tamanho);
    
    vector<Item> itensInseridos;
    vector<Chave> chavesInseridas;
    
    int i = 0;
    do
    {
        char* chaveStr = new char[20];
        sprintf(chaveStr, "chave-%d", i);
        
        char* conteudo = new char[20];
        sprintf(conteudo, "conteudo-%d", i);
        
        Chave chave = TAB_CriarChave(chaveStr);
        delete chaveStr;
        
        Item item = TAB_CriarItem(conteudo);
        delete conteudo;
        
        chavesInseridas.push_back(chave);
        itensInseridos.push_back(item);
        
        TAB_Inserir(tabela, chave, item);
        i++;
    } while( (float)(tabela->qtdItens+1) / tabela->tamanho <= 0.5f );
    
    
    // Quando chegar aqui, está exatamente antes de fazer o redimensionamento
    int tamanhoAntes = tabela->tamanho;
    
    char* chaveNovaStr = new char[20];
    sprintf(chaveNovaStr, "ChaveNova");
    Chave chaveNova = TAB_CriarChave(chaveNovaStr);
    chavesInseridas.push_back(chaveNova);
    delete chaveNovaStr;
    
    char* itemNovoStr = new char[20];
    sprintf(itemNovoStr, "ConteudoNovo");
    Item itemNovo = TAB_CriarItem(itemNovoStr);
    itensInseridos.push_back(itemNovo);
    delete itemNovoStr;
    
    TAB_Inserir(tabela, chaveNova, itemNovo);
    int tamanhoDepois = tabela->tamanho;
    
    if( 1 + 2*tamanhoAntes != tamanhoDepois )
    {
        cout << "\t*ERRO - Teste Inserir_Redimensionamento: Tabela não foi redimensionada corretamente. Tamanho antes de inserir = " << tamanhoAntes << ". Tamnho depois de inserir = " << tamanhoDepois << ". Esperado após inserir era: " << 1+2*tamanhoAntes << endl;

        return false;
    }
    
    // Verifica se todos elementos que estavam antes do redimensionamento continuam na tabela
    for(Chave chave : chavesInseridas)
    {
        bool achou = false;
        for(int i = 0; i < tabela->tamanho; i++)
        {
            Chave c = tabela->chaves[i];
            if(c!=NULL && c!=CHAVE_REMOVIDA)
            {
                if( strcmp(c->chave, chave->chave)==0 )
                {
                    achou = true;
                    break;
                }
            }
        }
        if(!achou)
        {
            cout << "\t*ERRO - Teste Inserir_Redimensionamento: O item com chave igual a "<< chave->chave << " estava na tabela antes do redimensionamento, mas não se encontra após." << endl;
            TAB_DestruirTabela(tabela);
                return false;
            break;
        }
    }
    
    // Verifica se todos elementos que estão na tabela após o redimensionamento já estavam na tabela
    for(int i = 0; i < tabela->tamanho; i++)
    {
        Chave c = tabela->chaves[i];
        if(c!=NULL && c!=CHAVE_REMOVIDA)
        {
            bool achou = false;
            for(Chave chave : chavesInseridas)
            {
                if( strcmp(c->chave, chave->chave)==0 )
                {
                    achou = true;
                    break;
                }
            }
            if(!achou)
            {
                cout << "\t*ERRO - Teste Inserir_Redimensionamento: Item com chave igual a "<< c->chave << " está na tabela após o redimensionamento, mas não se encontrava antes." << endl;
                TAB_DestruirTabela(tabela);
                return false;
            }
        }
    }
    
    TAB_DestruirTabela(tabela);
    
    return true;
}

bool testar_Inserir_Atualizar()
{
    Tabela tabela = TAB_CriarTabela(7);
    
    char* cStr = new char[20];
    sprintf(cStr, "chave");
    Chave c = TAB_CriarChave(cStr);
    delete cStr;
    
    char* item1Str = new char[20];
    sprintf(item1Str, "ConteudoInicial");
    Item item1 = TAB_CriarItem(item1Str);
    delete item1Str;
    
    TAB_Inserir(tabela, c, item1);
    
    char* item2Str = new char[20];
    sprintf(item2Str, "ConteudoAtualizado");
    Item item2 = TAB_CriarItem(item2Str);
    delete item2Str;
    
    TAB_Inserir(tabela, c, item2);
    
    bool resultado = true;
    
    if( tabela->qtdItens == 1 )
    {
        for(int i = 0; i < tabela->tamanho; i++)
        {
            Item item = tabela->itens[i];
            if( item != NULL && strcmp(item->conteudo, item2->conteudo)!=0)
            {
                cout << "\t*ERRO - Teste Inserir_Atualizar: Ao inserir dois itens com mesma chave, o valor do segundo deve sobrescrever valor do primeiro. Neste teste, dois elementos com mesma chave foram inseridos na tabela. O esperado era que o conteúdo do item na tabela fosse igual a '" << item2->conteudo << "', mas valor encontrado foi igual a '" << item->conteudo << "'." << endl;
                resultado = false;
                break;
            }
        }
    }
    else
    {
        cout << "\t*ERRO - Teste Inserir_Atualizar: Ao inserir dois itens com mesma chave, o valor do segundo deve sobrescrever valor do primeiro. Neste teste, dois elementos com mesma chave foram inseridos na tabela; o esperado era uma tabela com 1 item, mas a tabela ficou com " << tabela->qtdItens << " itens." << endl;
        TAB_Imprimir(tabela);
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return resultado;
}

bool testar_Inserir_Colisao()
{
    Tabela tabela = TAB_CriarTabela(17);
    Chave c1 = TAB_CriarChave("abba");
    Item i1 = TAB_CriarItem("conteudo1");
    
    Chave c2 = TAB_CriarChave("bbaa");
    Item i2 = TAB_CriarItem("conteudo2");
    
    TAB_Inserir(tabela, c1, i1);
    TAB_Inserir(tabela, c2, i2);
    
    bool achou1 = false;
    for(int x = 0; x < tabela->tamanho; x++)
    {
        Chave c = tabela->chaves[x];
        
        if( c!=NULL && strcmp(c->chave, c1->chave)==0 )
        {
            achou1 = true;
        }
    }
    
    bool achou2 = false;
    for(int x = 0; x < tabela->tamanho; x++)
    {
        Chave c = tabela->chaves[x];
        
        if( c!=NULL && strcmp(c->chave, c2->chave)==0 )
        {
            achou2 = true;
        }
    }
    
    bool resultado = true;
    if( (achou1 && !achou2)||(!achou1 && achou2) )
    {
        cout << "\t*ERRO - Teste Inserir_Colisao: Duas chaves que colidem foram inseridas, mas apenas uma foi encontrada na tabela. Provavelmente uma sobrescreveu a outra. Rever tratamento de colisão." << endl;
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return resultado;
}

bool testar_Inserir()
{
    cout << "\nINÍCIO: Testes Inserir" << endl;
    
    bool resultado = true;
    
    cout << "\tTeste Inserir - Caso Normal" << endl;
    resultado = testar_Inserir_CasoNormal();
    
    if(resultado)
    {
        cout << "\tTeste Inserir - Colisão" << endl;
        resultado = testar_Inserir_Colisao();
    }
    if(resultado)
    {
        cout << "\tTeste Inserir - Caso Excepcional" << endl;
        resultado = testar_Inserir_CasoExcepcional();
    }
    if(resultado)
    {
        cout << "\tTeste Inserir - Redimensionamento" << endl;
        resultado = testar_Inserir_Redimensionamento();
    }
    if(resultado)
    {
        cout << "\tTeste Inserir - Caso Atualizar" << endl;
        resultado = testar_Inserir_Atualizar();
    }
    
    cout << "FIM: Testes Inserir" << endl;
    
    return resultado;
}

bool testar_Remover_CasoNormal()
{
    Tabela tabela = TAB_CriarTabela(17);
    
    Chave c1 = TAB_CriarChave("abba");
    Item i1 = TAB_CriarItem("conteudo1");
    
    char c2Str[] = "cdefg";
    Chave c2 = TAB_CriarChave(c2Str);
    Item i2 = TAB_CriarItem("conteudo2");
    
    Chave c3 = TAB_CriarChave("baee");
    Item i3 = TAB_CriarItem("conteudo3");
    
    TAB_Inserir(tabela, c1, i1);
    TAB_Inserir(tabela, c2, i2);
    TAB_Inserir(tabela, c3, i3);
    
    int qtdAntes = tabela->qtdItens;
    
    TAB_Remover(tabela, c2);
    
    bool resultado = true;
    
    int qtdDepois = tabela->qtdItens;
    
    if( qtdAntes - 1 != qtdDepois )
    {
        cout << "\t*ERRO - Teste Remover_CasoNormal: Não decrementou corretamente a quantidade de itens durante a remoção." << endl;
        resultado = false;
    }
    
    bool achou = false;
    for(int x = 0; x < tabela->tamanho; x++)
    {
        Chave c = tabela->chaves[x];
        
        if( c!=NULL && c!= CHAVE_REMOVIDA && strcmp(c->chave, c2Str)==0 )
        {
            achou = true;
            break;
        }
    }

    if(achou)
    {
        cout << "\t*ERRO - Teste Remover_CasoNormal: Remoção não foi feita corretamente, pois o item passado como parâmetro ainda foi encontrado na tabela." << endl;
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);

    return resultado;
}

bool testar_Remover_Sucessivas()
{
    int tamanho = 177;
    
    Tabela tabela = TAB_CriarTabela(tamanho);
    
    bool removeu = false;
    
    // Essas quantidades evitam que a tabela sofra um redimensionamento
    int qtdInserido = tabela->tamanho/2;
    int qtdRemovido = qtdInserido - 1 - tabela->tamanho/4;
    
    // Inicialização da tabela
    for(int i = 0; i < qtdInserido; i++)
    {
        char* chaveStr = new char[20];
        
        // Forçando colisões
        if( i%3==0 )
        {
            sprintf(chaveStr, "chave-%d", i);
        }
        else if( i%3==1 )
        {
            sprintf(chaveStr, "cveha-%d", i-1);
        }
        else
        {
            sprintf(chaveStr, "vecha-%d", i-2);
        }
        
        Chave chave = TAB_CriarChave(chaveStr);
        
        Item item = TAB_CriarItem("Conteudo");
        
        TAB_Inserir(tabela, chave, item);
        
        delete chaveStr;
    }
    
    // Série de remoções com sucesso
    for(int i = 0; i < qtdRemovido; i++)
    {
        char* chaveStr = new char[20];
        if( i%3==0 )
        {
            sprintf(chaveStr, "chave-%d", i);
        }
        else if( i%3==1 )
        {
            sprintf(chaveStr, "cveha-%d", i-1);
        }
        else
        {
            sprintf(chaveStr, "vecha-%d", i-2);
        }
        
        Chave chave = TAB_CriarChave(chaveStr);
        
        delete chaveStr;
        
        int qtdAntes = tabela->qtdItens;
        
        removeu = TAB_Remover(tabela, chave);
        
        if(!removeu)
        {
            cout << "\t*ERRO - Teste Remover_Sucessivas: Não removeu corretamente item com chave igual a : " << chave->chave << "." << endl;
            removeu = false;

            //TAB_Imprimir(tabela);

            break;
        }
        
        int qtdDepois = tabela->qtdItens;
        
        if( qtdAntes - 1 != qtdDepois )
        {
            cout << "\t*ERRO - Teste Remover_Sucessivas: Não decrementou corretamente a quantidade de itens durante a remoção." << endl;
            removeu = false;
            break;
        }
    }
    
    int qtdEsperada = qtdInserido-qtdRemovido;
    
    if( tabela->qtdItens != qtdEsperada )
    {
        cout << "\t*ERRO - Teste Remover_Sucessivas: Ao todo, foram inseridos " << qtdInserido << " itens na tabela e removidos " << qtdRemovido << " itens. No fim, eram esperados " << qtdEsperada << ", mas restaram: " << tabela->qtdItens << "." << endl;
        removeu = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return removeu;
}

bool testar_Remover_CasoExcepcional()
{
    cout << "\t  - Caso Excpecional - Tentando remover de uma tabela nula" << endl;
    bool removeu = TAB_Remover(NULL, NULL);
    
    if( removeu )
    {
        cout << "\t*ERRO - Teste Remover_CasoExcepcional: Função TAB_Remover não deveria poder receber tabela nula como entrada." << endl;
        return false;
    }
    
    int tamanho = 177;
    
    Tabela tabela = TAB_CriarTabela(tamanho);
    
    cout << "\t  - Caso Excpecional - Tentando remover uma chave nula de uma tabela" << endl;
    removeu = TAB_Remover(tabela, NULL);
    if( removeu )
    {
        cout << "\t*ERRO - Teste Remover_CasoExcepcional: Função TAB_Remover não deveria poder receber chave nula como entrada." << endl;
        return false;
    }
    
    // Essas quantidades evitam que a tabela sofra um redimensionamento
    int qtdInserido = tabela->tamanho/2;
    int qtdRemovido = qtdInserido - 1 - tabela->tamanho/4;
    
    
    // Inicialização da tabela
    for(int i = 0; i < qtdInserido; i++)
    {
        char* chaveStr = new char[20];
        
        // Forçando colisões
        if( i%3==0 )
        {
            sprintf(chaveStr, "chave-%d", i);
        }
        else if( i%3==1 )
        {
            sprintf(chaveStr, "cveha-%d", i-1);
        }
        else
        {
            sprintf(chaveStr, "vecha-%d", i-2);
        }
        
        Chave chave = TAB_CriarChave(chaveStr);
        
        Item item = TAB_CriarItem("Conteudo");
        
        TAB_Inserir(tabela, chave, item);
        
        delete chaveStr;
    }
    
    cout << "\t  - Caso Excpecional - Tentando remover uma chave que não existe na tabela" << endl;
    removeu = true;
    for(int i = 0; i < qtdRemovido; i++)
    {
        if( i%2==0 )
        {
            Chave chave = TAB_CriarChave("INSUCESSO");
            
            if( TAB_Remover(tabela, chave) )
            {
                cout << "\t*ERRO - Teste Remover_CasoExcepcional: Retornou verdadeiro para uma remoção de uma chave que não existe na Tabela: " << chave->chave << "." << endl;
                removeu = false;
                break;
            }
        }
        else
        {
            char* chaveStr = new char[20];
            
            if( i%3==0 )
            {
                sprintf(chaveStr, "chave-%d", i);
            }
            else if( i%3==1 )
            {
                sprintf(chaveStr, "cveha-%d", i-1);
            }
            else
            {
                sprintf(chaveStr, "vecha-%d", i-2);
            }
            
            // Aqui remove com sucesso
            Chave chave = TAB_CriarChave(chaveStr);
            
            delete chaveStr;
            
            if( !TAB_Remover(tabela, chave) )
            {
                cout << "\t*ERRO - Teste Remover_CasoExcepcional: Retornou falso para uma remoção de uma chave que existe na Tabela: " << chave->chave << "." << endl;
                removeu = false;
                break;
            }
        }
    }
    
    TAB_DestruirTabela(tabela);
    
    return removeu;
}

bool testar_Remover_Redimensionamento()
{
    bool removeu = true;
    
    int tamanho = 177;
    
    Tabela tabela = TAB_CriarTabela(tamanho);
    
    // Essas quantidades evitam que a tabela sofra um redimensionamento
    int qtdInserido = tabela->tamanho/2;
    int qtdRemovido = qtdInserido - 1 - tabela->tamanho/4;
    
    // Inicialização da tabela
    for(int i = 0; i < qtdInserido; i++)
    {
        char* chaveStr = new char[20];
        
        // Forçando colisões
        if( i%3==0 )
        {
            sprintf(chaveStr, "chave-%d", i);
        }
        else if( i%3==1 )
        {
            sprintf(chaveStr, "cveha-%d", i-1);
        }
        else
        {
            sprintf(chaveStr, "vecha-%d", i-2);
        }
        
        Chave chave = TAB_CriarChave(chaveStr);
        
        Item item = TAB_CriarItem("Conteudo");
        
        TAB_Inserir(tabela, chave, item);
        
        delete chaveStr;
    }
    
    for(int i = 0; i < qtdRemovido; i++)
    {
        char* chaveStr = new char[20];
        
        if( i%3==0 )
        {
            sprintf(chaveStr, "chave-%d", i);
        }
        else if( i%3==1 )
        {
            sprintf(chaveStr, "cveha-%d", i-1);
        }
        else
        {
            sprintf(chaveStr, "vecha-%d", i-2);
        }
        
        Chave chave = TAB_CriarChave(chaveStr);
        
        delete chaveStr;
        
        removeu = TAB_Remover(tabela, chave);
        
        if(!removeu)
        {
            cout << "\t*ERRO - Teste Remover_Redimensionamento: Não removeu corretamente item com chave igual a: " << chaveStr << endl;
            removeu = false;
            break;
        }
    }
    
    // Ao chegar aqui a Tabela está prestes a sofrer uma redução no seu tamanho, basta mais uma remoção
    // Escolhe uma chave qualquer para remover item
    Chave chave = NULL;
    
    for(int i = 0; i < tabela->tamanho; i++)
    {
        chave = tabela->chaves[i];
        if(chave!=NULL && chave!=CHAVE_REMOVIDA)
        {
            break;
        }
    }
    
    int tamanhoAntes = tabela->tamanho;
    
    removeu = TAB_Remover(tabela, chave);
    
    int tamanhoDepois = tabela->tamanho;
    
    if( 1+tamanhoAntes/2 != tamanhoDepois )
    {
        cout << "\t*ERRO - Teste Remover_Redimensionamento: Tabela não foi redimensionada corretamente. Tamanho antes de remover = " << tamanhoAntes << ". Tamanho depois de remover = " << tamanhoDepois << ". Esperado após inserir era: " << 1+tamanho/2 << endl;
        removeu = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return removeu;
}

bool testar_Remover_Colisao()
{
    Tabela tabela = TAB_CriarTabela(17);
    Chave c1 = TAB_CriarChave("abba");
    Item i1 = TAB_CriarItem("conteudo1");
    
    Chave c2 = TAB_CriarChave("bbaa");
    Item i2 = TAB_CriarItem("conteudo2");
    
    Chave c3 = TAB_CriarChave("baba");
    Item i3 = TAB_CriarItem("conteudo3");
    
    TAB_Inserir(tabela, c1, i1);
    TAB_Inserir(tabela, c2, i2);
    TAB_Inserir(tabela, c3, i3);
    
    TAB_Remover(tabela, c2);
    
    bool achou1 = false;
    for(int x = 0; x < tabela->tamanho; x++)
    {
        Chave c = tabela->chaves[x];
        
        if( c!=NULL && c!= CHAVE_REMOVIDA && strcmp(c->chave, c1->chave)==0 )
        {
            achou1 = true;
        }
    }
    
    bool achou3 = false;
    for(int x = 0; x < tabela->tamanho; x++)
    {
        Chave c = tabela->chaves[x];
        
        if( c!=NULL && c!= CHAVE_REMOVIDA && strcmp(c->chave, c3->chave)==0 )
        {
            achou3 = true;
        }
    }
    
    bool resultado = true;
    if( (achou1 && !achou3)||(!achou1 && achou3) )
    {
        cout << "\t*ERRO - Teste Remover_Colisao: Três chaves que colidem foram inseridas e uma foi removida, mas foi removida a chave errada. Rever tratamento de colisão." << endl;
        resultado = false;
    }
    
    TAB_DestruirTabela(tabela);
    
    return resultado;
}

bool testar_Remover()
{
    cout << "\nINÍCIO: Testes Remover" << endl;
    
    bool resultado = true;
    
    cout << "\tTeste Remover - Caso Normal" << endl;
    resultado = testar_Remover_CasoNormal();
    
    if(resultado)
    {
        cout << "\tTeste Remover - Sucessivas" << endl;
        resultado = testar_Remover_Sucessivas();
    }
    if(resultado)
    {
        cout << "\tTeste Remover - Colisão" << endl;
        resultado = testar_Remover_Colisao();
    }
    if(resultado)
    {
        cout << "\tTeste Remover - Caso Excepcional" << endl;
        resultado = testar_Remover_CasoExcepcional();
    }
    if(resultado)
    {
        cout << "\tTeste Remover - Redimensionamento" << endl;
        resultado = testar_Remover_Redimensionamento();
    }
    
    cout << "FIM: Testes Remover" << endl;
    
    return resultado;
}

bool testar_Tudo()
{
    cout << "\nINÍCIO: Testes Tudo" << endl;
    
    bool resultado = true;
    
    Tabela tabela = TAB_CriarTabela(7);
    
    for(int i = 0; i < 100; i++)
    {
        char* conteudoStr = new char[20];
        sprintf(conteudoStr, "conteudo-%d", i);
        
        char* chaveStr = new char[20];
        if( i%3==0 )
        {
            sprintf(chaveStr, "chave-%d", i);
        }
        else if( i%3==1 )
        {
            sprintf(chaveStr, "cveha-%d", i-1);
        }
        else
        {
            sprintf(chaveStr, "vecha-%d", i-2);
        }
        
        Item item = TAB_CriarItem(conteudoStr);
        Chave chave = TAB_CriarChave(chaveStr);
        
        delete conteudoStr;
        delete chaveStr;
        
        if(!TAB_Inserir(tabela, chave, item))
        {
            cout << "\t*ERRO - Teste Tudo: Não inseriu item corretamente." << endl;
            resultado = false;
            break;
        }
        
        if( TAB_Buscar(tabela, chave) != item )
        {
            cout << "\t*ERRO - Teste Tudo: Não buscou item corretamente." << endl;
            resultado = false;
            break;
        }
    }
    
    if( resultado )
    {
        for(int i = 30; i < 70; i++)
        {
            char* conteudoStr = new char[20];
            sprintf(conteudoStr, "NovoConteudo-%d", i);
            
            char* chaveStr = new char[20];
            if( i%3==0 )
            {
                sprintf(chaveStr, "chave-%d", i);
            }
            else if( i%3==1 )
            {
                sprintf(chaveStr, "cveha-%d", i-1);
            }
            else
            {
                sprintf(chaveStr, "vecha-%d", i-2);
            }
            
            Item item = TAB_CriarItem(conteudoStr);
            Chave chave = TAB_CriarChave(chaveStr);
            
            TAB_Inserir(tabela, chave, item);
            
            Item retornado = TAB_Buscar(tabela, chave);
            
            delete chaveStr;
            delete conteudoStr;
            
            if( strcmp(retornado->conteudo, item->conteudo)!=0 )
            {
                cout << "\t*ERRO - Teste Tudo: Não atualizou item corretamente." << endl;
                resultado = false;
                break;
            }
        }
    }
    
    if(resultado)
    {
        for(int i = 30; i < 100; i++)
        {
            char* chaveStr = new char[20];
            if( i%3==0 )
            {
                sprintf(chaveStr, "chave-%d", i);
            }
            else if( i%3==1 )
            {
                sprintf(chaveStr, "cveha-%d", i-1);
            }
            else
            {
                sprintf(chaveStr, "vecha-%d", i-2);
            }
            
            Chave chave = TAB_CriarChave(chaveStr);
            
            delete chaveStr;
            
            if( i % 3 == 2 )
            {
                if(!TAB_Remover(tabela, chave))
                {
                    cout << "\t*ERRO - Teste Tudo: Não removeu item corretamente." << endl;
                    resultado = false;
                    break;
                }
                
                Item x = TAB_Buscar(tabela, chave);
                
                if( x != ITEM_REMOVIDO && x != NULL )
                {
                    cout << "\t*ERRO - Teste Tudo: Busca após remoção incorreta." << endl;
                    resultado = false;
                    break;
                }
            }
        }
    }

    cout << "FIM: Testes Tudo" << endl;
    
    TAB_DestruirTabela(tabela);
    
    return true;
}