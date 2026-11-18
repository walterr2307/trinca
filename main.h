#ifndef MAIN_H
#define MAIN_H

extern int ind_jog, qtd_jogs, ind_baralho, qtd_cartas_baralho;
extern struct carta ult_carta, penult_carta, baralho[104];
extern struct jogador jog, jogs[4];

void embaralhar(void);

void jogar_carta(void);

#endif
