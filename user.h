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
void menuUsuario(NoAssinatura **assin, NoCertificado **certificados, Usuario);
void autenticarUsuario(NoUsuario *usuarios, NoCertificado *certificados, NoAssinatura *assin);
void registrarUsuario(NoUsuario **usuarios);
void listarUsuarios(NoUsuario *usuarios);
void alterarTipo_usuario(NoUsuario **usuarios);
void bloquearUsuario(NoUsuario **usuarios);
void estatisticasDeUso(NoAssinatura *assin, NoCertificado *certificados, Usuario user);
void salvarDadosEmFicheiros(NoUsuario *usuarios, NoCertificado *certificados, NoAssinatura *assinaturas);

Usuario currentUser;

void autenticarUsuario(NoUsuario *usuarios, NoCertificado *certificados, NoAssinatura *assin)
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
                currentUser = atual->dados;
                 // Armazena o usuário atual
                printf("Bem-vindo, administrador!\n");
                menuAdmin(&usuarios, &certificados);
            }
            else if (atual->dados.tipo == USUARIO)
            {
                currentUser = atual->dados;
                printf("Bem-vindo, usuário!\n");
                autenticado = 1;
                menuUsuario(&assin, &certificados, currentUser);
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
            // alertasExpiracao();
            esperarTecla();
            break;

        case 0:
            printf("\nVoltando ao menu principal...\n");
            salvarDadosEmFicheiros(*usuarios, *certificados, NULL);
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

void menuUsuario(NoAssinatura **assin, NoCertificado **certificados, Usuario user)
{
    int opcao;
    do
    {
        printf("\n========== MENU USUÁRIO ==========\n");
        printf("1. Consultar estado do certificado\n");
        printf("2. Assinar documento digitalmente\n");
        printf("3. Consultar histórico de assinaturas\n");
        printf("4. Consultar estatísticas de uso\n");
        printf("0. Sair\n");
        printf("==================================\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Consultar estado do certificado
            listarCertificadoUsuario(*certificados, user); // Ou implemente uma função específica para mostrar só o do usuário
            esperarTecla();
            break;
        case 2:
        {
            criarAssinatura(assin, *certificados);
            esperarTecla();
            break;
        }
        case 3:
            // Consultar histórico pessoal de assinaturas
            consultarHistoricoAssinaturas(*assin, *certificados, user);
            esperarTecla();
            break;
        case 4:
            // Consultar estatísticas de uso
            estatisticasDeUso(*assin, *certificados, user);
            esperarTecla();
            break;
        case 0:
            printf("Saindo do menu usuário...\n");
            salvarDadosEmFicheiros(NULL, *certificados, *assin);
            break;
        default:
            printf("Opção inválida! Tente novamente.\n");
            esperarTecla();
        }
    } while (opcao != 0);
}

void estatisticasDeUso(NoAssinatura *assin, NoCertificado *certificados, Usuario user){
    int totalAssinaturas = 0;
    int totalCertificados = 0;

    // Contar assinaturas do usuário
    NoAssinatura *atualAssinatura = assin;
    while (atualAssinatura != NULL) {
        if (atualAssinatura->dados.id_certificado == user.id_certificado) {
            totalAssinaturas++;
        }
        atualAssinatura = atualAssinatura->proximo;
    }

    // Contar certificados do usuário
    NoCertificado *atualCertificado = certificados;
    while (atualCertificado != NULL) {
        if (atualCertificado->dados.id == user.id_certificado) {
            totalCertificados++;
        }
        atualCertificado = atualCertificado->proximo;
    }

    printf("\n===== Estatísticas de Uso do Usuário: %s =====\n", user.username);
    printf("Total de Assinaturas: %d\n", totalAssinaturas);
    printf("Total de Certificados: %d\n", totalCertificados);
}

void salvarDadosEmFicheiros(NoUsuario *usuarios, NoCertificado *certificados, NoAssinatura *assinaturas) {
    // Salvar usuários (exemplo em binário)
    FILE *fUsuarios = fopen("ficheiros/dat/users.dat", "wb");
    if (fUsuarios != NULL) {
        NoUsuario *atual = usuarios;
        while (atual != NULL) {
            fwrite(&atual->dados, sizeof(Usuario), 1, fUsuarios);
            atual = atual->proximo;
        }
        fclose(fUsuarios);
    } else {
        printf("Erro ao salvar usuários.\n");
    }

    // Salvar certificados (exemplo em texto)
    FILE *fCertificados = fopen("ficheiros/text/relatorio_certificados.txt", "w");
    if (fCertificados != NULL) {
        NoCertificado *atual = certificados;
        while (atual != NULL) {
            fprintf(fCertificados, "%d %s %s %s %s %s %s\n",
                atual->dados.id,
                atual->dados.nome,
                atual->dados.email,
                atual->dados.data_emissao,
                atual->dados.data_validade,
                atual->dados.estado,
                atual->dados.chave_publica
            );
            atual = atual->proximo;
        }
        fclose(fCertificados);
    } else {
        printf("Erro ao salvar certificados.\n");
    }

    // Salvar assinaturas (exemplo em binário)
    FILE *fAssinaturas = fopen("ficheiros/dat/assinaturas.dat", "wb");
    if (fAssinaturas != NULL) {
        NoAssinatura *atual = assinaturas;
        while (atual != NULL) {
            fwrite(&atual->dados, sizeof(Assinatura), 1, fAssinaturas);
            atual = atual->proximo;
        }
        fclose(fAssinaturas);
    } else {
        printf("Erro ao salvar assinaturas.\n");
    }
}
    
#endif // USERS_H