#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#define ValoresCuentasAdmin "cuentaAdmin.dat"

int main()
{
    TDatosCuentaAdminYCajero datos;
    //crearArchivoBinario(ValoresCuentasAdmin);
    menuPrincipal(&datos);

    return 0;
}
