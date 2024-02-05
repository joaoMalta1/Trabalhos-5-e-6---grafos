/* João Ricardo Malta De Oliveira - 2112714
Vinícius Machado Da Rocha Viana - 2111343 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#define INFINITO -1

typedef struct no {
  int no;
  float peso;
  struct no *prox;
} NO;

typedef struct grafo {
  int numNo; // número de nós do grafo
  int na;    // número de arestas
  NO **viz;  // viz[i] aponta para a lista de arestas incidindo em i
} Grafo;

// Função para inicializar o grafo
Grafo *criarGrafo(int numNo) {
  Grafo *grafo = (Grafo *)malloc(sizeof(Grafo));
  if (grafo == NULL) {
    printf("Erro ao alocar memoria para o grafo\n");
    exit(1);
  }
  grafo->numNo = numNo;
  grafo->na = 0;
  grafo->viz = (NO **)malloc(numNo * sizeof(NO *));
  if (grafo->viz == NULL) {
    printf("Erro ao alocar memoria de inicializacao do nó");
    exit(1);
  }
  return grafo;
}

// Função para adicionar uma aresta ao grafo
void adicionarAresta(Grafo *grafo, int ini, int fim, float peso) {
  NO *novoNo = (NO *)malloc(sizeof(NO));
  if (novoNo == NULL) {
    printf("Erro ao alocar memoria para o novo No\n");
    exit(1);
  }
  novoNo->no = fim;
  novoNo->peso = peso;
  novoNo->prox = grafo->viz[ini];
  grafo->viz[ini] = novoNo;
  grafo->na++;
}

// Função busca em profundidade
void dfs(Grafo *grafo, int no_inicial, int *visitado) {
  visitado[no_inicial] = 1;
  printf("Nó: %d\n", no_inicial);

  NO *atual = grafo->viz[no_inicial];
  while (atual) {
    if (!visitado[atual->no]) {
      printf("Aresta: (%d, %d)  Nó %d não visitado\n\n", no_inicial, atual->no,
             atual->no);
      dfs(grafo, atual->no, visitado);
    } else {
      printf("Aresta: (%d, %d) Nó %d visitado\n\n", no_inicial, atual->no,
             atual->no);
    }
    atual = atual->prox;
  }
}

void dijkstra(Grafo *grafo, int no_origem) {
  int *distancia = (int *)malloc((grafo->numNo + 1) * sizeof(int));
  int *visitado = (int *)malloc((grafo->numNo + 1) * sizeof(int));
  int *anterior = (int *)malloc((grafo->numNo + 1) * sizeof(int));

  // Inicializa as distâncias e marca todos os nós como não visitados
  for (int i = 1; i <= grafo->numNo; ++i) {
    distancia[i] = INT_MAX; // Usamos INT_MAX em vez de -1
    visitado[i] = 0;
    anterior[i] = -1; // Inicializa o array de nós anteriores
  }

  // A distância até o nó de origem é sempre 0
  distancia[no_origem] = 0;

  for (int count = 0; count < grafo->numNo; ++count) {
    int minDistancia = INT_MAX;
    int ind = -1;

    // Encontra o nó com a menor distância entre os nós não visitados
    for (int j = 1; j <= grafo->numNo; ++j) {
      if (!visitado[j] && (ind == -1 || distancia[j] < minDistancia)) {
        minDistancia = distancia[j];
        ind = j;
      }
    }

    // Verifica se há um nó válido a ser visitado
    if (ind == -1)
      break;

    // Marca o nó escolhido como visitado
    visitado[ind] = 1;

    // Atualiza as distâncias dos nós adjacentes ao nó escolhido
    NO *atual = grafo->viz[ind];
    while (atual) {
      if (!visitado[atual->no] && distancia[ind] != INT_MAX &&
          distancia[ind] + (int)atual->peso < distancia[atual->no]) {
        distancia[atual->no] = distancia[ind] + (int)atual->peso;
        anterior[atual->no] = ind; // Armazena o nó anterior
      }
      atual = atual->prox;
    }
  }

  // Imprime os menores percursos
  printf("Menores percursos a partir do nó %d:\n", no_origem);

  for (int i = 1; i <= grafo->numNo; ++i) {
    if (no_origem != i) {
      printf("Nó %d: Distância = %d, Caminho = ", i, distancia[i]);

      // Imprime o caminho mais curto para o nó i
      int j = i;
      while (j != -1) {
        if (j == no_origem) {
          printf("%d ", j);
        } else {
          printf("%d <- ", j);
        }
        j = anterior[j];
      }
      printf("\n");
    }
  }
  free(distancia);
  free(visitado);
  free(anterior);
}

int main() {
  Grafo *grafo = criarGrafo(10);

  // adcionando aretsa ida, aresta volta
  adicionarAresta(grafo, 1, 3, 3.0);
  adicionarAresta(grafo, 3, 1, 3.0);
  adicionarAresta(grafo, 1, 5, 4.0);
  adicionarAresta(grafo, 5, 1, 4.0);
  adicionarAresta(grafo, 1, 9, 3.0);
  adicionarAresta(grafo, 9, 1, 3.0);
  adicionarAresta(grafo, 1, 8, 3.0);
  adicionarAresta(grafo, 8, 1, 3.0);
  adicionarAresta(grafo, 1, 10, 1.0);
  adicionarAresta(grafo, 10, 1, 1.0);
  adicionarAresta(grafo, 3, 4, 1.0);
  adicionarAresta(grafo, 4, 3, 1.0);
  adicionarAresta(grafo, 3, 8, 2.0);
  adicionarAresta(grafo, 8, 3, 2.0);
  adicionarAresta(grafo, 3, 9, 4.0);
  adicionarAresta(grafo, 9, 3, 4.0);
  adicionarAresta(grafo, 3, 6, 1.0);
  adicionarAresta(grafo, 6, 3, 1.0);
  adicionarAresta(grafo, 3, 10, 4.0);
  adicionarAresta(grafo, 10, 3, 4.0);
  adicionarAresta(grafo, 10, 8, 2.0);
  adicionarAresta(grafo, 8, 10, 2.0);
  adicionarAresta(grafo, 2, 10, 1.0);
  adicionarAresta(grafo, 10, 2, 1.0);
  adicionarAresta(grafo, 2, 3, 4.0);
  adicionarAresta(grafo, 3, 2, 4.0);
  adicionarAresta(grafo, 4, 5, 2.0);
  adicionarAresta(grafo, 5, 4, 2.0);
  adicionarAresta(grafo, 5, 7, 2.0);
  adicionarAresta(grafo, 7, 5, 2.0);
  adicionarAresta(grafo, 8, 5, 4.0);
  adicionarAresta(grafo, 5, 8, 4.0);
  adicionarAresta(grafo, 4, 7, 2.0);
  adicionarAresta(grafo, 7, 4, 2.0);
  adicionarAresta(grafo, 7, 6, 3.0);
  adicionarAresta(grafo, 6, 7, 3.0);
  adicionarAresta(grafo, 9, 8, 1.0);
  adicionarAresta(grafo, 8, 9, 1.0);
  adicionarAresta(grafo, 9, 10, 4.0);
  adicionarAresta(grafo, 10, 9, 4.0);

  int *visitado = (int *)malloc(grafo->numNo * sizeof(int));
  for (int i = 0; i < grafo->numNo; ++i) {
    visitado[i] = 0;
  }
  dfs(grafo, 3, visitado);
  dijkstra(grafo, 3);

  // Libere a memória alocada
  for (int i = 0; i < grafo->numNo; i++) {
    NO *atual = grafo->viz[i];
    while (atual != NULL) {
      NO *temp = atual;
      atual = atual->prox;
      free(temp);
    }
  }
  free(visitado);
  free(grafo->viz);
  free(grafo);
  return 0;
}
