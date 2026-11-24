#include "cartas_ordem_num.h"
#include "conf_iniciais.h"
#include "jogador.h"
#include "menu.h"
#include "ui.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#endif

int ind_jog, ind_baralho = 0, qtd_jogs, qtd_cartas_baralho = 104;
struct carta ult_carta, penult_carta, baralho[104];
struct jogador jog, jogs[4];

void embaralhar()
{
    struct carta copia;

    for (int i = qtd_cartas_baralho - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);

        copia = baralho[i];
        baralho[i] = baralho[j];
        baralho[j] = copia;
    }
}

void reorganizar_cartas()
{
    struct carta copia;

    for (int i = 8; i > 0; i--)
    {
        if (jog.cartas[i - 1].naipe > jog.cartas[i].naipe ||
                jog.cartas[i - 1].naipe == jog.cartas[i].naipe &&
                jog.cartas[i - 1].num > jog.cartas[i].num)
        {
            copia = jog.cartas[i];
            jog.cartas[i] = jog.cartas[i - 1];
            jog.cartas[i - 1] = copia;
        }
        else
        {
            break;
        }
    }
}

void verificar_embaralhamento()
{
    if (++ind_baralho == qtd_cartas_baralho)
    {
        ind_baralho = 0;

        strcpy(ult_carta.formato, "[    ]");
        embaralhar();
    }
}

void comprar_carta()
{
    imprimir_cartas(9);

    if (comprou_do_baralho())
    {
        jog.cartas[9] = baralho[ind_baralho];
        cartas_ordem_num[9] = baralho[ind_baralho];

        baralho[ind_baralho] = ult_carta;

        verificar_embaralhamento();
    }
    else
    {
        jog.cartas[9] = ult_carta;
        cartas_ordem_num[9] = ult_carta;

        ult_carta = penult_carta;
    }
}

void jogar_carta()
{
    imprimir_cartas(10);

    int ind_carta = escolher_indice_carta();

    penult_carta = ult_carta;
    ult_carta = jog.cartas[ind_carta];

    for (int i = ind_carta; i < 9; i++)
        jog.cartas[i] = jog.cartas[i + 1];

    reorganizar_cartas();
    ajustar_cartas_ordem_numerica(9);
}

int continuar_jogo()
{
    if (carregar_jogo())
    {
        carregar_arquivo();
        return 1;
    }
    else
    {
        iniciar_jogo();
        return !finalizar_jogo();
    }
}

void atualizar_jogador()
{
    jogs[ind_jog] = jog;

    ind_jog = (ind_jog + 1) % qtd_jogs;

    jog = jogs[ind_jog];
}

int main()
{
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    srand(time(NULL));

    int jogo_continua = continuar_jogo();

    while(jogo_continua)
    {
        ajustar_cartas_ordem_numerica(9);

        comprar_carta();
        jogar_carta();

        if(finalizar_jogo())
            jogo_continua = 0;
        else
            atualizar_jogador();
    }

    mostrar_vencedor();

    return 0;
}
