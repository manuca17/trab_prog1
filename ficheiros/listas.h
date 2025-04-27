#ifndef LISTAS_H
#define LISTAS_H

#include "certificados.h"
#include "assinaturas.h"
#include "user.h"

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

#endif // LISTAS_H