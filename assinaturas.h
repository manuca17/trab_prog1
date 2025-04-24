#ifndef ASSINATURAS_H
#define ASSINATURAS_H

typedef struct {
    int id;
    char nome_documento[100];
    char hash_documento[64]; // SHA-256
    char data_assinatura[11];
    int id_certificado;
} Assinatura;

// Funções de gestão de assinaturas
void criarAssinatura(Assinatura* assin);
void destruirAssinatura(Assinatura* assin);
void listarAssinaturas(Assinatura* assin);
void consultarHistorico_assinaturas(Assinatura* assin);
void registrarAssinatura(Assinatura* assin);
void estatisticasAssinaturas(Assinatura* assin);

#endif // ASSINATURAS_H