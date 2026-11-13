#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    char nomePet[50];
    char especie[30];
    int idadePet;
    int codigoTutor;
} Animal;

typedef struct {
    int codigoAnimal;
    int tipoServico;
    int quantidade;
    float valorTotal;
} Atendimento;


void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int lerInteiro(const char *mensagem, int *destino) {
    char buffer[64];
    char *fim;

    printf("%s", mensagem);
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return 0;
    }

    if (strchr(buffer, '\n') == NULL) {
        limparBuffer();
    }

    buffer[strcspn(buffer, "\n")] = '\0';
    if (buffer[0] == '\0') {
        return 0;
    }

    long valor = strtol(buffer, &fim, 10);
    while (isspace((unsigned char)*fim)) {
        fim++;
    }

    if (*fim != '\0') {
        return 0;
    }

    *destino = (int)valor;
    return 1;
}

int lerStringNaoVazia(const char *mensagem, char *destino, size_t tamanho) {
    printf("%s", mensagem);
    if (fgets(destino, tamanho, stdin) == NULL) {
        return 0;
    }

    if (strchr(destino, '\n') == NULL) {
        limparBuffer();
    }

    destino[strcspn(destino, "\n")] = '\0';

    // Verifica se a string esta vazia ou contem apenas espacos
    int temConteudo = 0;
    for (size_t i = 0; destino[i] != '\0'; i++) {
        if (!isspace((unsigned char)destino[i])) {
            temConteudo = 1;
            break;
        }
    }

    return temConteudo;
}

int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) {
        return 0;
    }
    for (int i = 0; i < 11; i++) {
        if (!isdigit((unsigned char)cpf[i])) {
            return 0;
        }
    }
    return 1;
}

int stringsIguaisIgnoreCase(const char *s1, const char *s2) {
    while (*s1 && *s2) {
        if (tolower((unsigned char)*s1) != tolower((unsigned char)*s2)) {
            return 0;
        }
        s1++;
        s2++;
    }
    return *s1 == *s2;
}


int buscarIndiceTutor(const Tutor *tutores, int totalTutores, int codigo) {
    for (int i = 0; i < totalTutores; i++) {
        if (tutores[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int buscarIndiceAnimal(const Animal *animais, int totalAnimais, int codigo) {
    for (int i = 0; i < totalAnimais; i++) {
        if (animais[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

int cpfJaCadastrado(const Tutor *tutores, int totalTutores, const char *cpf) {
    for (int i = 0; i < totalTutores; i++) {
        if (strcmp(tutores[i].cpf, cpf) == 0) {
            return 1;
        }
    }
    return 0;
}

void imprimirTutor(const Tutor *t) {
    printf("\nCodigo: %d\n", t->codigo);
    printf("Nome: %s\n", t->nomeCompleto);
    printf("CPF: %s\n", t->cpf);
    printf("Telefone: %s\n", t->telefone);
    printf("--------------------------\n");
}

void imprimirAnimal(const Animal *a) {
    printf("\nCodigo: %d\n", a->codigo);
    printf("Nome: %s\n", a->nomePet);
    printf("Especie: %s\n", a->especie);
    printf("Idade: %d\n", a->idadePet);
    printf("Codigo do tutor: %d\n", a->codigoTutor);
    printf("--------------------------\n");
}


void menu() {
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

void cadastrarTutor(Tutor *tutores, int *totalTutores) {
    if (*totalTutores >= MAX_TUTORES) {
        printf("Limite de tutores atingido!\n");
        return;
    }

    Tutor novo;
    novo.codigo = *totalTutores + 1;

    printf("\nCodigo do tutor: %d\n", novo.codigo);

    if (!lerStringNaoVazia("Digite o nome completo do tutor: ", novo.nomeCompleto, sizeof(novo.nomeCompleto))) {
        printf("Nome invalido! Cadastro cancelado.\n");
        return;
    }

    if (!lerStringNaoVazia("Digite o CPF do tutor (11 digitos): ", novo.cpf, sizeof(novo.cpf)) || !validarCPF(novo.cpf)) {
        printf("CPF invalido! Digite exatamente 11 numeros. Cadastro cancelado.\n");
        return;
    }

    if (cpfJaCadastrado(tutores, *totalTutores, novo.cpf)) {
        printf("CPF ja cadastrado no sistema! Cadastro cancelado.\n");
        return;
    }

    if (!lerStringNaoVazia("Digite o telefone do tutor: ", novo.telefone, sizeof(novo.telefone))) {
        printf("Telefone invalido! Cadastro cancelado.\n");
        return;
    }

    tutores[*totalTutores] = novo;
    (*totalTutores)++;

    printf("\nTutor cadastrado com sucesso!\n");
}

void cadastrarAnimal(Animal *animais, int *totalAnimais, const Tutor *tutores, int totalTutores) {
    if (*totalAnimais >= MAX_ANIMAIS) {
        printf("Limite de animais atingido!\n");
        return;
    }

    if (totalTutores == 0) {
        printf("Nenhum tutor cadastrado! Cadastre um tutor primeiro.\n");
        return;
    }

    Animal novo;
    novo.codigo = *totalAnimais + 1;

    printf("\nCodigo do animal: %d\n", novo.codigo);

    if (!lerStringNaoVazia("Digite o nome do animal: ", novo.nomePet, sizeof(novo.nomePet))) {
        printf("Nome invalido! Cadastro cancelado.\n");
        return;
    }

    if (!lerStringNaoVazia("Digite a especie do animal (cachorro/gato): ", novo.especie, sizeof(novo.especie))) {
        printf("Especie invalida! Cadastro cancelado.\n");
        return;
    }

    if (!stringsIguaisIgnoreCase(novo.especie, "cachorro") && !stringsIguaisIgnoreCase(novo.especie, "gato")) {
        printf("Especie invalida! Apenas cachorro ou gato sao aceitos. Cadastro cancelado.\n");
        return;
    }

    if (!lerInteiro("Digite a idade do animal (1 a 50): ", &novo.idadePet) || novo.idadePet <= 0 || novo.idadePet > 50) {
        printf("Idade invalida! Cadastro cancelado.\n");
        return;
    }

    if (!lerInteiro("Digite o codigo do tutor: ", &novo.codigoTutor) || buscarIndiceTutor(tutores, totalTutores, novo.codigoTutor) == -1) {
        printf("Tutor nao encontrado! Cadastro cancelado.\n");
        return;
    }

    animais[*totalAnimais] = novo;
    (*totalAnimais)++;

    printf("\nAnimal cadastrado com sucesso!\n");
}

void listarTutores(const Tutor *tutores, int totalTutores) {
    if (totalTutores == 0) {
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }
    printf("\n===== LISTA DE TUTORES =====\n");
    for (int i = 0; i < totalTutores; i++) {
        imprimirTutor(&tutores[i]);
    }
}

void listarAnimais(const Animal *animais, int totalAnimais) {
    if (totalAnimais == 0) {
        printf("\nNenhum animal cadastrado!\n");
        return;
    }
    printf("\n===== LISTA DE ANIMAIS =====\n");
    for (int i = 0; i < totalAnimais; i++) {
        imprimirAnimal(&animais[i]);
    }
}

void listarAnimaisPorTutor(const Animal *animais, int totalAnimais, const Tutor *tutores, int totalTutores) {
    if (totalTutores == 0) {
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }
    if (totalAnimais == 0) {
        printf("\nNenhum animal cadastrado!\n");
        return;
    }

    int codigoTutor;
    if (!lerInteiro("\nDigite o codigo do tutor: ", &codigoTutor)) {
        printf("\nCodigo invalido!\n");
        return;
    }

    if (buscarIndiceTutor(tutores, totalTutores, codigoTutor) == -1) {
        printf("\nTutor nao encontrado!\n");
        return;
    }

    int encontrouAnimal = 0;
    printf("\n===== ANIMAIS DO TUTOR %d =====\n", codigoTutor);
    for (int i = 0; i < totalAnimais; i++) {
        if (animais[i].codigoTutor == codigoTutor) {
            imprimirAnimal(&animais[i]);
            encontrouAnimal = 1;
        }
    }

    if (!encontrouAnimal) {
        printf("\nEste tutor nao possui animais cadastrados.\n");
    }
}

void buscarTutor(const Tutor *tutores, int totalTutores) {
    if (totalTutores == 0) {
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }

    int codigo;
    if (!lerInteiro("\nDigite o codigo do tutor que deseja buscar: ", &codigo)) {
        printf("\nCodigo invalido!\n");
        return;
    }

    int indice = buscarIndiceTutor(tutores, totalTutores, codigo);
    if (indice == -1) {
        printf("\nTutor nao encontrado!\n");
        return;
    }

    printf("\n===== TUTOR ENCONTRADO =====\n");
    imprimirTutor(&tutores[indice]);
}

void alterarTutor(Tutor *t) {
    char novoNome[50];
    char novoTelefone[15];

    if (!lerStringNaoVazia("Digite o novo nome: ", novoNome, sizeof(novoNome))) {
        printf("Nome invalido! Alteracao cancelada.\n");
        return;
    }

    if (!lerStringNaoVazia("Digite o novo telefone: ", novoTelefone, sizeof(novoTelefone))) {
        printf("Telefone invalido! Alteracao cancelada.\n");
        return;
    }

    strcpy(t->nomeCompleto, novoNome);
    strcpy(t->telefone, novoTelefone);

    printf("\nTutor alterado com sucesso!\n");
}

void buscarAlterarTutor(Tutor *tutores, int totalTutores) {
    if (totalTutores == 0) {
        printf("\nNenhum tutor cadastrado!\n");
        return;
    }

    int codigo;
    if (!lerInteiro("\nDigite o codigo do tutor: ", &codigo)) {
        printf("\nCodigo invalido!\n");
        return;
    }

    int indice = buscarIndiceTutor(tutores, totalTutores, codigo);
    if (indice == -1) {
        printf("\nTutor nao encontrado!\n");
        return;
    }

    alterarTutor(&tutores[indice]);
}

void buscarAnimal(const Animal *animais, int totalAnimais) {
    if (totalAnimais == 0) {
        printf("\nNenhum animal cadastrado!\n");
        return;
    }

    int codigo;
    if (!lerInteiro("\nDigite o codigo do animal que deseja buscar: ", &codigo)) {
        printf("\nCodigo invalido!\n");
        return;
    }

    int indice = buscarIndiceAnimal(animais, totalAnimais, codigo);
    if (indice == -1) {
        printf("\nAnimal nao encontrado!\n");
        return;
    }

    printf("\n===== ANIMAL ENCONTRADO =====\n");
    imprimirAnimal(&animais[indice]);
}

void registrarAtendimento(Atendimento atendimentos[], int *contador, const Animal *animais, int totalAnimais) {
    if (*contador >= MAX_ATENDIMENTOS) {
        printf("Limite de atendimentos atingido!\n");
        return;
    }

    if (totalAnimais == 0) {
        printf("Nenhum animal cadastrado! Cadastre um animal primeiro.\n");
        return;
    }

    int codAnimal;
    if (!lerInteiro("Digite o codigo do animal: ", &codAnimal)) {
        printf("Codigo invalido!\n");
        return;
    }

    if (buscarIndiceAnimal(animais, totalAnimais, codAnimal) == -1) {
        printf("Erro: Animal inexistente. Cadastre o animal primeiro.\n");
        return;
    }

    int servico, qtd;
    printf("\n--- Catalogo de Servicos ---\n");
    printf("1 - Banho (55.00 Reais)\n");
    printf("2 - Tosa (30.00 Reais)\n");
    printf("3 - Consulta (75.00 Reais)\n");
    printf("4 - Vacinacao (30.00 Reais)\n");

    if (!lerInteiro("Escolha o servico (1-4): ", &servico) || servico < 1 || servico > 4) {
        printf("Servico invalido!\n");
        return;
    }

    if (!lerInteiro("Quantidade: ", &qtd) || qtd <= 0) {
        printf("Quantidade invalida!\n");
        return;
    }

    float precoUnitario = 0.0f;
    switch (servico) {
        case 1: precoUnitario = 55.00f; break;
        case 2: precoUnitario = 30.00f; break;
        case 3: precoUnitario = 75.00f; break;
        case 4: precoUnitario = 30.00f; break;
    }

    atendimentos[*contador].codigoAnimal = codAnimal;
    atendimentos[*contador].tipoServico = servico;
    atendimentos[*contador].quantidade = qtd;
    atendimentos[*contador].valorTotal = precoUnitario * qtd;

    printf("Atendimento registrado com sucesso! Total: %.2f Reais\n", atendimentos[*contador].valorTotal);
    (*contador)++;
}

void exibirRelatorio(const Atendimento atendimentos[], int contador) {
    float faturacaoTotal = 0.0f;
    int contagemServicos[5] = {0};

    for (int i = 0; i < contador; i++) {
        faturacaoTotal += atendimentos[i].valorTotal;
        if (atendimentos[i].tipoServico >= 1 && atendimentos[i].tipoServico <= 4) {
            contagemServicos[atendimentos[i].tipoServico]++;
        }
    }

    printf("\n--- Relatorio da Sessao ---\n");
    printf("Numero total de atendimentos: %d\n", contador);
    printf("Faturacao total: %.2f Reais\n", faturacaoTotal);
    printf("Total de registros por servico:\n");
    printf("Banho: %d | Tosa: %d | Consulta: %d | Vacinacao: %d\n",
           contagemServicos[1], contagemServicos[2], contagemServicos[3], contagemServicos[4]);
}

int main() {
    Tutor tutores[MAX_TUTORES];
    Animal animais[MAX_ANIMAIS];
    Atendimento listaAtendimentos[MAX_ATENDIMENTOS];

    int totalTutores = 0;
    int totalAnimais = 0;
    int contadorAtendimentos = 0;
    int opcao = -1;

    do {
        menu();

        if (!lerInteiro("\nEscolha uma opcao: ", &opcao)) {
            printf("\nOpcao invalida! Digite apenas numeros.\n");
            opcao = -1;
            continue;
        }

        switch (opcao) {
            case 1:
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
                registrarAtendimento(listaAtendimentos, &contadorAtendimentos, animais, totalAnimais);
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
    } while (opcao != 0);

    return 0;
}