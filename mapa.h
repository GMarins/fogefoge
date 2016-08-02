#ifndef MAPA_H_INCLUDED
#define MAPA_H_INCLUDED




#define HEROI '@'
#define FANTASMA 'F'
#define VAZIO '.'
#define PAREDE_VERTICAL '|'
#define PAREDE_HORIZONTAL '-'
#define PILULA  'P'


struct mapa
{
    char** matriz;
    int linhas;
    int colunas;

};
typedef struct mapa MAPA;

struct posicao
{
  int x;
  int y;
};
typedef struct posicao POSICAO;

void libera_mapa(MAPA* mp);
void aloca_mapa(MAPA* mp);
void le_mapa(MAPA* mp);
int encontra_mapa(MAPA* mp, POSICAO* p, char c);
int movvalido(MAPA *mp, int x, int y);
int proximacasavazia(MAPA *mp, int x, int y);
void atualizapersonagem(MAPA* mp, int xorigem, int yorigem, int xdestino, int ydestino);
void copiamapa(MAPA* destino, MAPA* origem);
int podeandar(MAPA* mp, int x, int y, char personagem);
int ehparede(MAPA* mp, int x, int y);
int ehpersonagem(MAPA* mp, int x, int y, char personagem);

#endif // MAPA_H_INCLUDED
