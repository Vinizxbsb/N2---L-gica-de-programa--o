#include <stdio.h>
#include <string.h>


#define MAX_TUTORES 50
typedef struct {
    char nomeCompleto[50];
    char cpf[15];
    char telefone[15];
} Tutor;

void menu(){
    printf("===== Menu =====\n");
    printf("1. Cadastrar tutor\n");
    printf("2. Cadastrar animal\n");
    printf("3. Listar tutores\n");
    printf("4. Listar animais\n");
    printf("5. Listar animais por tutor\n");
    printf("6. Buscar tutor\n");
    printf("7. Alterar dados do tutor\n");
    printf("0. Sair\n");
}

void cadastrarTutor(Tutor *tutores, int *totalTutores){
    if(*totalTutores >= MAX_TUTORES){
        printf("Limite de tutores atingido!\n");
        return;
    }

    printf("Digite o nome completo do tutor: ");
    fgets(tutores[*totalTutores].nomeCompleto, sizeof(tutores[*totalTutores].nomeCompleto), stdin);
    tutores[*totalTutores].nomeCompleto[strcspn(tutores[*totalTutores].nomeCompleto, "\n")] = '\0';
    printf("Digite o CPF do tutor: ");
    scanf(" %[^\n]", tutores[*totalTutores].cpf);
    printf("Digite o telefone do tutor: ");
    scanf(" %[^\n]", tutores[*totalTutores].telefone);

    (*totalTutores)++;
    printf("Tutor cadastrado com sucesso!\n");
}



int main(){
    Tutor tutores[MAX_TUTORES];
    int totalTutores = 0;
    int opcao;
    
    do{
        menu();
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                cadastrarTutor(tutores, &totalTutores);
                break;
            case 2:
                // Função para cadastrar animal.
                break;
            case 3:
                // Função para listar tutores.
                break;
            case 4:
                // Função para listar animais.
                break;
            case 5:
                // Função para listar animais por tutor.
                break;
            case 6:
                // Função para buscar tutor.
                break;
            case 7: 
                // Função para alterar dados do tutor.
                break;
            case 0:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                break;
        }

    }while (opcao != 0);
}