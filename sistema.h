#ifndef SISTEMA_H
#define SISTEMA_H

#include "certificados.h"
#include "assinaturas.h"
#include "user.h"

// Funções principais do sistema
void iniciarSistema();
void menuPrincipal();
void menuAdministrador();
void menuUsuario();
void carregarDados();
void salvarDados();
void logOperacao();

#endif // SISTEMA_H