/*
                    Cabeçalho

G7 - TEMA 5

- Componentes:

    Lucas Dantas Vasconcelos
    Lucas Oliveira Teles Cavancante
    Gabriel Lima Dantas
    Guilherme Ferreira Amâncio
    Pietro Oliveira Lima

- Questão:

TEMA 5 - Utilizando multilista faça um programa para gerenciamento de uma escola. O
programa deve cadastrar uma lista duplamente encadeada de classes. Além de apontar
para antecessor e sucessor, cada classe também deve apontar para uma lista simplesmente
encadeada onde estarão os alunos que estudam nessa classe. Para cada classe devem ser
guardadas as informações de série, turma, etapa, quantidade de alunos e nome do
professor. Para cada aluno devem ser guardadas as informações nome do aluno, idade e
matrícula.
O programa deve ter as seguintes funcionalidades.
    • Cadastrar classe
    • Matricular aluno em determinada classe
    • Remover aluno de classe
    • Exibir listagem de alunos matriculados em uma classe
    • Exibir lista de classes (com quantitativo de alunos matriculados em cada uma delas e nome do professor)
    • Remover classe (só é possível se não tiver alunos matriculados nela)
    • Pesquisar e exibir qual a classe de um aluno
    Obs: Com relação às informações das classes as séries podem ser 1o, 2o e etc. As turmas
    podem ser A, B, C e etc, as etapas são Fundamental I, Fundamental II e Médio.

*/

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

/* Função para inicializar as listas (inicializar os ponteiros com os devidos valores NULL ou 0)*/
void inicializaListaClasses(tipoListaClasses *listaClasses){
    listaClasses->inicio = NULL;
    listaClasses->fim = NULL;
    listaClasses->quant = 0;
} 

/* Função para cadastrar uma classe, caso não tenha nenhum elemento na classe */
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

/* Função para cadastrar uma nova classe no sistema, que já tenha ao menos um elemento */
int cadastrarClasse(tipoListaClasses *listaClasses, char serie[5], char turma, char etapa[20], char nomeProf[50]){
    if(listaClasses->quant == 0){                                                 // Verificação se já tem alguma coisa na lista,
        return cadastrarClasseVazia(listaClasses, serie, turma, etapa, nomeProf); // se não tiver elementos, basta inicializar a lista,
    }
    else{                                                                         // se tiver, começa a alocação de memória para mais um elemento
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

/* Função para cadastrar novo aluno na classe*/
int matricularAluno(tipoClasse *listaEnc, const char *nome, int *idade, char const *matricula) {
    tipoAluno *novoAluno = (tipoAluno*) malloc (sizeof(tipoAluno)); 
        if(novoAluno == NULL){
            printf("Erro na alocacao de memoria!");
            return 0;
        }

    strcpy(novoAluno->nome, nome);
    novoAluno->idade = idade;
    strcpy(novoAluno->matricula, matricula);
    novoAluno->prox = NULL;

    listaEnc->fim->prox = novoAluno;
    listaEnc->quantAlunos++;

    return 1;

}

/*Função que faz pesquisa sequencial para achar uma classe */
tipoClasse* pesqClasse(tipoListaClasses *listaEnc, const char *turma, const char *serie, const char *etapa){
    tipoClasse *atual;  //Variável que será usada para percorrer a lista*/
    if(listaEnc->fim->prox == NULL)
        return 0;
    atual = listaEnc->fim->prox;    
    while(atual != listaEnc->fim){
        if((strcmp(turma, atual->serie) == 0) && (strcmp(serie, atual->turma) == 0) && (strcmp(etapa, atual->etapa) == 0)){                                                                                                
            return atual;
        } 
        atual = atual->prox;
    }
    printf("Elemento não encontrado");
    return NULL;
}

/* Função para exibir lista de classes (com quantitativo de alunos matriculados em cada uma delas e nome do professor) */
int exibeClasses(tipoListaClasses *listaEnc){
  tipoClasse *atual;  //Variável que será usada para percorrer a lista*/
    if(listaEnc->fim->prox == NULL)
        printf("\nNenhuma classe cadastrada.");
        return 0;
    atual = listaEnc->fim->prox;
    printf("\nLista de calsses: ");
    printf("\n- Série: %s\n- Turma: %s\n- Etapa: %s\n- Quantidade de alunos: %s\n- Nome do professor: %s",
                                                        atual->serie, atual->turma, atual->etapa, atual->quantAlunos, atual->nomeProf);
    while(atual != listaEnc->fim){
        atual = atual->prox;
        printf("\n- Série: %s\n- Turma: %s\n- Etapa: %s\n- Quantidade de alunos: %s\n- Nome do professor: %s",
                                                        atual->serie, atual->turma, atual->etapa, atual->quantAlunos, atual->nomeProf);
        }
        return 1;
}

int main() {

    tipoListaClasses listaClasses; // Criação da lista que será passada nas funções de manipulação de nós cabeça com as classes das matérias
    inicializaListaClasses(&listaClasses); // Alocando o espaço na memória para essa lista
    tipoClasse classe; // Criação da lista que contém as informações dos alunos
    tipoClasse *aux;

    int op; // Variável para controle do switch

    /* Variáveis para pesquisar as classes - servem para auxiliar no cadastro do aluno */
    char serie[5];
    char turma;
    char etapa[20];

    /* Variáveis para cadastro do aluno */
    char nome[50];
    int idade;
    char matricula[30];

    do {
        printf("\n---- Bem vindo ao menu inicial do SIGMA ----");
        printf("\n\n        Menu inical");
        printf("\n 1 - Cadastrar nova classe no sistema");
        printf("\n 2 - Cadastrar novo aluno no sistema");
        printf("\n 3 - Exibir todas as classes cadastradas no sistema");
        printf("\n 0 - Encerar o SIGMA");

        printf("\nDigite sua opção:");
        scanf("%d",&op);

        switch (op) {

            case 1: 
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
            break;
            case 2: printf("\nSelecione a turma que deseja cadatrar o aluno");
                printf("\n\nDigite a série");
                scanf("%s", serie);
                printf("\n\nDigite a turma");
                scanf("%s", turma);
                printf("\n\nDigite a etapa");
                scanf("%s", etapa);

                aux = pesqClasse(&listaClasses, serie, turma, etapa);

                if (aux != NULL){
                    printf("\nDigite o nome do aluno");
                    scanf("%s", nome);
                    printf("\nDigite a idade do aluno");
                    scanf("%d", &idade);
                    printf("\nDigite a matricula do aluno");
                    scanf("%s", matricula);

                    matricularAluno(&aux, nome, idade, matricula);

                }
                else 
                    printf("\n\nALuno não cadastrado, tente novamente em uma turma existente");
            break;
            case 3:
                exibeClasses(&listaClasses);
            break;
    } // Fim do switch

    } while (op != 0); // Fim doa do-while

    return 0;
    
} // Fim do main