#ifndef ASSINATURAS_H
#define ASSINATURAS_H
#include "estruturas.h"

// Funções de gestão de assinaturas
void criarAssinatura(Assinatura* assin);
void destruirAssinatura(Assinatura* assin);
void listarAssinaturas(Assinatura* assin);
void consultarHistorico_assinaturas(Assinatura* assin);
void registrarAssinatura(Assinatura* assin);
void estatisticasAssinaturas(Assinatura* assin);

#endif // ASSINATURAS_H