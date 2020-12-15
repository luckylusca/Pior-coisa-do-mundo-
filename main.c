#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct onibus_trajeto{
    int terminal;
    char data[9];
    int hora;
    char placa[8];
    int empresa;
    struct onibus_trajeto *prox;
};
typedef struct onibus_trajeto elemento;

const elemento VL_NULO = {0, "", 0, "", 0, NULL};
#include "tad_list2.c"

tipo_lista lista;

typedef struct {
           char placa[7];
           int tempo_trajeto_acumulado;
           int qt;
       } tipo_tempos;

// ============================================ TELAS ==============================================
void monta_tela() {
        printf("\n\n\nMENU - Programa Trajetos Terminais");
        printf("\n\n1 - Carregar lista");
        printf("\n2 - Listar dados");
        printf("\n3 - Media tempo das viagens dos onibus");
        printf("\n4 - Valor a receber por empresa");
        printf("\n5 - Inverter lista (sem recursividade)");
        printf("\n6 - Inverter lista (COM RECURSIVIDADE)");
        printf("\n7 - Tamanho da lista (quantidade de nodos na lista encadeadade)");
        printf("\n9 - Sair");
        printf("\n\nDigite a sua escolha: ");
}

char escolhe_opcao() {
	return getchar();
}

void limpa_tela() {
   #if defined(WIN32) && !defined(UNIX)
      system("cls");
   #elif defined(UNIX) && !defined(WIN32)
      system("clear");
   #else
      system("clear");
   #endif
}

// ====================================== CARREGAR DADOS NA LISTA ==============================================
int carregar_lista(tipo_lista *l) {
    FILE *arquivo;
    arquivo = fopen("2019-09-06.txt","r");
    elemento t;
    inicializa_lista(l);
    if (arquivo==NULL) {
        printf("\nErro - fopen()\n");
        return 0;
    }
    else {
       while (1) {
          fscanf(arquivo, "%d %s %d %s %d", &t.terminal, &t.data, &t.hora, &t.placa, &t.empresa);
          if (!feof(arquivo))
             incluir_elemento(l,tamanho(*l)+1,t);
          else
             break;
       }
    }
    fclose(arquivo);
    return 1;
}

// ======================================== LISTAR DADOS ====================================================
void listar(tipo_lista l){
   elemento t;
   if(tamanho(l) == 0) {
       printf("\nLista vazia!\n");
   }
   for(int i=1;i<=tamanho(l);i++){
        obter_elemento(l, i, &t);
        printf("%d \t%s \t%04d \t%s \t%d \n", t.terminal, t.data, t.hora, t.placa, t.empresa);
   }
}


//======================================== CALCULO DA MÉDIA ====================================================
int calcula_tempo_intervalos(int tempo1, int tempo2) {
   int xH, yH, xM, yM, horas, minutos;
   xH = tempo1/100; // pega a primeira parte da hora
   yH = tempo2/100;
   xM = tempo1-((int)tempo1/100)*100; // pega a segunda parte da hora
   yM = tempo2-((int)tempo2/100)*100;
   if (xM > yM) {
      yH--;
      yM=yM+60;
   }
   horas = yH - xH;
   minutos = yM - xM;
   return (horas*60 + minutos);
}

int placa_esta_no_vetor(char placa[7], tipo_tempos vet[], int n){
   int ret=0;
   for (int i=0; i<=n; i++) {
      if (!strcmp(placa, vet[i].placa)) {
          return (ret=1);
      }
   }
   return ret;
}

int media_tempo(tipo_lista l){
    elemento t1, t2; int soma=0, cont=0, k=0;
    tipo_tempos vet_tempos[1000];

    if (!tamanho(l))
       printf("\nNenhum trajeto para realizar o calculo!\n");
    else {
       for (int i=1; i < tamanho(l); i++) {
             obter_elemento(l, i, &t1);
             if (!(placa_esta_no_vetor(t1.placa, vet_tempos,k-1))) { // ainda não usou para o cálculo da média
                 for (int j = i+1; j <= tamanho(l); j++) {
                     obter_elemento(l, j, &t2);
                     if (!strcmp(t1.placa,t2.placa)) {
                        soma = soma + calcula_tempo_intervalos(t1.hora,t2.hora);
                        t1 = t2;
                        cont++;
                     }
                 }
                 strcpy(vet_tempos[k].placa, t1.placa);
                 vet_tempos[k].tempo_trajeto_acumulado = soma;
                 vet_tempos[k].qt=cont;
                 cont=soma=0;
                 k++;
             }

       }
       printf("\nPlaca\t || Media(em minutos)\n");
       for (int i=0; i<k; i++) {
         printf("%s\t || %0.0f\n", vet_tempos[i].placa, (float)vet_tempos[i].tempo_trajeto_acumulado/vet_tempos[i].qt);
       }
   }
}

// =========================================== VALOR A RECEBER PELAS EMPRESAS ===========================================
int valor_por_empresa(tipo_lista l) {
    elemento t; int cont, i, j;

    printf("\nEmpresa\t\t || Valor Acumulado\n");
    for(i = 1; i <= 100; i++) {
       cont=0;
       for(j = 1; j <= tamanho(l); j++) {
           obter_elemento(l, j, &t);
           if (t.empresa == i) cont++;
       }
       if (cont>0) printf("%d\t\t || R$ %d.00\n",i, cont*100);
    }


/* OUTRA FORMA - COM CUSTO COMPUTACIONAL MENOR
    elemento t;
    typedef struct {
           int empresa;
           int valor_acumulado;
       } tipo_empresas_valor;

    tipo_empresas_valor vet[100];

    for (int i=0; i<100; i++,vet[i].valor_acumulado=0); // inicializa vetor
    if (!tamanho(l))
       printf("\nNenhum trajeto para realizar o calculo!\n");

    for(int i = 1; i <= tamanho(l); i++) {
        obter_elemento(l, i, &t);
        vet[t.empresa-1].valor_acumulado = vet[t.empresa-1].valor_acumulado + 100; // R$ 100,00 por cada trajeto

    }
    printf("\nEmpresa\t\t || Valor Acumulado\n");
    for (int i = 0; i < 100; i++) {
       if (vet[i].valor_acumulado > 0) {
          printf("%d\t\t || R$ %d.00\n",i+1, vet[i].valor_acumulado);
       }
    }
*/
}


// =========================================== PROGRAMA PRINCIPAL ================================================
int main() {
   char opcao;
   inicializa_lista(&lista);
   do {
        limpa_tela();
   	monta_tela();
        opcao = escolhe_opcao();
   	switch (opcao) {
      	case '1':
            carregar_lista(&lista);
            printf("\nLista carregada!\n");
            break;
      	case '2':
            listar(lista);
            break;
      	case '3':
            media_tempo(lista);
            break;
      	case '4':
            valor_por_empresa(lista);
            break;
      	case '5':
            inverte(&lista); // função de implementação no TAD
            printf("\nLista invertida!\n");
            break;
      	case '6':
            inverte_recursivo(&lista,NULL,NULL,NULL); // função de implementação no TAD
            printf("\nLista invertida!\n");
            break;
      	case '7':
            printf("\nQuantidade de nodos: %d\n",tamanho_quantidade_nodos(lista)); // função de implementação no TAD
            break;
        case '9':
            exit(1);
            break;
        }
        printf("tecle <enter> para continuar");
        getchar(); getchar();
   } while (1);
}
