typedef struct nodo* ptr_nodo;
struct nodo{
		elemento elem;
		ptr_nodo prox;
};

typedef struct {
		  ptr_nodo lista;
		  int tamanho;
		} lista_encadeada;

typedef lista_encadeada tipo_lista;


/* Implementações */

int tamanho(lista_encadeada le) {
	return le.tamanho;
}


int obter_elemento(lista_encadeada le, int i, elemento *e) {
	int j;
	ptr_nodo pnodo;

	if ((i <= le.tamanho) && (i > 0)) {
		pnodo = le.lista;
		for(j=2;j<=i;j++)
			pnodo = pnodo->prox;
		*e = pnodo->elem;
      	return 1;
	}
	else {
		*e = VL_NULO;
      return 0;
	}
}


void inicializa_lista(lista_encadeada *le) {
	le->tamanho = 0;
	le->lista = NULL;
}


int incluir_elemento(lista_encadeada *le, int i, elemento e) {
	int j;
    ptr_nodo pnodo_incluido, pnodo_anterior;

  	if ((i <= le->tamanho+1) && (i > 0)) {
      pnodo_incluido = (ptr_nodo)malloc(sizeof(struct nodo));
    	if (pnodo_incluido == NULL)
			return 0;   /* FALTA MEMÓRIA */
    	else {
       		pnodo_incluido->elem = e;
       		if (i == 1) {
       			pnodo_incluido->prox = le->lista;
          		le->lista = pnodo_incluido;
       		}
       		else {
          		pnodo_anterior = le->lista;
               		for (j=2; j<i; j++)
				pnodo_anterior = pnodo_anterior->prox;
          		pnodo_incluido->prox = pnodo_anterior->prox;
          		pnodo_anterior->prox = pnodo_incluido;
				}
       		le->tamanho++;
       		return 1;
    	}
   }
  else
    	return 0;    /* POSIÇÃO INVÁLIDA */
}


int alterar_elemento(lista_encadeada *le, int i, elemento e) {
	int j; ptr_nodo pnodo;
  	if ((i <= le->tamanho) && (i > 0)) {
     	pnodo = le->lista;
		for (j=2; j<=i;j++)
			pnodo = pnodo->prox;
      	pnodo->elem = e;
      	return 1;
	}
  	else
    		return 0; /* POSIÇÃO INVÁLIDA */
}


int excluir_elemento(lista_encadeada *le, int i) {
	 int j; ptr_nodo pnodo_excluido, pnodo_anterior;
  	if ((i <= le->tamanho) && (i > 0)) {
    		if (i == 1) {
       			pnodo_excluido = le->lista;
       			le->lista = pnodo_excluido->prox;
		}
    		else {
       			pnodo_anterior = le->lista;
               		for (j=2;j<i; j++)
			pnodo_anterior =  pnodo_anterior->prox;
       			pnodo_excluido = pnodo_anterior->prox;
       			pnodo_anterior->prox = pnodo_excluido->prox;
		}
    		free(pnodo_excluido);
    		le->tamanho = le->tamanho - 1;
    		return 1;
	}
  	else
    		return 0; /* POSIÇÃO INVÁLIDA */
}

int inverte_recursivo(tipo_lista *l, ptr_nodo a, ptr_nodo b, ptr_nodo aux){
   if (a == NULL) {
      a = l->lista;
      b = a->prox;
      l->lista = b->prox;
   }
   b->prox = a;
   a->prox = aux;
   aux=b;
   if ((l->lista != NULL) && (l->lista->prox!=NULL)) {
      a = l->lista;
      b = a->prox;
      l->lista = b->prox;
      inverte_recursivo(l, a, b, aux);
   }
   else {
      if (l->lista == NULL)
         l->lista = b;
      else
         l->lista->prox=aux;
   }
}

ptr_nodo pegaPenultimo(ptr_nodo p){
    if (p->prox->prox == NULL)
        return p;
    return pegaPenultimo(p->prox);
}

ptr_nodo pegaUltimo(ptr_nodo p){
    if (p->prox == NULL)
        return p;
    return pegaUltimo(p->prox);
}

int inverte(tipo_lista *l){
    ptr_nodo ultimo=NULL, penultimo = NULL, novoprimeiro=NULL;

    if (tamanho(*l) > 1) {
       novoprimeiro = ultimo = pegaUltimo(l->lista);
       penultimo = pegaPenultimo(l->lista);
       while (l->lista->prox != ultimo) {
          ultimo->prox = penultimo;
          ultimo = penultimo;
          ultimo->prox = NULL;
          penultimo = pegaPenultimo(l->lista);
       }
       ultimo->prox = l->lista;
       l->lista->prox = NULL;
       l->lista = novoprimeiro;
    }
}

int tamanho_quantidade_nodos(lista_encadeada l){
	int cont = 0;
	while(l.lista != NULL){
	   cont++;
	   l.lista = l.lista->prox;
	}
	return cont;
}
