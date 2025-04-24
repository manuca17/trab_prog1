#ifndef USERS_H
#define USERS_H

typedef enum {
    ADMIN,
    USUARIO
} TipoUsuario;

typedef struct {
    char username[50];
    char password[50];
    TipoUsuario tipo;
    int id_certificado; // -1 se não tiver
} Usuario;

// Funções de gestão de usuários
Usuario* autenticarUsuario();
void registrarUsuario();
void listarUsuarios();
void alterarTipo_usuario();
void bloquearUsuario();

#endif // USERS_H