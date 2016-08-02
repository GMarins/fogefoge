#ifndef FOGE_H_INCLUDED
#define FOGE_H_INCLUDED






#define CIMA 'w'
#define BAIXO 's'
#define DIREITA 'd'
#define ESQUERDA 'a'
#define BOMBA 'b'

int acabou();
int direcaovalida(char direcao);
void move(char direcao);
void fantasmas();
int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino);
void explodepilulaaux(int x, int y, int somax, int somay, int qtd );
void explodepilula();

#endif // FOGE_H_INCLUDED
