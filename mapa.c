#include <stdio.h>
#include <stdlib.h>
#include "mapa.h"
#include <string.h>


void copiamapa(MAPA* destino, MAPA* origem)
{
  destino->linhas = origem->linhas;
  destino->colunas = origem->colunas;

  aloca_mapa (destino);
  for(int i = 0; i < origem->linhas; i++)
  {
    strcpy(destino->matriz[i],origem->matriz[i]);
  }

}

void atualizapersonagem(MAPA* mp, int xorigem, int yorigem,
                        int xdestino, int ydestino)
{
      char personagem = mp->matriz[xorigem][yorigem];
      mp->matriz[xdestino][ydestino] = personagem;
      mp->matriz[xorigem][yorigem] = VAZIO;
}

int ehparede(MAPA* mp, int x, int y)
{
  return mp->matriz[x][y] == PAREDE_VERTICAL || mp->matriz[x][y] == PAREDE_HORIZONTAL;
}

int ehpersonagem(MAPA* mp, int x, int y, char personagem)
{
  return mp->matriz[x][y] == personagem;
}

int podeandar(MAPA* mp, int x, int y, char personagem)
{

  return movvalido(mp, x,  y) && !ehparede(mp,  x,  y)  && !ehpersonagem(mp, x,y,personagem);
}

int movvalido(MAPA *mp, int x, int y) //Checa se movimento está dentro das bordas do mapa
{
  if(x >= mp->linhas) return 0;
  if(y >= mp->colunas) return 0;

  return 1;
}
int proximacasavazia(MAPA *mp, int x, int y)
{
  if(mp->matriz[x][y] == VAZIO ) return 1;
  return 0;
}

int encontra_mapa(MAPA* mp, POSICAO* p, char c)
{
  for(int i = 0; i < mp->linhas; i++)
  {
      for(int j = 0; j < mp->colunas; j ++)
      {
          if(mp->matriz[i][j] == c)
          {
              p->x = i;
              p->y = j;
              return 1;
          }
      }
    }
    return 0;
}

void libera_mapa(MAPA* mp)
{
    for(int i = 0; i< mp->linhas; i++)
    {
        free(mp->matriz[i]);
    }
    free(mp->matriz);
}

void aloca_mapa(MAPA* mp)
{
    mp->matriz = malloc(sizeof(char*) * mp->linhas);
    for(int i = 0; i < mp->linhas; i++)
    {
        mp->matriz[i] = malloc(sizeof(char) * (mp->colunas+1));

    }


}



void le_mapa(MAPA* mp)
{
    FILE* m;
    m = fopen("mapa.txt","r");
    if (m == 0)
    {
        printf("Erro na leitura do mapa\n");
        exit(1);
    }

    fscanf(m, "%d %d", &(mp->linhas), &(mp->colunas));

    aloca_mapa(mp);



   for(int i = 0; i< mp->linhas; i++)
   {
       fscanf(m,"%s", mp->matriz[i]);

   }

   fclose(m);

}
