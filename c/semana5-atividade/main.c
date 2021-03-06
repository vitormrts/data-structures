#include <stdio.h>
#include <stdlib.h>

typedef struct estrutura {
    int chave;
    int info;
    struct estrutura *prox
} NO;

typedef struct {
    NO* inicio;
} LISTA;

// Inicializa a lista
void inicializarLista(LISTA* l) {
    l->inicio = NULL;
}

// Retorna o primeiro elmento da lista
NO* primeiroElemLista(LISTA l) {
    return (l.inicio->chave);
}

// Retorna o ultimo elemento da lista
NO* ultimoElemLista(LISTA l) {
    NO* p = l.inicio;

    if (p) while (p->prox) p = p->prox;
    return p;
}

// Retorna o enesimo elemento da lista
NO* enesimoElemLista(LISTA l, int n) {
    NO* p = l.inicio;
    int i = 1;

    if (p != NULL) {
        while ((p->prox) && (i<n)) {
            p = p->prox;
            i++;
        }
    }

    if (i != n) return NULL;
    else return p;
}

// Exibe o tamanho da lista
int tamanho(LISTA *l) {
    NO* p = l->inicio;
    int tam = 0;

    while (p != NULL) {
        tam ++;
        p = p->prox;
    }

    return tam;
}

// Exibe os elementos da lista
void exibirLista(LISTA l) {
    NO* p = l.inicio;
    printf("\nExibindo a lista:\n");

    while (p) {
        printf("%i ", p->chave);
        p = p->prox;
    }
}

// Busca um elemento numa sequencia ordenada
NO* buscaSeqOrd(LISTA l, int ch, NO* *ant) {
    NO *p = l.inicio;
    *ant = NULL;

    while (p != NULL) {
        if (p->chave >= ch) break;
        *ant = p;
        p = p->prox;
    }

    if (p != 0 && p->chave == ch) return p;
    return NULL;
}

// Insercao de chave sem repeticoes
int inserirElemListaOrd(LISTA* l, int ch) {
    printf("\nInicio: %i\n", l->inicio);
    NO* novo;
    NO* ant;
    novo = buscaSeqOrd(*l, ch, &ant);
    // Significa que ja tem um numero igual a ch
    if (novo != NULL) return -1;
    novo = (NO*) malloc(sizeof(NO));
    if (novo == NULL) printf("Faltou memoria.");
    novo->chave = ch;

    if (l->inicio == NULL) { // 1a. insercao em lista vazia
            printf("Primeira insercao\n");
        l->inicio = novo;
        novo->prox = NULL;
    }
    else {
        if (ant == NULL) { // insercao no inicio da lista
            printf("Inicio da lista\n");
            novo->prox = l->inicio;
            l->inicio = novo;
        }

        else { // insercao apos um no existente
            printf("Apos elemento\n");
            novo->prox = ant->prox;
            ant->prox = novo;
        }
    }

    return 1;
}

// Anexa um novo elemento ao final da lista
void anexarElemLista(LISTA* l, int ch) {
    NO* novo;
    NO* ant;
    ant = ultimoElemLista(*l);
    novo = (NO*) malloc(sizeof(NO));
    novo->chave = ch;
    novo->prox = NULL;
    if(!ant) l->inicio = novo;
    else ant->prox = novo;
}

// Exclui um elemento da lista
int excluirElemListaOrd(LISTA* l, int ch) {
    NO* ant;
    NO* elem;
    elem = buscaSeqOrd(*l, ch, &ant);

    if (elem != NULL) return -1;             // nada a excluir
    if (ant != NULL) l->inicio = elem->prox; // exclui o 1o. elemento da lista
    else ant->prox = elem->prox;             // exclui o elemento que possui anterior

    free(elem);

    return 1;
}

// Destruicao da lista
void destruirLista(LISTA* l) {
    NO* atual;
    NO* prox;
    atual = l->inicio;

    while (atual != NULL) {
        prox = atual->prox;
        free(atual);
        atual = prox;
    }
    l->inicio = NULL;
}

// Exclui todos os elementos x da lista
void excluirOcorrencias (LISTA* l, int x) {
    NO* atual;
    NO* prox;
    NO* ant;
    NO* aux;

    ant = NULL;

    atual = l->inicio;

    while (atual != NULL) {
        aux = atual;
        if (atual->chave == x) {
                if (!ant) {
                    ant = aux;
                    l->inicio = atual->prox;
                }

                prox = atual->prox;
                free(atual);
                atual = prox;
                ant->prox = atual;
        }
        else {
                atual = atual->prox;
                ant = aux;
        }
    }
}

// Copia uma lista dinamica apontada por *p
NO* copia(NO* p) {
    NO* inicio = NULL;
    NO* fim = NULL;

    while (p) {
        NO* novo = (NO*) malloc(sizeof(NO));
        novo->chave = p->chave;
        novo->prox = NULL;

        if (fim) fim->prox = novo;
        else inicio = novo;

        fim = novo;
        p = p->prox;
    }
    return inicio;
}

int main()
{
    LISTA l;

    inicializarLista(&l);


    inserirElemListaOrd(&l, 3);
    inserirElemListaOrd(&l, 1);
    inserirElemListaOrd(&l, 5);
    inserirElemListaOrd(&l, 7);
    inserirElemListaOrd(&l, 9);



    //exibirLista(l);



    copia(l.inicio);

    //excluirOcorrencias(&l, 9);



    //exibirLista(l);

    return 0;
}
