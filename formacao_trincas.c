#include "formacao_trincas.h"
#include "jogador.h"
#include "main.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>

struct carta trinca[3], copia_cartas[9], trincas[3][3];

int escolher_indice_trinca(int qtd_cartas, int i, int j)
{
    int ind_carta;

    while (1)
    {
        printf("\n\nColoque o indice da %d* carta para a %d* trinca: ",
               j + 1, i + 1);

        if (scanf("%d", &ind_carta) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');
        }

        else if (ind_carta < 1 || ind_carta > qtd_cartas)
            printf("\n\tErro: indice de carta invalido.\n");
        else
            break;
    }

    return --ind_carta;
}

void verificar_trinca_real()
{
    int indice_as = -1, tem_rainha = 0, tem_rei = 0;

    for (int i = 0; i < 3; i++)
    {
        switch(trinca[i].num)
        {
        case 1:
            indice_as = i;
            break;

        case 12:
            tem_rainha = 1;
            break;

        case 13:
            tem_rei = 1;
            break;

        default:
            return;
        }
    }

    if (indice_as >= 0 && tem_rainha && tem_rei)
        trinca[indice_as].num = 14;
}

void ordenar_trinca()
{
    struct carta copia;
    int troca = 1;

    while(troca)
    {
        troca = 0;

        for (int i = 0; i < 2; i++)
        {
            if(trinca[i].num > trinca[i + 1].num)
            {
                troca = 1;

                copia = trinca[i];
                trinca[i] = trinca[i + 1];
                trinca[i + 1] = copia;
            }
        }
    }
}

void preencher_trincas(int i)
{
    for (int j = 0; j < 3; j++)
        trincas[i][j] = trinca[j];
}

void limpar_trinca()
{
    for (int i = 0; i < 3; i++)
        strcpy(trinca[i].formato, "[    ]");
}

void imprimir_trinca()
{
    printf("\n\n\nTrinca: ");

    for (int i = 0; i < 3; i++)
        printf("%s ", trinca[i].formato);

    printf("\n");
}

void copiar_cartas()
{
    for (int i = 0; i < 9; i++)
        copia_cartas[i] = jog.cartas[i];
}

void deletar_carta(int ind_carta, int qtd_cartas)
{
    for (int i = ind_carta; i < qtd_cartas; i++)
        jog.cartas[i] = jog.cartas[i + 1];
}

void devolver_cartas()
{
    for (int i = 0; i < 9; i++)
        jog.cartas[i] = copia_cartas[i];
}

void formar_trinca(int i)
{
    int ind_carta, qtd_cartas = 9 - 3 * i;

    for (int j = 0; j < 3; j++)
    {
        imprimir_cartas(qtd_cartas);
        imprimir_trinca();

        ind_carta = escolher_indice_trinca(qtd_cartas, i, j);
        trinca[j] = jog.cartas[ind_carta];

        deletar_carta(ind_carta, --qtd_cartas);
        ajustar_cartas_ordem_numerica(qtd_cartas);
    }
}

int nao_formou_trinca()
{
    int mesmo_naipe = trinca[0].naipe == trinca[1].naipe &&
                      trinca[1].naipe == trinca[2].naipe;

    int em_sequencia = trinca[0].num + 1 == trinca[1].num &&
                       trinca[1].num + 1 == trinca[2].num;

    int naipes_diferentes = trinca[0].naipe != trinca[1].naipe &&
                            trinca[1].naipe != trinca[2].naipe &&
                            trinca[2].naipe != trinca[0].naipe;

    int mesmo_num = trinca[0].num == trinca[1].num &&
                    trinca[1].num == trinca[2].num;

    return !(mesmo_naipe && em_sequencia || naipes_diferentes && mesmo_num);
}

int formou_trincas()
{
    copiar_cartas();

    for (int i = 0; i < 3; i++)
    {
        limpar_trinca();
        formar_trinca(i);

        verificar_trinca_real();
        ordenar_trinca();

        if (nao_formou_trinca())
        {
            devolver_cartas();
            return 0;
        }

        preencher_trincas(i);
    }

    return 1;
}
