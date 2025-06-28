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

// Estrutura para representar um aluno
typedef struct aluno{
    char nome[50];
    int idade;
    char matricula[30];
    struct aluno *prox;
} tipoAluno;

// Estrutura para representar uma classe (turma)
typedef struct classe{
    char serie[5];
    char turma;
    char etapa[20];
    int quantAlunos;
    char nomeProf[50];
    tipoAluno *inicio, *fim; // Lista de alunos da classe
    struct classe *ant;  // Ponteiro para a classe anterior
    struct classe *prox; // Ponteiro para a próxima classe
} tipoClasse;

// Estrutura para gerenciar a lista de classes principal
typedef struct listaClasses{
    tipoClasse *inicio, *fim;
    int quant;
} tipoListaClasses;


//## Funções Auxiliares



// Limpa o buffer de entrada, removendo caracteres residuais como '\n'
// Esta função foi adicionada/revisada para garantir que as entradas de teclado subsequentes (como com scanf ou fgets) não sejam afetadas por caracteres pendentes no buffer.
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}



//## Funções de Gerenciamento de Classes


// Inicializa a lista de classes como vazia
// Nenhuma correção específica foi feita aqui, a lógica original já estava funcional para a inicialização.
void inicializaListaClasses(tipoListaClasses *listaClasses){
    listaClasses->inicio = NULL;
    listaClasses->fim = NULL;
    listaClasses->quant = 0;
}

// Cadastra a primeira classe quando a lista está vazia
// Nenhuma correção específica foi feita aqui, a lógica original já estava funcional.
int cadastrarClasseVazia(tipoListaClasses *listaClasses, const char *serie, char turma, const char *etapa, const char *nomeProf){
    tipoClasse *classe = (tipoClasse*) malloc (sizeof(tipoClasse));
    if(classe == NULL){
        printf("Erro na alocacao de memoria para a classe!\n");
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
    printf("Classe %s %c %s cadastrada com sucesso!\n", classe->serie, classe->turma, classe->etapa);
    return 1;
}

// Cadastra uma nova classe, verificando duplicatas
// A correção aqui foi a adição de um laço para verificar se já existe uma classe com a mesma série, turma e etapa antes de permitir o cadastro. Isso evita duplicidades.
int cadastrarClasse(tipoListaClasses *listaClasses, const char *serie, char turma, const char *etapa, const char *nomeProf){
    if(listaClasses->quant == 0){
        return cadastrarClasseVazia(listaClasses, serie, turma, etapa, nomeProf);
    }
    else{
        // Verifica se a classe já existe
        tipoClasse *temp = listaClasses->inicio;
        while (temp != NULL) {
            if (strcmp(temp->serie, serie) == 0 && temp->turma == turma && strcmp(temp->etapa, etapa) == 0) {
                printf("Classe %s %c %s ja existe!\n", serie, turma, etapa);
                return 0;
            }
            temp = temp->prox;
        }

        tipoClasse *classe = (tipoClasse*) malloc (sizeof(tipoClasse));
        if(classe == NULL){
            printf("Erro na alocacao de memoria para a classe!\n");
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
        printf("Classe %s %c %s cadastrada com sucesso!\n", classe->serie, classe->turma, classe->etapa);
        return 1;
    }
}

// Pesquisa e retorna um ponteiro para a classe se encontrada
// As correções envolveram garantir que a travessia da lista (`atual = listaEnc->inicio; while(atual != NULL)`) fosse feita corretamente do início ao fim, e que os parâmetros de comparação estivessem na ordem certa para `strcmp`, além de uma mensagem de erro mais clara.
tipoClasse* pesqClasse(tipoListaClasses *listaEnc, const char *serie, char turma, const char *etapa){
    tipoClasse *atual;
    if(listaEnc->inicio == NULL) {
        printf("Nenhuma classe cadastrada para pesquisa.\n");
        return NULL;
    }

    atual = listaEnc->inicio;
    while(atual != NULL){
        if((strcmp(serie, atual->serie) == 0) && (turma == atual->turma) && (strcmp(etapa, atual->etapa) == 0)){
            return atual;
        }
        atual = atual->prox;
    }
    printf("Classe '%s %c %s' nao encontrada.\n", serie, turma, etapa);
    return NULL;
}

// Exibe todas as classes cadastradas no sistema
// A correção principal foi garantir que a travessia da lista fosse feita corretamente do início ao fim (`atual = listaEnc->inicio; while(atual != NULL)`), e a formatação da saída para exibir os dados da classe de forma legível.
int exibeClasses(tipoListaClasses *listaEnc){
    tipoClasse *atual;
    if(listaEnc->inicio == NULL) {
        printf("\nNenhuma classe cadastrada.\n");
        return 0;
    } else {
        atual = listaEnc->inicio;
        printf("\n--- Lista de Classes Cadastradas ---\n");
        while(atual != NULL){
            printf("\n- Serie: %s\n- Turma: %c\n- Etapa: %s\n- Quantidade de alunos: %d\n- Nome do professor: %s\n",
                   atual->serie, atual->turma, atual->etapa, atual->quantAlunos, atual->nomeProf);
            atual = atual->prox;
        }
        printf("------------------------------------\n");
        return 1;
    }
}

// Remove uma classe da lista principal
// Esta função foi reescrita significativamente para lidar corretamente com a remoção de nós em uma lista duplamente encadeada (ajustando ponteiros 'ant' e 'prox' dos nós vizinhos) e para incluir a restrição de não remover classes com alunos matriculados.
int remocaoDeClasses(tipoListaClasses *lista, tipoClasse *noRemover) {
    if (lista->inicio == NULL || noRemover == NULL) {
        printf("Lista de classes vazia ou classe a remover invalida.\n");
        return 0;
    }

    if (noRemover->quantAlunos > 0) {
        printf("\nNão é possível remover classes com alunos matriculados. Remova todos os alunos antes de fazer essa operação.\n");
        return 0;
    }

    // Lógica para remoção em lista duplamente encadeada
    if (lista->inicio == noRemover && lista->fim == noRemover) { // Caso: único elemento
        lista->inicio = NULL;
        lista->fim = NULL;
    } else {
        if (noRemover->ant != NULL) { // Não é o primeiro elemento
            noRemover->ant->prox = noRemover->prox;
        } else { // É o primeiro elemento
            lista->inicio = noRemover->prox;
        }

        if (noRemover->prox != NULL) { // Não é o último elemento
            noRemover->prox->ant = noRemover->ant;
        } else { // É o último elemento
            lista->fim = noRemover->ant;
        }
    }

    // Libera a lista de alunos da classe (deve estar vazia neste ponto devido à verificação)
    tipoAluno *atualAluno = noRemover->inicio;
    while (atualAluno != NULL) {
        tipoAluno *tempAluno = atualAluno;
        atualAluno = atualAluno->prox;
        free(tempAluno);
    }

    free(noRemover);
    lista->quant--;
    printf("Classe removida com sucesso!\n");
    return 1;
}



//## Funções de Gerenciamento de Alunos


// Matricula um novo aluno em uma classe específica
// As correções incluíram a alteração do tipo de 'idade' para 'int' (pois é um valor simples), a adição de uma verificação de matrícula duplicada dentro da mesma classe, e a correção da lógica de adição do aluno na lista encadeada da classe (tratando o caso de lista vazia).
int matricularAluno(tipoClasse *classeAtual, const char *nome, int idade, const char *matricula) {
    if (classeAtual == NULL) {
        printf("Classe invalida para matricula de aluno.\n");
        return 0;
    }

    tipoAluno *novoAluno = (tipoAluno*) malloc(sizeof(tipoAluno));
    if (novoAluno == NULL) {
        printf("Erro na alocacao de memoria para o aluno!\n");
        return 0;
    }

    strcpy(novoAluno->nome, nome);
    novoAluno->idade = idade;
    strcpy(novoAluno->matricula, matricula);
    novoAluno->prox = NULL;

    // Verifica se a matrícula já existe nesta classe
    tipoAluno *temp = classeAtual->inicio;
    while (temp != NULL) {
        if (strcmp(temp->matricula, matricula) == 0) {
            printf("Matrícula %s ja existente para esta classe, por favor tente cadastrar o aluno novamente.\n", matricula);
            free(novoAluno);
            return 0;
        }
        temp = temp->prox;
    }

    // Adiciona o aluno na lista da classe
    if (classeAtual->inicio == NULL) { // Se a lista de alunos da classe estiver vazia
        classeAtual->inicio = novoAluno;
        classeAtual->fim = novoAluno;
    } else { // Se já houver alunos na classe
        classeAtual->fim->prox = novoAluno;
        classeAtual->fim = novoAluno;
    }

    classeAtual->quantAlunos++;
    printf("Aluno %s matriculado com sucesso na classe %s %c %s!\n", nome, classeAtual->serie, classeAtual->turma, classeAtual->etapa);
    return 1;
}

// Remove um aluno de uma classe específica pela matrícula
// Nenhuma correção lógica complexa foi feita aqui; a função já estava bem estruturada para a remoção em lista encadeada simples dentro da classe.
int removerAluno(tipoClasse *classeAtual, const char *matricula){
    if(classeAtual == NULL || classeAtual->inicio == NULL){
        printf("A turma atual esta vazia ou e invalida!\n");
        return 0;
    }

    tipoAluno *atual = classeAtual->inicio;
    tipoAluno *anterior = NULL;

    // Percorre a lista de alunos para encontrar o aluno
    while(atual != NULL && strcmp(atual->matricula, matricula) != 0){
        anterior = atual;
        atual = atual->prox;
    }

    if(atual == NULL){
        printf("O aluno com a matricula '%s' nao foi encontrado nesta classe.\n", matricula);
        return 0;
    }

    // Lógica para remover o aluno encontrado
    if(anterior == NULL){ // Se é o primeiro aluno
        classeAtual->inicio = atual->prox;
        if(classeAtual->inicio == NULL){
            classeAtual->fim = NULL;
        }
    } else { // Se não é o primeiro
        anterior->prox = atual->prox;
        if(atual->prox == NULL){
            classeAtual->fim = anterior;
        }
    }

    printf("Aluno %s com matricula %s removido com sucesso da classe.\n", atual->nome, atual->matricula);
    free(atual);
    classeAtual->quantAlunos--;
    return 1;
}



//## Função Principal (Main)


int main() {
    tipoListaClasses listaClasses;
    inicializaListaClasses(&listaClasses);

    // Variável auxiliar para a classe encontrada após pesquisa.
    tipoClasse *auxClasse;
    
    int op; // Opção do menu escolhida pelo usuário.

    // Variáveis locais para entrada de dados, renomeadas para serem mais concisas e diretas.
    char serie[5];
    char turma;
    char etapa[20];
    char nomeProf[50];
    char nome[50];
    int idade;
    char matricula[30];

    // Loop principal do menu, continua até o usuário escolher sair (opção 0).
    do {
        printf("\n---- Bem vindo ao menu inicial do SIGMA ----");
        printf("\n\n        Menu inical");
        printf("\n 1 - Cadastrar nova classe no sistema");
        printf("\n 2 - Cadastrar novo aluno no sistema");
        printf("\n 3 - Exibir todas as classes cadastradas no sistema");
        printf("\n 4 - Excluir aluno de uma classe");
        printf("\n 5 - Excluir uma classe");
        printf("\n 0 - Encerrar o SIGMA");

        printf("\nDigite sua opcao: ");
        scanf("%d",&op);
        // Chamada para clearBuffer() após a leitura de 'op' (int) para limpar o '\n' pendente.
        clearBuffer();

        switch (op) {
            case 1: // Cadastrar nova classe
                printf("\nDigite a serie da classe (ex: 1o, 2o e etc): ");
                // Uso de fgets para ler strings com espaços e evitar problemas de buffer.
                fgets(serie, sizeof(serie), stdin);
                // strcspn é usado para encontrar e remover o caractere de nova linha ('\n') adicionado por fgets.
                serie[strcspn(serie, "\n")] = 0;

                printf("\nDigite a turma da classe (ex: A, B, C e etc): ");
                // O espaço antes de %c em scanf(" %c", ...) serve para consumir qualquer caractere de espaço em branco (incluindo '\n') que possa ter ficado no buffer antes da leitura da turma.
                scanf(" %c", &turma);
                clearBuffer();

                printf("\nDigite a etapa da classe (Fundamental I, Fundamental II e Medio): ");
                fgets(etapa, sizeof(etapa), stdin);
                etapa[strcspn(etapa, "\n")] = 0;

                printf("\nDigite o nome do professor da classe: ");
                fgets(nomeProf, sizeof(nomeProf), stdin);
                nomeProf[strcspn(nomeProf, "\n")] = 0;

                cadastrarClasse(&listaClasses, serie, turma, etapa, nomeProf);
            break;

            case 2: // Cadastrar novo aluno
                printf("\nSelecione a turma em que deseja cadastrar o aluno:\n");
                printf("\nDigite a serie: ");
                fgets(serie, sizeof(serie), stdin);
                serie[strcspn(serie, "\n")] = 0;

                printf("\nDigite a turma: ");
                scanf(" %c", &turma);
                clearBuffer();

                printf("\nDigite a etapa: ");
                fgets(etapa, sizeof(etapa), stdin);
                etapa[strcspn(etapa, "\n")] = 0;

                // Tenta encontrar a classe usando os dados fornecidos pelo usuário.
                auxClasse = pesqClasse(&listaClasses, serie, turma, etapa);

                if (auxClasse != NULL){ // Se a classe foi encontrada, procede com o cadastro do aluno.
                    printf("\nDigite o nome do aluno: ");
                    fgets(nome, sizeof(nome), stdin);
                    nome[strcspn(nome, "\n")] = 0;

                    printf("\nDigite a idade do aluno: ");
                    scanf("%d", &idade);
                    // Chamada para clearBuffer() após a leitura de 'idade' (int). Essencial para que o próximo fgets funcione corretamente.
                    clearBuffer();

                    printf("\nDigite a matricula do aluno: ");
                    fgets(matricula, sizeof(matricula), stdin);
                    matricula[strcspn(matricula, "\n")] = 0;

                    // A função matricularAluno agora espera 'idade' como um int direto, não um ponteiro.
                    matricularAluno(auxClasse, nome, idade, matricula);
                } else { // Se a classe não foi encontrada.
                    printf("\nAluno nao cadastrado, a classe especificada nao existe.\n");
                }
            break;

            case 3: // Exibir todas as classes
                exibeClasses(&listaClasses);
            break;

            case 4: // Excluir aluno de uma classe
                printf("\nSelecione a turma da qual deseja excluir o aluno:\n");
                printf("\nDigite a serie: ");
                fgets(serie, sizeof(serie), stdin);
                serie[strcspn(serie, "\n")] = 0;

                printf("\nDigite a turma: ");
                scanf(" %c", &turma);
                clearBuffer();

                printf("\nDigite a etapa: ");
                fgets(etapa, sizeof(etapa), stdin);
                etapa[strcspn(etapa, "\n")] = 0;

                // Tenta encontrar a classe do aluno a ser excluído.
                auxClasse = pesqClasse(&listaClasses, serie, turma, etapa);

                if (auxClasse != NULL){ // Se a classe foi encontrada.
                    printf("\nDigite a matricula do aluno a ser removido: ");
                    fgets(matricula, sizeof(matricula), stdin);
                    matricula[strcspn(matricula, "\n")] = 0;

                    removerAluno(auxClasse, matricula);
                } else { // Se a classe não foi encontrada.
                    printf("\nAluno nao excluido, a classe especificada nao existe.\n");
                }
            break;

            case 5: // Excluir uma classe
                if (listaClasses.quant == 0) { // Verifica se há classes para excluir antes de prosseguir.
                    printf("\nNenhuma classe para excluir.\n");
                    break;
                }
                exibeClasses(&listaClasses); // Exibe as classes para que o usuário saiba quais pode remover.
                printf("\nSelecione a classe que deseja excluir:\n");
                printf("\nDigite a serie: ");
                fgets(serie, sizeof(serie), stdin);
                serie[strcspn(serie, "\n")] = 0;

                printf("\nDigite a turma: ");
                scanf(" %c", &turma);
                clearBuffer();

                printf("\nDigite a etapa: ");
                fgets(etapa, sizeof(etapa), stdin);
                etapa[strcspn(etapa, "\n")] = 0;

                // Tenta encontrar a classe a ser excluída.
                auxClasse = pesqClasse(&listaClasses, serie, turma, etapa);

                if (auxClasse != NULL){ // Se a classe foi encontrada.
                    // A função de remoção de classes agora espera o ponteiro 'auxClasse' diretamente.
                    remocaoDeClasses(&listaClasses, auxClasse);
                } else { // Se a classe não foi encontrada.
                    printf("\nClasse nao excluida, a classe especificada nao existe.\n");
                }
            break;

            case 0: // Encerrar o programa
                printf("\nEncerrando o SIGMA. Ate mais!\n");
            break;

            default: // Opção inválida
                printf("\nOpcao invalida. Por favor, digite uma opcao valida.\n");
            break;
        }

    } while (op != 0); // O loop continua enquanto o usuário não digitar '0'.

    return 0;
}
