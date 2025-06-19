#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct aluno{
    char nome[50];
    int idade;
    char matricula[30];
    struct aluno *prox;
} tipoAluno;

typedef struct classe{
    char serie[5];
    char turma;
    char etapa[20];
    int quantAlunos;
    char nomeProf[50];
    tipoAluno *inicio, *fim;
    struct classe *ant;
    struct classe *prox;
} tipoClasse;

typedef struct listaClasses{
    tipoClasse *inicio, *fim;
    int quant;
} tipoListaClasses;

void inicializaListaClasses(tipoListaClasses *listaClasses){
    listaClasses->inicio = NULL;
    listaClasses->fim = NULL;
    listaClasses->quant = 0;
}

int cadastrarClasseVazia(tipoListaClasses *listaClasses, char serie[5], char turma, char etapa[20], char nomeProf[50]){
    tipoClasse *classe = (tipoClasse*) malloc (sizeof(tipoClasse));
    if(classe == NULL){
        printf("Erro na alocacao de memoria!");
        return 0;
    }
    strcpy(classe->serie, serie);
    classe->turma = turma;
    strcpy(classe->etapa, etapa);
    strcpy(classe->nomeProf, nomeProf);
    classe->ant = NULL;
    classe->prox = NULL;
    classe->inicio = NULL;
    classe->fim = NULL;
    classe->quantAlunos = 0;
    listaClasses->inicio = classe;
    listaClasses->fim = classe;
    listaClasses->quant++;
    return 1;
}

int cadastrarClasse(tipoListaClasses *listaClasses, char serie[5], char turma, char etapa[20], char nomeProf[50]){
    if(listaClasses->quant == 0){
        return cadastrarClasseVazia(listaClasses, serie, turma, etapa, nomeProf);
    }
    else{
        tipoClasse *classe = (tipoClasse*) malloc (sizeof(tipoClasse));
        if(classe == NULL){
            printf("Erro na alocacao de memoria!");
            return 0;
        }
        strcpy(classe->serie, serie);
        classe->turma = turma;
        strcpy(classe->etapa, etapa);
        strcpy(classe->nomeProf, nomeProf);
        classe->ant = listaClasses->fim;
        classe->prox = NULL;
        classe->inicio = NULL;
        classe->fim = NULL;
        classe->quantAlunos = 0;
        listaClasses->fim->prox = classe;
        listaClasses->fim = classe;
        listaClasses->quant++;
        return 1;
    }
}

int main(){
    tipoListaClasses listaClasses;
    inicializaListaClasses(&listaClasses);
    tipoClasse classe;
    printf("Digite a serie da classe(ex: 1º, 2º e etc): ");
    fgets(classe.serie, sizeof(classe.serie), stdin);
    classe.serie[strlen(classe.serie) - 1] = '\0';
    printf("Digite a turma da classe(ex: A, B, C e etc): ");
    scanf(" %c", &classe.turma);
    getchar();
    printf("Digite a etapa da classe(Fundamental I, Fundamental II e Médio): ");
    fgets(classe.etapa, sizeof(classe.etapa), stdin);
    classe.etapa[strlen(classe.etapa) - 1] = '\0';
    printf("Digite o nome do professor da classe: ");
    fgets(classe.nomeProf, sizeof(classe.nomeProf), stdin);
    classe.nomeProf[strlen(classe.nomeProf) - 1] = '\0';
    if(cadastrarClasse(&listaClasses, classe.serie, classe.turma, classe.etapa, classe.nomeProf)){
        printf("Serie: %s\nTurma: %c\nEtapa: %s\nNome do professor: %s\nQuantidade de classes: %d", listaClasses.inicio->serie, listaClasses.inicio->turma, listaClasses.inicio->etapa, listaClasses.inicio->nomeProf, listaClasses.quant);
    }
    return 0;
}