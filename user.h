#ifndef USERS_H
#define USERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "utils.h"
#include "sistema.h"

// Funções de gestão de usuários
void menuAdmin(NoUsuario **usuarios, NoCertificado **certificados);
void autenticarUsuario(NoUsuario *usuarios, NoCertificado *certificados);
void registrarUsuario(NoUsuario **usuarios);
void listarUsuarios(NoUsuario *usuarios);
void alterarTipo_usuario(NoUsuario **usuarios);
void bloquearUsuario(NoUsuario **usuarios);

void autenticarUsuario(NoUsuario *usuarios, NoCertificado *certificados)
{
    char username[50];
    char password[50];
    int autenticado = 0;
    NoUsuario *atual = usuarios;

    printf("Digite o nome de usuário: ");
    scanf("%49s", username);
    printf("Digite a senha: ");
    scanf("%49s", password);

    while (usuarios != NULL)
    {
        if (strcmp(atual->dados.username, username) == 0 && strcmp(atual->dados.password, password) == 0)
        {

            if (atual->dados.tipo == ADMIN)
            {
                printf("Bem-vindo, administrador!\n");
                menuAdmin(&usuarios, &certificados);
            }
            else if (atual->dados.tipo == USUARIO)
            {
                printf("Bem-vindo, usuário!\n");
                autenticado = 1;
                // menuUsuario();
                break;
            }
            else
            {
                printf("Tipo de usuário desconhecido.\n");
            }
        }
        atual = atual->proximo;
    }
}
void registrarUsuario(NoUsuario **usuarios)
{
    NoUsuario *novo = (NoUsuario *)malloc(sizeof(NoUsuario));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória para o novo usuário.\n");
        return;
    }

    printf("Digite o nome de usuário: ");
    scanf("%49s", novo->dados.username);
    printf("Digite a senha: ");
    scanf("%49s", novo->dados.password);
    novo->dados.tipo = USUARIO;      // Tipo padrão
    novo->dados.id_certificado = -1; // Sem certificado inicialmente

    novo->proximo = *usuarios;
    *usuarios = novo;

    printf("Usuário registrado com sucesso!\n");
}

void listarUsuarios(NoUsuario *usuarios)
{
    printf("Lista de usuários:\n");
    NoUsuario *atual = usuarios; // Usar um ponteiro auxiliar para preservar o original
    while (atual != NULL)
    {
        printf("Usuário: %s, Tipo: %d\n", atual->dados.username, atual->dados.tipo);
        atual = atual->proximo;
    }
}

void menuAdmin(NoUsuario **usuarios, NoCertificado **certificados)
{
    int opcao = -1;

    do
    {
        // system("cls || clear"); // Limpa a tela (Windows/Linux)

        printf("=================================\n");
        printf("        MENU ADMINISTRADOR       \n");
        printf("=================================\n");
        printf("1. Listar usuários\n");
        printf("2. Alterar tipo de usuário\n");
        printf("3. Bloquear usuário\n");
        printf("4. Criar certificado digital\n");
        printf("5. Renovar certificado digital\n");
        printf("6. Revogar certificado digital\n");
        printf("7. Listar certificados\n");
        printf("8. Ordenar certificados por nome\n");
        printf("9. Ordenar certificados por data\n");
        printf("10. Gerar relatório de certificados\n");
        printf("11. Exportar certificados para CSV\n");
        printf("12. Gerar alertas de expiração\n");
        printf("0. Sair\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Listar usuários
            listarUsuarios(*usuarios);
            esperarTecla();
            break;

        case 2:
            // Alterar tipo de usuário
            alterarTipo_usuario(usuarios);
            esperarTecla();
            break;

        case 3:
            // Bloquear usuário
            bloquearUsuario(usuarios);
            esperarTecla();
            break;

        case 4:
            // Criar certificado digital
            criarCertificado(certificados, *usuarios);
            esperarTecla();
            break;

        case 5:
            // Renovar certificado digital
            renovarCertificado(*certificados);
            esperarTecla();
            break;

        case 6:
            // Revogar certificado digital
            revogarCertificado(*certificados);
            esperarTecla();
            break;

        case 7:
            // Listar certificados
            listarCertificados(*certificados);
            esperarTecla();
            break;

        case 8:
            // Ordenar certificados por nome
            ordenarCertificadosNome(certificados);
            esperarTecla();
            break;

        case 9:
            // Ordenar certificados por data
            ordenarCertificadosData(certificados);
            esperarTecla();
            break;

        case 10:
            // Gerar relatório de certificados
            gerarRelatorioCertificados(*certificados);
            esperarTecla();
            break;

        case 11:
            // Exportar certificados para CSV
            exportarCertificadosCsv(*certificados);
            esperarTecla();
            break;

        case 12:
            // Gerar alertas de expiração
            //alertasExpiracao();
            esperarTecla();
            break;

        case 0:
            printf("\nVoltando ao menu principal...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            esperarTecla();
        }

    } while (opcao != 0);
}
void alterarTipo_usuario(NoUsuario **usuarios)
{
    char username[50];
    int novoTipo;

    printf("Digite o nome de usuário: ");
    scanf("%49s", username);
    printf("Digite o novo tipo de usuário (0 para ADMIN, 1 para USUARIO): ");
    scanf("%d", &novoTipo);

    if (novoTipo != ADMIN && novoTipo != USUARIO)
    {
        printf("Tipo inválido. Use 0 para ADMIN ou 1 para USUARIO.\n");
        return;
    }

    NoUsuario *atual = *usuarios;
    while (atual != NULL)
    {
        if (strcmp(atual->dados.username, username) == 0)
        {
            atual->dados.tipo = novoTipo;
            printf("Tipo de usuário alterado com sucesso!\n");
            return;
        }
        atual = atual->proximo;
    }

    printf("Usuário não encontrado.\n");
}

void bloquearUsuario(NoUsuario **usuarios)
{
    char username[50];
    printf("Digite o nome de usuário a ser bloqueado: ");
    scanf("%49s", username);

    NoUsuario *atual = *usuarios;
    NoUsuario *anterior = NULL;

    while (atual != NULL)
    {
        if (strcmp(atual->dados.username, username) == 0)
        {
            if (anterior == NULL)
            {
                *usuarios = atual->proximo; // Remove o primeiro nó
            }
            else
            {
                anterior->proximo = atual->proximo; // Remove o nó do meio ou fim
            }
            free(atual);
            printf("Usuário bloqueado com sucesso!\n");
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }

    printf("Usuário não encontrado.\n");
}

#endif // USERS_H