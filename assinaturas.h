#ifndef ASSINATURAS_H
#define ASSINATURAS_H
#include "estruturas.h"
#include "utils.h"

// Funções de gestão de assinaturas
void criarAssinatura(NoAssinatura **assin, NoCertificado *certificados);
void destruirAssinatura(NoAssinatura **assin);
void listarAssinaturas(NoAssinatura *assin);
void consultarHistoricoAssinaturas(NoAssinatura *assin, NoCertificado *certificados, Usuario user);


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

    printf("Insira a data da assinatura (DD/MM/AAAA): ");
    scanf(" %10s", assinatura.data_assinatura);

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
}

void consultarHistoricoAssinaturas(NoAssinatura *assin, NoCertificado *certificados, Usuario user)
{
    int encontrou = 0;
    printf("\n===== Histórico de Assinaturas do Usuário: %s =====\n", user.username);

    // Percorre a lista de assinaturas
    while (assin != NULL) {
        // Verifica se a assinatura foi feita com o certificado do usuário
        if (assin->dados.id_certificado == user.id_certificado) {
            encontrou = 1;
            printf("ID da Assinatura: %d\n", assin->dados.id);
            printf("Nome do Documento: %s\n", assin->dados.nome_documento);
            printf("Hash do Documento: %s\n", assin->dados.hash_documento);
            printf("Data da Assinatura: %s\n", assin->dados.data_assinatura);
            printf("-------------------------------\n");
        }
        assin = assin->proximo;
    }

    if (!encontrou) {
        printf("Nenhuma assinatura encontrada para este usuário.\n");
    }
}
#endif // ASSINATURAS_H