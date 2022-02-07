#include <stdio.h>
#include <string.h>

#define MAX_STR 50

typedef struct portos
{
  int x_p, y_p;
} portos;

typedef struct robalo
{
  int x_r, y_r, quant_r;
} robalo;

typedef struct cioba
{
  int x_c, y_c, quant_c;
} cioba;

typedef struct tainha
{
  int x_t, y_t, quant_t;
} tainha;

typedef struct bots
{
  int x_b, y_b;
} bots;

portos p[100] = {};
robalo r[15] = {};
cioba c[20] = {};
tainha t[50] = {};

/* typedef struct mybot{
  int x_mb, y_mb;
} mybot; */

int v, n, x, y;
int state = 0;
int freezer = 0;

int d[100];
int d_p[40];

int minIndexRobalo = 0;
int minIndexCioba = 0;
int minIndexTainha = 0;
int minIndex = 0;

int minIndexPorto = 0;
int quant = 0;

int porto_position = 0;
int robalo_position = 0;
int cioba_position = 0;
int tainha_position = 0;
int bots_position = 0;

/* ADAPTAR EM FUNÇÃO DE COMO OS DADOS SERÃO ARMAZENADOS NO SEU BOT */
void readData(int altura, int largura)
{
  porto_position = 0;
  robalo_position = 0;
  cioba_position = 0;
  tainha_position = 0;
  bots_position = 0;

  // lê os dados da área de pesca
  for (int i = 0; i < altura; i++)
  {
    for (int j = 0; j < largura; j++)
    {
      scanf("%i", &v);

      if (v == 1)
      {
        p[porto_position].x_p = i;
        p[porto_position].y_p = j;
        porto_position++;
      }

      else if (v >= 12 && v <= 19)
      {
        t[tainha_position].x_t = i;
        t[tainha_position].y_t = j;
        t[tainha_position].quant_t = v - 10;
        tainha_position++;
      }

      else if (v >= 22 && v <= 29)
      {
        c[cioba_position].x_c = i;
        c[cioba_position].y_c = j;
        c[cioba_position].quant_c = v - 20;
        cioba_position++;
      }

      else if (v >= 32 && v <= 39)
      {
        r[robalo_position].x_r = i;
        r[robalo_position].y_r = j;
        r[robalo_position].quant_r = v - 30;
        robalo_position++;
      }
    }
  }

  char id[MAX_STR];

  // lê os dados dos bots
  scanf(" BOTS %i", &n);
  // o " " antes de BOTS é necessário para ler o '\n' da linha anterior
  for (int i = 0; i < n; i++)
  {
    scanf("%s %i %i", id, &x, &y);
  }
}

void readBots(char myId[])
{
}

void fishing()
{
  for (int i = 0; i < robalo_position; i++)
  {
    d[i] = (x - r[i].x_r) * (x - r[i].x_r) + (y - r[i].y_r) * (y - r[i].y_r);
  }

  for (int i = 0; i < cioba_position; i++)
  {
    d[i + robalo_position] = (x - c[i].x_c) * (x - c[i].x_c) + (y - c[i].y_c) * (y - c[i].y_c);
  }

  for (int i = 0; i < tainha_position; i++)
  {
    d[i + robalo_position + cioba_position] = (x - t[i].x_t) * (x - t[i].x_t) + (y - t[i].y_t) * (y - t[i].y_t);
  }

  for (int i = 0; i < porto_position; i++)
  {
    d_p[i] = (x - p[i].x_p) * (x - p[i].x_p) + (y - p[i].y_p) * (y - p[i].y_p);
  }

  for (int i = 0; i < robalo_position; i++)
  {
    int curr = d[i];
    if (curr < d[minIndexRobalo])
    {
      minIndexRobalo = i;
    }
  }
  fprintf(stderr, "minIndexRobalo = %i\n", minIndexRobalo);
  for (int i = 0; i < cioba_position; i++)
  {
    int curr = d[i + robalo_position];
    if (curr < d[minIndexCioba])
    {
      minIndexCioba = i;
    }
  }
  fprintf(stderr, "minIndexCioba = %i\n", minIndexCioba);
  for (int i = 0; i < tainha_position; i++)
  {
    int curr = d[i + robalo_position + cioba_position];
    if (curr < d[minIndexTainha])
    {
      minIndexTainha = i;
    }
  }
  fprintf(stderr, "minIndexTainha = %i\n", minIndexTainha);
  for (int i = 0; i < porto_position; i++)
  {
    int curr = d_p[i];
    if (curr < d_p[minIndexPorto])
    {
      minIndexPorto = i;
    }
  }

  if (minIndexRobalo < minIndexCioba && minIndexRobalo < minIndexTainha)
  {
    minIndex = minIndexRobalo;
  }
  else if (minIndexCioba < minIndexTainha && minIndexCioba < minIndexRobalo)
  {
    minIndex = minIndexCioba;
  }
  else if (minIndexTainha < minIndexRobalo && minIndexTainha < minIndexCioba)
  {
    minIndex = minIndexTainha;
  }
  else if (minIndexRobalo == minIndexCioba && minIndexRobalo == minIndexTainha && minIndexCioba == minIndexTainha)
  {
    minIndex == minIndexRobalo;
  }
  else if (minIndexRobalo > minIndexCioba && minIndexRobalo > minIndexTainha && minIndexCioba == minIndexTainha)
  {
    minIndex == minIndexCioba;
  }
  else if (minIndexRobalo == minIndexCioba && minIndexRobalo == minIndexTainha)
  {
    minIndex == minIndexRobalo;
  }
  state = 1;

  fprintf(stderr, "minIndex: %i\n", minIndex);
}

void goToFish()
{
  if (x != r[minIndexRobalo].x_r)
  {
    if (x < r[minIndexRobalo].x_r)
    {
      printf("DOWN");
    }
    else
    {
      printf("UP");
    }
  }
  else if (y != r[minIndexRobalo].y_r)
  {
    if (y < r[minIndexRobalo].y_r)
    {
      printf("RIGHT");
    }
    else
    {
      printf("LEFT");
    }
  }
  else
  {
    state = 2;
    quant = r[minIndexRobalo].quant_r;
  }
}

void fish()
{
  if (quant == 1)
  {
    state = 0;
  }
  else
  {
    printf("FISH");
    quant--;
    freezer += 1;
  }
}

void goToPorto()
{
  if (x != p[minIndexPorto].x_p)
  {
    if (x < p[minIndexPorto].x_p)
    {
      printf("DOWN");
    }
    else
    {
      printf("UP");
    }
  }
  else if (y != p[minIndexPorto].y_p)
  {
    if (y < p[minIndexPorto].y_p)
    {
      printf("RIGHT");
    }
    else
    {
      printf("LEFT");
    }
  }
  else
  {
    state = 4;
  }
}

void sellFish()
{
  printf("SELL");
  freezer = 0;
  state = 0;
}

int main()
{
  char line[MAX_STR]; // dados temporários
  char myId[MAX_STR]; // identificador do bot em questão

  setbuf(stdin, NULL);  // stdin, stdout e stderr não terão buffers
  setbuf(stdout, NULL); // assim, nada é "guardado temporariamente"
  setbuf(stderr, NULL);

  // === INÍCIO DA PARTIDA ===
  int altura, largura;
  scanf("AREA %i %i", &altura, &largura); // lê a dimensão da área de pesca: altura (h) x largura (w)
  scanf(" ID %s", myId);                  // ...e o id do bot
  // obs: o " " antes de ID é necessário para ler o '\n' da linha anterior

  // Para "debugar", é possível enviar dados para a saída de erro padrão (stderr).
  // Esse dado não será enviado para o simulador, apenas para o terminal.
  // A linha seguinte é um exemplo. Pode removê-la se desejar.
  fprintf(stderr, "Meu id = %s\n", myId);

  // === PARTIDA ===
  // O bot entra num laço infinito, mas não se preocupe porque o simulador irá matar
  // o processo quando o jogo terminar.
  while (1)
  {
    // LÊ OS DADOS DO JOGO E ATUALIZA OS DADOS DO BOT
    readData(altura, largura);
    // INSIRA UMA LÓGICA PARA ESCOLHER UMA AÇÃO A SER EXECUTADA

    if (freezer == 10 && x != p[minIndexPorto].x_p && y != p[minIndexPorto].y_p)
    {
      state = 3;
    }

    switch (state)
    {
    case 0: // buscar por peixe
      fishing();
      break;
    case 1: // ir at o peixe
      goToFish();
      break;
    case 2: // pegar peixe
      fish();
      break;
    case 3:
      goToPorto();
      break;
    case 4:
      sellFish();
      break;
    }
    // envia a ação escolhida (nesse exemplo, ir para esquerda)
    printf("\n");
    // lê qual foi o resultado da ação (e eventualmente atualiza os dados do bot).
    scanf("%s", line);
    fprintf(stderr, "Resultado da ação: %s\n", line);
  }

  return 0;
}