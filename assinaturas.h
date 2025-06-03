#ifndef ASSINATURAS_H
#define ASSINATURAS_H
#include "estruturas.h"
#include "utils.h"

// Funções de gestão de assinaturas
void criarAssinatura(NoAssinatura **assin, NoCertificado *certificados);
void destruirAssinatura(NoAssinatura **assin);
void listarAssinaturas(NoAssinatura *assin);
void consultarHistoricoAssinaturas(NoAssinatura *assin, NoCertificado *certificados, Usuario user);

#include <time.h>
// ...existing code...

void criarAssinatura(NoAssinatura **assin, NoCertificado *certificados)
{
    Assinatura assinatura;
    int id_certificado, encontrado = 0;
    printf("Insira o id do certificado associado: ");
    scanf("%d", &id_certificado);

    NoCertificado *atual = certificados;
    while (atual != NULL)
    {
        if (atual->dados.id == id_certificado)
        {
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Certificado com ID %d não encontrado.\n", id_certificado);
        return;
    }

    assinatura.id_certificado = id_certificado;
    printf("Insira o nome do documento: ");
    scanf(" %[^\n]", assinatura.nome_documento);

    // Gerar data atual automaticamente
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    snprintf(assinatura.data_assinatura, sizeof(assinatura.data_assinatura), "%02d/%02d/%04d",
             tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);

    // Gerar hash aleatório para o documento (simulação)
    gerarString64(assinatura.hash_documento);

    // Gerar ID para a assinatura (pode ser incremental ou baseado em tempo, aqui exemplo simples)
    assinatura.id = rand();

    // Inserir no início da lista de assinaturas
    NoAssinatura *novo = (NoAssinatura *)malloc(sizeof(NoAssinatura));
    if (novo == NULL)
    {
        printf("Erro ao alocar memória para nova assinatura.\n");
        return;
    }
    novo->dados = assinatura;
    novo->proximo = *assin;
    *assin = novo;

    printf("Assinatura criada com sucesso!\n");
    printf("Data da assinatura: %s\n", assinatura.data_assinatura);
}

void consultarHistoricoAssinaturas(NoAssinatura *assin, NoCertificado *certificados, Usuario user)
{
    int encontrou = 0;
    printf("\n===== Histórico de Assinaturas do Usuário: %s =====\n", user.username);

    // Percorre a lista de assinaturas
    while (assin != NULL)
    {
        // Procurar o certificado associado à assinatura
        NoCertificado *cert = certificados;
        while (cert != NULL)
        {
            if (cert->dados.id == assin->dados.id_certificado)
            {
                // Verifica se o certificado pertence ao usuário
                if (cert->dados.userId == user.userId)
                {
                    encontrou = 1;
                    printf("ID da Assinatura: %d\n", assin->dados.id);
                    printf("Nome do Documento: %s\n", assin->dados.nome_documento);
                    printf("Hash do Documento: %s\n", assin->dados.hash_documento);
                    printf("Data da Assinatura: %s\n", assin->dados.data_assinatura);
                    printf("-------------------------------\n");
                }
                break; // Certificado encontrado, não precisa continuar procurando
            }
            cert = cert->proximo;
        }
        assin = assin->proximo;
    }

    if (!encontrou)
    {
        printf("Nenhuma assinatura encontrada para este usuário.\n");
    }
}
#endif // ASSINATURAS_H