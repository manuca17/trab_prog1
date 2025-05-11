#ifndef SISTEMA_H
#define SISTEMA_H

#include "certificados.h"
#include "assinaturas.h"
#include "utils.h"
#include "estruturas.h"
#include "user.h"

// Funções principais do sistema;
void iniciarSistema(NoUsuario **usuarios, NoCertificado **certificados, NoAssinatura **assinaturas);
void menuPrincipal(NoUsuario **usuarios, NoCertificado **certificados);
void menuUsuario();
void carregarDados(NoUsuario **usuarios, NoCertificado **certificados, NoAssinatura **assinaturas);
void carregarUsuarios(NoUsuario **usuarios);
void carregarCertificados(NoCertificado **certificados);
void carregarAssinaturas(NoAssinatura **assinaturas);
void salvarDados();
void logOperacao();

void menuPrincipal(NoUsuario **usuarios, NoCertificado **certificados)
{
    int opcao = -1;

    do
    {
        // system("cls || clear"); // Limpa a tela (Windows/Linux)

        printf("=================================\n");
        printf("    SISTEMA DE CERTIFICADOS      \n");
        printf("=================================\n");
        printf("1. Login\n");
        printf("2. Registar novo utilizador\n");
        printf("3. Sobre o sistema\n");
        printf("0. Sair\n");
        printf("=================================\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            // Chamar função de login
            printf("\nLogin selecionado\n");
            autenticarUsuario(*usuarios, *certificados);
            esperarTecla();
            break;

        case 2:
            // Chamar função de registro
            printf("\nRegistro de novo utilizador\n");
            registrarUsuario(usuarios);
            esperarTecla();
            break;

        case 3:
            // Mostrar informações do sistema
            printf("\nSobre o Sistema:\n");
            printf("Versao 1.0\n");
            printf("Sistema de Gestao de Certificados Digitais\n");
            esperarTecla();
            break;

        case 0:
            printf("\nA sair do sistema...\n");
            break;

        default:
            printf("\nOpcao invalida! Tente novamente.\n");
            esperarTecla();
        }

    } while (opcao != 0);
}

void carregarDados(NoUsuario **usuarios, NoCertificado **certificados, NoAssinatura **assinaturas)
{
    // Carregar dados de usuários, certificados e assinaturas de arquivos
    carregarUsuarios(usuarios);
    carregarCertificados(certificados);
    carregarAssinaturas(assinaturas);
}

void carregarUsuarios(NoUsuario **usuarios)
{
    // Abrir o arquivo binário de usuários
    FILE *file = fopen("ficheiros/dat/users.dat", "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo de usuarios.\n");
        return;
    }

    // Ler os dados do arquivo e preencher a lista de usuários
    Usuario temp;
    while (fread(&temp, sizeof(Usuario), 1, file))
    {
        NoUsuario *novo = (NoUsuario *)malloc(sizeof(NoUsuario));
        novo->dados = temp;
        novo->proximo = *usuarios;
        *usuarios = novo;
    }

    fclose(file);
    printf("Usuários carregados com sucesso.\n");
}
void carregarCertificados(NoCertificado **certificados)
{
    // Abrir o arquivo de texto para leitura
    FILE *file = fopen("ficheiros/text/relatorio_certificados.txt", "r");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo de certificados.\n");
        return;
    }

    // Ler os dados do arquivo e preencher a lista de certificados
    while (!feof(file))
    {
        Certificado temp;
        if (fscanf(file, "%d %99s %99s %10s %10s %19s %255s",
                   &temp.id, temp.nome, temp.email, temp.data_emissao,
                   temp.data_validade, temp.estado, temp.chave_publica) == 7)
        {
            // Criar um novo nó para o certificado
            NoCertificado *novo = (NoCertificado *)malloc(sizeof(NoCertificado));
            if (novo == NULL)
            {
                printf("Erro ao alocar memória para o certificado.\n");
                fclose(file);
                return;
            }

            // Preencher os dados do novo nó
            novo->dados = temp;
            novo->proximo = *certificados;

            // Adicionar o novo nó ao início da lista
            *certificados = novo;
        }
    }

    printf("Certificados carregados com sucesso.\n");

    fclose(file);
}
void carregarAssinaturas(NoAssinatura **assinaturas)
{
    // Abrir o arquivo binário de assinaturas
    FILE *file = fopen("ficheiros/dat/assinaturas.dat", "rb");
    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo de assinaturas.\n");
        return;
    }

    // Ler os dados do arquivo e preencher a lista de assinaturas
    Assinatura temp;
    while (fread(&temp, sizeof(Assinatura), 1, file))
    {
        NoAssinatura *novo = (NoAssinatura *)malloc(sizeof(NoAssinatura));
        novo->dados = temp;
        novo->proximo = *assinaturas;
        *assinaturas = novo;
    }

    fclose(file);
    printf("Assinaturas carregadas com sucesso.\n");
}

void iniciarSistema(NoUsuario **usuarios, NoCertificado **certificados, NoAssinatura **assinaturas)
{
    carregarDadosFicticios();
    carregarDados(usuarios, certificados, assinaturas);
    menuPrincipal(usuarios, certificados);
}

#endif // SISTEMA_H