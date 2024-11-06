#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TamG 7

typedef struct no{
    int vertice;
    char item[20]; //  nome para o item
    int peso; //  atributo peso ( preco neste caso)
    struct no * aresta;    
}no;
 
typedef no * grafo[TamG];
 
void iniGrafo(grafo g) {
    int i;
    for(i = 0; i < TamG; i++) {
        g[i] = NULL;
    }
}
 
void preencherG(grafo g, int v, char *item, int p, int a) {
    no *novo = (no*)malloc(sizeof(no));
    novo->vertice = a;
    strcpy(novo->item, item);
    novo->peso = p;
    novo->aresta = NULL;
    
    if(g[v] == NULL) {
        g[v] = novo;
    } else {
        no *atual = g[v];
        while(atual->aresta != NULL) {
            atual = atual->aresta;
        }
        atual->aresta = novo;
    }
}
 
void mostrarG(grafo g) {  
	int i = 0;
	for(i = 1; i < (TamG-1); i++){
		no * atual = g[i];
		while (atual != NULL){
			printf("Item %d: %s", i, atual->item);
			if(atual->aresta != NULL || atual != NULL){
				no * prox = g[atual->vertice];
				printf(" -- %d --> |  %s  |", atual->peso, prox->item);
				printf("\n");
			}		
			atual = atual->aresta;	
		}
		printf("\n");
		
	}
}
// praticamente mesma coisa dos outros algoritmos que fizemos ate aqui

void dijkstra(grafo g, int origem, int fim) {
    int custo[TamG]; // Vetor que armazena o menor custo (distancia) do vertice de origem ate os outros vertices
    int visitado[TamG]; // Vetor para marcar quais vertices ja foram visitados
    int pai[TamG]; // Vetor para armazenar o vertice pai de cada vertice no caminho mais curto
    int i;
    
    for (i = 0; i < TamG; i++) { // Inicializa o vetor de custo com infinito e os vetores de visitado e pai
        custo[i] = 99999;
        visitado[i] = 0;
        pai[i] = -1; // -1 indica que o vertice ainda nao tem um pai
    }
    custo[origem] = 0; // A origem tem custo 0 de si mesma
    
    int fila[TamG]; // Fila para armazenar os vertices a serem processados
    int inicio = 0, fimFila = 0;
    fila[fimFila++] = origem; // Coloca a origem na fila para iniciar o algoritmo
    
    while (inicio < fimFila) {
        int u = fila[inicio++]; // Retira o primeiro vertice da fila (u) para processa-lo
		        
        no *atual = g[u]; // Atual para receber o grafo na posicao do "u"
        while (atual != NULL) {
            int v = atual->vertice; // O vertice v e o vizinho de u
            int peso = atual->peso; // O peso da aresta entre u e v
            
            if (visitado[v] == 0) { // Se o vertice v ainda nao foi visitado
                if (custo[u] + peso < custo[v]) { // Se o custo do caminho atual for menor que o custo ja registrado para v
                    custo[v] = custo[u] + peso; // Atualiza o custo de v
                    pai[v] = u; // Define u como o pai de v no caminho mais curto
                    fila[fimFila++] = v; // Adiciona v a fila para ser processado
                }
            }
            atual = atual->aresta;
        }
    }
    printf("\n\nO menor custo para trocar %s para %s e de: R$%d\n", g[origem]->item, g[fim]->item , custo[fim]);
}


int main() {
    grafo g;
    iniGrafo(g);
    char entrada[20],saida[20];
    int ini, fim;
    preencherG(g, 1, "Livro", 5, 2);
    preencherG(g, 1, "Livro", 0, 3);
    preencherG(g, 2, "LP-RARO", 15, 4);
    preencherG(g, 2, "LP-RARO", 20, 5);
    preencherG(g, 3, "Poster", 30, 4);
    preencherG(g, 3, "Poster", 35, 5);
    preencherG(g, 4, "Baixo", 20, 6);
    preencherG(g, 5, "Bateria", 10, 6);
    preencherG(g, 6, "Piano", 0, 0);

    mostrarG(g);
    
    printf("Entre com o item que voce tem [INICIO]:    ");
    scanf("%d",  & ini);    
    printf("\nEntre com o item que voce deseja trocar [FINAL]:    ");
    scanf("%d",  & fim);
    
    dijkstra(g, ini, fim);
    
    return 0;
}

