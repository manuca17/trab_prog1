#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "certificados.h"
#include "assinaturas.h"
#include "estruturas.h"

#include <stdio.h>

void escreverLog(const char *format, ...);
void atualizarEstadoCertificados(NoCertificado *certificados);
void esperarTecla();
void gerarString64(char *destino);

void esperarTecla()
{
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();
}

void carregarDadosFicticios();


void carregarDadosFicticios()
{
    // Criar dados fictícios de usuários (arquivo binário)
    FILE *file = fopen("ficheiros/dat/users.dat", "wb");
    if (file == NULL)
    {
        printf("Erro ao criar o arquivo de usuários.\n");
        return;
    }
    Usuario usuarios[] = {
        {0, "admin", "admin", ADMIN},
        {1, "user1", "password1", USUARIO},
        {2, "user2", "password2", USUARIO}};
    fwrite(usuarios, sizeof(Usuario), 3, file);
    fclose(file);

    // Criar dados fictícios de certificados (arquivo texto)
    file = fopen("ficheiros/text/relatorio_certificados.txt", "w");
    if (file == NULL)
    {
        printf("Erro ao criar o arquivo de certificados.\n");
        return;
    }
fprintf(file, "1 1 Certificado1 user1@email.com 01/01/2023 01/01/2023 ativo ChavePublica1\n");
fprintf(file, "2 2 Certificado2 user2@email.com 01/01/2025 01/01/2026 ativo ChavePublica2\n");
    fclose(file);

    // Criar dados fictícios de assinaturas (arquivo binário)
    file = fopen("ficheiros/dat/assinaturas.dat", "wb");
    if (file == NULL)
    {
        printf("Erro ao criar o arquivo de assinaturas.\n");
        return;
    }
    Assinatura assinaturas[] = {
        {1, "Documento1", "Hash1", "2025-04-01", 1},
        {2, "Documento2", "Hash2", "2025-04-02", 2}};
    fwrite(assinaturas, sizeof(Assinatura), 2, file);
    fclose(file);

    printf("Dados fictícios carregados com sucesso!\n");
}

// Gera uma string aleatória de 64 caracteres
void gerarString64(char *destino)
{
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    int charsetSize = sizeof(charset) - 1;

    for (int i = 0; i < 64; i++)
    {
        int key = rand() % charsetSize;
        destino[i] = charset[key];
    }
    destino[64] = '\0'; // Termina a string
}

#include <stdarg.h>

void escreverLog(const char *format, ...)
{
    FILE *logFile = fopen("ficheiros/text/log.txt", "a"); // Use "a" para adicionar, não sobrescrever!
    if (logFile == NULL)
    {
        printf("Erro ao abrir o arquivo de log.\n");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char buffer[20];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", t);

    char mensagem[256];
    va_list args;
    va_start(args, format);
    vsnprintf(mensagem, sizeof(mensagem), format, args);
    va_end(args);

    fprintf(logFile, "[%s] -- %s\n", buffer, mensagem);
    fclose(logFile);
}

#include <time.h>
#include <string.h>

void atualizarEstadoCertificados(NoCertificado *certificados)
{
    time_t agora = time(NULL);
    struct tm dataAtual = *localtime(&agora);

    NoCertificado *atual = certificados;
    while (atual != NULL)
    {
        int dia, mes, ano;
        // Espera formato DD/MM/AAAA
        if (sscanf(atual->dados.data_validade, "%d/%d/%d", &dia, &mes, &ano) == 3)
        {
            struct tm validade = {0};
            validade.tm_mday = dia;
            validade.tm_mon = mes - 1;
            validade.tm_year = ano - 1900;

            time_t t_validade = mktime(&validade);

            if (difftime(agora, t_validade) > 0 && strcmp(atual->dados.estado, "expirado") != 0)
            {
                strcpy(atual->dados.estado, "expirado");
                escreverLog("Certificado ID %d expirado automaticamente.", atual->dados.id);
            }
        }
        atual = atual->proximo;
    }
}

#endif