#include "jogador.h"
#include "main.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void imprimir_por_ordem_numerica(struct carta cartas[], int qtd_cartas)
{
    int troca = 1, copia_ind, indices[qtd_cartas];
    struct carta copia;

    for(int i = 0; i < qtd_cartas; i++)
        indices[i] = i;

    while(troca)
    {
        troca = 0;

        for (int i = qtd_cartas - 1; i > 0; i--)
        {
            char *prox_naipe = cartas[i].naipe;
            char *naipe = cartas[i - 1].naipe;

            int comparacao = strcmp(naipe, prox_naipe);

            int prox_num = cartas[i].num;
            int num = cartas[i - 1].num;

            if (num > prox_num || (num == prox_num && comparacao > 0))
            {
                copia = cartas[i];
                cartas[i] = cartas[i - 1];
                cartas[i - 1] = copia;

                copia_ind = indices[i];
                indices[i] = indices[i - 1];
                indices[i - 1] = copia_ind;

                troca = 1;
            }
        }
    }

    for (int i = 0; i < qtd_cartas; i++)
        printf("%d.%s ", indices[i] + 1, cartas[i].formato);

    printf("\n\n");
}

void imprimir_cartas(int qtd_cartas)
{
    fflush(stdout);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    struct carta cartas[qtd_cartas];

    for (int i = 0; i < qtd_cartas; i++)
        cartas[i] = jog.cartas[i];

    printf("Carta na Mesa:\n\n\t%s\n", ult_carta.formato);
    printf("\nCartas de %s:\n", jog.nome);

    imprimir_por_ordem_numerica(cartas, qtd_cartas);

    for (int i = 0; i < qtd_cartas; i++)
        printf("%d.%s ", i + 1, jog.cartas[i].formato);
}

int escolher_indice_carta()
{
    int ind_carta;

    while (1)
    {
        printf("\n\nSelecione o indice correspondente a carta: ");

        if (scanf("%d", &ind_carta) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");
            while (getchar() != '\n');
        }

        else if (ind_carta < 1 || ind_carta > 10)
            printf("\n\tErro: indice de carta invalido.\n");
        else
            break;
    }

    return --ind_carta;
}

int comprou_do_baralho()
{
    char opcao;

    while (1)
    {
        printf("\nEscolha 'b' para puxar uma carta do baralho");
        printf(" e 'm' para puxar a carta na mesa: ");

        if (scanf(" %c", &opcao) != 1)
        {
            printf("\n\tErro ao ler a entrada.\n");
            continue;
        }

        opcao = tolower(opcao);

        if (opcao != 'b' && opcao != 'm')
            printf("\n\tErro: escolha invalida. Digite 'b' ou 'm'.\n");
        else
            break;
    }

    return opcao == 'b';
}
