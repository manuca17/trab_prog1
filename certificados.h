#ifndef CERTIFICADOS_H
#define CERTIFICADOS_H

typedef struct {
    int id;
    char nome[100];
    char email[100];
    char data_emissao[11]; // formato DD/MM/AAAA
    char data_validade[11];
    char estado[20]; // "ativo", "expirado", "revogado"
    char chave_publica[256];
} Certificado;

// Funções de gestão de certificados
void criarCertificado(Certificado* cert);
void destruirCertificado(Certificado* cert);
void listarCertificados(Certificado* cert);
void ordenarCertificadosNome(Certificado* cert);
void ordenarCertificadosData(Certificado* cert);
void renovarCertificado(Certificado* cert);
void revogarCertificado(Certificado* cert);
void exportarCertificadosCsv(Certificado* cert);
void gerarRelatorioCertificados(Certificado* cert);
void alertasExpiracao();

#endif // CERTIFICADOS_H