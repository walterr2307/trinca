#ifndef JOGADOR_H
#define JOGADOR_H

#include "carta.h"

struct jogador
{
    char nome[15];
    struct carta cartas[10];
};

#endif
