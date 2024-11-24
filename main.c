// Adição de bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

// Criando uma estrutura de dados e adicionando variaveis
typedef struct{
    char nome[50];
    char cpf[12];
    char tipo_conta[6];
    float saldo;
    char senha[20];
    } Cliente;

// Função de executar próxima linha
void limparlinha(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

// Função de criar um novo cliente
void novo_cliente(){
    FILE *arquivo;
    Cliente cliente;

    // Entrada de dados do nome do cliente
    printf("Digite o nome: ");
    fgets(cliente.nome, 50, stdin);
    cliente.nome[strcspn(cliente.nome, "\n")] = '\0';

    // Entrada de dados do cpf do cliente
    printf("Digite o CPF: ");
    fgets(cliente.cpf, 12, stdin);
    cliente.cpf[strcspn(cliente.cpf, "\n")] = '\0';

    // Entrada de dados do tipo de conta do cliente
    printf("Digite o tipo de conta (comum ou plus): ");
    fgets(cliente.tipo_conta, 6, stdin);
    cliente.tipo_conta[strcspn(cliente.tipo_conta, "\n")] = '\0';

    // Entrada de dados do valor inicial da conta
    printf("Digite o valor inicial: ");
    scanf("%f", &cliente.saldo);
    limparlinha();

    // Entrada de dados da senha do cliente
    printf("Digite a senha: ");
    fgets(cliente.senha, 20, stdin);
    cliente.senha[strcspn(cliente.senha, "\n")] = '\0';
    

    // Verifica se a abertura do arquivo foi bem sucedida ou não
    arquivo = fopen("clientes.dat", "ab");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Atualiza os dados do cliente no arquivo
    fwrite(&cliente, sizeof(Cliente), 1, arquivo);
    fclose(arquivo);
    printf("Cliente cadastrado com sucesso!\n");
    }

void apaga_cliente(){
    FILE *arquivo;
    FILE *temp;
    Cliente cliente;
    char cpf[12];
    char senha[20];
    float valor;
    int encontrado = 0;

    // Entrada de dados do cpf do cliente
    printf("Digite o CPF do cliente que deseja apagar: ");
    fgets(cpf, 12, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    // Entrada de dados senha do cliente
    printf("Digite a senha: ");
    fgets(senha, 20, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    // Entrada de dados saldo da conta do cliente
    printf("Digite o valor que deseja apagar: ");
    scanf("%f", &valor);
    limparlinha();

    // Verifica se a abertura do arquivo foi bem sucedida ou não
    arquivo = fopen("clientes.dat", "rb");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Arquivo temporário
    temp = fopen("temp.dat", "wb");
    if (temp == NULL){
        printf("Erro ao abrir o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    // Executa função de ler a estrutura do cliente e atualiza o arquivo
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)){
        if (strcmp(cliente.cpf, cpf) != 0){
            fwrite(&cliente, sizeof(Cliente), 1, temp);           
        } else{
            encontrado = 1;
        }
    }
    // Fecha os arquivos
    fclose(arquivo);
    fclose(temp);

    // Arquivo irá atualizar se foi removido ou não encontrado
    if (encontrado){
        remove("clientes.dat");
        rename("temp.dat", "clientes.dat");
        printf("Cliente removido com sucesso!\n");
        }
}

// Função de débito
void debito(){
    FILE *arquivo;
    Cliente cliente;
    char cpf[12];
    char senha[20];
    float valor;

    // Entrada de dados do CPF do cliente
    printf("Digite o CPF: ");
    fgets(cpf, 12, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    // Entrada de dados da senha
    printf("Digite a senha: ");
    fgets(senha, 20, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    // Entrada de dados do valor de débito
    printf("Digite o valor a debitar: ");
    scanf("%f", &valor);
    limparlinha();

    // Verifica se a abertura do arquivo foi bem sucedida ou não
    arquivo = fopen("clientes.dat", "rb+");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Percorre pela estrutura de clientes, compara os dados se correspondem, realiza o calculo se o cliente é plus ou comum e aplica a taxa
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)) {
        if (strcmp(cliente.cpf, cpf) == 0 && strcmp(cliente.senha, senha) == 0){
            if (strcmp(cliente.tipo_conta, "comum") == 0){
                cliente.saldo -= valor + (valor * 0.05);
                if (cliente.saldo < -1000.0){
                    printf("Saldo negativo máximo para conta comum.\n");
                    fclose(arquivo);
                    return;
                }
            } else if (strcmp(cliente.tipo_conta, "plus") == 0){
                cliente.saldo -= valor + (valor * 0.03);
                if (cliente.saldo < -5000.0){
                    printf("Saldo negativo máximo para conta plus.\n");
                    fclose(arquivo);
                    return;
                }
            }
            // Posiciona o indicador em determinado local, atualiza os dados de somente 1 indicado e volta ao inicio 
            fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
            fwrite(&cliente, sizeof(Cliente), 1, arquivo);
            fclose(arquivo);
            printf("Débito realizado com sucesso!\n");
            return;
        }
    }
    // Fecha o arquivo e caso não encontrar o usuario ou a senha estiver incorreta ele avisa o usuario
    fclose(arquivo);
    printf("Cliente não encontrado ou senha incorreta.\n");
    }

    // Função de depositar valor na conta
    void depositar(){
        FILE *arquivo;
        Cliente cliente;
        char cpf[12];
        float valor;

        // Entrada de dados do cpf do cliente
        printf("Digite o CPF: ");
        fgets(cpf, 12, stdin);
        cpf[strcspn(cpf, "\n")] = '\0';

        // Entrada de dados do valor do depósito
        printf("Digite o valor a depositar: ");
        scanf("%f", &valor);
        limparlinha();

        // Verifica se a abertura do arquivo foi bem sucedida ou não
        arquivo = fopen("clientes.dat", "rb+");
        if (arquivo == NULL){
            printf("Erro ao abrir o arquivo.\n");
            return;
        }

        // Lê os dados, compara se bate as informações um por um usuário e atualiza o dado requisitado
        while (fread(&cliente, sizeof(Cliente), 1, arquivo)){
            if (strcmp(cliente.cpf, cpf) == 0){
                cliente.saldo += valor;
                fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
                fwrite(&cliente, sizeof(Cliente), 1, arquivo);
                fclose(arquivo);
                printf("Valor depositado com sucesso!\n");
            }
        }
        // Fecha o arquivo e caso o cliente não seja encontrado ele informa o usuario
        fclose(arquivo);
        printf("Cliente não encontrado.\n");
    }

// Função do extrato do cliente
void extrato(){
    FILE *arquivo;
    Cliente cliente;
    char cpf[12];
    char senha[20];

    // Entrada de dados do cpf do cliente
    printf("Digite o CPF: ");
    fgets(cpf, 12, stdin);
    cpf[strcspn(cpf, "\n")] = '\0';

    // Entrada de dados da senha do cliente
    printf("Digite a senha: ");
    fgets(senha, 20, stdin);
    senha[strcspn(senha, "\n")] = '\0';

    // Verifica se a abertura do arquivo foi bem sucedida ou não
    arquivo = fopen("clientes.dat", "rb");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Acessa o arquivo, compara informações e exibe ao cliente
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)){
        if (strcmp(cliente.cpf, cpf) == 0 && strcmp(cliente.senha, senha) == 0){
            printf("Nome do cliente: %s\n", cliente.nome);
            printf("CPF: %s\n", cliente.cpf);
            printf("Tipo de conta: %s\n", cliente.tipo_conta);
            printf ("Saldo: R$ %.2f\n", cliente.saldo);
            fclose(arquivo);
            return;
        }
    }
    // Fecha o arquivo e caso usuario erre na entrada de dados do cliente, ele exibirá o erro
    fclose(arquivo);
    printf("Cliente não encontrado ou senha incorreta.\n");
}

// Função transferencia de valores entre contas
void transferencia(){
    FILE *arquivo;
    Cliente origem;
    Cliente destino;
    char cpf_origem[12];
    char senha_origem[20];
    char cpf_destino[12];
    float valor;

    // Entrada de dados do cpf de origem
    printf("Digite seu CPF: ");
    fgets(cpf_origem, 12, stdin);
    cpf_origem[strcspn(cpf_origem, "\n")] = '\0';

    // Entrada de dados da senha da conta origem
    printf("Digite sua senha: ");
    fgets(senha_origem, 20, stdin);
    senha_origem[strcspn(senha_origem, "\n")] = '\0';

    // Entrada de dados do cpf destino
    printf("Digite o CPF da conta que deseja transferir: ");
    fgets(cpf_destino, 12, stdin);
    cpf_destino[strcspn(cpf_destino, "\n")] = '\0';

    // Entrada de dados do valor da transferencia
    printf("Digite o valor da transferencia: ");
    scanf("%f", &valor);
    limparlinha();

    // Verifica se a abertura do arquivo foi bem sucedida ou não
    arquivo = fopen("clientes.dat", "rb+");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Acessa o arquivo, compara informações e exibe ao cliente
    while (fread(&origem, sizeof(Cliente), 1, arquivo)){
        if (strcmp(origem.cpf, cpf_origem) == 0 && strcmp(origem.senha, senha_origem) == 0){
            if (origem.saldo < valor){
                printf("Saldo insuficiente para transferencia.\n");
                fclose(arquivo);
                return;
            }

            // Verifica se a abertura do arquivo temporario foi bem sucedida
            FILE *temp = fopen("temp.dat", "wb");
            if (temp == NULL){
                printf("Erro ao abrir arquivo temporario.\n");
                fclose(arquivo);
                return;
            }

            // Acessa o arquivo temporario binario com os registros, o original é copiado para o temporario
            while (fread(&destino, sizeof(Cliente), 1, arquivo)){
                if (strcmp(destino.cpf, cpf_destino) == 0){
                    destino.saldo += valor;
                    fwrite(&destino, sizeof(Cliente), 1, temp);
                } else {
                    fwrite(&destino, sizeof(Cliente), 1, temp);
                }
            }

            // Acessa o arquivo atualiza o saldo da conta origem, sobrescreve o arquivo original e informa a realização da transferencia
            fseek(arquivo, -sizeof(Cliente), SEEK_CUR);
            fwrite(&origem, sizeof(Cliente), 1, temp);
            fclose(arquivo);
            fclose(temp);
            remove("clientes.dat");
            rename("temp.dat", "clientes.dat");
            printf("Transferencia concluida com sucesso!\n");
            return;
        }
    }

    // Caso o usuario tenha inserido os dados incorretos, sera exibido
    fclose(arquivo);
    printf("Conta não encontrada ou senha incorreta.\n");
}

// Operação livre escolhi fazer a função de saldo total das contas
void saldo_total(){
    FILE *arquivo;
    Cliente cliente;
    float saldototal = 0.0;

    // Verifica se a abertura do arquivo foi bem sucedida ou não
    arquivo = fopen("clientes.dat", "rb");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Lê a estrutura de clientes percorrendo um a um no arquivo, soma todos os saldos
    while (fread(&cliente, sizeof(Cliente), 1, arquivo)){
        saldototal += cliente.saldo;
    }

    // Fecha o arquivo e exibe ao usuario o saldo total das contas
    fclose(arquivo);
    printf("Saldo total de todas as contas: R$ %.2f\n", saldototal);
}

// Função principal de executar o meu e chamada das funções
int main(){
    int opcao;

    // Exibe ao usuario um menu de opções para chamar as funções
    do{
        printf("Bem vindo ao Banco QUEMPOUPATEM!\n");
        printf("--------------------------------\n");
        printf("Menu de acesso:\n");
        printf("1 - Novo cliente\n");
        printf("2 - Apaga cliente\n");
        printf("3 - Débito\n");
        printf("4 - Depósito\n");
        printf("5 - Extrato\n");
        printf("6 - Transferencia entre contas\n");
        printf("7 - Saldo total em contas\n");
        printf("8 - Sair\n");
        printf("----------------------------\n");
        printf("Escolha a opção desejada: \n");
        printf("----------------------------\n");
        scanf("%d", &opcao);
        limparlinha();

        // Escolha de opção (função)
        switch (opcao){
        case 1:
            printf("Você escolheu: NOVO CLIENTE\n");
            novo_cliente();
            break;
        case 2:
            printf("Você escolheu: APAGA CLIENTE\n");
            apaga_cliente();
            break;
        case 3:
            printf("Você escolheu: DEBITO\n");
            debito();
            break;
        case 4:
            printf("Você escolheu: DEPOSITAR\n");
            depositar();
            break;
        case 5:
            printf("Você escolheu: EXTRATO\n");
            extrato();
            break;
        case 6:
            printf("Você escolheu: TRANSFERENCIA ENTRE CONTAS\n");
            transferencia();
            break;
        case 7:
            printf("Você escolheu: SALDO TOTAL DAS CONTAS\n");
            saldo_total();
            break;
        case 8:
            printf("Saindo.\n");
            break;
        default:
            printf("Opção invalida! Tente novamente.\n");
            break;
        }
        // Pular linha
        printf("\n");
    } while (opcao != 8); //Retorna ao menu com um laço
    return 0;
}
