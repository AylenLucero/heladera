#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#define ValoresCuentasAdmin "cuentaAdmin.dat"

int main()
{
    TDatosCuentaAdmin datos;
    //crearArchivoBinario(ValoresCuentasAdmin);
    menuPrincipal(&datos);

    return 0;
}
