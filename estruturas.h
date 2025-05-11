#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

// Certificado
typedef struct {
    int id;
    char nome[100];
    char email[100];
    char data_emissao[11]; // formato DD/MM/AAAA
    char data_validade[11];
    char estado[20]; // "ativo", "expirado", "revogado"
    char chave_publica[256];
} Certificado;

// Assinatura
typedef struct {
    int id;
    char nome_documento[100];
    char hash_documento[64]; // SHA-256
    char data_assinatura[11];
    int id_certificado;
} Assinatura;

// Tipo de usuário
typedef enum {
    ADMIN,
    USUARIO
} TipoUsuario;

// Usuário
typedef struct {
    char username[50];
    char password[50];
    TipoUsuario tipo;
    int id_certificado; // -1 se não tiver
} Usuario;

// Nó para lista de certificados
typedef struct NoCertificado {
    Certificado dados;
    struct NoCertificado* proximo;
} NoCertificado;

// Lista de certificados
typedef struct {
    NoCertificado* primeiro;
    int quantidade;
} ListaCertificados;

// Nó para lista de assinaturas
typedef struct NoAssinatura {
    Assinatura dados;
    struct NoAssinatura* proximo;
} NoAssinatura;

// Lista de assinaturas
typedef struct {
    NoAssinatura* primeiro;
    int quantidade;
} ListaAssinaturas;

// Nó para lista de usuários
typedef struct NoUsuario {
    Usuario dados;
    struct NoUsuario* proximo;
} NoUsuario;

// Lista de usuários
typedef struct {
    NoUsuario* primeiro;
    int quantidade;
} ListaUsuarios;

#endif // ESTRUTURAS_H