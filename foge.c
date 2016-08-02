#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapa.h"
#include "foge.h"
#include "ui.h"


MAPA mp;
POSICAO heroi;
int tempilula = 0;

int praondefantasmavai(int xatual, int yatual, int* xdestino, int* ydestino)
{
  int opcoes[4][2] = {
                      {xatual, yatual + 1 },
                      {xatual + 1, yatual},
                      {xatual, yatual -1},
                      {xatual -1, yatual}
                    }; //Sortearemos a posição final diretamente nas 4 disponíveis
  srand(time(NULL));
  for (int i = 0; i < 10; i++) //Máximo de 10 tentativas para achar uma posicao válida
  {
    int posicao = rand() % 4;
    if (podeandar(&mp,opcoes[posicao][0],opcoes[posicao][1],FANTASMA))
    {
      *xdestino = opcoes[posicao][0];
      *ydestino = opcoes[posicao][1];

      return 1;
    }
  }
  return 0; //Se não randomizar em 10 tentativas, não se move
}

void fantasmas()
{
    MAPA copia;
    copiamapa(&copia,&mp);
    for(int i = 0; i < mp.linhas; i++)
    {
      for(int j = 0; j < mp.colunas; j++)
      {
        if(copia.matriz[i][j] == FANTASMA)
        {
          int xdestino;
          int ydestino;

          int encontrou = praondefantasmavai(i,j,&xdestino,&ydestino);
          if (encontrou)
          {
            atualizapersonagem(&mp,i,j, xdestino, ydestino);
          }


        }
      }
    }
    libera_mapa(&copia);
}

int acabou() {
	POSICAO pos;

	int perdeu = !encontra_mapa(&mp, &pos, HEROI);
	int ganhou = !encontra_mapa(&mp, &pos, FANTASMA);

	return ganhou || perdeu;

}

int direcaovalida(char direcao)
{
  return direcao == 'w' ||
      direcao == 'a' ||
      direcao == 's' ||
      direcao == 'd';
}

void move(char direcao)
{

    if(!direcaovalida(direcao) ) return; //Ignora entradas não definidas

    int proximox = heroi.x;
    int proximoy = heroi.y;

    switch(direcao)
    {
        case ESQUERDA:
            proximoy--;
            break;
        case CIMA:
            proximox--;
            break;
        case BAIXO:
            proximox++;
            break;
        case DIREITA:
            proximoy++;
            break;
    }


    if(!podeandar(&mp,proximox,proximoy,HEROI)) return;
    if(ehpersonagem(&mp, proximox,proximoy, PILULA)) tempilula = 1;

    atualizapersonagem(&mp, heroi.x,heroi.y, proximox,proximoy);
    heroi.x = proximox;
    heroi.y = proximoy;

}

void explodepilula() //Explode nas 4 direções
{
  if(!tempilula) return;
  explodepilulaaux(heroi.x,heroi.y,0,1,3);
  explodepilulaaux(heroi.x,heroi.y,1,0,3);
  explodepilulaaux(heroi.x,heroi.y,-1,0,3);
  explodepilulaaux(heroi.x,heroi.y,0,-1,3);

  tempilula = 0;
}

void explodepilulaaux(int x, int y, int somax, int somay, int qtd ) //explode na direção (somax,somay)
{

    if (qtd == 0) return;
    int novox = x + somax;
    int novoy = y + somay;

    if(!movvalido(&mp,novox,novoy)) return;
    if(ehparede(&mp,novox,novoy)) return;

    mp.matriz[novox][novoy] = VAZIO;
    explodepilulaaux(novox,novoy, somax, somay, qtd - 1);

}

int main()
{

    le_mapa(&mp);
    encontra_mapa(&mp,&heroi,HEROI);

    do
    {
         printf("Tem Pilula: %s\n", (tempilula ? "SIM" : "NAO"));
         print_mapa(&mp);
         char comando;
         scanf(" %c",&comando);
         if(direcaovalida(comando))  move(comando);

         if(comando == BOMBA) explodepilula();

         fantasmas();
    }while(!acabou());

    libera_mapa(&mp);
    printf("\n\n\nGAME OVER\n\n\n");
    system("pause");
    return 0;
}
