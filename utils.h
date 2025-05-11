#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "certificados.h"
#include "assinaturas.h"
#include "estruturas.h"


void esperarTecla();

void esperarTecla()
{
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();
}

void carregarDadosFicticios();

void carregarDadosFicticios() {
    // Criar dados fictícios de usuários (arquivo binário)
    FILE* file = fopen("ficheiros/dat/users.dat", "wb");
    if (file == NULL) {
        printf("Erro ao criar o arquivo de usuários.\n");
        return;
    }
    Usuario usuarios[] = {
        {"admin", "admin", ADMIN, 0},
        {"user1", "password1", USUARIO, 1},
        {"user2", "password2", USUARIO, 1}
    };
    fwrite(usuarios, sizeof(Usuario), 3, file);
    fclose(file);

    // Criar dados fictícios de certificados (arquivo texto)
    file = fopen("ficheiros/text/relatorio_certificados.txt", "w");
    if (file == NULL) {
        printf("Erro ao criar o arquivo de certificados.\n");
        return;
    }
    fprintf(file, "1 Certificado1 user1@email.com 2025-01-01 2026-01-01 ativo ChavePublica1\n");
    fprintf(file, "2 Certificado2 user2@email.com 2025-02-01 2026-02-01 ativo ChavePublica2\n");
    fclose(file);

    // Criar dados fictícios de assinaturas (arquivo binário)
    file = fopen("ficheiros/dat/assinaturas.dat", "wb");
    if (file == NULL) {
        printf("Erro ao criar o arquivo de assinaturas.\n");
        return;
    }
    Assinatura assinaturas[] = {
        {1, "Documento1", "Hash1", "2025-04-01", 1},
        {2, "Documento2", "Hash2", "2025-04-02", 2}
    };
    fwrite(assinaturas, sizeof(Assinatura), 2, file);
    fclose(file);

    printf("Dados fictícios carregados com sucesso!\n");
}

#endif 