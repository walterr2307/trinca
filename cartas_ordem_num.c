#include "cartas_ordem_num.h"
#include "jogador.h"
#include "main.h"

struct carta cartas_ordem_num[10];
int inds_ordem_num[10];

void organizar_cartas_ordem_numerica(int qtd_cartas)
{
    int copia_ind, troca = 1;
    struct carta copia_carta;

    while (troca)
    {
        troca = 0;

        for (int i = 0; i < qtd_cartas - 1; i++)
        {
            if (cartas_ordem_num[i].num > cartas_ordem_num[i + 1].num ||
                    cartas_ordem_num[i].num == cartas_ordem_num[i + 1].num &&
                    cartas_ordem_num[i].naipe > cartas_ordem_num[i + 1].naipe)
            {
                troca = 1;

                copia_carta = cartas_ordem_num[i];
                cartas_ordem_num[i] = cartas_ordem_num[i + 1];
                cartas_ordem_num[i + 1] = copia_carta;

                copia_ind = inds_ordem_num[i];
                inds_ordem_num[i] = inds_ordem_num[i + 1];
                inds_ordem_num[i + 1] = copia_ind;
            }
        }
    }
}

void ajustar_cartas_ordem_numerica(int qtd_cartas)
{
    for (int i = 0; i < qtd_cartas; i++)
    {
        cartas_ordem_num[i] = jog.cartas[i];
        inds_ordem_num[i] = i + 1;
    }

    organizar_cartas_ordem_numerica(qtd_cartas);
}
