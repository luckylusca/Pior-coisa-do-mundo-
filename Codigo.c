#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct aluno{
    int cod_aluno;
    int serie;
    float nota1;
    float nota2;
    float nota3;
    float nota_recuperacao;
    char nome[50];
    struct aluno *prox;
};
typedef struct aluno elemento;

const elemento VL_NULO = {0, 0, 0, 0, 0, 0, "", NULL};

#include "tad_list2.c"
tipo_lista lista;

struct disciplinas{
    int cod_disciplina;
    char sigla_disciplina[4];
};
typedef struct disciplinas cad;


void monta_tela() {
    printf("\n----- MENU - DIARIO DE CLASSE ----- ");
    printf("\n\n1 - Carregar listas");
    printf("\n2 - Listar dados");
    printf("\n3 - Cadastrar aluno");
    printf("\n4 - Diario de disciplina");
    printf("\n9 - Sair");
    printf("\n\nDigite a sua escolha: ");
}

char escolhe_opcao() {
	return getchar();
}

void limpa_tela() {
    system("cls");
}



int carregar_lista(tipo_lista *l) {
    FILE *arquivo; FILE *arq;
    arquivo = fopen("alunos.txt","r");
    arq = fopen("arq.txt","r");
    elemento t;
    inicializa_lista(l);
    if (arquivo==NULL) {
        printf("\nErro - fopen()\n");
        return 0;
    }
    else {
       while (1) {
          fscanf(arquivo, "%d %d %s ", &t.cod_aluno, &t.serie, &t.nome);

          if (!feof(arquivo));
             incluir_elemento(l,tamanho(*l)+1,t);
          else
             break;
       }
    }
    fclose(arquivo);
    return 1;
}

void listar(tipo_lista l){
   elemento t;
   if(tamanho(l) == 0) {
       printf("\nLista vazia!\n");
   }
   for(int i=1;i<=tamanho(l);i++){
        obter_elemento(l, i, &t);
        printf("%d \t%s \t%04d \t%s \t%d \n");
   }
}

int main() {
   char opcao;
   inicializa_lista(&lista);
   do{
    limpa_tela();
    monta_tela();
    opcao = escolhe_opcao();
   	switch (opcao) {
      	case '1':
            carregar_lista(&lista);
            printf("\nLista carregada!\n");
            break;
      	case '2':
            break;
      	case '3':
            break;
      	case '4':
            break;
        case '9':
            exit(1);
            break;
        }
        printf("tecle <enter> para continuar");
        getchar();
   } while (1);
}
