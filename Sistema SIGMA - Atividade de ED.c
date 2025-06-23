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

/* ************************ Função para inicializar as listas (inicializar os ponteiros com os devidos valores NULL ou 0) ************************ */
void inicializaListaClasses(tipoListaClasses *listaClasses){
    listaClasses->inicio = NULL;
    listaClasses->fim = NULL;
    listaClasses->quant = 0;
}

/* ************************ Função para cadastrar uma classe, caso não tenha nenhum elemento na classe ************************ */
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

/* ************************ Função para cadastrar uma nova classe no sistema, que já tenha ao menos um elemento ************************ */
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

/* ************************ Função para cadastrar novo aluno na classe ************************ */
int matricularAluno(tipoClasse *listaEnc, const char *nome, int *idade, char const *matricula) {
    tipoAluno *novoAluno = (tipoAluno*) malloc (sizeof(tipoAluno));
    tipoAluno *aux = (tipoAluno*) malloc (sizeof(tipoAluno));
        if(novoAluno == NULL){
            printf("Erro na alocacao de memoria!");
            return 0;
        }

    aux = listaEnc->inicio;
    strcpy(novoAluno->nome, nome);
    novoAluno->idade = idade;

    // Verificação se já existe algum aluno com a mesma matrícula, o que não pode ocorrer
    while (aux->prox != NULL){
        if (strcmp(aux->matricula, matricula) == 0){
            printf("Matrícula já existente, por favor tente cadastrar o aluno novamente.");
            return 0;
        }
    }

    strcpy(novoAluno->matricula, matricula);
    novoAluno->prox = NULL;

    listaEnc->fim->prox = novoAluno;
    listaEnc->quantAlunos++;

    return 1;

}

/* ************************ Função que faz a remoção de uma classe da lista (função para lsita circular) ************************ */
int remocaoDeClasses(tipoListaClasses *lista, tipoClasse *noRemover){
    if (lista->fim == NULL){
        return 0;
    }

    // Verificando a condição de não ter alunos matriculados na referida turma
    if (noRemover->quantAlunos > 0){
        printf("\nNão é possível remover classes com alunos matriculados, remova todos os alunos antes de fazer essa operação.\n");
        return 0;
    } else {

        // Criação de auxiliares para poder remorver os nós da lista
        tipoClasse *anterior = lista->fim;
        tipoClasse *atual = lista->fim->prox;

        while(atual != lista->fim){

            // Verificação se os nós são iguais
            if(strcmp(atual->turma, noRemover->turma) == 0 && strcmp(atual->serie, noRemover->serie) == 0 &&
               strcmp(atual->etapa, noRemover->etapa) == 0 && strcmp(atual->nomeProf, noRemover->nomeProf) == 0){

                anterior->prox = atual->prox;

                if(atual == lista->fim){
                    lista->fim = anterior;
                }

                if(atual->prox == atual){
                    lista->fim = NULL;
                }

                free(atual); // Liberação de momória
                lista->quant--;

                return 1;
            }

            anterior = atual;
            atual = atual->prox;

        }
        return 1;
    }
}

/* ************************ Função para remover o aluno de certa turma ************************ */
int removerAluno(tipoClasse *listaEnc,  char const *matricula){
	if(listaEnc->inicio == NULL){ //Checagem caso a turma já esteja vazia
		printf("A turma atual já esta vazia!");
		return 0;
	}

    // Estabelecimento de ponteiros auxiliares para a procura
	tipoAluno *atual = listaEnc->inicio;
	tipoAluno *anterior = NULL;

	while(atual != NULL && strcmp(atual->matricula, matricula) != 0){ // Loop de procura
		anterior = atual;
		atual = atual->prox;
	}

	if(atual == NULL){ // Para caso o programa nao encontre a matrícula fornercida
		printf("O aluno com esta matricula nao foi encontrado\n");
		return 0;
	}

	if(anterior == NULL){ // No caso de o aluno ser o inicio, ou seja, o elemento anterior nao existe
		listaEnc->inicio = atual->prox;
		if(listaEnc->quantAlunos == 1){
			listaEnc->fim = NULL;
		}
	} else if(atual->prox == NULL){ // No caso do aluno ser o fim, ou seja, o proximo elemento nao existe
		listaEnc->fim = anterior;
		anterior->prox = NULL;
	  } else{ // Caso geral
		  anterior->prox = atual->prox;
		}

	free(atual); // Liberação da memória
	listaEnc->quantAlunos--;
	return 1;
}

/* ************************ Função que faz pesquisa sequencial para achar uma classe ************************ */
tipoClasse* pesqClasse(tipoListaClasses *listaEnc, const char *turma, const char *serie, const char *etapa){
    tipoClasse *atual;  //Variável que será usada para percorrer a lista*/
    if(listaEnc->inicio == NULL)
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
    if(listaEnc->inicio == NULL) {
        printf("\nNenhuma classe cadastrada.\n");
        return 0;
    } else {
    atual = listaEnc->fim->prox;
    printf("\nLista de classes: ");
    printf("\n- Série: %s\n- Turma: %s\n- Etapa: %s\n- Quantidade de alunos: %s\n- Nome do professor: %s",
                                                        atual->serie, atual->turma, atual->etapa, atual->quantAlunos, atual->nomeProf);
    while(atual != listaEnc->fim){
        atual = atual->prox;
        printf("\n- Série: %s\n- Turma: %s\n- Etapa: %s\n- Quantidade de alunos: %s\n- Nome do professor: %s",
                                                        atual->serie, atual->turma, atual->etapa, atual->quantAlunos, atual->nomeProf);
        }
        return 1;
    }
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
        printf("\n 4 - Excluir aluno de uma classe");
        printf("\n 5 - Excluir uma classe");
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
                    printf("\n\nAluno não cadastrado, tente novamente em uma turma existente");
            break;
            case 3:
                exibeClasses(&listaClasses);
            break;
            case 4: printf("\nSelecione a turma que deseja excluir o aluno");
                printf("\n\nDigite a série");
                scanf("%s", serie);
                printf("\n\nDigite a turma");
                scanf("%s", turma);
                printf("\n\nDigite a etapa");
                scanf("%s", etapa);

                aux = pesqClasse(&listaClasses, serie, turma, etapa);

                if (aux != NULL){
                    printf("\nDigite a matricula do aluno");
                    scanf("%s", matricula);
                    removerAluno( &aux,  matricula);
                } else
                    printf("\n\nAluno não excluído, tente novamente em uma turma existente");
            break;
            case 5:

                // Verificação, se não tiver nenhuma classe, não é possível excluir.
                if (exibeClasses(&listaClasses)){ // Isso foi feito apra evitar que o programa pare.

                printf("\nSelecione a classe que deseja excluir");
                printf("\n\nDigite a série");
                scanf("%s", serie);
                printf("\n\nDigite a turma");
                scanf("%s", turma);
                printf("\n\nDigite a etapa");
                scanf("%s", etapa);

                aux = pesqClasse(&listaClasses, serie, turma, etapa);

                if (aux != NULL){
                    remocaoDeClasses(&listaClasses, &aux);
                } else
                    printf("\n\Classe não excluída, tente novamente em uma turma existente\n");
                }
                else
                    printf("\nInsira alguma classe antes de tentar excluir.\n");
            break;
    } // Fim do switch

    } while (op != 0); // Fim doa do-while

    return 0;

} // Fim do main
