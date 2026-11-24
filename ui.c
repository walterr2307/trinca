#include "cartas_ordem_num.h"
#include "formacao_trincas.h"
#include "jogador.h"
#include "main.h"
#include "ui.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void imprimir_cartas(int qtd_cartas)
{
    fflush(stdout);

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    printf("Carta na Mesa:\n\n\t%s\n", ult_carta.formato);
    printf("\nCartas de %s:\n", jog.nome);

    for (int i = 0; i < qtd_cartas; i++)
        printf("%d.%s ", inds_ordem_num[i], cartas_ordem_num[i].formato);

    printf("\n\n");

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
        printf("\n\nEscolha 'b' para puxar uma carta do baralho");
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

int deseja_formar_trincas()
{
    char opcao;

    while (1)
    {
        printf("\n\nDeseja formar as trincas? ");
        printf("Escolha 's' para sim e 'n' para nao: ");

        if (scanf(" %c", &opcao) != 1)
        {
            printf("\n\tErro ao ler a entrada.\n");
            continue;
        }

        opcao = tolower(opcao);

        if (opcao != 's' && opcao != 'n')
            printf("\n\tErro: escolha invalida. Digite 's' ou 'n'.\n");
        else
            break;
    }

    return opcao == 's';
}

int finalizar_jogo()
{
    imprimir_cartas(9);

    while (deseja_formar_trincas())
    {
        if(formou_trincas())
            return 1;
        else
            printf("\n\nNao conseguiu formar as trincas!\n");
    }

    return 0;
}

void mostrar_vencedor()
{
    printf("\n\t%s venceu!!!\n", jog.nome);
}
