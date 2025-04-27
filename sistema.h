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
void esperarTecla();


void esperarTecla() {
    printf("Pressione qualquer tecla para continuar...\n");
    getchar();
}


void menuPrincipal() {
    int opcao;
    
    do {
        system("cls || clear"); // Limpa a tela (Windows/Linux)
        
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
        
        switch(opcao) {
            case 1:
                // Chamar função de login
                printf("\nLogin selecionado\n");
                esperarTecla();
                break;
                
            case 2:
                // Chamar função de registro
                printf("\nRegistro de novo utilizador\n");
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
        
    } while(opcao != 0);
}

#endif // SISTEMA_H