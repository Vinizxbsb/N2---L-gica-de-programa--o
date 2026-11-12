#include <stdio.h>
#include <string.h>

#define MAX_TUTORES 50
#define MAX_ANIMAIS 50
#define MAX_ATENDIMENTOS 100

typedef struct {
    int codigo; 
    char nomeCompleto[50];
    char cpf[15];
    char telefone[15];
} Tutor;

typedef struct {
    int codigo;
    char nome_pet[50];
    char especie[30];
    int idade_pet;
    int codigoTutor;
} Animal;

typedef struct {
    int codigoAnimal;
    int tipoServico; 
    int quantidade;
    float valorTotal;
} Atendimento;

void menu(){
    printf("\n===== Menu =====\n");
    printf("1. Cadastrar tutor\n");
    printf("2. Cadastrar animal\n");
    printf("3. Listar tutores\n");
    printf("4. Listar animais\n");
    printf("5. Listar animais por tutor\n");
    printf("6. Buscar tutor\n");
    printf("7. Alterar dados do tutor\n");
    printf("8. Buscar animal\n"); 
    printf("9. Registrar atendimento\n"); 
    printf("10. Exibir relatorio da sessao\n"); 
    printf("0. Sair\n");
}

void cadastrarTutor(Tutor *tutores, int *totalTutores){
    if(*totalTutores >= MAX_TUTORES){
        printf("Limite de tutores atingido!\n");
        return;
    }

    tutores[*totalTutores].codigo = *totalTutores + 1; 

    printf("\nCodigo do tutor: %d\n", tutores[*totalTutores].codigo);
    printf("Digite o nome completo do tutor: ");

    fgets(tutores[*totalTutores].nomeCompleto,
          sizeof(tutores[*totalTutores].nomeCompleto), stdin);

    tutores[*totalTutores].nomeCompleto[strcspn(tutores[*totalTutores].nomeCompleto, "\n")] = '\0';

    printf("Digite o CPF do tutor: ");
    scanf(" %[^\n]", tutores[*totalTutores].cpf);

    printf("Digite o telefone do tutor: ");
    scanf(" %[^\n]", tutores[*totalTutores].telefone);

    (*totalTutores)++;

    printf("\nTutor cadastrado com sucesso!\n");
}

void cadastrarAnimal(Animal *animais, int *totalAnimais, Tutor *tutores, int totalTutores){
    int i;
    int tutorEncontrado = 0;

    if(*totalAnimais >= MAX_ANIMAIS){
        printf("Limite de animais atingido!\n");
        return;
    }

    if(totalTutores == 0){
        printf("Nenhum tutor cadastrado! Cadastre um tutor primeiro.\n");
        return;
    }

    animais[*totalAnimais].codigo = *totalAnimais + 1;

    printf("\nCodigo do animal: %d\n", animais[*totalAnimais].codigo);

    printf("Digite o nome do animal: ");
    scanf(" %[^\n]", animais[*totalAnimais].nome_pet);

    printf("Digite a especie do animal: ");
    scanf(" %[^\n]", animais[*totalAnimais].especie);

    printf("Digite a idade do animal: ");
    scanf("%d", &animais[*totalAnimais].idade_pet);

    printf("Digite o codigo do tutor: ");
    scanf("%d", &animais[*totalAnimais].codigoTutor);

    for(i = 0; i < totalTutores; i++){
        if(animais[*totalAnimais].codigoTutor == tutores[i].codigo){
            tutorEncontrado = 1;
            break;
        }
    }

    if(tutorEncontrado == 0){
        printf("\nTutor nao encontrado! Cadastro cancelado.\n");
        return;
    }

    (*totalAnimais)++;
    printf("\nAnimal cadastrado com sucesso!\n");
}

void listarAnimais(Animal *animais, int totalAnimais){
    int i;
    if(totalAnimais == 0){
        printf("\nNenhum animal cadastrado!\n");
        return;
    }
    printf("\n===== LISTA DE ANIMAIS =====\n");
    for(i = 0; i < totalAnimais; i++){
        printf("\nCodigo: %d\n", animais[i].codigo);
        printf("Nome: %s\n", animais[i].nome_pet);
        printf("Especie: %s\n", animais[i].especie);
        printf("Idade: %d\n", animais[i].idade_pet);
        printf("Codigo do tutor: %d\n", animais[i].codigoTutor);
        printf("--------------------------\n");
    }
}

void buscarAnimal(Animal *animais, int totalAnimais){
    int codigo;
    int i;
    int encontrado = 0;

    if(totalAnimais == 0){
        printf("\nNenhum animal cadastrado!\n");
        return;
    }

    printf("\nDigite o codigo do animal que deseja buscar: ");
    scanf("%d", &codigo);

    for(i = 0; i < totalAnimais; i++){
        if(animais[i].codigo == codigo){
            printf("\n===== ANIMAL ENCONTRADO =====\n");
            printf("Codigo: %d\n", animais[i].codigo);
            printf("Nome: %s\n", animais[i].nome_pet);
            printf("Especie: %s\n", animais[i].especie);
            printf("Idade: %d\n", animais[i].idade_pet);
            printf("Codigo do tutor: %d\n", animais[i].codigoTutor);
            encontrado = 1;
            break;
        }
    }
    if(encontrado == 0){
        printf("\nAnimal nao encontrado!\n");
    }
}

void registarAtendimento(Atendimento atendimentos[], int *contador, Animal *animais, int totalAnimais) {
    if (*contador >= MAX_ATENDIMENTOS) {
        printf("Limite de atendimentos atingido!\n");
        return;
    }

    int codAnimal;
    printf("Introduza o codigo do animal: ");
    scanf("%d", &codAnimal);

    int animalEncontrado = 0;
    for (int i = 0; i < totalAnimais; i++) {
        if (animais[i].codigo == codAnimal) {
            animalEncontrado = 1;
            break;
        }
    }

    if (!animalEncontrado) { 
        printf("Erro: Animal inexistente. Cadastre o animal primeiro.\n"); 
        return; 
    }

    int servico, qtd;
    printf("\n--- Catalogo de Servicos ---\n");
    printf("1 - Banho (15.00 euros)\n");
    printf("2 - Tosa (25.00 euros)\n");
    printf("3 - Consulta (50.00 euros)\n");
    printf("4 - Vacinacao (30.00 euros)\n");
    printf("Escolha o servico (1-4): ");
    scanf("%d", &servico);

    printf("Quantidade: ");
    scanf("%d", &qtd);

    float precoUnitario = 0.0;
    switch(servico) {
        case 1: precoUnitario = 15.00; break;
        case 2: precoUnitario = 25.00; break;
        case 3: precoUnitario = 50.00; break;
        case 4: precoUnitario = 30.00; break;
        default: printf("Servico invalido!\n"); return;
    }

    atendimentos[*contador].codigoAnimal = codAnimal;
    atendimentos[*contador].tipoServico = servico;
    atendimentos[*contador].quantidade = qtd;
    atendimentos[*contador].valorTotal = precoUnitario * qtd;

    printf("Atendimento registado com sucesso! Total: %.2f euros\n", atendimentos[*contador].valorTotal);
    (*contador)++;
}

void exibirRelatorio(Atendimento atendimentos[], int contador) {
    float faturacaoTotal = 0.0;
    int contagemServicos[5] = {0}; 

    for (int i = 0; i < contador; i++) {
        faturacaoTotal += atendimentos[i].valorTotal;
        contagemServicos[atendimentos[i].tipoServico]++;
    }

    printf("\n--- Relatorio da Sessao ---\n");
    printf("Numero total de atendimentos: %d\n", contador);
    printf("Faturacao total: %.2f euros\n", faturacaoTotal);
    printf("Total de registos por servico:\n");
    printf("Banho: %d | Tosa: %d | Consulta: %d | Vacinacao: %d\n",
           contagemServicos[1], contagemServicos[2], contagemServicos[3], contagemServicos[4]);
}

void alterarTutor(Tutor *t){
    printf("Digite o novo nome: ");
    scanf(" %[^\n]", t->nomeCompleto);

    printf("Digite o novo telefone: ");
    scanf(" %[^\n]", t->telefone);

    printf("\nTutor alterado com sucesso!\n");
}

void buscarAlterarTutor(Tutor tutores[], int totalTutores){
    int codigo, i;

    if(totalTutores == 0){
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }

    printf("Digite o codigo do tutor: ");
    scanf("%d", &codigo);

    for(i = 0; i < totalTutores; i++){
        if(tutores[i].codigo == codigo){
            alterarTutor(&tutores[i]);
            return;
        }
    }

    printf("\nTutor nao encontrado!\n");
}

void listarTutores(Tutor *tutores, int totalTutores){
    int i;
    if(totalTutores == 0){
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }
    printf("\n===== LISTA DE TUTORES =====\n");
    for(i = 0; i < totalTutores; i++){
        printf("\nCodigo: %d\n", tutores[i].codigo);
        printf("Nome: %s\n", tutores[i].nomeCompleto);
        printf("CPF: %s\n", tutores[i].cpf);
        printf("Telefone: %s\n", tutores[i].telefone);
        printf("--------------------------\n");
    }
}

void listarAnimaisPorTutor(Animal *animais, int totalAnimais, Tutor *tutores, int totalTutores){
    int codigoTutor, i;
    int tutorEncontrado = 0;
    int encontrouAnimal = 0;

    if(totalTutores == 0){
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }

    if(totalAnimais == 0){
        printf("\nNenhum animal cadastrado!\n");
        return;
    }

    printf("\nDigite o codigo do tutor: ");
    scanf("%d", &codigoTutor);

    for(i = 0; i < totalTutores; i++){
        if(tutores[i].codigo == codigoTutor){
            tutorEncontrado = 1;
            break;
        }
    }

    if(tutorEncontrado == 0){
        printf("\nTutor nao encontrado!\n");
        return;
    }

    printf("\n===== ANIMAIS DO TUTOR %d =====\n", codigoTutor);
    for(i = 0; i < totalAnimais; i++){
        if(animais[i].codigoTutor == codigoTutor){
            printf("\nCodigo: %d\n", animais[i].codigo);
            printf("Nome: %s\n", animais[i].nome_pet);
            printf("Especie: %s\n", animais[i].especie);
            printf("Idade: %d\n", animais[i].idade_pet);
            printf("--------------------------\n");
            encontrouAnimal = 1;
        }
    }

    if(encontrouAnimal == 0){
        printf("\nEste tutor nao possui animais cadastrados.\n");
    }
}

void buscarTutor(Tutor *tutores, int totalTutores){
    int codigo, i;
    int encontrado = 0;

    if(totalTutores == 0){
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }

    printf("\nDigite o codigo do tutor que deseja buscar: ");
    scanf("%d", &codigo);

    for(i = 0; i < totalTutores; i++){
        if(tutores[i].codigo == codigo){
            printf("\n===== TUTOR ENCONTRADO =====\n");
            printf("Codigo: %d\n", tutores[i].codigo);
            printf("Nome: %s\n", tutores[i].nomeCompleto);
            printf("CPF: %s\n", tutores[i].cpf);
            printf("Telefone: %s\n", tutores[i].telefone);
            encontrado = 1;
            break;
        }
    }

    if(encontrado == 0){
        printf("\nTutor nao encontrado!\n");
    }
}

int main(){
    Tutor tutores[MAX_TUTORES];    
    Animal animais[MAX_ANIMAIS];   
    Atendimento listaAtendimentos[MAX_ATENDIMENTOS]; 

    int totalTutores = 0;
    int totalAnimais = 0;
    int contadorAtendimentos = 0; 
    
    int opcao;

    do{
        menu(); 

        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                getchar(); 
                cadastrarTutor(tutores, &totalTutores);
                break;
            case 2:
                cadastrarAnimal(animais, &totalAnimais, tutores, totalTutores); 
                break;
            case 3:
                listarTutores(tutores, totalTutores);
                break;
            case 4:
                listarAnimais(animais, totalAnimais); 
                break;
            case 5:
                listarAnimaisPorTutor(animais, totalAnimais, tutores, totalTutores);
                break;
            case 6:
                buscarTutor(tutores, totalTutores);
                break;
            case 7:
                buscarAlterarTutor(tutores, totalTutores);
                break;
            case 8:
                buscarAnimal(animais, totalAnimais); 
                break;
            case 9:
                registarAtendimento(listaAtendimentos, &contadorAtendimentos, animais, totalAnimais);
                break;
            case 10:
                exibirRelatorio(listaAtendimentos, contadorAtendimentos);
                break;
            case 0:
                printf("\nSaindo do programa...\n");
                break;
            default:
                printf("\nOpcao invalida! Tente novamente.\n");
                break;
        }
    }while(opcao != 0);

    return 0;
}