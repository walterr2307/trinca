#include "cartas_ordem_num.h"
#include "conf_iniciais.h"
#include "jogador.h"
#include "main.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>

int ler_qtd_jogs()
{
    int qtd_jogs;

    while (1)
    {
        printf("\nInsira a quantidade de jogadores (2 a 4): ");

        if (scanf("%d", &qtd_jogs) != 1)
        {
            printf("\n\tErro: digite um numero inteiro.\n");

            while (getchar() != '\n');
            continue;
        }

        if (qtd_jogs < 2 || qtd_jogs > 4)
            printf("\n\tErro: quantidade de jogadores invalida.\n");
        else
            break;
    }

    return qtd_jogs;
}

void comprar_primeira_carta()
{
    int c;

    imprimir_cartas(9);

    while ((c = getchar()) != '\n' && c != EOF);

    printf("\n\nPressione qualquer tecla para comprar a primeira carta: ");

    getchar();

    jog.cartas[9] = baralho[103];
    cartas_ordem_num[9] = baralho[103];
}

struct jogador organizar_jogador_por_cartas(struct jogador jog)
{
    struct carta copia;
    int troca = 1;

    while(troca)
    {
        troca = 0;

        for (int i = 0; i < 8; i++)
        {
            if (jog.cartas[i].naipe > jog.cartas[i + 1].naipe ||
                    jog.cartas[i].naipe == jog.cartas[i + 1].naipe &&
                    jog.cartas[i].num > jog.cartas[i + 1].num)
            {
                troca = 1;

                copia = jog.cartas[i];
                jog.cartas[i] = jog.cartas[i + 1];
                jog.cartas[i + 1] = copia;
            }
        }
    }

    return jog;
}

void gerar_jogadores()
{
    int k = 102;

    for (int i = 0; i < qtd_jogs; i++)
    {
        for (int j = 0; j < 9; j++)
            jogs[i].cartas[j] = baralho[k--];

        getchar();

        printf("Insira o nome do %d* jogador: ", i + 1);
        scanf("%14[^\n]", jogs[i].nome);

        jogs[i] = organizar_jogador_por_cartas(jogs[i]);
    }
}

struct carta gerar_carta(int num, int naipe, char emoji[])
{
    struct carta carta;

    switch (num)
    {
    case 1:
        sprintf(carta.formato, "[A|%s]", emoji);
        break;
    case 11:
        sprintf(carta.formato, "[J|%s]", emoji);
        break;
    case 12:
        sprintf(carta.formato, "[Q|%s]", emoji);
        break;
    case 13:
        sprintf(carta.formato, "[K|%s]", emoji);
        break;
    default:
        sprintf(carta.formato, "[%d|%s]", num, emoji);
    }

    carta.naipe = naipe;
    carta.num = num;

    return carta;
}

void gerar_meio_baralho(int i)
{
    char emojis[4][4] = {"♣", "♥", "♠", "♦"};

    for (int j = 0; j < 4; j++)
    {
        char *emoji = emojis[j];

        for (int num = 1; num < 14; num++)
            baralho[i++] = gerar_carta(num, j, emoji);
    }
}

void gerar_baralho()
{
    for (int i = 0; i < 104; i += 52)
        gerar_meio_baralho(i);

    embaralhar();
}

void iniciar_jogo()
{
    sprintf(ult_carta.formato, "[    ]");

    qtd_jogs = ler_qtd_jogs();

    gerar_baralho();
    gerar_jogadores();

    qtd_cartas_baralho = 103 - 9 * qtd_jogs;

    ind_jog = rand() % qtd_jogs;
    jog = jogs[ind_jog];

    inds_ordem_num[9] = 10;

    ajustar_cartas_ordem_numerica(9);
    comprar_primeira_carta();
    jogar_carta();
}
