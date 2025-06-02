#include <stdio.h>
#include <stdlib.h>
#include "sistema.h"
#include "estruturas.h"
#include <locale.h>
#include "utils.h"

NoUsuario *usuarios = NULL;
NoCertificado *certificados = NULL;
NoAssinatura *assinaturas = NULL;

int main()
{
    setlocale(LC_ALL, "Portuguese");
    iniciarSistema(&usuarios, &certificados, &assinaturas);
    return 0;
}