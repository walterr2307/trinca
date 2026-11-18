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

int ind_jog, qtd_jogs, ind_baralho = 0, qtd_cartas_baralho = 104;
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
        char *prox_naipe = jog.cartas[i].naipe;
        char *naipe = jog.cartas[i - 1].naipe;

        int comparacao = strcmp(naipe, prox_naipe);

        int prox_num = jog.cartas[i].num;
        int num = jog.cartas[i - 1].num;

        if (comparacao > 0 || (comparacao == 0 && num > prox_num))
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
        embaralhar();
    }
}

void comprar_carta()
{
    imprimir_cartas(9);

    if (comprou_do_baralho())
    {
        jog.cartas[9] = baralho[ind_baralho];
        baralho[ind_baralho] = ult_carta;

        verificar_embaralhamento();
    }
    else
    {
        jog.cartas[9] = ult_carta;
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
}

int finalizar_jogo()
{
    imprimir_cartas(9);

    /*while (deseja_formar_trincas())
    {
    	if(formou_trincas())
    		return 1;
    }*/

    return 0;
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

void mostrar_vencedor()
{
    printf("\n\t%s venceu!!!\n", jog.nome);
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
        reorganizar_cartas();
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
