

#ifndef CERTIFICADOS_H
#define CERTIFICADOS_H

#include "estruturas.h"
#include <string.h>

// Funções de gestão de certificados
void criarCertificado(NoCertificado** certificados, NoUsuario* usuarios);
void destruirCertificado(Certificado* cert);
void listarCertificados(NoCertificado* certificados);
void ordenarCertificadosNome(NoCertificado** certificados);
void ordenarCertificadosData(Certificado* cert);
void renovarCertificado(NoCertificado* certificados);
void revogarCertificado(NoCertificado* certificados);
void exportarCertificadosCsv(NoCertificado* certificados);
void gerarRelatorioCertificados(Certificado* cert);
void alertasExpiracao();


void criarCertificado(NoCertificado** certificados, NoUsuario* usuarios)
{
    Certificado* cert = (Certificado*)malloc(sizeof(Certificado));
    if (cert == NULL) {
        printf("Erro ao alocar memória para o novo certificado.\n");
        return;
    }
    // Solicitar os dados do certificado ao administrador
    printf("Digite o ID do certificado: ");
    scanf("%d", &cert->id);

    printf("Digite o nome do titular do certificado: ");
    scanf(" %[^\n]", cert->nome); // Lê uma string com espaços

    printf("Digite o email do titular do certificado: ");
    scanf(" %[^\n]", cert->email);

    printf("Digite a data de emissão (DD/MM/AAAA): ");
    scanf(" %[^\n]", cert->data_emissao);

    printf("Digite a data de validade (DD/MM/AAAA): ");
    scanf(" %[^\n]", cert->data_validade);

    printf("Digite o estado do certificado (ativo, expirado, revogado): ");
    scanf(" %[^\n]", cert->estado);

    printf("Digite a chave pública do certificado: ");
    scanf(" %[^\n]", cert->chave_publica);

    // Criar um novo nó para o certificado
    NoCertificado* novo = (NoCertificado*)malloc(sizeof(NoCertificado));
    if (novo == NULL) {
        printf("Erro ao alocar memória para o novo certificado.\n");
        return;
    }

    // Preencher os dados do novo nó
    novo->dados = *cert;
    novo->proximo = *certificados;

    // Adicionar o novo nó à lista de certificados
    *certificados = novo;

    // Procurar o usuário pelo nome e atribuir o ID do certificado
    NoUsuario* atual = usuarios;
    int encontrado = 0;
    while (atual != NULL) {
        if (strcmp(atual->dados.username, cert->nome) == 0) {
            atual->dados.id_certificado = cert->id;
            encontrado = 1;
            break;
        }
        atual = atual->proximo;
    }

    if (encontrado) {
        printf("Certificado criado e atribuído ao usuário '%s' com sucesso!\n", cert->nome);
    } else {
        printf("Usuário '%s' não encontrado. Certificado criado, mas não atribuído a nenhum usuário.\n", cert->nome);
    }
}


void listarCertificados(NoCertificado* certificados)
{
    if (certificados == NULL)
    {
        printf("Nenhum certificado encontrado.\n");
        return;
    }

    printf("Lista de Certificados:\n");
    printf("=========================================\n");

    NoCertificado* atual = certificados; // Usar um ponteiro auxiliar para percorrer a lista
    while (atual != NULL)
    {
        printf("ID: %d\n", atual->dados.id);
        printf("Nome: %s\n", atual->dados.nome);
        printf("Email: %s\n", atual->dados.email);
        printf("Data de Emissão: %s\n", atual->dados.data_emissao);
        printf("Data de Validade: %s\n", atual->dados.data_validade);
        printf("Estado: %s\n", atual->dados.estado);
        printf("Chave Pública: %s\n", atual->dados.chave_publica);
        printf("-----------------------------------------\n");

        atual = atual->proximo; // Avançar para o próximo certificado
    }
}


void renovarCertificado(NoCertificado* certificados)
{
    if (certificados == NULL)
    {
        printf("Nenhum certificado encontrado para renovar.\n");
        return;
    }

    int id;
    printf("Digite o ID do certificado que deseja renovar: ");
    scanf("%d", &id);

    NoCertificado* atual = certificados;
    int encontrado = 0;

    while (atual != NULL)
    {
        if (atual->dados.id == id)
        {
            encontrado = 1;

            // Solicitar a nova data de validade
            printf("Digite a nova data de validade (DD/MM/AAAA): ");
            scanf(" %[^\n]", atual->dados.data_validade);

            // Atualizar o estado do certificado para "ativo"
            strcpy(atual->dados.estado, "ativo");

            printf("Certificado com ID %d renovado com sucesso!\n", id);
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Certificado com ID %d não encontrado.\n", id);
    }
}

void revogarCertificado(NoCertificado* certificados)
{
    if (certificados == NULL)
    {
        printf("Nenhum certificado encontrado para revogar.\n");
        return;
    }

    int id;
    printf("Digite o ID do certificado que deseja revogar: ");
    scanf("%d", &id);

    NoCertificado* atual = certificados;
    int encontrado = 0;

    while (atual != NULL)
    {
        if (atual->dados.id == id)
        {
            encontrado = 1;

            // Atualizar o estado do certificado para "revogado"
            strcpy(atual->dados.estado, "revogado");

            printf("Certificado com ID %d foi revogado com sucesso!\n", id);
            break;
        }
        atual = atual->proximo;
    }

    if (!encontrado)
    {
        printf("Certificado com ID %d não encontrado.\n", id);
    }
}

void exportarCertificadosCsv(NoCertificado* certificados)
{
    if (certificados == NULL)
    {
        printf("Nenhum certificado encontrado para exportar.\n");
        return;
    }

    // Abrir o arquivo CSV para escrita
    FILE* file = fopen("ficheiros/csv/certificados.csv", "w");
    if (file == NULL)
    {
        printf("Erro ao criar o arquivo CSV.\n");
        return;
    }

    // Escrever o cabeçalho do CSV
    fprintf(file, "ID,Nome,Email,Data de Emissão,Data de Validade,Estado,Chave Pública\n");

    // Percorrer a lista de certificados e escrever os dados no arquivo
    NoCertificado* atual = certificados;
    while (atual != NULL)
    {
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s\n",
                atual->dados.id,
                atual->dados.nome,
                atual->dados.email,
                atual->dados.data_emissao,
                atual->dados.data_validade,
                atual->dados.estado,
                atual->dados.chave_publica);

        atual = atual->proximo;
    }

    fclose(file);

    printf("Certificados exportados com sucesso para 'ficheiros/certificados.csv'.\n");
}


void ordenarCertificadosNome(NoCertificado** certificados)
{
    if (*certificados == NULL || (*certificados)->proximo == NULL)
    {
        printf("Não há certificados suficientes para ordenar.\n");
        return;
    }

    int trocou;
    NoCertificado* atual;
    NoCertificado* anterior = NULL;

    do
    {
        trocou = 0;
        atual = *certificados;

        while (atual->proximo != anterior)
        {
            if (strcmp(atual->dados.nome, atual->proximo->dados.nome) > 0)
            {
                // Trocar os dados dos nós
                Certificado temp = atual->dados;
                atual->dados = atual->proximo->dados;
                atual->proximo->dados = temp;

                trocou = 1;
            }
            atual = atual->proximo;
        }
        anterior = atual;
    } while (trocou);

    printf("Certificados ordenados por nome com sucesso!\n");
}
#endif // CERTIFICADOS_H