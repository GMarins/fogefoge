#ifndef FOGE_H_INCLUDED
#define FOGE_H_INCLUDED



#endif // FOGE_H_INCLUDED


#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'


int acabou();
int direcaovalida(char direcao);
void move(char direcao);
void fantasmas();
int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);
