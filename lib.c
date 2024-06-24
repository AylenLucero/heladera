#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#define ValoresCuentasAdmin "cuentaAdmin.dat"
#define ValoresCuentasCajero "cuentasCajeros.dat"

TDatosCuentaCajeros datosCuentaCajero;

void menuPrincipal(TDatosCuentaAdmin *datos)
{
    int opPuesto = 0;
    int dni_input;
    do
    {
        printf("BIENVENIDO A LA HELADERIA ICE!!!\n");
        printf("Indique su puesto para continuar\n1)Cajero\n2)Administrador\n3)Salir\n");
        fflush(stdin);
        scanf("%d",&opPuesto);
        switch(opPuesto)
        {
        case 1:
            break;
        case 2:
            if(archivoEstaVacio(ValoresCuentasAdmin)==0)
            {
                printf("Ingrese su dni:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                //si el dni existe redirigimos al login
                if(existe_dni(ValoresCuentasAdmin,dni_input)==1)
                {
                    //login..
                    printf("Dni encontrado, procedemos al login.\n");
                    system("pause");
                    login_admin(ValoresCuentasAdmin,dni_input);
                }
                else
                {
                    //si no existe en la tabla lo llevamos al registro
                    printf("El dni no está registrado en la tabla administadores.\n");
                    system("pause");
                    guardar_admin(ValoresCuentasAdmin, dni_input);
                }
            }
            else
            {
                printf("Ingrese su dni:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                system("pause");
                guardar_admin(ValoresCuentasAdmin,dni_input);
            }


            break;
        default:
            break;
        }
    }
    while(opPuesto!=3);
}
void crearArchivoBinario(char *nombreArchivoBinario)
{
    FILE *archivo = fopen(nombreArchivoBinario, "ab");
    if(archivo == NULL)
    {
        printf("No se pudo crear el arcrivo\n");
    }
    else
    {
        printf("Se creo el archivo correctamente\n");
    }
    fclose(archivo);
}

int archivoEstaVacio(char *nombreArchivo)
{
    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL)
    {
        perror("No se pudo abrir el archivo");
        return 1; // Consideramos vacío si no se puede abrir
    }

    fseek(archivo, 0, SEEK_END);
    long size = ftell(archivo);
    fclose(archivo);

    return size == 0; // Retorna 1 si el archivo está vacío, 0 si no lo está
}

void menuAdmin(TDatosCuentaAdmin *datos)
{
    int op = 0;
    int dni_input;
    do
    {
        printf("Bienvenido al ADMINISTRADOR\n");
        listar_admins();
        printf("Elija una de las opciones:\n1)Agregar nuevo cajero\n2)Agregar nuevo administrador\n3)Revisar stock\n4)Realizar compra\n5)Volver al menu principal\n6)Eliminar admin\n");
        fflush(stdin);
        scanf("%d",&op);
        switch(op)
        {
        case 1:
            if(archivoEstaVacio(ValoresCuentasCajero)==0)
            {
                printf("Ingrese su dni:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                //si el dni existe redirigimos al login
                if(existe_dni(ValoresCuentasAdmin,dni_input)==1)
                {
                    //login..
                    printf("Dni encontrado, procedemos al login.\n");
                    system("pause");
                    login_admin(ValoresCuentasAdmin,dni_input);
                }
                else
                {
                    //si no existe en la tabla lo llevamos al registro
                    printf("El dni no está registrado en la tabla administadores.\n");
                    system("pause");
                    guardar_admin(ValoresCuentasAdmin, dni_input);
                }
            }
            else
            {
                printf("Ingrese su dni:\n");
                fflush(stdin);
                scanf("%d",&dni_input);
                system("pause");
                guardar_admin(ValoresCuentasAdmin,dni_input);
            }
            break;
        case 2:
            printf("Ingrese su dni:\n");
            fflush(stdin);
            scanf("%d",&dni_input);
            system("pause");
            while(existe_dni(ValoresCuentasAdmin,dni_input)==1)
            {
                //login..
                printf("Dni encontrado, ingrese dni que no tenga cuenta\n");
                fflush(stdin);
                scanf("%d",&dni_input);
            }
            guardar_admin(ValoresCuentasAdmin,dni_input);
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            menuPrincipal(&datos);
            break;
        case 6:
            printf("Indique dni a eliminar\n");
            fflush(stdin);
            scanf("%d",&dni_input);
            eliminar_admin(dni_input);
            break;
        default:
            break;
        }
    }
    while (op<1 || op>6);
}

int existeEnArchivo(char *nombreArchivoBinario, int dniBuscar)
{
    FILE *archivo = fopen(nombreArchivoBinario, "rb");
    if (archivo == NULL)
    {
        return 0;
    }

    TDatosCuentaAdmin datos;
    while (fread(&datos, sizeof(TDatosCuentaAdmin), 1, archivo))
    {
        if (datos.dni == dniBuscar)
        {
            fclose(archivo);
            return 1; // DNI encontrado
        }
    }

    fclose(archivo);
    return 0; // DNI no encontrado
}


void guardar_admin(char *nomArchivo, int dni_input)
{
    if(existe_dni(nomArchivo,dni_input)==0)//si el dni no está registrado, procedemos
    {
        TDatosCuentaAdmin admin;
        FILE * archivo;
        archivo=fopen(nomArchivo,"ab");
        if(archivo!=NULL)
        {
            admin.dni = dni_input;

            //levantamos los demás datos solicitandolos por pantalla
            printf("Password \n");
            fflush(stdin);
            gets(admin.contrasena);

            fwrite(&admin, sizeof(admin), 1, archivo);

            if(fclose(archivo)==0)
            {
                printf("Administrador cargado!\n");
                printf("\n");
                return;
            }
            else
            {
                printf("No se pudo cargar el administrador \n");
            }
        }
        else
        {
            printf("No se pudo abrir el archivo. ERROR: %s\n",strerror(errno));
        }
    }
    else
    {
        printf("DNI ya registrado\n");
        login_admin(nomArchivo,dni_input);

    }
}


int existe_dni(char *ValoresCuentasAdmins,int dni_input)
{
    TDatosCuentaAdmin admin;
    FILE * archivo = fopen(ValoresCuentasAdmins,"rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo)) //mientras el puntero tenga para leer..
        {
            if(fread(&admin, sizeof(admin), 1, archivo)==1)
            {
                if (admin.dni==dni_input)
                {
                    fclose(archivo);
                    return 1;//ID encontrado
                }
            }
        }
        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo. ERROR: %s\n",strerror(errno));
    }
    return 0;//ID no encontrado

}

void leerArchivoBinario(char *nombreArchivoBinario, TDatosCuentaAdmin *datos, char *puesto)
{
    system("cls");
    FILE *archivo = fopen(nombreArchivoBinario, "rb");
    int dato;
    if(archivo != NULL)
    {
        int dniBuscar;
        char contrasena[20];
        printf("INICIAR SESION\nPara ingresar a su cuenta de %s, debe:\n", puesto);
        printf("Ingresar DNI: ");
        fflush(stdin);
        scanf("%d",&dniBuscar);
        printf("Ingresar contrasena: ");
        fflush(stdin);
        scanf("%s",&contrasena);
        while (fread(datos, sizeof(TDatosCuentaAdmin), 1, archivo))
        {
            if ((datos->dni == dniBuscar) && (strcmp(contrasena,datos->contrasena)==0))
            {
                fclose(archivo);
                menuAdmin(datos);
                break;
            }
        }

    }
    else
    {
        printf("No se pudo abrir el archivo. ERROR: %s\n",strerror(errno));
    }
}

void login_admin(char *ValoresCuentasAdmins,int dni_admin)
{
    TDatosCuentaAdmin admin;
    char contrasena_input[20];
    FILE *archivo = fopen(ValoresCuentasAdmins, "rb");
    if(archivo!=NULL)
    {
        while (!feof(archivo))//mientras el puntero tenga para leer..
        {

            if(fread(&admin, sizeof(admin), 1, archivo)==1)
            {
                if (admin.dni == dni_admin)//coincide?
                {
                    printf("Ingrese su password:\n");
                    fflush(stdin);
                    gets(contrasena_input);

                    //comparamos la contraseña ingresada con la guardada en ese registro
                    if(strcmp(contrasena_input,admin.contrasena)==0)
                    {
                        //si coincide..
                        printf("Redirigiendo..\n");
                        menuAdmin(&admin);

                    }
                    else
                    {
                        printf("Password incorrecta!\n");
                    }

                }
            }

        }
        fclose(archivo);
    }
    else
    {
        printf("No se pudo abrir el archivo. ERROR: %s\n",strerror(errno));
    }
}

void eliminar_admin(int dni_input)
{
    TDatosCuentaAdmin cuenta;
    char contrasena_input[20];
    FILE *archivo = fopen("cuentaAdmin.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    int encontrado = 0;
    char decision;

    if (!archivo || !temp)
    {
        printf("No se pudo abrir el archivo. ERROR: %s\n", strerror(errno));
        if (archivo) fclose(archivo);
        if (temp) fclose(temp);
        return;
    }

    printf("Esta acción es irreversible. ¿Está seguro de que desea continuar? (S/N): \n");
    scanf(" %c", &decision);
    decision = toupper(decision);

    if (decision == 'S')
    {
        while (fread(&cuenta, sizeof(cuenta), 1, archivo) == 1)
        {
            if (cuenta.dni != dni_input)
            {
                fwrite(&cuenta, sizeof(cuenta), 1, temp);
            }
            else
            {
                printf("Ingrese la contraseña correspondiente a su DNI '%d':\n", cuenta.dni);
                fflush(stdin);
                gets(contrasena_input);  // Consider using fgets instead of gets for safety
                // Remove newline character from input
                printf("La contrasena es:%s\n", cuenta.contrasena);
                if (strcmp(contrasena_input, cuenta.contrasena) == 0)
                {
                    encontrado = 1;
                }
                else
                {
                    printf("Contraseña incorrecta\n");
                    fclose(archivo);
                    fclose(temp);
                    remove("temp.dat"); // Clean up the temp file
                    return;
                }
            }
        }

        fclose(archivo);
        fclose(temp);

        if (encontrado == 1)
        {
            // Retry mechanism for remove
            for (int attempt = 0; attempt < 5; ++attempt)
            {
                if (remove("cuentaAdmin.dat") == 0)
                {
                    break;
                }
                printf("Intento de eliminar '%s' fallido. Reintentando...\n", "cuentaAdmin.dat");
                sleep(1); // Wait for 1 second before retrying
            }

            // Retry mechanism for rename
            for (int attempt = 0; attempt < 5; ++attempt)
            {
                if (rename("temp.dat", "cuentaAdmin.dat") == 0)
                {
                    break;
                }
                printf("Intento de renombrar 'temp.dat' a '%s' fallido. Reintentando...\n", "cuentaAdmin.dat");
                sleep(1); // Wait for 1 second before retrying
            }
        }
        else
        {
            remove("temp.dat");
            printf("Administrador con DNI '%d' no encontrado.\n", dni_input);
        }
    }
    else if (decision == 'N')
    {
        printf("Se canceló la operación.\n");
        fclose(archivo);
        fclose(temp);
        remove("temp.dat"); // Clean up the temp file
    }
}

void listar_admins()
{
    TDatosCuentaAdmin admin;
    FILE *archivo = fopen(ValoresCuentasAdmin, "rb");
    if(!archivo)
    {
        printf("El archivo no se encontro");
    }
    else
    {
        fread(&admin, sizeof(admin),1,archivo);
        while(!feof(archivo))
        {
            printf("Dni:%d, contraseña:%s\n",admin.dni,admin.contrasena);
            fread(&admin, sizeof(admin),1,archivo);
        }
    }
    fclose(archivo);
}

/**********************SECCION CAJEROS*****************************************/

